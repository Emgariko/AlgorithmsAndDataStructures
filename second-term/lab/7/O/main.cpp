#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 2e5 + 100;
const int INF = 2e9 + 123;

vector <int> d[MAXN];
int ans;
int p[MAXN][150];
int dp[MAXN][150];
int h[MAXN];

bool used[MAXN];

int n, MAXK;

void dfs(int u, int he) {
    used[u] = 1;
    h[u] = he;
    int nw;
    for (int i = 0; i < int(d[u].size()); i++) {
        nw = d[u][i];
        if (!used[nw]) {
            dfs(nw, he + 1);
        }
    }
}

int lca(int u, int v) {
    ans = INF;
    if (h[u] > h[v]) {
        swap(u, v);
    }
    for (int k = MAXK; k > -1; k--) {
        if (h[v] - h[u] >= 1 << k) {
            ans = min(ans, dp[v][k]);
            v = p[v][k];
        }
    }
    if (v == u) {
        return ans;
    } else {
        for (int k = MAXK; k >= 0; k--) {
            if (p[v][k] != p[u][k]) {
                ans = min(ans, min(dp[v][k], dp[u][k]));
                v = p[v][k];
                u = p[u][k];
            }
        }
        ans = min(ans, min(dp[v][0], dp[u][0]));
        return ans;
    }
}

int main() {
    #ifdef HOME
        freopen("input.txt", "rt", stdin);
    #endif
    int n, a, b;
    cin >> n;
    int root;
    for (int i = 1; i < n; i++) {
        cin >> a >> b;
        p[i + 1][0] = a;
        d[i + 1].push_back(a);
        d[a].push_back(i + 1);
        dp[i + 1][0] = b;
    }
    root = 1;
    p[root][0] = root;
    dfs(root, 0);
    MAXK = 22;
    for (int k = 1; k <= MAXK ; k++) {
        for (int i = 1; i <= n; i++) {
            p[i][k] = p[p[i][k - 1]][k - 1];
            dp[i][k] = min(dp[p[i][k - 1]][k - 1], dp[i][k - 1]);
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        cout << lca(a, b) << endl;
    }
    return 0;
}
