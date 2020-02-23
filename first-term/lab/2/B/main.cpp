#include <bits/stdc++.h>

using namespace std;

vector <int> d;

int left_search(vector <int> &a, int x) {
	int l = -1, r = int(a.size()) - 1, m;
	while (r - l > 1) {
		m = (l + r) / 2;
		if (a[m] >= x) {
			r = m;
		} else {
			l = m;
		}
	}
	if (a[r] != x) {
		return -1;
	} else {
		return r;
	}
}

int right_search(vector <int> &a, int x) {
	int l = 0, r = int(a.size()), m;
	while (r - l > 1) {
		m = (l + r) / 2;
		if (a[m] > x) {
			r = m;
		} else {
			l = m;
		}
	}
	if (a[l] != x) {
		return -1;
	} else {
		return l;
	}
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif
	int n;
	cin >> n;
	d.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> d[i];
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		int l = left_search(d, x);
		int r = right_search(d, x);
		if (l != -1) {
			l++;
		}
		if (r != -1) {
			r++;
		}
		cout << l << ' ' << r << "\n";
	}
	return 0;
}
