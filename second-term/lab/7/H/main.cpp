#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 1e5 + 123;
const int MAXT = 4 * MAXN;
const int INF = 2e9 + 123;

string s;
int a[MAXN];
pair<int, int> t[MAXT];

void build(int v, int l, int r) {
    if (l == r) {
        t[v] = {0, l};
    } else {
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m + 1, r);
        t[v].second = t[2 * v + 1].second;
    }
}

void put(int v, int tl, int tr, int id, int value) {
    if (tl == tr) {
        t[v] = {value, tl};
    } else {
        int tm = (tl + tr) / 2;
        if (tm >= id) {
            put(2 * v + 1, tl, tm, id, value);
        } else {
            put(2 * v + 2, tm + 1, tr, id, value);
        }
        t[v].first = min(t[2 * v + 1].first, t[2 * v + 2].first);
        if (t[2 * v + 1].first == t[2 * v + 2].first) {
            t[v].second = min(t[2 * v + 1].second, t[2 * v + 2].second);
        } else {
            if (t[v].first == t[2 * v + 1].first) {
                t[v].second = t[2 * v + 1].second;
            } else {
                t[v].second = t[2 * v + 2].second;
            }
        }
    }
}
pair<int, int> get_min(int v, int tl, int tr, int l, int r) {
    if (l > r) { return {INF, INF}; }
    if (tl == l && tr == r) {
        return {t[v].first, t[v].second};
    } else {
        int tm = (tl + tr) / 2;
        pair<int, int> res = get_min(2 * v + 1, tl, tm, l, min(tm, r));
        pair<int, int> res1 = min(res, get_min(2 * v + 2, tm + 1, tr, max(tm + 1, l), r));
        if (res.first == res1.first) {
            return {res.first, min(res.second, res1.second)};
        } else {
            if (res.first > res1.first) {
                return res1;
            } else {
                return res;
            }
        }
    }
}

int main() {
    #ifdef HOME
        freopen("input.txt", "rt", stdin);
    #endif
    int n, m;
    cin >> n >> m;
    build(0, 0, n - 1);
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        cin >> s;
        if (s == "enter") {
            int x;
            cin >> x;
            x--;
            pair<int, int> res = get_min(0, 0, n - 1, x, n - 1);
            // cout << res.first << ' ' << res.second << "\n";
            if (res.first != 1) {
                put(0, 0, n - 1, res.second, 1);
                cout << res.second + 1 << "\n";
            } else {
                res = get_min(0, 0, n - 1, 0, n - 1);
                put(0, 0, n - 1, res.second, 1);
                cout << res.second + 1 << "\n";
            }
        } else {
            int x;
            cin >> x;
            x--;
            put(0, 0, n - 1, x, 0);
        }
    }
}
