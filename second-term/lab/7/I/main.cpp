#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int K = 1000;
const int MAXS = 1e6 + 123;
const int MAXM = 2e5 + 1;

struct querry {
    int l;
    int r;
    int id;
    querry() {}
    querry(int ll, int rr, int idd) {
        l = ll;
        r = rr;
        id = idd;
    }
    bool operator < (const querry & other) {
    	if (l / K != other.l / K) {
    		return l < other.l;
    	}
  		return r < other.r;

        // return ((l / K != other.l / K) && (l < other.l)) || (r < other.r);
    }
};

ll cnt[MAXS];
querry d[MAXM];
ll a[MAXM];
ll ans[MAXS];

ll func = 0;
int n;

void del(int i) {
    if (i < 0 || i > n) { return; }
    func -= (1ll * cnt[(size_t) a[i]]) * (1ll * cnt[(size_t) a[i]] * a[i]);
    cnt[(size_t) a[i]]--;
    func += (1ll * cnt[(size_t) a[i]]) * (1ll * cnt[(size_t) a[i]] * a[i]);
}

void add(int i) {
    if (i < 0 || i > n) { return; }
    func -= (1ll * cnt[(size_t) a[i]]) * (1ll * cnt[(size_t) a[i]] * a[i]);
    cnt[(size_t) a[i]]++;
    func += (1ll * cnt[(size_t) a[i]]) * (1ll * cnt[(size_t) a[i]] * a[i]);
}

ll get_ans() {
    return func;
}

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> d[i].l >> d[i].r;
        d[i].l--;
        d[i].r--;
        d[i].id = i;
    }
    sort(d, d + m);
    int L = d[0].l, R = d[0].r;
    for (int i = L; i <= R; i++) {
        add(i);
    }
    ans[d[0].id] = func;
    for (int i = 1; i < m; i++) {
        int l = d[i].l, r = d[i].r;
        if (L > l) {
        	// L - added
        	for (int j = L - 1; j >= l; j--) {
        		add(j);
        	}
        }
        if (L < l) {
        	for (int j = L; j < l; j++) {
        		del(j);
        	}
        }
        if (R > r) {
        	for (int j = R; j > r; j--) {
        		del(j);
        	}
        }
        if (R < r) {
        	for (int j = R + 1; j <= r; j++) {
        		add(j);
        	}
        }
        ans[d[i].id] = get_ans();
        L = l;
        R = r;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}
