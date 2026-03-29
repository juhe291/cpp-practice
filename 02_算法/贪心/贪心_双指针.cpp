#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

bool cmp(const pair<int, int>& a,const pair<int, int>& b){
	return a.first < b.first;
}

int main() {
	int m, n;
	cin >> m >> n;
	vector<pair<int, int>> milk(n);
	for (int i = 0; i < n; i++) {
		cin >> milk[i].first >> milk[i].second;

	}
	sort(milk.begin(), milk.end(),cmp);

	long long sum = 0;
	int remain = m;
	for (int i = 0; i < n; i++) {
		if (remain - milk[i].second < 0) {
			sum += remain * milk[i].first;
			break;
		}
		else{
			sum += milk[i].first * milk[i].second;
		}
		remain -= milk[i].second;
	}
	cout << sum;

	return 0;
}