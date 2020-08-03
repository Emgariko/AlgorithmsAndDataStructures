#include <bits/stdc++.h>

using namespace std;

vector <string> d;
string a, b, c;

int main() {
	#ifdef HOME
		freopen("input.txt", "rt", stdin);
	#endif
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	a = "mEfi";
	b = "ldfi";
	for (int i = 1; i <= n; i++) {
		int index = i;
		int t = 0;
		c.clear();
		while (index > 0) {
			if (index % 2 == 0) {
				c = c + a;
			} else {
				c = c + b;
			}
			index /= 2;
			t++;
		}
		for (int i = 0; i < 12 - t; i++) {
			c = c + a;
		}
		d.push_back(c);
	}
	for (int i = 0; i < int(d.size()); i++) {
		cout << d[i] << "\n";
	}
	return 0;
}
