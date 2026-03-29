#include<iostream>
#include<vector>
#define ll long long
using namespace std;

int main() {
	ll n = 0;
	ll x = 0;
	cin >> n >> x;
	vector<ll>a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	ll cont = 0;
	ll sum = 0;
	for (ll i = 1; i < n; i++) {
		sum = a[i] + a[i - 1];
		ll eat = sum - x;
		if (sum > x) {
			if (a[i] >= eat) {
				cont += eat;
				a[i] -= eat;
			}
			else {
				cont += eat;
				a[i] = 0;
				ll eat_2 = eat - a[i];
				a[i - 1] -= eat_2;
			}
		}

	}
	cout << cont;
}