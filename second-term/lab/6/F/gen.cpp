#include <bits/stdc++.h>

using namespace std;

string a, b, c;

string gen_str(int n) {
	for (int i = 0; i < n; i++) {
		c[i] = 'a' + rand() % 26;
	}
	return c;
}

int has(string s) {
	int res = 0;
	int n = s.length();
	for (int i = 0; i < n; i++) {
		res = res * 31 + s[i];
	}
	return res;
}

int main() {
	#ifdef HOME
		freopen("input.txt", "rt", stdin);
	#endif
	int n;
	cout << "Enter strings length: \n";
	cin >> n;
	c.resize(n);
	srand(time(NULL));
	int t = 0;
	while (true) {
		a = gen_str(n);
		b = gen_str(n);
		if (has(a) == has(b)) {
			cout << "Yes!\n";
			int c = log10(t);
			for (int i = 0; i < 10 - c; i++) {
				cout << " ";
			}
			cout << t << " ";
			cout << a << ' ' << b << ' ';
			break;
		} else {
			t++;
			int c = log10(t);
			cout << "Failed";
			for (int j = 0; j < 10 - c; j++) {
				cout << " ";
			}
			cout << t << " ";
			cout << a << ' ' << b << "\n";
		}
	}
	return 0;
}