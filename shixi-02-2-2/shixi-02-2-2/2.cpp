#include<iostream>
using namespace std;

int* jiaoji(int* a, int m, int* b, int n) {
    int cnt = 0;
    int* jiaoji = new int[cnt];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i] == b[j]) {
                cnt++;
                jiaoji[cnt] = b[j];
            }
        }
    }
    return jiaoji;
}

int main() {
    int m, n;

    cin >> m;
    int* a = new int[m];
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }

    cin >> n;
    int* b = new int[n];
    for (int j = 0; j < n; j++) {
        cin >> b[j];
    }
    int* result = jiaoji(a, m, b, n);
    for (int e: result) {
        cout << e;
    }

    delete[] a;
    delete[] b;
    delete[] result;
    return 0;
}