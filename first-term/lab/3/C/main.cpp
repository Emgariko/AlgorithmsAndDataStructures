#include <bits/stdc++.h>

using namespace std;

string s;

vector <pair<int, int>> d;
vector <int> p;

void sift_up(int id) {
    while (true) {
        if (id == 0) { break; }
        if (d[id].first >= d[(id - 1) / 2].first) { break; }
        swap(p[d[id].second], p[d[(id - 1) / 2].second]);
        swap(d[id], d[(id - 1) / 2]);
        id = (id - 1) / 2;
    }
}

void sift_down(int id) {
    while (2 * id + 1 < int(d.size())) {
        int j = 2 * id + 1;
        if (2 * id + 2 < int(d.size()) && d[2 * id + 2] < d[2 * id + 1]) {
            j = 2 * id + 2;
        }
        if (d[id].first <= d[j].first) break;
        swap(p[d[id].second], p[d[j].second]);
        swap(d[id], d[j]);
        id = j;
    }
}

void push(int x, int num) {
    d.push_back({x, num});
    p.push_back(int(d.size()) - 1);
    sift_up(int(d.size()) - 1);
}

pair<int, int> extract_min() {
    if (d.size() == 0) {
        return {-1, -2};
    }
    pair<int, int> res = d[0];
    swap(d[0], d[int(d.size()) - 1]);
    swap(p[d[0].second], p[d[int(d.size()) - 1].second]);
    d.pop_back();
    sift_down(0);
    p[res.second] = -1;
    return res;
}

void decrease(int id, int value) {
    d[id].first = value;
    sift_up(id);
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    int i = 0;
    while (cin >> s) {
        if (s[0] == 'p') {
            int x;
            cin >> x;
            push(x, i);
        } else {
            p.push_back(-1);
            if (s[0] == 'e') {
                pair<int, int> res = extract_min();
                if (res.second == -2) {
                    cout << "*\n";
                } else {
                    cout << res.first << ' ' << res.second + 1 << "\n";
                }
            } else if (s[0] == 'd') {
                int x, y;
                cin >> x >> y;
                x--;
                if (p[x] != -1 && p[x] != -2) {
                    decrease(p[x], y);
                }
            }
        }
        i++;
    }
    return 0;
}
