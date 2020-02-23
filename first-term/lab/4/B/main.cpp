#include <bits/stdc++.h>

using namespace std;

const int INF = int(2e9 + 123);

vector <int> d, a, pos, pre, ans;

int main() {
#ifdef HOME
    freopen("input.txt", "rt", stdin);
#else
    freopen("lis.in", "rt", stdin);
    freopen("lis.out", "wt", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    d.resize(n);
    a.resize(n);
    pos.resize(n);
    pre.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        a[i] = INF;
        pre[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int x = lower_bound(a.begin(), a.end(), d[i]) - a.begin();
        if (a[x] > d[i]) {
            a[x] = d[i];
            pos[x] = i;
            if (x > 0) {
                pre[i] = pos[x - 1];
            }
        }
    }
    int x = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != INF)
            x = i;
    }
    x = pos[x];
    while (true) {
        if (x == -1) { break; }
        ans.push_back(d[x]);
        x = pre[x];
    }
    reverse(ans.begin(), ans.end());
    cout << int(ans.size()) << "\n";
    for (int i = 0; i < int(ans.size()); i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}
