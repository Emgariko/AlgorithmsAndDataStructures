#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1100000;

string s;

struct Node {
	int x, y;
	int l, r;
	Node() {
		y = rand();
		l = r = -1;
	}
	Node(int a) {
		x = a;
		y = rand();
		l = r = -1;
	}
};

Node treap[MAXN];
int counter = 0, root = -1, count = 0;

int new_node(int x) {
	treap[counter] = Node(x);
	return counter++;
}

pair<int, int> split(int x, int t) {
	if (t == -1) { return {-1, -1}; }
	if (treap[t].x < x) {
		pair <int, int> tt = split(x, treap[t].r);
		treap[t].r = tt.first;
		return {t, tt.second};
	} else {
		pair <int, int> tt = split(x, treap[t].l);
		treap[t].l = tt.second;
		return {tt.first, t};
	}
}

int merge(int t1, int t2) {
	if (t1 == -1) { return t2; }
	if (t2 == -1) { return t1; }
	if (treap[t1].y > treap[t2].y) {
		treap[t1].r = merge(treap[t1].r, t2);
		return t1;
	} else {
		treap[t2].l = merge(t1, treap[t2].l);
		return t2;
	}
}

void add(int x) {
    if (counter == 0) {
        root = counter;
        new_node(x);
    } else {
        pair<int, int> t = split(x, root);
        int node = new_node(x);
        root = merge(merge(t.first, node), t.second);
    }
}

void remove(int x) {
    pair <int, int> t = split(x, root);
    pair <int, int> tt = split(x + 1, t.second);
    root = merge(t.first, tt.second);
}

bool find(int t, int x) {
    while (t != -1) {
        if (treap[t].x == x) { return true; }
        if (treap[t].x > x) {
            t = treap[t].l;
        } else {
            t = treap[t].r;
        }
    }
    return false;
}

int next(int x) {
    pair <int, int> tt = split(x + 1, root);
    int t = tt.second;
    int val = -1e9 - 1;
    while (t != -1) {
        val = treap[t].x;
        t = treap[t].l;
    }
    root = merge(tt.first, tt.second);
    return val;
}

int prev(int x) {
    pair <int, int> tt = split(x, root);
    int t = tt.first;
    int val = -1e9 - 1;
    while (t != -1) {
        val = treap[t].x;
        t = treap[t].r;
    }
    root = merge(tt.first, tt.second);
    return val;
}

int main() {
	#ifdef HOME
		freopen("input.txt", "rt", stdin);
    #endif
		srand(time(NULL));
	int x;
	while (cin >> s) {
		cin >> x;
		if (s == "insert") {
            if (find(root, x)) {
                continue;
            }
			add(x);
		} else if (s == "exists") {
			if (find(root, x)) {
				cout << "true\n";
			} else {
				cout << "false\n";
			}
		} else if (s == "delete") {
            if (!find(root, x)) {
                continue;
            }
		    remove(x);
		} else if (s == "next") {
		    int res = next(x);
		    if (res != -1e9 - 1) {
                cout << res << "\n";
            } else {
		        cout << "none\n";
		    }
		} else if (s == "prev") {
            int res = prev(x);
            if (res != -1e9 - 1) {
                cout << res<< "\n";
            } else {
                cout << "none\n";
            }
		}
	}
	return 0;
}
