#include <iostream>

using namespace std;

template <typename T> struct Node {
	T value;
	Node <T> *prev;
	Node() {
		prev = nullptr;
	}
	Node(T x){
		value = x;
		prev = nullptr;
	}
};

template <typename T> struct List {
	Node <T> *root;
	Node <T> *leaf;
	List() {
		root = new Node <T> ();
		leaf = root;
	}
	void add(T x) {
		Node <T> *new_node = new Node <T> (x);
		new_node->prev = leaf;
		leaf = new_node;
	}
	T pop() {
		Node <T> * buf = leaf;
		T deleted = leaf->value;
		buf = buf->prev;
		delete(leaf);
		leaf = buf;
		return deleted;
	}
};

template <typename T> struct mystack {
	List <T> d;
	mystack() {}
	void add(T x) {
		d.add(x);
	}
	T pop() {
		return d.pop();
	}
};

mystack <int> d;

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
			d.add(y);
		} else {
			cout << d.pop() << "\n";
		}
	}
	return 0;
}
