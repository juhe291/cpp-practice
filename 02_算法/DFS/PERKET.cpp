#include <iostream>
#include <cmath>
using namespace std;

int n;
int s[15], b[15];
int ans = 1e9;

void dfs(int i, int sour, int bitter, bool chosen) {
    if (i == n) {
        if (chosen) {
            ans = min(ans, abs(sour - bitter));
        }
        return;
    }

    // 选第 i 个食材
    dfs(i + 1, sour * s[i], bitter + b[i], true);

    // 不选第 i 个食材
    dfs(i + 1, sour, bitter, chosen);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> b[i];
    }

    dfs(0, 1, 0, false);

    cout << ans << endl;
    return 0;
}