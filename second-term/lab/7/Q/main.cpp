#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 123;
const int MAXT = 4 * MAXN;
const ll INF = 2e18 + 123;

vector <vector<int>> g;
int p[MAXN];
int cnum[MAXN];  //  chain_number for all vertices
int num[MAXN];   //  number of vertex
int head[MAXN];
int tail[MAXN];
int h[MAXN];
int sz[MAXN];
int nxt[MAXN];
bool used[MAXN];
int counter = 0;
int chains = 0;
ll t[MAXT];
ll pls[MAXN];
int n;

bool check(int v) {
    return v < MAXT;
}

void tree_add(int v, int tl, int tr, int l, ll value) {
    if (tl == tr) {
        t[v] += value;
    } else {
        int tm = (tl + tr) / 2;
        if (l <= tm) {
            tree_add(2 * v + 1, tl, tm, l, value);
        } else {
            tree_add(2 * v + 2, tm + 1, tr, l, value);
        }
        t[v] = max(t[2 * v + 1], t[2 * v + 2]);
    }
}

ll tree_get(int v, int tl, int tr, int l, int r) {
    if (l > r) { return 0; }
    if (tl == l && tr == r) {
        return t[v];
    } else {
        int tm = (tl + tr) / 2;
        ll ans = tree_get(2 * v + 1, tl, tm, l, min(tm, r));
        ans = max(ans, tree_get(2 * v + 2, tm + 1, tr, max(l, tm + 1), r));
        return ans;
    }
}

void dfs(int u, int he) {
    sz[u] = 1;
    used[u] = true;
    h[u] = he;
    for (int i = 0; i < int(g[u].size()); i++) {
        int v = g[u][i];
        if (used[v]) { continue; }
        if (nxt[u] == -1) {
            nxt[u] = v;
        }
        p[v] = u;
        dfs(v, he + 1);
        sz[u] += sz[v];
        if (sz[nxt[u]] < sz[v]) {
            nxt[u] = v;
        }
    }
}

void hld(int u, int par) {
    cnum[u] = chains;
    num[u] = counter++;
    if (head[chains] == -1) {
        head[chains] = u;
    }
    if (nxt[u] != -1) {
        hld(nxt[u], u);
    } else {
        tail[chains] = u;
    }
    for (int i = 0; i < int(g[u].size()); i++) {
        int v = g[u][i];
        if (v == par || v == nxt[u]) { continue; }
        chains++;
        hld(v, u);
    }
}

void add(int u, ll d) {
    int l = num[u];
    tree_add(0, 0, n - 1, l, d);
    pls[cnum[u]] = tree_get(0, 0, n - 1, head[cnum[u]], tail[cnum[u]]);
}

ll get(int u, int v) {
    ll res = 0;
    while (true) {
        if (cnum[u] == cnum[v]) { break; }
        if ((h[head[cnum[u]]] < h[head[cnum[v]]])) { swap(u, v); }  //  I :(u > v)
        if (tail[cnum[u]] == u) {
            res = max(tree_get(0, 0, n - 1, num[head[cnum[u]]], num[u]), res);
        } else {
            res = max(res, tree_get(0, 0, n - 1, num[head[cnum[u]]], num[u]));
        }
        u = p[head[cnum[u]]];
    }
    int l = min(num[u], num[v]);
    int r = max(num[u], num[v]);
    res = max(res, tree_get(0, 0, n - 1, l, r));
    return res;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    g.resize(n);
    memset(nxt, -1, sizeof(int) * MAXN);
    memset(head, -1, sizeof(int) * MAXN);
    for (int i = 0; i < MAXN; i++) {
        pls[i] = 0;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    p[0] = 0;
    dfs(0, 0);
    hld(0, -1);
#ifdef HOME
    for (int i = 0; i < n; i++) {
        cout << "U = " << i << " : " << "sz = " << sz[i] <<
        ", " << "next = " << nxt[i] << ", chain = " << cnum[i] <<
         ", number = " << num[i] << "\n";
    }
#endif
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char chr;
        cin >> chr;
        if (chr == 'I') {
            ll v;
            int u;
            cin >> u >> v;
            u--;
            add(u, v);
        } else if (chr == 'G') {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            ll resssss = get(u, v);
            cout << resssss << "\n";
        }
    }
    return 0;
}
