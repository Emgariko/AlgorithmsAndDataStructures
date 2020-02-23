#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 123;

struct DSU{
    int p[MAXN];
    int sz;
    DSU() {
        for (int i = 0; i < MAXN; i++) {
            p[i] = i;
        }
        sz = MAXN;
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
    int add(int x) {
        int res = get(x);
        un(res, res + 1);
        return res;
    }
    void un(int x, int y) {
        if (y >= sz)
            y %= sz;
        p[x] = y;
    }
};

DSU d;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    d.sz = n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        cout << d.add(x) + 1 << ' ';
    }
    return 0;
}
