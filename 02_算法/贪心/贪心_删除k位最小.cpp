#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int N = 1e5 + 10;
int n;
int a[N];               // 原始实力值
int need[N];            // 每个组当前需要的下一个数值（即组尾+1）
int siz[N];            // 每个组当前人数
int cnt;                // 当前已有的组数

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)cin >> a[i];
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		int pos = lower_bound(need + 1, need + cnt + 1, a[i]) - need;
		while (pos < cnt && need[pos + 1] == a[i])pos++;
		if (pos > cnt || need[pos] != a[i]) {
			cnt++;
			need[cnt] = a[i] + 1;
			siz[cnt] = 1;
		}
		else {
			siz[pos]++;
			need[pos]++;
		}
	}
	sort(siz + 1, siz + cnt + 1);
	cout << siz[1];
}