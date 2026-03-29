#include <iostream>
#include <cstdlib>
#include <exception>

using namespace std;

template<typename T>
class dyArray {
private:
    //member of data
    T* _pData = nullptr;//指针，指向heap中的内存空间首地址
    size_t _nSize = 0;//数组中元素个数
    size_t _nCapacity = 0;//容量
public:
    //member of function
    //ctor
    dyArray(size_t n = 10);
    //ctor overload n为申请空间中的元素个数 val为数组中各元素的初始值
    dyArray(size_t n, const T& val);
    //copy ctor
    dyArray(const dyArray& obj);
    //dtor
    ~dyArray();

private:
    //memory allocate 分配内存空间
    void memset(size_t n) {
        release();
        //invoke operator operator new
        if (n > 0) { _pData = new T[n]; }
    }
    //dump memory 释放内存空间
    void release() {
        if (_pData) { delete[] _pData; _pData = nullptr; }
    }

public:
    //member of function
    //overload operator []
    //nidx为下标索引
    T& operator[](size_t nidx) {
        return _pData[nidx];
    }
    const T& operator[](size_t nidx)const {
        return _pData[nidx];
    }
    //overload operator=
    //rhs source of array
    dyArray<T>& operator=(const dyArray<T>& rhs);

public:
    //get begin & end
    T* begin() { return _pData; }
    const T* begin()const { return _pData; }
    T* end() { return _pData + _nSize; }
    const T* end()const { return _pData + _nSize; }
    //get size 获取数组中元素个数
    size_t size()const { return _nSize; }
    //get capacity 获取数组中容量个数
    size_t capacity()const { return _nCapacity; }


    //append 在尾部增加一个数据
    void push_back(const T& val);
    //delete at 删除指定位置(nidx)的元素
    bool deleteAt(size_t nidx);
    void removeAll();//移除所有的元素
    //insert value 在指定位置（nidx）后面插入一个数据val
    bool insert(size_t nidx, const T& val);

public:
    //conversion function
    operator T* () { return _pData; }
    operator const T* ()const { return _pData; }

private:
    //扩容 当战备池用完后，需要扩容时，进行2倍扩容
    void expansion();

};

template <typename T>
dyArray<T>::dyArray(size_t n) {
    _nSize = (n> 0) ? n : 1;
    _nCapacity = _nSize;
    _pData = new T[_nSize];
}

//ctor overload n为申请空间中的元素个数 val为数组中各元素的初始值
template <typename T>
dyArray<T>::dyArray(size_t n, const T& val) {
    _nSize = n;
    _nCapacity = n;
    _pData = new T[_nCapacity];
    for (int i = 0; i < _nSize; i++) {
        _pData[i] = val;
    }
}

//copy ctor
template <typename T>
dyArray<T>::dyArray(const dyArray& obj) {
    _nSize = obj._nSize;
    _nCapacity = obj._nCapacity;          // 复制容量
    _pData = new T[_nCapacity];
    for (int i = 0; i < _nSize; i++) {
        _pData[i] = obj[i];
    }
}

//dtor
template <typename T>
dyArray<T>::~dyArray() {
    if (_pData) {
        delete[]_pData;
        _pData = NULL;
    }
}

template <typename T>
dyArray<T>& dyArray<T>::operator=(const dyArray<T>& rhs) {
    {
        if (this == & rhs) { return *this; }

        delete[]_pData;
        _nSize = rhs._nSize;
        _nCapacity = rhs._nCapacity;
        _pData = new T[_nCapacity];
        for (int i = 0; i < _nSize; i++) {
            _pData[i] = rhs._pData[i];
        }
        return *this;
    }
}


template <typename T>
//append 在尾部增加一个数据
void dyArray<T>::push_back(const T& val) {
    if (_nSize >= _nCapacity) {
        expansion();
    }
    _pData[_nSize++] = val;
}


//delete at 删除指定位置(nidx)的元素
template <typename T>
bool dyArray<T>::deleteAt(size_t nidx) {
    if (nidx >= _nSize) {
        return false; 
    }

    for (size_t i = nidx; i < _nSize - 1; ++i) {
        _pData[i] = _pData[i + 1];
    }

   --_nSize;
   _pData[_nSize] = T();
    return true;
}

template <typename T>
void dyArray<T>::removeAll() {
    if (_pData) {
        delete[]_pData;
        _pData = NULL;
    }
    _nSize = 0;
    _nCapacity = 0;
}


//insert value 在指定位置（nidx）后面插入一个数据val
template <typename T>
bool dyArray<T>::insert(size_t nidx, const T& val) {
    if (nidx > _nSize) return false;
    if (_nSize >= _nCapacity) {
        expansion();
    }
    for (size_t i = _nSize; i > nidx; --i) {
        _pData[i] = _pData[i - 1];
    }
    _pData[nidx + 1] = val;
    ++_nSize;
    return 1;
}

template <typename T>
void dyArray<T>::expansion() {
    size_t newCapacity = (_nCapacity == 0) ? 1 : _nCapacity * 2;
    T* newData = new T[newCapacity]();

    for (size_t i = 0; i < _nSize; ++i) {
        newData[i] = _pData[i];
    }


    delete[] _pData;

    _pData = newData;
    _nCapacity = newCapacity;
}


template<typename T>
void display(T* first, T* last) {
    T* start = first;
    while (start != last) {
        cout << *start << " ";
        start++;
    }
    cout << endl;
}

int main() {
    int n = 10;
    int val = 0;
    int val1 = 0;
    cin >> n >> val;

    size_t npos = 0;
    cin >> npos >> val1;
    dyArray<int> ar(n, val);

    int* first = ar.begin();
    int* last = ar.end();
    display(first, last);

    ar.insert(npos, val1);

    first = ar.begin();
    last = ar.end();
    display(first, last);
    size_t nc = ar.capacity();
    for (size_t i = 0; i < nc; ++i)
    {
        ar.push_back(i);
    }

    cout << ar.size() << " " << ar.capacity() << endl;

    first = ar.begin();
    last = ar.end();
    display(first, last);

    return 0;
}