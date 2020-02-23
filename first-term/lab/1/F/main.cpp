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
};

mystack <int> d;
string s;

bool is_digit(char x) {
    return '0' <= x && x <= '9';
}

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
    while (cin >> s) {
        int val;
        if (is_digit(s[0])) {
            val = int(s[0] - '0');
            d.add(val);
        } else {
            int y = d.top();
            d.pop();
            int x = d.top();
            d.pop();
            int res = 0;
            if (s == "+") {
                res = x + y;
            } else if (s == "-") {
                res = x - y;
            } else if (s == "*") {
                res = x * y;
            }
            d.add(res);
        }
    }
    cout << d.top();
	return 0;
}
