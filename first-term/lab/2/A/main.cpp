#include <bits/stdc++.h>

using namespace std;

int partition(int l, int r, vector <int> &a) {
    int id = l + rand() % (r - l + 1);
    int x = a[id];
    int i = l, j = r;
    while (i <= j) {
        while (a[i] < x) {
            i++;
        }
        while (a[j] > x) {
            j--;
        }
       	if (i >= j)
        	break;
        swap(a[i++], a[j--]);
    }
    return j;
}

void qsort(int l, int r, vector <int> &a) {
    if (l >= r) return;
    int q = partition(l, r, a);
    qsort(l, q, a);
    qsort(q + 1, r, a);
}

vector <int> d;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif
	srand(time(NULL));
    int n;
    cin >> n;
    d.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    qsort(0, n - 1, d);
    for (int i = 0; i < n; i++) {
        cout << d[i] << ' ';
    }
    return 0;
}
