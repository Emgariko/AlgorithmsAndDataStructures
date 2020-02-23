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

template <typename T> struct myqueue {
	T *begin;
    size_t l, r, capacity;
    myqueue() {
    	capacity = 1;
    	begin = (T*)malloc(1 * sizeof(T));
    	l = 0;
    	r = 0;
    }
   	void push(T x) {
   		if ((r - l + 1) != capacity) {
            begin[r % capacity] = x;
            r++;
        } else {
            capacity *= 2;
            T *nw = (T*)malloc(capacity * sizeof(T));
            for (size_t i = 0; i < r - l + 1; i++) {
                nw[i] = begin[(l + i) % capacity];
            }
            r = r - l + 1;
            nw[r++] = x;
            free(begin);
            begin = nw;
        }
   	}
   	T pop() { 
   		if ((r - l + 1) * 4 == capacity) {
   			capacity /= 2;
            T *nw = (T*)malloc(capacity * sizeof(T));
            for (size_t i = 0; i < r - l + 1; i++) {
                nw[i] = begin[(l + i) % capacity];
            }
            free(begin);
            begin = nw;
   		}
   		l++;
		return begin[l - 1];
   	}
};

myqueue <int> d;

int main() {
	#ifdef HOME
	freopen("input.txt", "rt", stdin);
	#endif
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		char x;
		cin >> x;
		if (x == '+') {
			int y;
			cin >> y;
			d.push(y);
		} else if (x == '-') {
			cout << d.pop() << "\n";
		}
	}
	return 0;
}
