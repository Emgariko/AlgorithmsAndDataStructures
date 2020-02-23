#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

vector <vector<ll>> dp;
vector <pair<ll, ll>> a;
vector <vector<pair<int, int>>> p;

ll prod(int l, int r) {
    return a[l].first * a[l].second * a[r].second;
}

ll getval(int l, int k, int r) {
    return a[l].first * a[k].second * a[r].second;
}

string get(int l, int r) {
    if (l == r) {
        return "A";
    } else {
    	// cout << l << ' ' << r << endl;
        int k = p[l][r].first;
        return "(" + get(l, k) + get(k + 1, r) + ")";
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("matrix.in", "rt", stdin);
	freopen("matrix.out", "wt", stdout);
#endif
    int n;
    cin >> n;
    a.resize(n);
    p.resize(n, vector<pair<int, int>>(n, {-1, -1}));
    dp.resize(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        dp[i][i] = 0;
        p[i][i] = {i, i};
    }
    for (int i = 0; i < n - 1; i++) {
        dp[i][i + 1] = prod(i, i + 1);
        p[i][i + 1] = {i, i};
    }
    for (int len = 3; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            for (int k = l; k < r; k++) {
                dp[l][r] = min(dp[l][k] + dp[k + 1][r] + getval(l, k, r), dp[l][r]);
                if (dp[l][r] == dp[l][k] + dp[k + 1][r] + getval(l, k, r)) {
                    p[l][r] = {k, k + 1};
                }
            }
            dp[l][r] = min(dp[l][r], dp[r][r] + dp[l][r - 1] + getval(l, r - 1, r));
        	if (dp[l][r] == dp[r][r] + dp[l][r - 1] + getval(l, r - 1, r)) {
                p[l][r] = {r - 1, r};
            }
        }
    }
    #ifdef HOME
    	for (int i = 0; i < n; i++) {
    		for (int j = 0; j < n; j++) {
    			cout << dp[i][j] << ' ';
    		}
    		cout << "\n";
    	}
    #endif
    // cout << "\n" << get(0, n - 1);
    cout << get(0, n - 1);
    return 0;
}
