#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAXN = 25;
const int MAXV = (1 << 22) + 123;

int mn[MAXN], mx[MAXN], sum[MAXV], c[MAXN], p[MAXV];
bool valid[MAXV];
vector <int> res;

bool check(int msk, int index) {
	return ((msk >> index) & 1) != 0;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("meetings.in", "rt", stdin);
	freopen("meetings.out", "wt", stdout);
#endif
	int n, k;
	cin >> n >> k;
	int R = (1 << n), ans_count = 0, ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> mn[i] >> mx[i] >> c[i];
	}
	sum[0] = 0;
	for (int msk = 1; msk < R; msk++) {
		for (int j = 0; j < n; j++) {
			if (check(msk, j)) {
				sum[msk] += c[j];
			}
		}
	}
	valid[0] = true;
	for (int msk = 0; msk < R; msk++) {
		if (!valid[msk]) { continue; }
		for (int j = 0; j < n; j++) {
			if (check(msk, j)) { continue; }
			if (k + sum[msk] > mx[j] || k + sum[msk] < mn[j]) { continue; }
			valid[msk ^ (1 << j)] = true;
			p[msk ^ (1 << j)] = j;
		}
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (check(msk, i)) { cnt++; }
		}
		if (cnt > ans_count) {
			ans = msk;
			ans_count = cnt;
		}
	}
	for (int i = ans_count - 1; i >= 0; i--) {
		res.push_back(p[ans]);
		ans ^= (1 << p[ans]);
	}
	reverse(res.begin(), res.end());
	cout << int(res.size()) << "\n";
	for (int i = 0; i < int(res.size()); i++) {
		cout << res[i] + 1 << ' ';
	}
    return 0;
}
