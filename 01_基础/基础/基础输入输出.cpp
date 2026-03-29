#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int n_pile = 0;
    int n_bag = 0;
    cin >> n_pile >> n_bag;
    vector<double> m(n_pile);
    vector<double> v(n_pile);

    for (int i = 0; i < n_pile; i++) {
        cin >> m[i] >> v[i];
    }
    vector<double> va(n_pile);
    for (int i = 0; i < n_pile; i++) {
        va[i] = ((double)v[i]) / ((double)m[i]);
    }
    for (int i = 0; i < n_pile; i++) {
        for (int j = i; j < n_pile; j++) {
            double max = va[i];
            if (va[j] > va[i]) {
                max = va[j];
                va[j] = va[i];
                va[i] = max;
                swap(m[i], m[j]);
                swap(v[i], v[j]);
            }
        }
    }

    int n_bag2 = n_bag;
    double sum = 0;
    for (int i = 0; i < n_pile; i++) {
        if (n_bag2 >= m[i]) {
            sum += v[i];
            n_bag2 -= m[i];
        }
        else {
            sum += va[i] * n_bag2;
            break;
        }
    }
    cout << fixed << setprecision(2) << sum << endl;

    system("pause");
}