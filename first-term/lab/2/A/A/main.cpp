#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

int d[MAXN], a[MAXN];

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
        if (d[i] > d[j]) {
            a[k] = d[j++];
        } else {
            a[k] = d[i++];
        }
    }
    for (int i = l; i <= r; i++) {
        d[i] = a[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    #ifdef HOME
       // freopen("input.txt", "rt", stdin);
    #endif
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    merge_sort(0, n - 1);
    for (int i = 0; i < n; i++) {
        cout << d[i] << ' ';
    }
    return 0;  
}
