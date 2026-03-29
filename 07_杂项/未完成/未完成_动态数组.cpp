#include <iostream>
#include<algorithm>

using namespace std;
 
template<typename T>

class dy_arr {
private:
	T* p_list = NULL;
	size_t n_size = 0;

public:
	dy_arr (size_t ini_n_size = 10) {   //类内声明可以不用T
		if (n_size <= 0) {
			n_size = 1;
		}
		p_list = new T[n_size];
	}
	dy_arr(const dy_arr& obj) {
		n_size = obj.n_size;
		p_list = new T[n_size];
		for (int i = 0; i < n_size; i++) {
			p_list[i] = obj.p_list;;
		}
	}
	~dy_arr() {
		if (p_list) {
			delete[]p_list;
			p_list = NULL;
		}
	}

	dy_arr operator=(const dy_arr<T> & obj) {
		if (this == &obj) { return *this; }

		delete[]p_list;
		n_size = obj.n_size;
		p_list = new T[n_size];
		for (int i = 0; i < n_size; i++) {
			p_list[i] = obj.n_list[i];
		}
		return *this;
	}

	operator[](size_t n) {
		return p_list[n];
	}
	const operator[](size_t n) const{
		return p_list[n];
	}
	operator T* () {
		return p_list;
	}
	operator const T* () const{
		return p_list;
	}

	int bin_search(const T list[], int n, const T& target) {
		int low = 0;
		int high = n - 1;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (list[mid] == target) { return mid; }
			else if (list[mid] > target) {
				low = mid + 1;
			}
			else (list[mid] < target) {
				high = mid - 1;
			}
		}
	}

	void insert()
};