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

mystack <char> d;
string s;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	while (cin >> s) {
		d.clear();
		bool ok = true;
		int n = int(s.length());
		for (int i = 0; i < n; i++) {
			if (s[i] == '[' || s[i] == '(')
				d.add(s[i]);
			if (s[i] == ']') {
				if (d.top() == '[') {
					d.pop();
				} else {
					ok = false;
					break;
				}
			}
			if (s[i] == ')') {
				if (d.top() == '(') {
					d.pop();
				} else {
					ok = false;
					break;
				}
			}
		}
		if (d.empty() && ok) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
	return 0;
}
