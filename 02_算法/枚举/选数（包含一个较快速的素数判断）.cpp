#include <iostream>
#include<cmath>
using namespace std;

int n, k;
long long a[25];

bool sushu(long long x) {
    if (x <= 3) return x > 1;
    if ((x & 1) == 0 || x % 3 == 0) return false;
    int limit = (int)sqrt(x);
    for (int i = 5; i <= limit; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return false;
    }
    return true;
}


int dfs(int idx, int cnt, long long sum) {
    if (cnt == k) {
        return sushu(sum) ? 1 : 0;
    }
    if (n - idx < k - cnt) return 0;

    int result = 0;
    for (int i = idx; i < n; i++) {
        result += dfs(i + 1, cnt + 1, sum + a[i]);
    }
    return result;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];

    cout << dfs(0, 0, 0) << endl;
    return 0;
}