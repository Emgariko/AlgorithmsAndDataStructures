#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 123;
const int INF = 1e9;
int shift = 0;

struct DSU{
    int p[MAXN], rnk[MAXN], c[MAXN];
    int sz;
    DSU() {
        for (int i = 0; i < MAXN; i++) {
            p[i] = i;
            c[i] = 0;
            rnk[i] = 1;
        }
        sz = MAXN;
    }
    int get(int u) {
        if (p[u] == u) { return u; }
        int v = get(p[u]);
        c[u] = c[u] + c[p[u]];
        return p[u] = v;
    }
    bool check(int x, int y) {
        x = get(x);
        y = get(y);
        return x == y;
    }
    void un(int x, int y) {
    	int xx = x, yy = y;
    	x = get(x);
    	y = get(y);
    	if (x == y) { return; }
    	p[y] = x;
    	if (c[yy] % 2 == c[xx] % 2) {
    		c[y] = c[x] + 1;
    	}
    }
};

DSU a;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
    	int t, x, y;
    	cin >> t >> x >> y;
    	x--;
    	y--;
    	x = (x + shift) % n;
    	y = (y + shift) % n;
    	if (t == 0) {
    		a.un(x, y);
    	} else {
    		a.get(x);
    		a.get(y);
    		if (a.c[x] % 2 == a.c[y] % 2) {
    			cout << "YES";
    			shift = (shift + 1) % n;
    		} else {
    			cout << "NO";
    		}
    		cout << "\n";
    	}
    }
    return 0;
}
