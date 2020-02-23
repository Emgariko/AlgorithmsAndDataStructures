#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1e9;

vector <ll> d;
vector <vector<ll>> dp;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int n;
    cin >> n;
    dp.resize(n, vector<ll>(n, 0));
    d.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
        if (d[i] == d[i + 1]) {
            dp[i][i + 1] = 3;
        } else {
            dp[i][i + 1] = 2;
        }
    }
    for (int len = 3; len <= n; len++) {
        for (int l = 0; l < n; l++) {
            if (l + len - 1 >= n) { break; }
            int r = l + len - 1;
            if (d[l] == d[r]) {
                dp[l][r] = ((dp[l + 1][r] % MOD + dp[l][r - 1] % MOD)
                	% MOD + 1) % MOD;
            } else {
                dp[l][r] = (dp[l + 1][r] % MOD + dp[l][r - 1] % MOD-
                           (dp[l + 1][r - 1] % MOD) + MOD) % MOD;
            }
        }
    }
    /*  for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << "\n";
    }   */
    cout << dp[0][n - 1] % MOD;
    return 0;
}
