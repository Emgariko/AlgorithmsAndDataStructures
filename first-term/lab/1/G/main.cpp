#include <iostream>

using namespace std;

template <typename T> struct myvector {
    T *begin;
    size_t length, capacity;
    T operator[](size_t i) {
        return begin[i];
    }
    myvector() {
        length = 0;
        capacity = 1;
        begin = (T*)malloc(1 * sizeof(T));
    }
    void add(T x) {
        if (length != capacity) {
            begin[length++] = x;
        } else {
            capacity *= 2;
            T *nw = (T*)malloc(capacity * sizeof(T));
            for (size_t i = 0; i < length; i++) {
                nw[i] = begin[i];
            }
            nw[length++] = x;
            free(begin);
            begin = nw;
        }
    }
    T pop() {
        length--;
        if (length * 4 == capacity) {
            capacity /= 2;
            T *nw = (T*)malloc(capacity * sizeof(T));
            for (size_t i = 0; i <= length; i++) {
                nw[i] = begin[i];
            }
            free(begin);
            begin = nw;
        }
        return begin[length];
    }
    void clear() {
        free(begin);
        length = 0;
        capacity = 1;
        begin = (T*)malloc(1 * sizeof(T));
    }
    T back() {
        return begin[length - 1];
    }
    bool empty() {
        return length == 0;
    }
    size_t get_length() {
        return length;
    }
};

template <typename T> struct mystack {
    myvector <T> d;
    mystack() {}
    void add(T x) {
        d.add(x);
    }
    T pop() {
        return d.pop();
    }
    void clear() {
        d.clear();
    }
    T top() {
        return d.back();
    }
    bool empty() {
        return d.empty();
    }
    size_t length() {
        return d.get_length();
    }
};

template <typename T> struct myminstack {
    mystack <pair<T, T>> d;
    void add(T x) {
        T mn;
        if (int(d.length()) != 0) {
            T y = d.top().second;
            if (x < y) {
                mn = x;
            } else {
                mn = y;
            }
        } else {
            mn = x;
        }
        d.add({x, mn});
    }
    T get_min() {
        return d.top().second;
    }
    void pop() {
        d.pop();
    }
    void clear() {
        d.clear();
    }
    pair <T, T> top() {
        return d.top();
    }
    size_t length() {
        return d.length();
    }
    bool empty() {
        return d.empty();
    }
};

template <typename T> struct myminqueue {
    myminstack <T> s1, s2;
    void add(T x) {
        s1.add(x);
    }
    void pop() {
        if (s2.length() == 0) {
            while (!s1.empty()) {
                pair <T, T> element = s1.top();
                s2.add(element.first);
                s1.pop();
            }
        }
        s2.pop();
    }
    T get_min() {
        T x, y;
        if (int(s1.length()) != 0 && int(s2.length()) != 0) {
            x = s1.top().second, y = s2.top().second;
            if (x > y) {
                x = y;
            }
            return x;
        }
        if (int(s1.length()) == 0 && int(s2.length()) != 0) {
            y = s2.top().second;
            return y;
        }
        if (int(s2.length()) == 0 && int(s1.length()) != 0) {
            x = s1.top().second;
            return x;
        }
        T z = T();
        return z;
    }
};

myminqueue <int> d;

int main() {
    #ifdef HOME
    freopen("input.txt", "rt", stdin);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, k, a, b, c;
    cin >> n >> m >> k >> a >> b >> c;
    int p1 = 1, p2 = 1;
    long long sum = 0;
    if (m >= k) {
        int cnt = 0;
        for (int i = 0; i < k; i++) {
            int x;
            cin >> x;
            if (i == 0) {
                p2 = x;
            } else if (i == 1) {
                p1 = x;
            } else {
                p2 = p1;
                p1 = x;
            }
            d.add(x);
            cnt++;
        }
        for (int i = cnt; i < m; i++) {
            int x = a * p2 + b * p1 + c;
            p2 = p1;
            p1 = x;
            d.add(x);
            cnt++;
        }
        for (int i = cnt; i < n; i++) {
            sum += d.get_min();
            d.pop();
            int x = a * p2 + b * p1 + c;
            p2 = p1;
            p1 = x;
            d.add(x);
            cnt++;
        }
        sum += d.get_min();
    } else {
        int cnt = 0;
        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            if (i == 0) {
                p2 = x;
            } else if (i == 1) {
                p1 = x;
            } else {
                p2 = p1;
                p1 = x;
            }
            d.add(x);
            cnt++;
        }
        for (int i = cnt; i < k; i++) {
            sum += d.get_min();
            d.pop();
            int x;
            cin >> x;
            if (i == 0) {
                p2 = x;
            } else if (i == 1) {
                p1 = x;
            } else {
                p2 = p1;
                p1 = x;
            }
            d.add(x);
            cnt++;
        }
        for (int i = cnt; i < n; i++) {
            sum += d.get_min();
            d.pop();
            int x = a * p2 + b * p1 + c;
            p2 = p1;
            p1 = x;
            d.add(x);
            cnt++;
        }
        sum += d.get_min();
    }
    cout << sum;
    return 0;
}
