#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 5e5 + 100;
const int INF = 2e9 + 123;

vector <int> d[MAXN];
int ans;
int p[MAXN][30];
int dp[MAXN][30];
int h[MAXN];

bool used[MAXN];

int n, MAXK;

void dfs(int u, int he, int pp) {
    used[u] = true;
    h[u] = he;
    p[u][0] = pp;
    int nw;
    for (int i = 0; i < int(d[u].size()); i++) {
        nw = d[u][i];
        if (!used[nw]) {
            dfs(nw, he + 1, u);
        }
    }
}

int lca(int u, int v) {
    if (h[u] > h[v]) {
        swap(u, v);
    }
    if (h[v] >= h[u]) {
        for (int k = MAXK; k >= 0; k--) {
            if (h[p[v][k]] >= h[u]) {
                v = p[v][k];
            }
        }
    }
    if (v == u) {
        return v;
    }
    for (int k = MAXK; k >= 0; k--) {
        if (p[v][k] != p[u][k]) {
            v = p[v][k];
            u = p[u][k];
        }
    }
    return p[u][0];
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int nn = -1;
    int n;
    while (cin >> n) {
        if (n == 0) { break; }
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            d[b].push_back(a);
            d[a].push_back(b);
        }
        p[1][0] = 1;
        dfs(1, 0, -1);
        int m;
        cin >> m;
        int rooot = 1;
        int root = 1;
        p[root][0] = root;
        MAXK = 22;
        nn = n;
        for (int k = 1; k <= MAXK ; k++) {
            for (int i = 1; i <= nn; i++) {
                p[i][k] = p[p[i][k - 1]][k - 1];
                dp[i][k] = min(dp[p[i][k - 1]][k - 1], dp[i][k - 1]);
            }
        }
        for (int i = 0; i < m; i++) {
            char c;
            cin >> c;
            if (c == '?') {
                int a, b;
                cin >> a >> b;
                int t1 = lca(a, b), t2 = lca(rooot, b), t3 = lca(rooot, a);
                int hhh = max(h[t1], max(h[t2], h[t3]));
                if (hhh == h[t1]) {
                    cout << t1 << "\n";
                } else if (hhh == h[t2]) {
                    cout << t2 << "\n";
                } else if (hhh == h[t3]) {
                    cout << t3 << "\n";
                }
            } else {
                int u;
                cin >> u;
                rooot = u;
            }
        }
        for (int i = 1; i < n + 1; i++) {
            d[i].clear();
            h[i] = 0;
            used[i] = false;
            p[i][0] = -1;
        }
    }
    return 0;
}
