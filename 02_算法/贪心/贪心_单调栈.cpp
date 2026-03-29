#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

bool cmp(const string& a, const string& b) {
    return a + b > b + a;
}

int main() {
    int n;
    cin >> n;
    vector<string> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end(), cmp);
    for (string& s : nums) {
        cout << s;
    }
    cout << endl;
    return 0;
}