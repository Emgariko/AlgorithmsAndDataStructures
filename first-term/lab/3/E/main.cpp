#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e5 + 123;
const int INF = 1e9;

struct DSU{
    int p[MAXN], rnk[MAXN];
    int l[MAXN], r[MAXN];
    int sz;
    DSU() {
        for (int i = 0; i < MAXN; i++) {
            p[i] = i;
            rnk[i] = 1;
            r[i] = i;
            l[i] = i;
        }
        sz = MAXN;
    }
    int get(int u) {
        if (p[u] == u) { return u; }
        return p[u] = get(p[u]);
    }
    bool check(int x, int y) {
        x = get(x);
        y = get(y);
        return x == y;
    }
    void unsegm(int x, int y, DSU &kek) {
        x = get(x);
        int t = y;
        y = get(y);
        for (int i = x; i < t; i++) {
        	bool flag = false;
        	if (p[i] == y) {
        		flag = true;
        	}
            p[i] = y;
            kek.un(i, y);
            if (flag) {
            	break;
            }
        }
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
        } else {
            p[x] = y;
        }
    }
};

DSU a, b;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    a.sz = n;
    for (int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        if (x > y) { swap(x, y); }
        x--;
        y--;
        if (t == 2) {
            a.unsegm(x, y, b);
        } else if (t == 1) {
            b.un(x, y);
        } else {
            int t3 = b.get(x);
            int t4 = b.get(y);
            if (t3 == t4) {
                cout << "YES";
            } else {
                cout << "NO";
            }
            cout << "\n";
        }
    }
    return 0;
}
