#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 1100;
const int MAXS = 11000;

int dp[MAXN][MAXS];

int c[MAXN];
int ms[MAXN];

bool inans[MAXN];

int main() {
    #ifdef HOME
        freopen("input.txt", "rt", stdin);
    #else
      	freopen("knapsack.in", "rt", stdin);
        freopen("knapsack.out", "wt", stdout);
    #endif
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> ms[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - ms[i - 1] >= 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - ms[i - 1]] + c[i - 1]);
            }
        }
    }
    int i = n;
    int j = m;
    while (dp[i][j] != 0) {
        if (dp[i - 1][j] == dp[i][j]) {
            i--;
        } else {
            inans[i] = 1;
            i--;
            j -= ms[i];
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (inans[i]) { cnt++; }
    }
    cout << cnt << "\n";
    for (int i = 0; i <= n; i++) {
    	if (inans[i]) { cout << i << ' '; }
    }
    return 0;
}
