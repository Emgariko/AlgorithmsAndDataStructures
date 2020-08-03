#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 123;
const int MAXL = 17;

int a[MAXN];
int t[MAXN][MAXL];
int ch[MAXN];
int lg[MAXN];

int get_ans(int l, int r) {
	int len = r - l + 1;
	int lgg = lg[(len)];
	return min(t[l][lgg], t[r - (1 << lgg) + 1][lgg]);
}

void build(int n) {
	lg[1] = 0;
	for (int i = 2; i < MAXN; i++) {
		lg[i] = lg[i / 2] + 1;
	}
    for (int j = 0; j < MAXL; j++) {
        for (int i = 0; i < n; i++) {
            if (j == 0) {
                t[i][j] = a[i];
            } else {
                t[i][j] = min(t[i][j - 1], t[min(n - 1, i + (1 << (j - 1)))][j - 1]);
            }
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int n, m, a1;
    cin >> n >> m >> a1;
    a[0] = a1;
    for (int i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    /*cout << log2(10) << "\n";
    cout << log2(1);*/
    build(n);
    int u, v;
    cin >> u >> v;
    int ans = -1;
    int wasu = -1, wasv = -1;
    for (int i = 0; i < m; i++) {
    	wasu = u;
    	wasv = v;
    	bool f = false;
        if (u > v) {
            swap(u, v);
            f = true;
        }
        u--;
        v--;

        ans = get_ans(u, v);
        if (f) {
        	swap(u, v);
        }
        u = ((17 * (u + 1) + 751 + ans + 2 * (i + 1)) % n) + 1;
        v = ((13 * (v + 1) + 593 + ans + 5 * (i + 1)) % n) + 1;
    }
    cout << wasu << ' ' << wasv << ' ' << ans;
    return 0;
}
