#include<iostream>
#include<vector>
using namespace std;

int n;
vector<int>a(10);
vector<vector<int>>ans;

void dfs(int k, int sum) {
	if (sum + (10 - k) > n)return;
	if (sum + (10 - k)*3 < n)return;

	if (k == 10) {
		if (sum == n) {
			ans.push_back(a);
		}
		return;
	}
	for (int i = 1; i <= 3; i++) {
		a[k] = i;
		dfs(k + 1, sum + i);
	}
}

int main() {
	cin >> n;
	if (n < 10||n > 30) { 
	    cout << 0;
	    return 0; 
	}
	dfs(0, 0);
	int x = ans.size();
	cout << x << endl;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < 10; j++) {
			cout << ans[i][j]<<" ";
		}
		cout << endl;
	}
	return 0;
}