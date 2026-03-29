#include <iostream>
using namespace std;

const int MAX = 9;

int main() {
	int m, n;
	int matN[MAX][MAX];
	int matM[MAX][MAX];

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cin >> matM[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> matN[i][j];
		}
	}

	for (int i = 0; i < m - n; i++) {
		for (int j = 0; j < m - n; j++) {
			if (matM[i][j] == matN[0][0]) {

			}
		}
	}
}