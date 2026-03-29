#include<iostream>
#include<cmath>
using namespace std;

class Vector2D {
public:
	////函数成员
	  //设置和获取数据
	void setx(float val) { _x = val; }
	void sety(float val) { _y = val; }
	float getx()const { return _x; }
	float gety()const { return _y; }

	  //构造函数
	Vector2D(float x=0.0f,float y=0.0f):_x(x),_y(y){}

	  //相加
	Vector2D add(const Vector2D &pt) {
		Vector2D temp(_x + pt._x, _y + pt._y);
		return temp;
	}
	  //相减
	Vector2D sub(const Vector2D& pt) {
		Vector2D temp(_x - pt._x, _y - pt._y);
		return temp;
	}
	  //点积
	float dot_product(const Vector2D& pt)const {
		float temp = pt._x * _x + pt._y * _y;
		return temp;
	}
	  //叉积
	float cross_product(const Vector2D& pt)const {
		float temp = _x * pt._y - _y * pt._x;
		return temp;
	}
      //模
	float len()const {
		float temp = sqrt(_x * _x + _y * _y);
		return temp;
	}
	  //归一化
	Vector2D norm() {
		float fl = this->len();
		float xx = _x / fl;
		float yy = _y / fl;
		Vector2D temp(xx, yy);
		return temp;
	}
      //输出
	void print() const {
		cout << "(" << _x << ", " << _y << ")" << endl;
	}

private:
	//数据
	float _x = 0.0f;
	float _y = 0.0f;
}; 

int main() {
		Vector2D pt1(1.0f, 2.0f);
		Vector2D pt2(3.0f, 4.0f);
		Vector2D pt3 = pt1.add(pt2);

		pt1.print();      // 输出: pt1 = (1, 2)
		pt2.print();      // 输出: pt2 = (3, 4)
		pt3.print();  // 输出: pt1+pt2 = (4, 6)

		return 0;
}