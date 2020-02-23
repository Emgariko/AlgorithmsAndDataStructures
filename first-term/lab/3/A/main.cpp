#include <bits/stdc++.h>

using namespace std;

vector <int> d;

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
	for (int i = 0; i < n; i++) {
		int x = d[i];
		int y;
		if (2 * i + 1 < n) {
			y = d[2 * i + 1];
			if (x > y) {
				cout << "NO";
				return 0;
			}
		}
		if (2 * i + 2 < n) {
			y = d[2 * i + 2];
			if (x > y) {
				cout << "NO";
				return 0;
			}
		}
	}
	cout << "YES";
	return 0;
}
