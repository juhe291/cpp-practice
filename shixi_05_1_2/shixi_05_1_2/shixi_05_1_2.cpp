#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

template<typename T>
// 二维点类
class Point2D {
private:
    T x, y;
public:
    //构造函数
    Point2D(T x = 0, T y = 0) : x(x), y(y) {}

    //获取x坐标
    T getX() const { return x; }

    //获取y坐标
    T getY() const { return y; }

    //设置坐标
    void setPoint(T newX, T newY) {
        x = newX;
        y = newY;
    }

    //计算两点间距离
    double p_dis(const Point2D& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};

template<typename T>
class polyline {
private:
    //数据
    Point2D<T> * points = NULL;
    T numPoints = 0;

public:
    //构造函数
    polyline(int n) :points(NULL), numPoints(n) {
        if (n < 2) {
            numPoints = 0;
            points = nullptr;
        }
        else {
            numPoints = n;
            points = new Point2D<T>[n];
        }
    }
    //析构函数
    ~polyline() {
        if (points != NULL) {
            delete[] points;
        }
    }


    //设点
    void setPoint(size_t i, T x, T y) {
        if (i < numPoints) {
            points[i].setPoint(x, y);
        }
    }

    //计算多段线长度
    double dist() const {
        if (numPoints < 2) {
            return 0;
        }
        double res = 0.0;
        for (int i = 0; i < numPoints - 1; i++) {
            res += points[i].p_dis(points[i + 1]);
        }
        return res;
    }

    //计算包围盒坐标
    Point2D<T> minzb() const{
        if (numPoints < 2) {
            return Point2D<T>(0, 0);
        }

        T minX = points[0].getX();
        T minY = points[0].getY();

        for (int i = 1; i < numPoints; i++) {
            if (points[i].getX() < minX) {
                minX = points[i].getX();
            }
            if (points[i].getY() < minY) {
                minY = points[i].getY();
            }
        }

        return Point2D<T>(minX, minY);
    }

    Point2D<T> maxzb() const {
        if (numPoints < 2) {
            return Point2D<T>(0, 0);
        }

        T maxX = points[0].getX();
        T maxY = points[0].getY();

        for (int i = 1; i < numPoints; i++) {
            if (points[i].getX() > maxX) {
                maxX = points[i].getX();
            }
            if (points[i].getY() > maxY) {
                maxY = points[i].getY();
            }
        }

        return Point2D<T>(maxX, maxY);
    }

    int getN() const {
        return numPoints;
    }
};



int main() {
    int n = 0;
    cin >> n;
    polyline<double> Po(n);

    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        Po.setPoint(i, x, y);
    }
    if (Po.getN() < 2) {
        cout << 0 << endl;
        cout << 0 << " " << 0 << endl;
        cout << 0 << " " << 0 << endl;
    }
    else {
        double len = Po.dist();
        cout << setprecision(6) << len << endl;

        Point2D<double> minPoint = Po.minzb();
        Point2D<double> maxPoint = Po.maxzb();

        cout << minPoint.getX() << " " << minPoint.getY() << endl;

        cout << maxPoint.getX() << " " << maxPoint.getY() << endl;
    }

    return 0;
}
