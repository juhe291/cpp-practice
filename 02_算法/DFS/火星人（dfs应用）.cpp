#include<iostream>
#include<vector>
#include<iomanip>
#include<string>
using namespace std;

const int N = 10010;

int n, m;
int a[N];
int temp[N];
int res = 0;
bool vis[N];
bool found = 0;

void dfs(int x) {

    if (x > n) {
        res++;
        if (res == m + 1) {
            for (int i = 1; i <= n; i++) {
                cout << a[i] << " ";
            }
            found = 1;
        }
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (found)return;
        if (!res) {
            i = temp[x];
        }
        if (!vis[i]) {
            vis[i] = 1;
            a[x] = i;
            dfs(x + 1);
            vis[i] = 0;
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> temp[i];
    }
    dfs(1);
    return 0;
}