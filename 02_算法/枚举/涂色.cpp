#include <iostream>
#include <cmath>
#include<string>
#include<vector>
using namespace std;

int n, m;
char color[60][60];
int cnt = 0;
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> color[i][j];
        }
    }
    int costW[60] = { 0 }; int costB[60] = { 0 }; int costR[60] = { 0 };
    //第一行全为白色
    for (int i = 1; i <= m; i++) {
        if (color[1][i] != 'W') {
            cnt++;
        }
    }
    //最后一行全为红色
    for (int i = 1; i <= m; i++) {
        if (color[n][i] != 'R') {
            cnt++;
        }
    }
    for (int i = 2; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            if (color[i][j] != 'W')costW[i]++;
            if (color[i][j] != 'B')costB[i]++;
            if (color[i][j] != 'R')costR[i]++;
        }
    }
    int big = 1e9;
    for (int i = 1; i <= n - 2; i++) {
        for (int j = i + 1; j <= n - 1; j++) {
            int sum = 0;
            for (int r = 1; r <= i; r++)sum += costW[r];
            for (int r = i + 1; r <= j; r++)sum += costB[r];
            for (int r = j + 1; r < n; r++)sum += costR[r];
            big = min(big, sum);
        }
    }

    cout << big + cnt;
    return 0;
}