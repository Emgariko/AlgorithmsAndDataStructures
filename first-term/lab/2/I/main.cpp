#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 2e18;

vector <ll> a, b, t, v;

int partition(int l, int r, vector <ll> &a) {
    int id = l + rand() % (r - l + 1);
    ll x = a[id];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < x) {
            i++;
        }
        while (a[j] > x) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swap(a[i++], a[j--]);
    }
    return j;
}

void qsort(int l, int r, vector <ll> &a) {
    if (l >= r) return;
    int q = partition(l, r, a);
    qsort(l, q, a);
    qsort(q + 1, r, a);
}


bool check(ll x, int p, int n) {
    int m = a.size();
    for (int i = 0; i < m; i++) {
    	if (a[i] == 0 && (x - t[i] - b[i] < 0)) {
    		v[i] = 0;
    	} else if (a[i] == 0 && (x - t[i] - b[i] >= 0)) {
            v[i] = INF;
        } else {
            v[i] = (x - t[i] - b[i]) / a[i];
        }
        if (v[i] < 0) {
            v[i] = 0;
        }
    }
    qsort(0, m - 1, v);
    long long sum = 0;
    for (int i = m - 1; i >= max(m - n, 0); i--) {
        if (v[i] == INF) {
            return true;
        }
        sum += v[i];
        if (sum >= p) {
        	return true;
        }
    }
    return sum >= p;
}

int main() {
	srand(time(NULL));
    int m;
    cin >> m;
    a.resize(m);
    b.resize(m);
    t.resize(m);
    v.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> t[i];
    }
    int n, p;
    cin >> n >> p;
    ll l = -1, r = 1e15, mid;
    while (r - l > 1) {
        mid = (l + r) / 2;
        if (check(mid, p, n)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r;
    return 0;
}
