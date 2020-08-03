#include <bits/stdc++.h>

using namespace std;


template <typename T, typename K> class my_map {
 private:
    const unsigned MOD = 3e6 + 247;
    const unsigned p = 157;
    vector <vector<pair<T, K>>> table;
    unsigned get_hash(T a) {
        unsigned res = 0;
        for (int i = 0; i < int(a.length()); i++) {
            res = ((res * p) % MOD + (a[i] - '0' + 1)) % MOD;
        }
        return res;
    }

 public:
    my_map() {
        table.resize(MOD);
    }
    void put(T a, K b) {
        unsigned hash = get_hash(a);
        bool putted = false;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].first == a) {
                table[hash][i].second = b;
                putted = true;
                break;
            }
        }
        if (!putted) {
            table[hash].push_back({a, b});
        }
    }
    void remove(T a) {
        unsigned hash = get_hash(a);
        auto it = table[hash].begin();
        bool found = false;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].first == a) {
                found = true;
                break;
            }
            it++;
        }
        if (found) {
            table[hash].erase(it);
        }
    }
    K get(T a) {
        unsigned hash = get_hash(a);
        K res;
        bool got = false;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].first == a) {
                res = table[hash][i].second;
                got = true;
                break;
            }
        }
        if (!got)
            res = "none";
        return res;
    }
};

string s, buf1, buf2;
my_map <string, string> d;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("map.in", "rt", stdin);
    freopen("map.out", "wt", stdout);
#endif
    while (cin >> s) {
        if (s == "put") {
            cin >> buf1 >> buf2;
            d.put(buf1, buf2);
        } else if (s == "delete") {
            cin >>  buf1;
            d.remove(buf1);
        } else if (s == "get") {
            cin >> buf1;
            cout << d.get(buf1) << "\n";
        }
    }
    return 0;
}
