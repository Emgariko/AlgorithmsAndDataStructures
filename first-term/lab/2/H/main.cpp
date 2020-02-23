#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector <unsigned int> d, a;

unsigned int nextRand24(unsigned int aa, unsigned int b, unsigned int& cur) {
    cur = cur * aa + b;
    return cur >> 8;
}

ll ans = 0;

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
            if (d[i - 1] > d[j]) {
                ans++;
            }
            a[k] = d[j++];
            continue;
        }
        if (j == r + 1) {
            a[k] = d[i++];
            continue;
        }
        if (d[i] > d[j]) {
            ans += m - i + 1;
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
    int n, m;
    unsigned int aa, b;
    cin >> n >> m >> aa >> b;
    unsigned int cur = 0;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        unsigned int x = nextRand24(aa, b, cur) % m;
        d.push_back(x);
    }
    merge_sort(0, n - 1);
    cout << ans;
    return 0;
}
