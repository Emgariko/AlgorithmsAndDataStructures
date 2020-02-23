#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 123;
const int INF = 2e9;

struct DSU{
	int p[MAXN], rnk[MAXN], mn[MAXN], mx[MAXN], sz[MAXN];
	DSU() {
		for (int i = 0; i < MAXN; i++) {
			p[i] = i;
			rnk[i] = 0;
			sz[i] = 1;
			mn[i] = i + 1;
			mx[i] = i + 1;
		}
	}
	int get(int u) {
		if (p[u] == u) return u;
		return p[u] = get(p[u]);
	}
	void un(int x, int y) {
		x = get(x);
		y = get(y);
		if (x == y) return;
		if (rnk[x] == rnk[y]) {
			rnk[x]++;
		}
		if (rnk[x] > rnk[y]) {
			p[y] = x;
			mn[x] = min(mn[x], mn[y]);
			mx[x] = max(mx[x], mx[y]);
			sz[x] += sz[y];
		} else {
			p[x] = y;
			mn[y] = min(mn[y], mn[x]);
			mx[y] = max(mx[y], mx[x]);
			sz[y] += sz[x];
		}
	}
};

string s;
DSU d;

int main() {
	#ifdef HOME
		freopen("input.txt", "rt", stdin);
	#endif
	int n;
	cin >> n;
	while (cin >> s) {
		if (s[0] == 'u') {
			int x, y;
			cin >> x >> y;
			x--;
			y--;
			d.un(x, y);
		} else {
			int x;
			cin >> x;
			x--;
			int id = d.get(x);
			cout << d.mn[id] << ' ' << d.mx[id] << ' ' << d.sz[id] << "\n";
		}
	}
	return 0;
}
