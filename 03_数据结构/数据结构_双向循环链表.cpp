#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prior;

    Node(const T& val = T()) : data(val), next(nullptr), prior(nullptr) {}
};

template<typename T>
class d_list {
private:
    Node<T>* head;   // 哨兵结点
    size_t sz;

public:
    // 构造函数
    d_list() : sz(0) {
        head = new Node<T>();
        head->next = head;
        head->prior = head;
    }

    // 拷贝构造
    d_list(const d_list<T>& other) : d_list() {
        Node<T>* cur = other.head->next;
        while (cur != other.head) {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    // 赋值运算符
    d_list<T>& operator=(const d_list<T>& other) {
        if (this == &other) {
            return *this;
        }

        clear();

        Node<T>* cur = other.head->next;
        while (cur != other.head) {
            push_back(cur->data);
            cur = cur->next;
        }
        return *this;
    }

    // 析构函数
    ~d_list() {
        clear();
        delete head;
        head = nullptr;
    }

    // 清空链表
    void clear() {
        Node<T>* cur = head->next;
        while (cur != head) {
            Node<T>* temp = cur;
            cur = cur->next;
            delete temp;
        }
        head->next = head;
        head->prior = head;
        sz = 0;
    }

    // 头插
    void push_front(const T& val) {
        Node<T>* newNode = new Node<T>(val);

        newNode->next = head->next;
        newNode->prior = head;

        head->next->prior = newNode;
        head->next = newNode;

        ++sz;
    }

    // 尾插
    void push_back(const T& val) {
        Node<T>* newNode = new Node<T>(val);

        newNode->next = head;
        newNode->prior = head->prior;

        head->prior->next = newNode;
        head->prior = newNode;

        ++sz;
    }

    // 在第 pos 个位置后插入
    // pos = 0 表示在第一个元素前面插入，可理解为头插位置
    bool insert(size_t pos, const T& val) {
        if (pos > sz) {
            return false;
        }

        Node<T>* cur = head;
        for (size_t i = 0; i < pos; ++i) {
            cur = cur->next;
        }

        Node<T>* newNode = new Node<T>(val);
        newNode->next = cur->next;
        newNode->prior = cur;

        cur->next->prior = newNode;
        cur->next = newNode;

        ++sz;
        return true;
    }

    // 删除第 pos 个元素，pos 从 1 开始
    bool removeAt(size_t pos) {
        if (pos < 1 || pos > sz) {
            return false;
        }

        Node<T>* cur = head->next;
        for (size_t i = 1; i < pos; ++i) {
            cur = cur->next;
        }

        cur->prior->next = cur->next;
        cur->next->prior = cur->prior;

        delete cur;
        --sz;
        return true;
    }

    size_t get_size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    void print() const {
        Node<T>* cur = head->next;
        while (cur != head) {
            cout << cur->data;
            if (cur->next != head) {
                cout << " ";
            }
            cur = cur->next;
        }
        cout << endl;
    }
};

int main() {
    d_list<int> lst;

    lst.push_back(10);
    lst.push_back(20);
    lst.push_front(5);
    lst.print();   // 5 10 20

    lst.insert(2, 15); // 在第2个位置后插入，效果：5 10 15 20
    lst.print();

    lst.removeAt(3);   // 删除第3个元素
    lst.print();       // 5 10 20

    cout << "size = " << lst.get_size() << endl;

    return 0;
}