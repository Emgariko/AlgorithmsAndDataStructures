#include <bits/stdc++.h>

using namespace std;

vector <string> d;
vector <vector<string>> a;
vector <int> cnt, head, cur, nw;

void bucketsort(vector <string> &b, int m, int k) {
    int iteration = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (iteration == k) break;
        for (int j = 0; j < int(cnt.size()); j++) {
            cnt[j] = 0;
        }
        for (int j = 0; j < int(b.size()); j++) {
            cnt[b[j][i] - 'a']++;
        }
        head[0] = 0;
        for (int j = 1; j < 26; j++) {
            head[j] = head[j - 1] + cnt[j - 1];
        }
        for (int j = 0; j < int(b.size()); j++) {
            nw[head[b[cur[j]][i] - 'a']++] = cur[j];
        }
        for (int j = 0; j < int(b.size()); j++) {
        	cur[j] = nw[j];
        }
        iteration++;
    }
}

int main() {
	int n, m, k;
    cin >> n >> m >> k;
    d.resize(n);
    cnt.resize(26);
    head.resize(26);
    cur.resize(n);
    nw.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        cur[i] = i;
    }
    bucketsort(d, m, k);
    for (int i = 0; i < n; i++) {
        cout << d[cur[i]] << "\n";
    }
    return 0;
}
