#include <bits/stdc++.h>

using namespace std;

vector <vector<pair<int, int>>> d;
vector <int> sz;

int l = 0, cnt = 0, L = 0;

void build(int n) {
	for (int i = 0; i < 8; i++) {
		d[l].push_back({1 + i * 2, 2 + i * 2});
	}
	l++;
	for (int i = 0; i < 4; i++) {
		d[l].push_back({1 + i * 4, 4 + i * 4});
	}
	for (int i = 0; i < 4; i++) {
		d[l].push_back({2 + i * 4, 3 + i * 4});
	}
	l++;
	for (int i = 0; i < 8; i++) {
		d[l].push_back({1 + i * 2, 2 + i * 2});
	}
	l++;
	for (int i = 0; i < 4; i++) {
		d[l].push_back({1 + i, 8 - i});
		d[l].push_back({9 + i, 16 - i});
	}
	l++;
	d[l].push_back({1, 3});
	d[l].push_back({2, 4});
	d[l].push_back({5, 7});
	d[l].push_back({6, 8});
	d[l].push_back({8 + 1, 8 + 3});
	d[l].push_back({8 + 2, 8 + 4});
	d[l].push_back({8 + 5, 8 + 7});
	d[l].push_back({8 + 6, 8 + 8});
	l++;
	for (int i = 0; i < 8; i++) {
		d[l].push_back({1 + i * 2, 2 + i * 2});
	}
	l++;
	for (int i = 0; i < 8; i++) {
		d[l].push_back({1 + i, 16 - i});
	}
	l++;
	d[l].push_back({1, 5});
	d[l].push_back({2, 6});
	d[l].push_back({3, 7});
	d[l].push_back({4, 8});
	d[l].push_back({8 + 1, 8 + 5});
	d[l].push_back({8 + 2, 8 + 6});
	d[l].push_back({8 + 3, 8 + 7});
	d[l].push_back({8 + 4, 8 + 8});
	l++;
	d[l].push_back({1, 3});
	d[l].push_back({2, 4});
	d[l].push_back({5, 7});
	d[l].push_back({6, 8});
	d[l].push_back({8 + 1, 8 + 3});
	d[l].push_back({8 + 2, 8 + 4});
	d[l].push_back({8 + 5, 8 + 7});
	d[l].push_back({8 + 6, 8 + 8});
	l++;
	for (int i = 0; i < 8; i++) {
		d[l].push_back({1 + i * 2, 2 + i * 2});
	}
	l++;
	for (int i = 0; i < l; i++) {
        for (int j = 0; j < int(d[i].size()); j++) {
            if (d[i][j].first <= n && d[i][j].second <= n) {
                sz[i]++;
                cnt++;
            }
        }
    }
    for (int i = 0; i < l; i++) {
        if (sz[i] > 0) {
            L++;
        }
    }
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif
	int n;
	cin >> n;
	d.resize(100);
	sz.resize(100);
	build(n);
	cout << n << ' ' << cnt << ' ' << L << "\n";
	for (int i = 0; i < l; i++) {
		if (sz[i] == 0) continue;
		cout << sz[i] << " ";
		for (int j =  0; j < int(d[i].size()); j++) {
			if (d[i][j].first <= n && d[i][j].second <= n) {
				cout << d[i][j].first << ' ' << d[i][j].second << ' ';
			}
		}
		cout << "\n";
	}
	return 0;
}
