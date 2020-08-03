#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1100000;

string s;

struct Node {
    int x, y;
    int l, r;
    int id;
    Node() {
        y = rand();
        l = r = -1;
    }
    Node(int a) {
        x = a;
        y = rand();
        l = r = -1;
    }
    Node(int a, int b) {
        x = a;
        y = b;
        l = r = -1;
    }
    Node(int a, int b, int i) {
        x = a;
        y = b;
        l = r = -1;
        id = i;
    }
};

Node treap[MAXN];
int counter = 0, count = 0;

int new_node(int x, int y, int id) {
    treap[counter] = Node(x, y, id);
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
    if (treap[t1].y < treap[t2].y) {
        treap[t1].r = merge(treap[t1].r, t2);
        return t1;
    } else {
        treap[t2].l = merge(t1, treap[t2].l);
        return t2;
    }
}

/* void add(int x) {
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
} */

bool find(int t, int x) {
    while (t != -1) {
        if (treap[t].x == x) { return true; }
        if (treap[t].x < x) {
            t = treap[t].l;
        } else {
            t = treap[t].r;
        }
    }
    return false;
}

/* int next(int x) {
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
} */

deque <int> q;
vector <pair<int, pair<int, int>>> v;
vector <pair<int, int>> d;
vector <int> p;

void print(int v, int from) {
    if (v == -1) {
        return;
    }
    // cout << "Node = (" << treap[v].x << ' ' << treap[v].y << ")";
    // cout << "\nch: ";
    if (treap[v].l != -1) {
        // p[treap[treap[v].l].id] = treap[from].id;
        d[treap[v].id].first = treap[treap[v].l].id;
        // cout << "(" << treap[treap[v].l].x << ' ' << treap[treap[v].l].y << ")";
    } else {
        // cout << "-1 ";
    }
    if (from != -1)
        p[treap[v].id] = treap[from].id;
    if (treap[v].r != -1) {
        // p[treap[treap[v].r].id] = treap[from].id;
        d[treap[v].id].second = treap[treap[v].r].id;
        // cout << "(" << treap[treap[v].r].x << ' ' << treap[treap[v].r].y << ")";
    } else {
        // cout << "-1";
    }
    // cout << "\n";
    print(treap[v].l, v);
    print(treap[v].r, v);
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
    // freopen("output.txt", "wt", stdout);
#endif
    srand(time(NULL));
    int n;
    cin >> n;
    d.resize(n);
    p.resize(n);
    v.resize(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        p[i] = -1;
        d[i] = {-1, -1};
        v[i] = {a, {b, i}};
    }
    sort(v.begin(), v.end());
    //  reverse(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        int a = v[i].first;
        int b = v[i].second.first;
        int id = v[i].second.second;
        q.push_back(new_node(a, b, id));
    }
    int root = -1;
    while (q.size() > 1) {
        /* for (auto i : q) {
            print(i, -1);
            cout << "\n\n";
        }
        cout << "_____________________\n"; */
        root = q.front();
        deque <int> q1;
        while (q.size() > 0) {
            int t1 = q.front();
            q.pop_front();
            if (q.empty()) {
                q1.push_back(t1);
                break;
            }
            int t2 = q.front();
            q.pop_front();
            q1.push_back(merge(t1, t2));
        }
        q.swap(q1);
    }
    root = q.front();
    q.pop_front();
    print(root, -1);
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        cout << p[i] + 1 << ' ' << d[i].first + 1 << ' ' << d[i].second + 1 << "\n";
    }
    return 0;
}
