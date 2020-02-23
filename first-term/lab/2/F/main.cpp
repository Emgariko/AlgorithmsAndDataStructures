#include <bits/stdc++.h>

using namespace std;

vector <int> d;

int main() {
    int n;
    cin >> n;
    d.resize(n);
    for (int i = 0; i < n; i++) {
        d[i] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        swap(d[i], d[i / 2]);
    }
    for (int i = 0; i < n; i++) {
        cout << d[i] << ' ';
    }
    return 0;
}
