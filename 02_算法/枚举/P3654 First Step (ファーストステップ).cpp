#include <iostream>
#include <cmath>
#include<string>
#include<vector>
using namespace std;

int n, m, k;

int sum = 0;
int main() {
    cin >> n >> m >> k;
    char q[110][110];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> q[i][j];
        }
    }
    if (k == 1) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (q[i][j] == '.') sum++;
            }
        }
        cout << sum;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (q[i][j] == '.') {
                int cnt = 0;
                for (int x = j; x <= m; x++) {
                    if (q[i][x] == '.') cnt++;
                    else break;
                }
                if (cnt >= k) { sum++; }
            }
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (q[i][j] == '.') {
                int cnt = 0;
                for (int x = i; x <= n; x++) {
                    if (q[x][j] == '.') cnt++;
                    else break;
                }
                if (cnt >= k) { sum++; }
            }
        }
    }
    cout << sum;


    return 0;
}