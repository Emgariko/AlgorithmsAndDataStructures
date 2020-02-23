#include <bits/stdc++.h>

using namespace std;

string a, b;
vector <vector<int>> dp;

int main() {
	#ifdef HOME
		freopen("input.txt", "rt", stdin);
	#else
		freopen("levenshtein.in", "rt", stdin);
		freopen("levenshtein.out", "wt", stdout);
	#endif
	cin >> a >> b;
	int n, m;
	n = a.length();
	m = b.length();
	dp.resize(n + 1, vector<int>(m + 1, 0));
	dp[0][0] = 0;
	for (int i = 0; i <= n; i++) {
		dp[i][0] = i;
	}
	for (int j = 0; j <= m; j++) {
		dp[0][j] = j;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = min(dp[i][j - 1] + 1,
				min(dp[i - 1][j - 1] + ((a[i - 1] == b[j - 1]) ? 0 : 1), dp[i - 1][j] + 1));
		}
	}
	cout << dp[n][m];
	return 0;
}
