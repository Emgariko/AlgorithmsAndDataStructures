#include <bits/stdc++.h>

using namespace std;

const unsigned long long ST = 579;
const unsigned long long ppp = 1001;
const int MAXN = 1e5 + 123;

vector <vector<int>> d;
vector <int> d1, d2;
vector <int> dist;
stack <int> q;
vector <unsigned long long> ha;
vector <unsigned long long> hb;
vector <int> sz;

int bfs(int t) {
    int n = d.size();
    q.push(t);
    dist.assign(n, -1);
    dist[t] = 0;
    while (!q.empty()) {
        int v = q.top();
        q.pop();
        for (auto u : d[v]) {
            if (dist[u] != -1) { continue; }
            dist[u] = dist[v] + 1;
            q.push(u);
        }
    }
    int max_dist = -1, node = -1;
    for (int i = 0; i < n; i++) {
        if (max_dist < dist[i]) {
            max_dist = dist[i];
            node = i;
        }
    }
    return node;
}

pair <int, int> get_nodes() {
    int t = bfs(0);
    int t1 = bfs(t);
    return {t, t1};
}

void dfs(int u, int p, int ch, vector<int>&tt) {
    for (auto v : d[u]) {
        if (v == p) { continue; }
        dfs(v, u, ch + 1, tt);
    }
    tt[u] = ch;
}

int find_node() {
    int res = -1;
    int n = d.size();
    for (int i = 0; i < n; i++) {
        if (d1[i] == d2[i]) {
            res = i;
            return res;
        }
    }
    return res;
}

pair<int, int> buf[MAXN];

void dfs2(int u, int p) {
    int s = 1;
    for (auto v : d[u]) {
        if (v == p) { continue; }
        dfs2(v, u);
        s += sz[v];
    }
    sz[u] = s;
}

void dfs1(int u, int p) {
    bool flag = false;
    int id = 0;
    for (auto v : d[u]) {
        if (v == p) { continue; }
        flag = true;
        dfs1(v, u);
    }
    for (auto v : d[u]) {
        if (v == p) { continue; }
        buf[id++] = {sz[v], v};
    }
    if (!flag) {
        ha[u] = d1[u];
        hb[u] = d1[u];
    } else {
        sort(buf, buf + id);
        unsigned long long cur_h = 0;
        for (int i = 0; i < id; i++) {
            cur_h = ((cur_h * ST) + ha[buf[i].second] * ((unsigned long long) (d1[buf[i].second])));
        }
        ha[u] = cur_h;
        cur_h = 0;
        for (int i = 0; i < id; i++) {
            cur_h = ((cur_h * ST) + hb[buf[i].second] * ((unsigned long long) (d1[buf[i].second])));
        }
        hb[u] = cur_h;
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int n;
    cin >> n;
    d.resize(n);
    dist.resize(n);
    d1.resize(n);
    d2.resize(n);
    sz.resize(n, 0);
    ha.resize(n, 0);
    hb.resize(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        d[a].push_back(b);
        d[b].push_back(a);
    }
    pair <int, int> t = get_nodes();
    dfs(t.first, -1, 1, d1);
    dfs(t.second, -1, 1, d2);
    int diam = d1[t.second];
    if (diam % 2 == 0) {
        cout << "NO";
        return 0;
    }
    int v = find_node();
    if (d[v].size() != 2) {
        cout << "NO";
        return 0;
    }
    dfs(v, -1, 1, d1);
    dfs2(v, -1);
    dfs1(v, -1);
    int aa = d[v][0];
    int bb = d[v][1];
    if (ha[aa] == ha[bb] && hb[aa] == hb[bb]) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
