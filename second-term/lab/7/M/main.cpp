#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXL = 20;

struct sparse_table {
    int* t[MAXL];
    int* id[MAXL];
    int* lg;
    int n;
    sparse_table() {}
    sparse_table(int nn) {
        n = nn;
        lg = (int*) malloc(sizeof(int) * (n + 1));
        for (int i = 0; i < MAXL; i++) {
            t[i] = (int*) malloc(sizeof(int) * (n));
            id[i] = (int*) malloc(sizeof(int) * (n));
        }
    }
    pair<int, int> get_ans(int l, int r) {
        int len = r - l + 1;
        int lgg = lg[(len)];
        int v1 = t[lgg][l];
        int v2 = t[lgg][r - (1 << lgg) + 1];
        int v = min(v1, v2);
        int ans_id;
        if (v == v1) {
            ans_id = id[lgg][l];
        } else {
            ans_id = id[lgg][r - (1 << lgg) + 1];
        }
        return {v, ans_id};
    }
    void init(int *a) {
        lg[1] = 0;
        for (int i = 2; i <= n; i++) {
            lg[i] = lg[i / 2] + 1;
        }
        for (int j = 0; j < MAXL; j++) {
            for (int i = 0; i < n; i++) {
                if (j == 0) {
                    t[j][i] = a[i];
                    id[j][i] = i;
                } else {
                    int v1 = t[j - 1][i], v2 = t[j - 1][min(n - 1, i + (1 << (j - 1)))];
                    t[j][i] = min(v1, v2);
                    if (v1 == t[j][i]) {
                        id[j][i] = id[j - 1][i];
                    } else {
                        id[j][i] = id[j - 1][min(n - 1, i + (1 << (j - 1)))];
                    }
                }
            }
        }
    }
};

vector <vector<int>> d;
vector <ll> a;
vector <int> lst, fst;
vector <int> route;
vector <int> h;

void dfs(int u, int p, int height) {
    fst[u] = int(route.size());
    route.push_back(u);
    h.push_back(height);
    for (auto v : d[u]) {
        if (v == p) { continue; }
        route.push_back(u);
        h.push_back(height);
        dfs(v, u, height + 1);
    }
    h.push_back(height);
    lst[u] = int(route.size());
    route.push_back(u);
}

const int SZ = 100;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int n, m;
    cin >> n >> m;
    d.resize(n);
    lst.resize(n);
    fst.resize(n);
    a.resize(SZ);
    for (int i = 1; i <= n - 1; i++) {
        int a;
        cin >> a;
        d[a].push_back(i);
        d[i].push_back(a);
    }
    dfs(0, 0, 0);
    /*for (int i = 0; i < int(route.size()); i++) {
        cout << route[i] << ' ';
    }
    cout << "\n";*/
    sparse_table table(int(h.size()));
    table.init(h.data());
    ll a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    a[0] = a1, a[1] = a2;
    ll ans = 0, last_ans = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        if (i != 0) {
	        ll ai = x * a[(2 * i - 2 + SZ) % SZ] + y * a[(2 * i - 1) % SZ] + z;
	        ai %= n;
	        a[(2 * i) % SZ] = ai;
	        ll aip1 = x * a[(2 * i - 1 + SZ) % SZ] + y * a[(2 * i) % SZ] + z;
	        aip1 %= n;
	        a[(2 * i + 1) % SZ] = aip1;
	        u = (int) aip1;
	        v = (int) (a[(2 * i) % SZ] + last_ans) % n;
	    } else {
	    	u = (int) a[1];
	    	v = (int) a[0];
	    }
        /*u = a[(2 * i) % SZ];
        v = (a[(2 * i - 1 + SZ) % SZ] + (int) last_ans) % n;*/
        // cout << u << ' ' << v << "\n";
        /*u = (int) a[(2 * i) % M];
        v = ((int) a[(2 * i - 1) % M] + (int) last_ans) % n;
        */int lu = fst[u], ru = lst[u], lv = fst[v], rv = lst[v];
        int l = min(lu, lv);
        int r = max(ru, rv);
        pair<int, int> res = table.get_ans(l, r);
        last_ans = route[res.second];
        ans += route[res.second];
    }
    cout << ans;
    return 0;
}
