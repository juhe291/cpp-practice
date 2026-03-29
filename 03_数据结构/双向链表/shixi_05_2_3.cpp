#include<iostream>
using namespace std;

template<typename T>
struct Node {
	T data;
	T* next = NULL;
	T* prior = NULL;
	Node(const T& val = T()) :data(val), next(NULL), prior(NULL) {}
};

template<typename T>
class d_list {
private:
	Node<T>* head = NULL;
	size_t size = 0;
public:
	//构造函数
	d_list(size_t size = 0) {
		head = new Node<T>();
		head->next = head;
		head->prior = head;
	}
	//拷贝构造函数
	d_list(const d_list<T>& obj) {}
	//析构函数
	~d_list() {
		auto current = head;
		while (current != head) {
			auto temp = current;
			current = current->next;
			delete temp;
		}
		delete head;
	}
	void push_front(const T& val) {
		Node<T> n_Node = new Node<T>(val);
		n_Node.next = head->next;
		n_Node.prior = head;
		head->next->prior = n_Node;
		head->next = n_Node;
		size++;
	}
	void push_back(const T& val) {
		Node<T> n_Node = new Node<T>(val);
		n_Node.next = head;
		n_Node.prior = head->prior;
		head->prior->next = n_Node;
		head->prior = n_Node;
		++size;
	}
	bool insert(size_t pos, const T& val) {
		size_t con = 0;
		if (pos > size) { return false; }
		else {
			Node<T> n_Node = new Node<T>(val);
			Node<T>* cur = head;
			while (con != pos) {
				con++;
				cur = cur->next;
			}
			n_Node.prior = cur;
			n_Node.next = cur->next;
			cur->next = n_Node;
			cur->next->prior = n_Node;
			++size;
			return true;
		}
	}
	bool removeAt(size_t pos) {
		size_t con = 0;
		if (pos > size) { return false; }
		else {
			Node<T>* cur = head;
			while (con != pos) {
				con++;
				cur = cur->next;
			}
			cur->prior = cur->next;
			cur->next = cur->prior;
			delete cur;
			++size;
			return true;
		}
	}

	size_t get_size() const {
		return size;
	}
};

template<typename T>
bool Sort(const d_list<T>& b) {
	int n = b.get_size();
}