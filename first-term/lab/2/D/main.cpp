#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-5;

vector <double> h;

int main() {
	int n;
	double a;
	cin >> n >> a;
	h.resize(n);
	h[0] = a;
	double l = 0, r = 1000, m;
	for (int i = 0; i < 50; i++) {
		m = (l + r) / 2;
		h[1] = m;
		bool ok = true;
		for (int i = 2; i < n; i++) {
			h[i] = 2 * h[i - 1] + 2 - h[i - 2];
			if (h[i] <= EPS) {
				ok = false;
				break;
			}
		}
		if (ok) {
			r = m;
		} else {
			l = m;
		}
	}
	cout << fixed;
	cout.precision(2);
	h[1] = l;
	for (int i = 2; i < n; i++) {
		h[i] = 2 * h[i - 1] + 2 - h[i - 2];
	}
	cout << h[n - 1];
	return 0;
}
