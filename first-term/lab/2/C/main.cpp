#include <bits/stdc++.h>

using namespace std;

vector <int> d;

int partition(int l, int r, vector <int> &a) {
    int id = (r + l) / 2;
    int x = a[id];
    int i = l, j = r;
    int res = id;
    while (i <= j) {
        while (a[i] < x) {
            i++;
        }
        while (a[j] > x) {
            j--;
        }
        if (i >= j)
            break;
        if (i ==  id) {
            res = j;
        } else if (j == id) {
            res = i;
        }
        swap(a[i++], a[j--]);
    }
    return res;
}

int kth(int k) {
    int l = 0, r = int(d.size());
    while (true) {
        int m = partition(l, r - 1, d);
        if (m == k) {
            return d[m];
        } else if (k > m) {
            r = m;
        } else {
            l = m + 1;
        }
    }
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("kth.in", "rt", stdin);
    freopen("kth.out", "wt", stdout);
#endif
    int n, k;
    cin >> n >> k;
    d.resize(n);
    int a, b, c, a1, a2;
    cin >> a >> b >> c >> a1 >> a2;
    d[0] = a1;
    d[1] = a2;
#ifdef HOME
    cout << d[0] << ' ' << d[1] << ' ';
#endif
    for (int i = 2; i < n; i++) {
        d[i] = d[i - 2] * a + d[i - 1] * b + c;
#ifdef HOME
        cout << d[i] << ' ';
#endif
    }
#ifdef HOME
    cout << "\n";
#endif
    cout << kth(k - 1);
    return 0;
}
