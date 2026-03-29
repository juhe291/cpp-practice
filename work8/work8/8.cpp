#include <iostream>
#include <cmath>
using namespace std;

class Point // 二维平面上的点类
{
public:
    // 构造函数
    Point(double x = 0, double y = 0);
    // 拷贝构造函数
    Point(const Point& oPt);
    // 析构函数
    ~Point();

    // 获取点的横坐标
    double getX();
    // 获取点的纵坐标
    double getY();

    // 获取两点之间的距离
    friend double getDistance(Point& p1, Point& p2);

protected:
    double m_x, m_y; // 点的横坐标与纵坐标
};

class Triangle // 三角形类
{
public:
    // 构造函数
    Triangle(Point& p1, Point& p2, Point& p3);
    // 拷贝构造函数
    Triangle(const Triangle& oTri);
    // 析构函数
    ~Triangle();

    // 获取三角形的面积
    double getArea();
    // 获取三角形的周长
    double getPerimeter();
protected:
    Point m_A, m_B, m_C; // 三角形的三个顶点
};

////Point class
//函数的实现
Point::Point(double x, double y) :m_x(x), m_y(y){}
Point::Point(const Point& oPt):m_x(oPt.m_x), m_y(oPt.m_y){}
Point::~Point(){}
//获取x,y
double Point::getX() {
    return m_x;
}
double Point::getY() {
    return m_y;
}
// 获取两点之间的距离
double getDistance(Point& p1, Point& p2) {
    return sqrt((p1.m_x - p2.m_x) * (p1.m_x - p2.m_x) + (p1.m_y - p2.m_y) * (p1.m_y - p2.m_y));
}

////Triangle class 
//函数的实现
Triangle::Triangle(Point& p1, Point& p2, Point& p3):m_A(p1), m_B(p2), m_C(p3){}
Triangle::Triangle(const Triangle& oTri):m_A(oTri.m_A), m_B(oTri.m_B), m_C(oTri.m_C) {}
Triangle::~Triangle(){}
//三角形的面积
double Triangle::getArea() {
    double a = getDistance(m_A, m_B);
    double b = getDistance(m_A, m_C);
    double c = getDistance(m_B, m_C);
    double p = (a + b + c) / 2;
    double area = sqrt(p * (p - a) * (p - b) * (p - c));
    return area;
}
double Triangle::getPerimeter() {
    double a = getDistance(m_A, m_B);
    double b = getDistance(m_A, m_C);
    double c = getDistance(m_B, m_C);
    double perimeter = a + b + c;
    return perimeter;
}


int main() {
    double x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    Point p1(x1, y1), p2(x2, y2), p3(x3, y3);
    Triangle oTri(p1, p2, p3);

    cout << oTri.getPerimeter() << endl;
    cout << oTri.getArea() << endl;

    system("pause");
    return 0;
}