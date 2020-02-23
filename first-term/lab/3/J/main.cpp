#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 123;
const int INF = 1e9;
const ll P = 1e6 + 3;

ll zerg = 0;

struct DSU{
    ll p[MAXN], rnk[MAXN];
    ll ms[MAXN], rd[MAXN];
    int sz;
    DSU() {
        for (int i = 0; i < MAXN; i++) {
            p[i] = i;
            rd[i] = 0;
            ms[i] = 0;
        }
        sz = MAXN;
    }
    int get(int u) {
        if (p[u] == u) { return u; }
        return get(int(p[u]));
    }
    bool check(int x, int y) {
        x = get(x);
        y = get(y);
        return x == y;
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
            ms[y] -= ms[x];
        } else {
            p[x] = y;
            ms[x] -= ms[y];
        }
    }
    ll count(int x) {
        ll cnt = 0;
        int xx = x;
        if (p[x] == x) {
            ll res = ms[x] - rd[x];
            rd[x] += res;
            return res;
        }
        while (true) {
            if (p[x] == x) {
                cnt += ms[x];
                break;
            }
            cnt += ms[x];
            x = int(p[x]);
        }
        cnt = cnt - rd[xx];
        rd[xx] += cnt;
        return cnt;
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
    ll n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            ll x;
            cin >> x;
            x = ((x + zerg) % n);
            a.ms[a.get(int(x))]++;
            zerg = (30 * zerg + 239) % P;
        } else if (t == 2) {
            ll x, y;
            cin >> x >> y;
            x = ((x + zerg) % n);
            y = ((y + zerg) % n);
            if (a.check(int(x), int(y))) { continue; }
            a.un(int(x), int(y));
            zerg = (13 * zerg + 11) % P;
        } else {
            ll x;
            cin >> x;
            x = ((x + zerg) % n);
            ll q = a.count(int(x));
            zerg = (zerg * 100500 + q) % P;
            cout << q << "\n";
        }
    }
    return 0;
}
