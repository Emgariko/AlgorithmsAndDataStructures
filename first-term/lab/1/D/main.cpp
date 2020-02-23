#include <iostream>

using namespace std;

template <typename T> struct Node {
	T value;
	Node <T> *prev;
	Node <T> *next;
	Node() {
		prev = nullptr;
		next = nullptr;
	}
	Node(T x){
		value = x;
		prev = nullptr;
		next = nullptr;
	}
};

template <typename T> struct List {
	Node <T> *root;
	Node <T> *leaf;
	List() {
		root = new Node <T> ();
		leaf = new Node <T> ();
		root->next = leaf;
		leaf->prev = root;
		root->prev = root;
		leaf->next = leaf;
	}
	void add_back(T x) {
		Node <T> *new_node = new Node <T> ();
		new_node->value = x;
		new_node->prev = leaf->prev;
		(leaf->prev)->next = new_node;
		new_node->next = leaf;
		leaf->prev = new_node;
	}
	T pop_front() {
		Node <T> *deleted = root->next;
		root->next = root->next->next;
		root->next->prev = root;
		T res = deleted->value;
		delete(deleted);
		return res;
	}
};

template <typename T> struct myqueue {
	List <T> d;
	myqueue() {}
	void add(T x) {
		d.add_back(x);
	}
	T pop() {
		return d.pop_front();
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
			d.add(y);
		} else {
			cout << d.pop() << "\n";
		}
	}
	return 0;
}
