#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector <vector<ll>> dp;
vector <vector<pair<int, ll>>> g;

void dfs(int u, int p) {
    if (int(g.size()) == 1) {
        dp[u][0] = 0;
        dp[u][1] = 0;
        dp[u][2] = 0;
    }
    for (int i = 0; i < int(g[u].size()); i++) {
        int v = g[u][i].first;
        if (v == p) { continue; }
        dfs(v, u);
    }
    dp[u][0] = 0;
    ll sum = 0;
    for (int i = 0; i < int(g[u].size()); i++) {
        int v = g[u][i].first;
        if (p == v) { continue; }
        dp[u][0] += dp[v][2];
        sum += dp[v][2];
    }
    for (int i = 0; i < int(g[u].size()); i++) {
        int v = g[u][i].first;
        if (p == v) { continue; }
        dp[u][1] = max(dp[u][1], dp[v][0] + g[u][i].second + sum - dp[v][2]);
    }
    dp[u][2] = max(dp[u][1], dp[u][0]);
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("matching.in", "rt", stdin);
	freopen("matching.out", "wt", stdout);
#endif
    int n;
    cin >> n;
    g.resize(n);
    dp.resize(n, vector<ll>(3, 0));
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        ll z;
        cin >> x >> y >> z;
        x--;
        y--;
        g[x].push_back({y, z});
        g[y].push_back({x, z});
    }
    dfs(0, -1);
    cout << dp[0][2];
    return 0;
}
