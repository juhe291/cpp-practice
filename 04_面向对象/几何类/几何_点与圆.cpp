#include<iostream>
#include<iomanip>
#include<cmath>
#define PI 3.1415926
using namespace std;

class Point2D {
private:
    double x, y;

public:
    Point2D(double x1 = 0.0, double y1 = 0.0) :x(x1), y(y1) {}
    Point2D(const Point2D& oth) :x(oth.x), y(oth.y) {}//or{ x = oth.x; y = oth.y; }
    ~Point2D() {}

    double getX() { return x; }
    double getY() { return y; }

    friend double dist(Point2D& p1, Point2D& p2) {
        return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
    } 
};
    class circle{
    private:
        double r;
        Point2D o;
    public:
        circle(const Point2D& o1,double r1=1.0):o(o1),r(r1){}
        circle(const circle& oth):o(oth.o),r(oth.r){}
        ~circle(){}

        void is_in_cir(circle& c,Point2D& p) {
            double s = dist(c.o, p);
            if (s > c.r) { cout << "这个点在圆外" << endl; }
            else if (s == c.r) { cout << "这个点在圆上" << endl; }
            else { cout << "这个点在圆内" << endl; }
        }

        double area() {
            return PI * r * r;
        }
        double s() {
            return PI * 2 * r;
        }
    };

int main() {
    double x, y, r, m, n;
    cout << "请输入圆心坐标";
    cin >> x >> y;
    cout << "请输入该圆的半径";
    cin >> r;
    cout << "请输入点的坐标";
    cin >> m >> n;
    Point2D c(x, y);
    Point2D p(m, n);
    circle c1(c,r);
    c1.is_in_cir(c1, p);
    cout << "该圆的周长为" << c1.s() << '\t' << "该圆的面积为" << c1.area();
    return 0;
}