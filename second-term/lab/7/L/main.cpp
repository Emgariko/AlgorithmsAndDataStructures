#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = (1 << 17);
const int MAXT = 4 * MAXN;

vector<vector<int>> d;
vector <int> arr;
unsigned int q;
unsigned int a, b, cur = 0;

unsigned int nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

void build(int v, int l, int r) {
    if (l == r) {
        d[v].push_back(arr[l]);
    } else {
        int m = (l + r) / 2;
        build(2 * v + 1, l, m);
        build(2 * v + 2, m + 1, r);
        d[v].resize(int(d[2 * v + 1].size() + d[2 * v + 2].size()));
        merge(d[2 * v + 1].begin(), d[2 * v + 1].end(), d[2 * v + 2].begin(),
        	d[2 * v + 2].end(), d[v].begin());
    }
}

unsigned int get_ans(int v, int tl, int tr, int l, int r, int x, int y) {
    if (l > r) {
        return 0;
    }
    if (tl == l && tr == r) {
        unsigned int res = upper_bound(d[v].begin(), d[v].end(), y)
         - lower_bound(d[v].begin(), d[v].end(), x);
        return res;
    } else {
        int tm = (tl + tr) / 2;
        unsigned int res = get_ans(2 * v + 1, tl, tm, l, min(r, tm), x, y);
        res += get_ans(2 * v + 2, tm + 1, tr, max(l, tm + 1), r, x, y);
        return res;
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    cin >> q >> a >> b;
    arr.resize(MAXN);
    d.resize(MAXT);
    for (int i = 0; i < MAXN; i++) {
        arr[i] = nextRand24();
    }
    build(0, 0, MAXN - 1);
    unsigned int l, r, x, y, sum = 0;
    for (int i = 0; i < int(q); i++) {
        l = nextRand17();
        r = nextRand17();
        if (l > r) { swap(l, r); }
        x = nextRand24();
        y = nextRand24();
        if (x > y) { swap(x, y); }
        unsigned int res = get_ans(0, 0, MAXN - 1, l, r, x, y);
        // cout << l << ' ' << r << "---" << x << ' ' << y << "\n";
        b += res;
        sum += res;
    }
    cout << sum;
    return 0;
}
