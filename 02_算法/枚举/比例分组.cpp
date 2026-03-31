#include <iostream>
using namespace std;

int A, B, C;
bool check(int x,int y,int z) {
    int used[10] = { 0 };

    if (x < 100 || x > 999 || y < 100 || y > 999 || z < 100 || z > 999) {
        return false;
    }

    for (int i = 0; i < 3; ++i) {
        int d = x % 10;
        if (used[d] || d == 0) { return false; }
        used[d] = 1;
        x /= 10;
    }

    for (int i = 0; i < 3; ++i) {
        int d = y % 10;
        if (used[d] || d == 0) { return false; }
        used[d] = 1;
        y /= 10;
    }
    for (int i = 0; i < 3; ++i) {
        int d = z % 10;
        if (used[d] || d == 0) { return false; }
        used[d] = 1;
        z /= 10;
    }
    return true;
}

int main() {
    cin >> A >> B >> C;
    bool found = false;
    for (int i = 1; C * i <= 999; i++) {
        int x = A * i;
        int y = B * i;
        int z = C * i;
        if (check(x, y, z)) {
            cout << x << " " << y << " " << z << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No!!!";
    }
    return 0;
}