#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

double max(double x, double y) {
    if (x > y) { return x; }
    if (y > x) { return y; }
}
double min(double x, double y) {
    if (x < y ) { return x; }
    if (y < x ) { return y; }
    
}

class Point{
    

public:
    double x, y;
    Point(double x1 = 0.0, double y1 = 0.0) :x(x1), y(y1) {}
    Point(const Point& oth) :x(oth.x), y(oth.y) {}//or{ x = oth.x; y = oth.y; }
    ~Point() {}

    double getX() { return x; }
    double getY() { return y; }
};

class AABB_Box2d {
private:
    Point p1,p2;

public:
    AABB_Box2d(Point p1,Point p2):p1(p1),p2(p2){}
    AABB_Box2d(const AABB_Box2d& oth) :p1(oth.p1), p2(oth.p2) {}


     bool intersects(const AABB_Box2d &j1){
         if(j1.p2.y>p1.y && j1.p2.y < p2.y&& j1.p1.x>p1.x && j1.p1.x < p2.x){ return 1; }
         else if (j1.p2.y < p1.y && j1.p2.y > p2.y && j1.p1.x<p1.x && j1.p1.x > p2.x) { return 1; }
         else return 0;
    }

    friend AABB_Box2d intersection(const AABB_Box2d& j1,AABB_Box2d& j2) {
        int x, y, m, n;
        x = max(j1.p1.x, j2.p1.x);
        y = max(j1.p1.y, j2.p1.y);
        m = min(j1.p2.x, j2.p2.x);
        n = min(j1.p2.y, j2.p2.y);
        Point c1(x,y); Point c2(m, n);
        AABB_Box2d c(c1, c2);
        return c;
    }

    double calArea() {
        double c = p2.x - p1.x;
        double k = p2.y - p1.y;
        return c * k;
    }
};

int main() {
    double x1, y1, x2, y2, m1, n1, m2, n2;
    cin >> x1 >> y1 >> x2 >> y2;
    cin >> m1 >> n1 >> m2 >> n2;
    Point p1(x1, y1); Point p2(x2, y2);
    Point p3(m1, n1); Point p4(m2, n2);
    AABB_Box2d a(p1,p2), b(p3,p4);

    if (a.intersects(b)) {

        //计算相交部分的AABB包围盒

        AABB_Box2d c = intersection(a, b);

        cout << "the first box area = " << a.calArea() << "\n"

            << "the second box area = " << b.calArea() << endl;

        cout << "the intersection box area = " << c.calArea() << endl;

    }

    else { cout << "not intersect" << endl; }
    return 0;
}
