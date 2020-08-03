#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300000;
const int INF = 2e9;
int jjj = 0;

string s;

struct Node {
    Node() {}
    int x, y, sz;
    int l, r;
    bool free;
    bool isfree;
    Node(int a) {
        x = a;
        // y = jjj++;
        y = rand();
        l = r = -1;
        sz = 1;
        free = true;
        isfree = true;
    }
};

Node treap[MAXN];
int counter = 0, root = -1, cnt = 0;
int last = 0;

int new_node(int x) {
    treap[counter] = Node(x);
    return counter++;
}

int get_sz(int v) {
    if (v == -1) {
        return 0;
    }
    return treap[v].sz;
}

bool get_free(int v) {
    if (v == -1) {
        return false;
    }
    return treap[v].free;
}

void calc(int v) {
    if (v == -1) {
        return;
    }
    treap[v].sz = get_sz(treap[v].l) + get_sz(treap[v].r) + 1;
    treap[v].free = get_free(treap[v].l) || get_free(treap[v].r) || treap[v].isfree;
}

pair<int, int> split(int x, int t) {
    if (t == -1) { return {-1, -1}; }
    int sz = 1;
    sz = get_sz(treap[t].l);
    if (sz >= x) {
        pair <int, int> tt = split(x, treap[t].l);
        treap[t].l = tt.second;
        calc(t);
        calc(tt.first);
        return {tt.first, t};
    } else {
        pair <int, int> tt = split(x - sz - 1, treap[t].r);
        treap[t].r = tt.first;
        calc(t);
        calc(tt.second);
        return {t, tt.second};
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
        int node = new_node(x);
        root = merge(root, node);
    }
}

void print(int t) {
    if (t == -1 || cnt <= 0) {
        return;
    }
    print(treap[t].l);
    if (cnt > 0) {
        cout << treap[t].x << ' ';
        cnt--;
    }
    print(treap[t].r);
}

void insert(int pos, int val) {
    pair <int, int> t = split(pos - 1, root);
    int tt = t.second;
    int sz = 0;
    while (true) {
        if (get_free(treap[tt].l)) {
            tt = treap[tt].l;
        } else if (treap[tt].isfree) {
            sz += get_sz(treap[tt].l);
            break;
        } else if (get_free(treap[tt].r)) {
            sz += get_sz(treap[tt].l) + 1;
            tt = treap[tt].r;
        }
    }
    pair <int, int> t1 = split(sz, t.second);
    int cursz = pos - 1 + sz + 1;
    last = max(last, cursz);
    pair <int, int> t2 = split(1, t1.second);
    int vv = t2.first;
    if (vv < MAXN) {
        treap[vv].x = val;
        treap[vv].isfree = false;
        treap[vv].free = false;
        vv++;
    }
    calc(t2.second);
    calc(t1.first);
    calc(t2.first);
    calc(t.first);
    root = merge(t.first, merge(t2.first, merge(t1.first, t2.second)));
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    srand(time(NULL));
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n + m + 123; i++) {
        add(0);
    }
    // cout << treap[split(4, root).first].sz;
    last = n;
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        insert(l, i + 1);
    }
    cnt = last;
    cout << cnt << "\n";
    print(root);
    return 0;
}
