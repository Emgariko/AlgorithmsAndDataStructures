#include <bits/stdc++.h>

using namespace std;

struct node {
    string key;
    string value;
    node* next = nullptr;
    node* prev = nullptr;
    node() {}
    node(string new_key, string new_value, node* new_next, node* new_prev) {
        key = new_key;
        value = new_value;
        prev = new_prev;
        next = new_next;
    }
};

template <typename T, typename K> class my_map {
 private:
    const unsigned MOD = 3e6 + 247;
    const unsigned p = 1589;
    vector <vector<node>> table;
    unsigned get_hash(T a) {
        unsigned res = 0;
        for (int i = 0; i < int(a.length()); i++) {
            res = ((res * p) % MOD + (a[i] - 'a' + 1)) % MOD;
        }
        return res;
    }

 public:
    node* last = nullptr;
    my_map() {
        table.resize(MOD);
        last = nullptr;
    }
    void put(T a, K b) {
        unsigned hash = get_hash(a);
        bool putted = false;
        node* pointer = nullptr;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].key == a) {
                table[hash][i].value = b;
                return;
                break;
            }
        }
        if (!putted) {
            table[hash].push_back(node(a, b, nullptr, last));
            int l = int(table[hash].size()) - 1;
            pointer = &table[hash][l];
        }
        if (last != pointer && last != nullptr) {
            last->next = pointer;
        }
        last = pointer;
    }
    void remove(T a) {
        unsigned hash = get_hash(a);
        auto it = table[hash].begin();
        bool found = false;
        node* pointer = nullptr;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].key == a) {
                found = true;
                pointer = &table[hash][i];
                break;
            }
            it++;
        }
        if (found) {
            if (pointer->next != nullptr) {
                pointer->next->prev = pointer->prev;
            }
            if (pointer->prev != nullptr) {
                pointer->prev->next = pointer->next;
            }
            if (pointer == last) {
                last = last->prev;
            }
            table[hash].erase(it);
        }
    }
    K get(T a) {
        unsigned hash = get_hash(a);
        K res;
        bool got = false;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].key == a) {
                res = table[hash][i].value;
                got = true;
                break;
            }
        }
        if (!got)
            res = "none";
        return res;
    }
    T next(T a) {
        unsigned hash = get_hash(a);
        bool found = false;
        node* pointer = nullptr;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].key == a) {
                found = true;
                pointer = &table[hash][i];
                break;
            }
        }
        if (found) {
            if (pointer->next != nullptr) {
                return pointer->next->value;
            }
        }
        return "none";
    }
    T prev(T a) {
        unsigned hash = get_hash(a);
        bool found = false;
        node* pointer = nullptr;
        for (int i = 0; i < int(table[hash].size()); i++) {
            if (table[hash][i].key == a) {
                found = true;
                pointer = &table[hash][i];
                break;
            }
        }
        if (found) {
            if (pointer->prev != nullptr) {
                return pointer->prev->value;
            }
        }
        return "none";
    }
};

string s, buf1, buf2;
my_map <string, string> d;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("linkedmap.in", "rt", stdin);
    freopen("linkedmap.out", "wt", stdout);
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
        } else if (s == "prev") {
            cin >> buf1;
            cout << d.prev(buf1) << "\n";
        } else if (s == "next") {
            cin >> buf1;
            cout << d.next(buf1) << "\n";
        }
       /* if (d.last == nullptr)
            cout << "null \n";
        else
            cout << d.last->key << ' ' << "\n";*/
    }
    return 0;
}