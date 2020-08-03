#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 123;
const int MAXT = 4 * MAXN;
const int INF = 1e9 + 123;

int t[MAXT];
int a[MAXN];

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

void upd(int v, int tl, int tr, int pos, int val) {
    if (tl == tr && pos == tl) {
        a[tl] = val;
        t[v] = val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            upd(2 * v + 1, tl, tm, pos, val);
        } else {
            upd(2 * v + 2, tm + 1, tr, pos, val);
        }
        t[v] = min(t[2 * v + 1], t[2 * v + 2]);
    }
}

int mn(int v, int tl, int tr, int l, int r) {
    if (l > r) { return INF; }
    if (tl == l && tr == r) {
        return t[v];
    } else {
        int tm = (tl + tr) / 2;
        int ans = mn(2 * v + 1, tl, tm, l, min(tm, r));
        ans = min(ans, mn(2 * v + 2, tm + 1, tr, max(l, tm + 1), r));
        return ans;
    }
}

string s;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, 0, n - 1);
    while (cin >> s) {
        int l, r;
        if (s == "min") {
            cin >> l >> r;
            l--;
            r--;
            int ans = mn(0, 0, n - 1, l, r);
            cout << ans << "\n";
        } else if (s == "set") {
            cin >> l >> r;
            l--;
            upd(0, 0, n - 1, l, r);
        }
    }
    return 0;
}
