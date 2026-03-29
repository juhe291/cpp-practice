#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

int main() {
	int w, n;
	cin >> w >> n;
	int N = n + 1;
	vector<int> p( N );
	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}
	p[N - 1] = 0;
	sort(p.rbegin(), p.rend());
	int tol = 0;
	for (int i = 0; i < N; i++) {
		for(int j = i + 1; j < N; j++){
			if (p[i] == 300) { break; }
			if (p[j] == 0) { tol++;  break; }
			if (p[i] + p[j] <= w) {
				tol++;
				p[j] = 300;
				break;
			}
		}
	}
	cout << tol;
}