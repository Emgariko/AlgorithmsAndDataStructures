#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector <vector <pair<int, int>>> d;
vector <bool> a;
vector <bool> buf;

void gen(int l) {
	if (l == n) {
		for (int i = 0; i < n; i++) {
			buf[i] = a[i];
		}
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < int(d[i].size()); j++) {
				int l = d[i][j].first - 1;
				int r = d[i][j].second - 1;
				int x = min(l, r), y = max(l, r);
				if (buf[x] > buf[y]) {
					swap(buf[x], buf[y]);
				}
			}
		}
		for (int i = 0; i < n - 1; i++) {
			if (buf[i] > buf[i + 1]) {
				cout << "No";
				exit(0);
			}
		}
	} else {
		a[l] = 0;
		gen(l + 1);
		a[l] = 1;
		gen(l + 1);
	}
}

int main() {
	cin >> n >> m >> k;
	d.resize(k);
	a.resize(n);
	buf.resize(n);
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		for (int j = 0; j < x; j++) {
			int l, r;
			cin >> l >> r;
			d[i].push_back({l, r});
		}
	}
	gen(0);
	cout << "Yes";
	return 0;
}
