#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 5e5 + 100;
const int INF = 2e9 + 123;

vector <int> d[MAXN];
int ans;
int p[MAXN][30];
int dp[MAXN][30];
int h[MAXN];

bool used[MAXN];

int n, MAXK;

void dfs(int u, int he) {
    used[u] = 1;
    h[u] = he;
    int nw;
    for (int i = 0; i < int(d[u].size()); i++) {
        nw = d[u][i];
        if (!used[nw]) {
            dfs(nw, he + 1);
        }
    }
}

int lca(int u, int v) {
    if (h[u] > h[v]) {
        swap(u, v);
    }
    if (h[v] >= h[u]) {
        for (int k = MAXK; k >= 0; k--) {
            if (h[p[v][k]] >= h[u]) {
                v = p[v][k];
            }
        }
    }
    if (v == u) {
        return v;
    }
    for (int k = MAXK; k >= 0; k--) {
        if (p[v][k] != p[u][k]) {
            v = p[v][k];
            u = p[u][k];
        }
    }
    return p[u][0];
}

vector <pair<string, pair<int, int>>> querry;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int kk;
    int nn = -1;
    cin >> kk;
    querry.resize(kk);
    for (int i = 0; i < kk; i++) {
        cin >> querry[i].first >> querry[i].second.first >> querry[i].second.second;
    }
    for (int i = 0; i < kk; i++) {
        if (querry[i].first == "ADD") {
            int a = querry[i].second.first;
            int b = querry[i].second.second;
            nn = max(nn, max(a, b));
            p[b][0] = a;
            d[b].push_back(a);
            d[a].push_back(b);
        }
    }
    int root = 1;
    p[root][0] = root;
    dfs(root, 0);
    MAXK = 22;
    for (int k = 1; k <= MAXK ; k++) {
        for (int i = 1; i <= nn; i++) {
            p[i][k] = p[p[i][k - 1]][k - 1];
            dp[i][k] = min(dp[p[i][k - 1]][k - 1], dp[i][k - 1]);
        }
    }
    for (int i = 0; i < kk; i++) {
        if (querry[i].first == "GET") {
            int a = querry[i].second.first, b = querry[i].second.second;
            cin >> a >> b;
            cout << lca(a, b) << endl;
        }
    }
    return 0;
}
