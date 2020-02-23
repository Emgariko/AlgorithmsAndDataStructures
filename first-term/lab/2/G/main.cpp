#include <bits/stdc++.h>

using namespace std;

int K = 65536;

unsigned int val;
vector <int> cnt, head, cur, nw;
vector <unsigned int> d;
vector <vector<unsigned int>> b;

void bucketsort(vector <vector<unsigned int>> &b, int m, int k) {
    int iteration = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (iteration == k) break;
        for (int j = 0; j < int(cnt.size()); j++) {
            cnt[j] = 0;
        }
        for (int j = 0; j < int(b.size()); j++) {
            cnt[b[j][i]]++;
        }
        head[0] = 0;
        for (int j = 1; j < K; j++) {
            head[j] = head[j - 1] + cnt[j - 1];
        }
        for (int j = 0; j < int(b.size()); j++) {
            nw[head[b[cur[j]][i]]++] = cur[j];
        }
        for (int j = 0; j < int(b.size()); j++) {
            cur[j] = nw[j];
        }
        iteration++;
    }
}


unsigned int nextRand24(unsigned int a, unsigned int b, unsigned int& v) {
    v = v * a + b;
    return v >> 8;
}

unsigned int nextRand32(unsigned int a, unsigned int b, unsigned int& v) {
    unsigned int aa = nextRand24(a, b, v);
    unsigned int bb = nextRand24(a, b, v);
    return (aa << 8) ^ bb;
}

int main() {
    int t, n;
    cin >> t >> n;
    d.resize(n);
    cur.resize(n);
    cnt.resize(K);
    head.resize(K);
    cur.resize(n);
    nw.resize(n);
    b.resize(n, vector<unsigned int>(2, 0));
    for (int i = 0; i < t; i++) {
        unsigned int a, bb;
        cin >> a >> bb;
        for (int j = 0; j < n; j++) {
            d[j] = nextRand32(a, bb, val);
            cur[j] = j;
            b[j][0] = d[j] / K;
            b[j][1] = d[j] % K;
        }
        unsigned long long res = 0;
        bucketsort(b, 2, 2);
        for (int j = 0; j < n; j++) {
            unsigned long long vall = b[cur[j]][0] * K + b[cur[j]][1];
            res += (j + 1) * vall;
        }
        cout << res << "\n";
    }
    return 0;
}
