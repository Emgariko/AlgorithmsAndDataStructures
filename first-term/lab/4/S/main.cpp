#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 999999937;

struct matrix {
    int n, m;
    vector <vector<ll>> d;
    matrix() {
        n = 5;
        m = 5;
        d.resize(5, vector<ll>(5, 0));
    }
    matrix(int a, int b, vector<vector<ll>> c) {
        n = a;
        m = b;
        d = c;
    }
    matrix operator * (const matrix b) {
        matrix a = *this;
        matrix c = matrix();
        for (int i = 0; i < a.n; i++) {
            for (int j = 0; j < b.m; j++) {
                for (int k = 0; k < a.n; k++) {
                    c.d[i][j] += a.d[i][k] * b.d[k][j] % MOD;
                    c.d[i][j] %= MOD;
                }
            }
        }
        return c;
    }
};

matrix aa = matrix(5, 5, {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1},
                          {1, 1, 1, 0, 0}, {1, 1, 1, 1, 1}, {1, 1, 1, 0, 0}});
matrix bb, c = matrix();

matrix bin_s(matrix a, ll b) {
    if (b == 1) {
        return a;
    }
    if (b % 2 == 0) {
        c = bin_s(a, b / 2);
        return c * c;
    } else {
        c = bin_s(a, b - 1);
        return a * c;
    }
}

ll solve(ll x) {
    bb = bin_s(aa, x);
    return (bb.d[0][0] + bb.d[0][1] + bb.d[0][2] + bb.d[0][3] + bb.d[0][4]) % MOD;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("sequences.in", "rt", stdin);
	freopen("sequences.out", "wt", stdout);
#endif
    ll x;
    while (cin >> x) {
        if (x == 0) break;
        cout << solve(x) << "\n";
    }
    return 0;
}
