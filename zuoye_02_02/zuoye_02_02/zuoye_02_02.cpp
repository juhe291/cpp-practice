#include <iostream>
#include <string>
using namespace std;

// 排序函数模板
template <typename T>
void Sort(T* A, int n, bool f) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (f) { 
                if (A[j] > A[j + 1]) {
                    T temp = A[j];
                    A[j] = A[j + 1];
                    A[j + 1] = temp;
                    swapped = true;
                }
            }
            else { 
                if (A[j] < A[j + 1]) {
                    T temp = A[j];
                    A[j] = A[j + 1];
                    A[j + 1] = temp;
                    swapped = true;
                }
            }
        }
        if (!swapped) break;
    }
}

// 自定义类模板：Person
template <typename T>
class Person {
private:
    string name;
    T age;
public:
    // 重载 << 运算符，方便输出
    friend ostream& operator<<(ostream& os, const Person& p) {
        os << p.name << ":" << p.age;
        return os;
    }
    Person(const string& n,const T& a):name(n),age(a){}

    bool operator>(const Person& obj) const{
        return age > obj.age;
    }
    bool operator<(const Person& obj) const {
        return age < obj.age;
    }
};

// 打印数组内容的函数模板
template <typename T>
void printArray(T* A, int n) {
    for (int i = 0; i < n; i++) {
        cout << A[i];
        if (i == n - 1) { cout << endl; }
        else { cout << " "; }
    }
}

int main() {
    // 测试 int 类型数组
    int intArr[] = { 5, 2, 9, 1, 5 };
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    cout << "Original int array: ";
    printArray(intArr, intSize);
    Sort(intArr, intSize, true); // 升序排序
    cout << "Sorted int array (ascending): ";
    printArray(intArr, intSize);

    // 测试 double 类型数组
    double doubleArr[] = { 3.2, 1.5, 4.8, 1.2 };
    int doubleSize = sizeof(doubleArr) / sizeof(doubleArr[0]);
    cout << "Original double array: ";
    printArray(doubleArr, doubleSize);
    Sort(doubleArr, doubleSize, false); // 降序排序
    cout << "Sorted double array (descending): ";
    printArray(doubleArr, doubleSize);

    // 测试自定义类模板 Person 的对象数组
    Person<int> personArr[] = {
        Person<int>("Alice", 25),
        Person<int>("Bob", 30),
        Person<int>("Charlie", 20)
    };
    int personSize = sizeof(personArr) / sizeof(personArr[0]);
    cout << "Original Person array: ";
    printArray(personArr, personSize);
    Sort(personArr, personSize, true); // 升序排序
    cout << "Sorted Person array (ascending): ";
    printArray(personArr, personSize);
    system("pause");
    return 0;
}