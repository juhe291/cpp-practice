#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int jc(int n) {
    int sum = 1;
    for (int i = 1; i <= 2 * n + 1; i++) {
        sum *= i;
    }
    return sum;
}

int cf(int x, int n) {
    int sum = 1;
    for (int i = 0; i < n * 2 + 1; i++) {
        sum *= x;
    }
    return sum;
}

int fu(int n) {
    int sum = 1;
    for (int i = 0; i < n; i++) {
        sum *= (-1);
    }
    return sum;
}
int main() {
    int x = 0, n = 0;
    cin >> x >> n;
    double result = 0.0;
    for (int i = 0; i <= n; i++) {
        result += (fu(i) * cf(x, i)) / jc(i);
    }
    cout << fixed << setprecision(6) << result << endl;
    return 0;
}