#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

int n;
int path[10];
bool vis[10];

void dfs(int step) {
    if (step == n) {
        for (int i = 0; i < n; i++) {
            cout << setw(5) << path[i];
        }
        cout << endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vis[i] = 1;
            path[step] = i;
            dfs(step + 1);
            vis[i] = 0;
        }
    }

}

int main() {
    cin >> n;
    dfs(0);
}
