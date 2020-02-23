#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e4 + 123;
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
vector <pair<int, pair<int, int>>> a;
vector <pair<int, int>> g;
vector <bool> ans;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    g.resize(m);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        g.push_back({x, y});
    }
    a.resize(k);
    for (int i = 0; i < k; i++) {
        cin >> s;
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (s[0] == 'a') {
            a[k - i - 1] = {0, {x, y}};
        } else {
            a[k - i - 1] = {1, {x, y}};
        }
    }
    for (int i = 0; i < k; i++) {
        int x = a[i].second.first, y = a[i].second.second;
        if (a[i].first == 0) {
            ans.push_back(d.check(x, y));
        } else {
            d.un(x, y);
        }
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < int(ans.size()); i++) {
        if (ans[i] == 1) {
            cout << "YES";
        } else {
            cout << "NO";
        }
        cout << "\n";
    }
    return 0;
}
