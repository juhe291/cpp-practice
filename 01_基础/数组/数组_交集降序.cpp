#include <iostream>
using namespace std;

void bp(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int m, n;
    int count = 0;
    int* arr_01 = NULL;
    int* arr_02 = NULL;
    int* con = NULL;

    cin >> m;
    arr_01 = new int[m];
    for (int i = 0; i < m; i++) {
        cin >> arr_01[i];
    }

    cin >> n;
    arr_02 = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr_02[i];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (arr_01[i] == arr_02[j]) {
                count++;
                break;
            }
        }
    }

    con = new int[count];
    int count_2 = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (arr_01[i] == arr_02[j]) {
                con[count_2] = arr_01[i];
                count_2++;
                break;
            }
        }
    }
    bp(con, count);
    for (int i = 0; i < count; i++) {
        cout << con[i];
        if (i < count - 1) {
            cout << " ";
        }
    }
    delete[] arr_01;
    delete[] arr_02;
    delete[] con;
    return 0;
}