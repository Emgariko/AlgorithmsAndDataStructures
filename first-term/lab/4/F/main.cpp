#include <bits/stdc++.h>

using namespace std;

string a, b;
vector <vector<bool>> dp;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    cin >> a >> b;
    if (a == "*") {
        cout << "YES";
        return 0;
    }
    int n, m;
    n = a.length();
    m = b.length();
    dp.resize(n + 10, vector<bool>(m + 10, false));
    a = "%%%%%" + a;
    b = "%%%%%" + b;
    n++;
    m++;
    dp[0][0] = 1;
    for (int i = 1; i <= m + 4; i++) {
        //  if (i == 1) { dp[0][i] = 1; }
        for (int j = 1; j <= n + 4; j++) {
            //  cout << i << ' ' << j << " : ";
            if (a[j] != '*' && a[j] != '?') {
            //      cout << 1;
                dp[j][i] = dp[j - 1][i - 1] && (a[j] == b[i] ? true : false);
            } else if (a[j] == '*') {
                dp[j][i] = min(dp[j - 1][i] + dp[j][i - 1], 1);
            //      cout << 2;
            } else if (a[j] == '?') {
                dp[j][i] = dp[j - 1][i - 1];
           //        cout << 3;
            }
            //  cout << endl;
        }
    }
/*
    for (int i = 0; i < m; i++) {
    	for (int j = 0; j < n; j++)
    		cout << dp[j][i] << ' ';
    	cout << endl;
    }*/
    /*cout << m - 1 << ' ' << n - 1 << endl;*/
    if (dp[n + 4][m + 4] == 1) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
