#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18 + 228;

vector <vector<pair<int, ll>>> g;
vector <vector<ll>> dp;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("salesman.in", "rt", stdin);
	freopen("salesman.out", "wt", stdout);
#endif
    int n, m;
    cin >> n >> m;
    int k = (1 << n) - 1;
    g.resize(n);
    dp.resize(n, vector<ll>(k + 1, INF));
    for (int i = 0; i < m; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        a--;
        b--;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }
    for (int i = 0; i < n; i++) {
        dp[i][(1 << i)] = 0;
    }
    for (int msk = 0; msk <= k; msk++) {
    	for (int i = 0; i < n; i++) {
            if (((msk >> i) & 1) == 0) { continue; }
            for (int j = 0; j < int(g[i].size()); j++) {
                int v = g[i][j].first;
                ll w = g[i][j].second;
                if (((msk >> v) & 1) == 1) { continue; }
                int nmsk = msk ^ (1 << v);
                dp[v][nmsk] = min(dp[i][msk] + w, dp[v][nmsk]);
            }
        }
    }
    ll ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[i][k]);
    }
    if (ans == INF) { ans = -1; }
    cout << ans;
    return 0;
}
