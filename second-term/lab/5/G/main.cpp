#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1100000;
const ll INF = 2e18;

string s;

struct Node {
    ll x, y;
    int sz;
    int l, r;
    ll sum;
    Node() {
        y = rand();
        l = r = -1;
        sz = 1;
        sum = 0;
    }
    Node(ll a) {
        x = a;
        y = rand();
        l = r = -1;
        sz = 1;
        sum = 1ll * a;
    }
};

Node treap[MAXN];
int counter = 0, root = -1, cnt = 0;

int new_node(ll x) {
    treap[counter] = Node(x);
    return counter++;
}

void calc(int t) {
    if (t == -1) {
        return;
    }
    if (treap[t].l != -1 && treap[t].r != -1) {
        treap[t].sz = treap[treap[t].l].sz + treap[treap[t].r].sz + 1;
        treap[t].sum = treap[treap[t].l].sum + treap[treap[t].r].sum + treap[t].x;
    } else if (treap[t].l != -1 && treap[t].r == -1) {
        treap[t].sz = treap[treap[t].l].sz + 1;
        treap[t].sum = treap[treap[t].l].sum + treap[t].x;
    } else if (treap[t].l == -1 && treap[t].r != -1) {
        treap[t].sz = treap[treap[t].r].sz + 1;
        treap[t].sum = treap[treap[t].r].sum + treap[t].x;
    } else if (treap[t].l == -1 && treap[t].r == -1) {
        treap[t].sz = 1;
        treap[t].sum = treap[t].x;
    }
}

int get_sz(int t) {
    if (t == -1) {
        return 0;
    } else {
        return treap[t].sz;
    }
}

pair<int, int> split(ll x, int t) {
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

void add(ll x) {
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

bool find(int t, ll x) {
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

void print(int t) {
    if (t == -1) {
        return;
    }
    print(treap[t].l);
    cout << treap[t].x << ' ';
    print(treap[t].r);
}

void shift(int l, int r) {
    pair<int, int> t = split(r + 1, root);
    pair<int, int> tt = split(l, t.first);
    root = merge(tt.second, merge(tt.first, t.second));
}

ll get_sum(ll l, ll r) {
    pair <int, int> t = split(r + 1ll, root);
    pair <int, int> tt = split(l, t.first);
    ll ans = treap[tt.second].sum;
    root = merge(merge(tt.first, tt.second), t.second);
    return ans;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    srand(time(NULL));
    int n;
    cin >> n;
    ll p = 0;
    for (int i = 0; i < n; i++) {
        char x;
        cin >> x;
        if (x == '+') {
            ll y;
            cin >> y;
            y += p;
            y %= ll(1e9);
            if (find(root, y)) {
                p = 0;
                continue;
            }
            add(y);
            p = 0;
        } else {
            ll y, z;
            cin >> y >> z;
            p = get_sum(y, z);
            cout << p << "\n";
        }
    }
    return 0;
}
