#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1100000;

string s;

struct Node {
    int x, y, sz;
    int l, r;
    Node() {
        y = rand();
        l = r = -1;
        sz = 1;
    }
    Node(int a) {
        x = a;
        y = rand();
        l = r = -1;
        sz = 1;
    }
};

Node treap[MAXN];
int counter = 0, root = -1, cnt = 0;

int new_node(int x) {
    treap[counter] = Node(x);
    return counter++;
}

void calc(int t) {
    if (treap[t].l != -1 && treap[t].r != -1) {
        treap[t].sz = treap[treap[t].l].sz + treap[treap[t].r].sz + 1;
    } else if (treap[t].l != -1 && treap[t].r == -1) {
        treap[t].sz = treap[treap[t].l].sz + 1;
    } else if (treap[t].l == -1 && treap[t].r != -1) {
        treap[t].sz = treap[treap[t].r].sz + 1;
    } else if (treap[t].l == -1 && treap[t].r == -1) {
        treap[t].sz = 1;
    }
}

pair<int, int> split(int x, int t) {
    if (t == -1) { return {-1, -1}; }
    if (treap[t].x < x) {
        pair <int, int> tt = split(x, treap[t].r);
        treap[t].r = tt.first;
        calc(t);
        return {t, tt.second};
    } else {
        pair <int, int> tt = split(x, treap[t].l);
        treap[t].l = tt.second;
        calc(t);
        return {tt.first, t};
    }
}

int merge(int t1, int t2) {
    if (t1 == -1) { return t2; }
    if (t2 == -1) { return t1; }
    if (treap[t1].y > treap[t2].y) {
        treap[t1].r = merge(treap[t1].r, t2);
        calc(t1);
        return t1;
    } else {
        treap[t2].l = merge(t1, treap[t2].l);
        calc(t2);
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

int kth(int t, int k) {
    while (k != -1) {
        int s = 0;
        if (treap[t].l != -1)
            s = treap[treap[t].l].sz;
        if (s + 1 == k) {
            return treap[t].x;
        } else if (s + 1 > k) {
            t = treap[t].l;
        } else {
            k = k - s - 1;
            t = treap[t].r;
        }
    }
    return -1;
}

int main() {
    #ifdef HOME
        freopen("input.txt", "rt", stdin);
    #endif
        srand(time(NULL));
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        if (x == 1) {
            add(y);
            cnt++;
        } else if (x == 0) {
            // cout << kth(root, y) << "\n";
            cout << kth(root, cnt - y + 1) << "\n";
        } else {
            remove(y);
            cnt--;
        }
    }
    return 0;
}
