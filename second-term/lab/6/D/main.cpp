#include <bits/stdc++.h>

using namespace std;

const int INF = 2e9;
const unsigned MOD = 1e6 + 247;
const unsigned p = 157;

struct hash_set {
	const int MOD1 = 150;
    vector<vector<string>> h;
    int sz = 0;
    hash_set() {
    	sz = 0;
        h.resize(MOD1);
    }
    hash_set(const hash_set &a) {
        h = a.h;
        sz = a.sz;
    }

    void operator=(const hash_set &a) {
    	h = a.h;
    	sz = a.sz;
    }

    hash_set(string& x) {
        h.resize(MOD1);
        add(x);
    }

    unsigned get_hash(string& a) {
        unsigned res = 0;
        for (int i = 0; i < int(a.length()); i++) {
            res = ((res * p) % MOD1 + (a[i] - '0' + 1)) % MOD1;
        }
        return res;
    }

    bool remove(string& x) {
        int y = get_hash(x);
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
            sz--;
            return true;
        }
        return false;
    }

    bool exists(string& x) {
        int y = get_hash(x);
        for (int i = 0; i < int(h[y].size()); i++) {
            if (h[y][i] == x) {
                return true;
            }
        }
        return false;
    }

    void add(string& x) {
        int y = get_hash(x);
        if (!exists(x)) {
            h[y].push_back(x);
            sz++;
        }
    }
    void getall() {
        for (int i = 0; i < int(MOD1); i++) {
            if (!h[i].empty()) {
                for (int j = 0; j < int(h[i].size()); j++) {
                    cout << h[i][j] << ' ';
                }
            }
        }
        cout << "\n";
    }
};

struct my_map {
    vector <vector<pair<string, hash_set>>> table;
    unsigned get_hash(string &a) {
        unsigned res = 0;
        for (int i = 0; i < int(a.length()); i++) {
            res = ((res * p) % MOD + (a[i] - '0' + 1)) % MOD;
        }
        return res;
    }

    my_map() {
        table.resize(MOD);
    }

    void put(string &a, string &b) {
        unsigned hash = get_hash(a);
        bool putted = false;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].first == a) {
                if (table[hash][i].second.sz != 0) {
                    table[hash][i].second.add(b);
                    putted = true;
                    break;
                }
            }
        }
        if (!putted) {
            table[hash].push_back({a, hash_set(b)});
        }
    }

    void remove(string &a, string &b) {
        unsigned hash = get_hash(a);
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].first == a && table[hash][i].second.sz != 0) {
                if (table[hash][i].second.remove(b)) {
                    break;
                }
            }
        }
    }

    void deleteall(string &a) {
        unsigned hash = get_hash(a);
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].first == a && table[hash][i].second.sz != 0) {
                table[hash][i].second = hash_set();
            }
        }
    }

    void get(string &a) {
        unsigned hash = get_hash(a);
        int s = -1;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].first == a && table[hash][i].second.sz != 0) {
                s = table[hash][i].second.sz;
                cout << s << ' ';
                table[hash][i].second.getall();
                break;
            }
        }
        if (s == -1)
            cout << s + 1 << "\n";
    }
};

string s, buf1, buf2;
my_map d;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("multimap.in", "rt", stdin);
    freopen("multimap.out", "wt", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> s) {
        if (s == "put") {
            cin >> buf1 >> buf2;
            d.put(buf1, buf2);
        } else if (s == "delete") {
            cin >>  buf1 >> buf2;
            d.remove(buf1, buf2);
        } else if (s == "deleteall") {
            cin >> buf1;
            d.deleteall(buf1);
        } else if (s == "get") {
            cin >> buf1;
            d.get(buf1);
        }
    }
    return 0;
}
