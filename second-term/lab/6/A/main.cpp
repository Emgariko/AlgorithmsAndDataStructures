#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e6 + 1337;
const int INF = 2e9;

string s;
vector<vector<int>> h;

void remove(int x) {
    int y = abs(x) % MOD;
    auto id = h[y].begin();
    bool ok = false;
    for (int i = 0; i < int(h[y].size()); i++) {
        if (h[y][i] == x) {
            ok = true;
            break;
        }
        id++;
    }
    if (ok) {
        h[y].erase(id);
    }
}

bool exists(int x) {
    int y = abs(x) % MOD;
    for (int i = 0; i < int(h[y].size()); i++) {
        if (h[y][i] == x) {
            return true;
        }
    }
    return false;
}

void add(int x) {
    int y = abs(x) % MOD;
    if (!exists(x))
        h[y].push_back(x);
}


int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("set.in", "rt", stdin);
	freopen("set.out", "wt", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    h.resize(MOD);
    while (cin >> s) {
        int x;
        cin >> x;
        if (s == "insert") {
            add(x);
        } else if (s == "exists") {
            if (exists(x)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        } else if (s == "delete") {
            remove(x);
        }
    }
    return 0;
}
