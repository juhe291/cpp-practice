#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

long long chapf(const int a, const int b) {
	return (long long)(a - b) * (long long)(a - b);
}

int main() {
	int n;
	cin >> n;
	vector<int> h(n);
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}

	sort(h.rbegin(), h.rend());
	long long sum = 0;
	int left = 0;
	int right = n - 1;
	sum += h[0] * h[0];
	while (left<right) {
		sum += chapf(h[left], h[right]);
		left++;
		sum += chapf(h[left], h[right]);
		right--;
	}
	cout << sum;
}