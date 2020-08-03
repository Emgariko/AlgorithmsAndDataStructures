#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = (1 << 24) + 123;

unsigned int cur = 0;
unsigned int nextRand(unsigned int a, unsigned int b) {
	cur = cur * a + b;
	return cur >> 8;
}

unsigned diff[MAXN], value[MAXN], pr[MAXN];

int main() {
	#ifdef HOME
		freopen("input.txt", "rt", stdin);
	#endif
	int m, q;
	unsigned int a, b;
	cin >> m >> q >> a >> b;
	for (int i = 0; i < m; i++) {
		unsigned int add = nextRand(a, b);
		unsigned int l = nextRand(a, b);
		unsigned int r = nextRand(a, b);
		if (l > r) {
			swap(l, r);
		}
		diff[l] += (add);
		diff[r + 1] -= (add);
	}
	unsigned int sum = 0;
	for (int i = 0; i <= MAXN - 1; i++) {
		sum += (unsigned int) diff[i];
		value[i] = (unsigned int) sum;
	}
	pr[0] = 0;
	for (int i = 1; i <= MAXN - 1; i++) {
		pr[i] = pr[i - 1] + value[i - 1];
	}
	unsigned int res = 0;
	for (int i = 0; i < q; i++) {
		unsigned int l = nextRand(a, b);
		unsigned int r = nextRand(a, b);
		if (l > r) {
			swap(l, r);
		}
		res = res + ((unsigned int) pr[r + 1] - pr[l]);
	}
	cout << res;
	return 0;
}
