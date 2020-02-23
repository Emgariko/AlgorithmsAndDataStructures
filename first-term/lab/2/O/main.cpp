#include <bits/stdc++.h>

using namespace std;

vector <int> a;
vector <pair<int, int>> d;

bool check_sorted(vector <int> &a) {
	for (int i = 0; i < int(a.size()) - 1; i++) {
		if (a[i] > a[i + 1]) {
			return false;
		}
	}
	return true;
}

bool solve() {
	int n;
	cin >> n;
	if (n == 0)
		return false;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (check_sorted(a)) {
		cout << -1 << endl;
		a.clear();
		d.clear();
		return true;
	}
	int first = -1, cnt = 0;
	for (int i = 0; i < n; i++) {
		cnt += a[i];
		if (a[i] == 1 && first == -1) {
			first = i;
		}
	}
	for (int i = 0; i < n; i++) {
		if (first != i && a[i] == 1) {
			d.push_back({first, i});
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (i != first && j != first) {
				d.push_back({i, j});
			}
		}
	}
	for (int i = first; i < n - cnt - 1; i++) {
		d.push_back({i, i + 1});
	}
	for (int i = n - cnt - 2; i >= 0; i--) {
		d.push_back({i + 1, i});
	}
	cout << int(d.size()) << endl;
	for (auto i : d) {
		cout << i.first + 1 << ' ' << i.second + 1 << endl;
	}
	a.clear();
	d.clear();
	return true;
}

int main() {
	#ifdef HOME
		freopen("input.txt", "rt", stdin);
	#endif
	while (true) {
		if (!solve())
			break;
	}
}
