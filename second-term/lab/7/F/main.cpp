#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

typedef long long int64;

const int MAXN = 5e5 + 100;
const int MAXS = 4 * MAXN;
const int INF = 2e9 + 123;

struct matrix {
    int a, b, c, d;
};

matrix o = {1, 0, 0, 1};

int MOD;
matrix k[MAXN];
matrix tree[MAXS];

string s;

matrix p(matrix a1, matrix b1) {
    int a, b, c, d, e, f, g, h;
    a = a1.a;
    b = a1.b;
    c = a1.c;
    d = a1.d;
    e = b1.a;
    f = b1.b;
    g = b1.c;
    h = b1.d;
    int a2, b2, c2, d2;
    a2 = (a * e + b * g) % MOD;
    b2 = (a * f + b * h) % MOD;
    c2 = (c * e + d * g) % MOD;
    d2 = (c * f + d * h) % MOD;
    return {a2, b2, c2, d2};
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = k[tl];
    } else {
        int mid = (tl + tr) / 2;
        build(2 * v + 1, tl, mid);
        build(2 * v + 2, mid + 1, tr);
        tree[v] = p(tree[2 * v + 1], tree[2 * v + 2]);
    }
}

matrix get_p(int v, int tl, int tr, int l, int r) {
    if (tl == l && tr == r) {
        return tree[v];
    } else {
        int mid = (tl + tr) / 2;
        matrix ans = o;
        if (l <= mid)
            ans = p(ans, get_p(2 * v + 1, tl, mid, l, min(r, mid)));
        if (r >= mid + 1)
            ans = p(ans, get_p(2 * v + 2, mid + 1, tr, max(l, mid + 1), r));
        return ans;
    }
}

void print(matrix a) {
    printf("%d %d \n%d %d \n", a.a, a.b, a.c, a.d);
}

int main() {
    int n, a, b, c, d, m;
    cin >> MOD >> n >> m;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        k[i] = {a, b, c, d};
    }
    build(0, 0, n - 1);
    int l, r;
    matrix ans;
    for (int i = 0; i < m; i++) {
        cin >> l >> r;
        l--;
        r--;
        ans = o;
        ans = get_p(0, 0, n - 1, l, r);
        print(ans);
    }
    return 0;
}
