#include<iostream>
#include<algorithm>
#include<vector>
#include<iomanip>

using namespace std;

int main() {
	int n = 0;
	cin >> n;
	vector<long long> T(n);
	vector<int> n_p(n);

	for (int i = 0; i < n; i++) {
		cin >> T[i];
		n_p[i] = i + 1;
	}

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			if (T[i] > T[j]||(T[i] == T[j]&&n_p[i]>n_p[j])) {
				swap(T[i], T[j]);
				swap(n_p[i], n_p[j]);

			}
		}
	}

	long long sum = 0;
	for (int i = 0; i < n - 1; i++) {
		T[i + 1] = T[i + 1] + T[i];
		sum += T[i];
	}
	double unit = (double)sum / (double)n;
	for (int i = 0; i < n; i++) {
		cout << n_p[i];
		if (i != n - 1) { cout << " "; }
		else { cout << endl; }
	}
	cout <<  fixed << setprecision(2) << unit << endl;

	system("pause");
}
