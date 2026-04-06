#include <iostream>
using namespace std;

int n, cnt = 0;
int hc[10] = { 6,2,5,5,4,5,6,3,7,6 };

int f(int x) {
    if (x == 0) return 6;
    int sum = 0;
    while (x > 0) {
        sum += hc[x % 10];
        x /= 10;
    }
    return sum;
}

int main() {
    cin >> n;

    for (int a = 0; a <= 1111; a++) {
        for (int b = 0; b <= 1111; b++) {
            int c = a + b;
            if (f(a) + f(b) + f(c) + 4 == n) {
                cnt++;
            }
        }
    }

    cout << cnt << endl;
    return 0;
}