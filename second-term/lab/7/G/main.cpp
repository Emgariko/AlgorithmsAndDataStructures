#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 123;
const int MAXT = 4 * MAXN;
const ll INF = 2e18 + 123;

ll a[MAXN];
ll t[MAXT];
ll p[MAXT];
ll pl[MAXT];

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v + 1, tl, tm);
        build(2 * v + 2, tm + 1, tr);
        t[v] = min(t[2 * v + 1], t[2 * v + 2]);
    }
}

string s;

bool check(int v) {
    return v < MAXT;
}

void push(int v) {
    int vv = 2 * v + 1;
    ll pv = p[v];
    ll plv = pl[v];
    if (check(vv)) {
        if (p[v] != INF) {
            p[vv] = p[v];
            pl[vv] = 0;
            // p[v] = INF;
            t[vv] = p[v];
            pv = INF;
        } else {
            // pl[vv] += pl[v];
            if (p[vv] != INF) {
                p[vv] += pl[v];
            } else {
                pl[vv] += pl[v];
            }
            // pl[v] = 0;
            t[vv] += pl[v];
            plv = 0;
        }
    }
    vv = 2 * v + 2;
    if (check(vv)) {
        if (p[v] != INF) {
            p[vv] = p[v];
            pl[vv] = 0;
            // p[v] = INF;
            t[vv] = p[v];
            pv = INF;
        } else {
            // pl[vv] += pl[v];
            if (p[vv] != INF) {
                p[vv] += pl[v];
            } else {
                pl[vv] += pl[v];
            }
            // pl[v] = 0;
            t[vv] += pl[v];
            plv = 0;
        }
    }
    p[v] = pv;
    pl[v] = plv;
}

ll get_min(int v, int tl, int tr, int l, int r) {
    if (l > r) { return INF; }
    if (tl == l && tr == r) {
        return t[v];
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        ll ans = get_min(2 * v + 1, tl, tm, l, min(tm, r));
        ans = min(ans, get_min(2 * v + 2, tm + 1, tr, max(l, tm + 1), r));
        return ans;
    }
}

void add(int v, int tl, int tr, int l, int r, ll x) {
    if (l > r) { return; }
    if (tl == l && tr == r) {
        t[v] += x;
        if (p[v] != INF) {
            p[v] += x;
        } else {
            pl[v] += x;
        }
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        add(2 * v + 1, tl, tm, l, min(tm, r), x);
        add(2 * v + 2, tm + 1, tr, max(l, tm + 1), r, x);
        t[v] = min(t[2 * v + 1], t[2 * v + 2]);
    }
}

void put(int v, int tl, int tr, int l, int r, ll x) {
    if (l > r) { return; }
    if (tl == l && tr == r) {
        t[v] = x;
        pl[v] = 0;
        p[v] = x;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        put(2 * v + 1, tl, tm, l, min(tm, r), x);
        put(2 * v + 2, tm + 1, tr, max(l, tm + 1), r, x);
        t[v] = min(t[2 * v + 1], t[2 * v + 2]);
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    for (int v = 0; v < MAXT; v++) {
        p[v] = INF;
        pl[v] = 0;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, 0, n - 1);
    while (cin >> s) {
        if (s == "min") {
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            ll ans = get_min(0, 0, n - 1, l, r);
            cout << ans << "\n";
        } else if (s == "add") {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            l--;
            r--;
            add(0, 0, n - 1, l, r, x);
        } else if (s == "set") {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            l--;
            r--;
            put(0, 0, n - 1, l, r, x);
        }
    }
    return 0;
}
