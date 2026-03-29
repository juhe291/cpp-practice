#include<iostream>
using namespace std;

int main() {
    int m, n;
    int* arr = NULL;
    cin >> m >> n;
    arr = new int[m * n];
    for (int i = 0; i < m * n; i++) {
        cin >> arr[i];
    }
    int* rowMax = new int[m];
    int* colMax = new int[n];
    for (int i = 0; i < m; i++) rowMax[i] = -10000000; 
    for (int j = 0; j < n; j++) colMax[j] = -10000000;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int yw = i * n + j;
            if (arr[yw] > rowMax[i]) {
                rowMax[i] = arr[yw];
            }
        }
    }

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            int yw = i * n + j;
            if (arr[yw] > colMax[j]) {
                colMax[j] = arr[yw];
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int yw = i * n + j;
            if (arr[yw] == rowMax[i] && arr[yw] == colMax[j]) {
                cout << arr[yw] <<" " << i + 1 <<" " << j + 1 << endl;
              
            }
        }
    }

    delete[] arr;
    delete[] rowMax;
    delete[] colMax;

    return 0;
}