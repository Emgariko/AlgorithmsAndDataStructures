#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;
const ll INF = 2e18;
const double EPS = 1e-6;

struct  item{
    double u, w;
    int id;
    item() {}
    item(double a, double b, int c) {
        u = a;
        w = b;
        id = c;
    }
};

item d[MAXN], a[MAXN];
int k, n;
double kek;

bool comparatorl(item &a, item &b) {
    return (double(a.u) - double(a.w) * kek - (double(b.u) - double(b.w) * kek) > 0);
}

bool comparatorg(item &a, item &b) {
    return (double(a.u) - double(a.w) * kek - (double(b.u) - double(b.w) * kek) <= 0);
}

void merge_sort(int l, int r) {
    if (l == r) {
        return;
    }
    int m = (l + r) / 2;
    merge_sort(l, m);
    merge_sort(m + 1, r);
    int i = l, j = m + 1;
    for (int k = l; k <= r; k++) {
        if (i == m + 1) {
            a[k] = d[j++];
            continue;
        }
        if (j == r + 1) {
            a[k] = d[i++];
            continue;
        }
        if (comparatorg(d[i], d[j])) {
            a[k] = d[j++];
        } else {
            a[k] = d[i++];
        }
    }
    for (int i = l; i <= r; i++) {
        d[i] = a[i];
    }
}

bool check() {
    merge_sort(0, n - 1);
    double sum = 0;
    for (int i = 0; i < k; i++) {
        sum += d[i].u - d[i].w * kek;
    }
    return sum >= 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    #ifdef HOME
        freopen("input.txt", "rt", stdin);
    #endif
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> d[i].u >> d[i].w;
        d[i].id = i;
    }
    double l = 0.0, r = 1e6;
    while (fabs(r - l) > EPS) {
        kek = (l + r) / 2;
        if (check()) {
            l = kek;
        } else {
            r = kek;
        }
    }
    kek = l;
    merge_sort(0, n - 1);
    for (int i = 0; i < k; i++) {
        cout << d[i].id + 1 << ' ';
    }
    return 0;
}
