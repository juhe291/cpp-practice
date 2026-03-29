#include<iostream>
#include<string>
using namespace std;

template<typename T>
T gcd(T a, T b) {
	if (!b) {
	    return a;
	}
	return gcd(b, a % b);
}
template<typename T>
class fraction{
private:
	T num = 0;
	T den = 0;
public:
	//构造函数
	fraction() = default;
	fraction(T num,T den=1):num(num),den(den){}
	//拷贝构造函数
	fraction(const fraction& obj) {}
	//析构函数
	~fraction(){}

	//"+"
	fraction operator+(const fraction&ref){
		T n_den = den * ref.den;
		T n_num = num * ref.den + ref.num * den;
		T gcd_ = gcd(n_den, n_num);
		if (gcd_ != n_den) {
			n_den = n_den / gcd_;
			n_num = n_num / gcd_;
		}
		return fraction(n_num, n_den);
	}
	//"-"
	fraction operator-(const fraction& ref) {
		T n_den = den * ref.den;
		T n_num = num * ref.den - ref.num * den;
		T gcd_ = gcd(n_den, n_num);
		if (gcd_ != n_den) {
			n_den = n_den / gcd_;
			n_num = n_num / gcd_;
		}
		return fraction(n_num, n_den);
	}
	//"*"
	fraction operator*(const fraction& ref) {
		T n_den = den * ref.den;
		T n_num = num * ref.num;
		T gcd_ = gcd(n_den, n_num);
		if(gcd_ != n_den) {
			n_den = n_den / gcd_;
			n_num = n_num / gcd_;
		}
		return fraction(n_num, n_den);
	}
	//"/"
	fraction operator/(const fraction& ref) {
		T n_den = den * ref.num;
		T n_num = num * ref.den;
		T gcd_ = gcd(n_den, n_num);
		if (gcd_ != n_den) {
			n_den = n_den / gcd_;
			n_num = n_num / gcd_;
		}
		return fraction(n_num, n_den);
	}
	//"=="
	bool operator==(const fraction& ref) {
		T gcd_1 = gcd(den, num);
		T den_1 = 0; T num_1 = 0; T den_2 = 0; T num_2 = 0;
		if (gcd_1 != den) {
			den_1 = den / gcd_1;
			num_1 = num / gcd_1;
		}
		T gcd_2 = gcd(ref.den, ref.num);
		if (gcd_2 != ref.den) {
			T den_2 = den / gcd_2;
			T num_2 = num / gcd_2;
		}
		if (den_1 == den_2 && num_1 == num_2) {
			return true;
		}
		else { return false; }
	}
	bool operator!=(const fraction& ref) {
		T gcd_1 = gcd(den, num);
		T den_1 = 0;T num_1 = 0;T den_2 = 0;T num_2 = 0;
		if (gcd_1 != den) {
			den_1 = den / gcd_1;
			num_1 = num / gcd_1;
		}
		T gcd_2 = gcd(ref.den, ref.num);
		if (gcd_2 != ref.den) {
			T den_2 = den / gcd_2;
			T num_2 = num / gcd_2;
		}
		if (den_1 == den_2 && num_1 == num_2) {
			return false;
		}
		else { return true; }
	}
	 operator double() const{
		return(double)(num) / (double)den;
	}
	operator string()const {
		string obj = to_string(num) + "/" + to_string(den);
		return obj;
	}
	friend ostream& operator <<(ostream& os, const fraction& f) {
		if (f.den == 1) {
			os << f.num;
		}
		else {
			os << f.num << "/" << f.den;
		}
		return os;
	}
};



int main() {
	fraction<int> a(1, 2);
	fraction<int> b(1, 3);
	cout << a + b << endl;
	cout << a - b << endl;
	cout << a * b << endl;
	cout << a / b << endl;
	if(a!=b)cout << "no" << endl;
	system("pause");
}