#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define ll long long

int main() {
	priority_queue<ll, vector<ll>, greater<ll>> qu_1;
	ll n = 0;
	ll t = 0;
	ll s = 0;
	ll tol = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t;
		qu_1.push(t);
	}
	while(qu_1.size()>1) {
		ll a = qu_1.top();
		qu_1.pop();
		ll b = qu_1.top();
		qu_1.pop();
		s = a + b;
		qu_1.push(s);
		tol += s;
	}
	cout << tol;

}
