#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

int main() {
    string str[20];
    int count = 0;

    for (int i = 0; i < 20; i++) {
        getline(cin, str[i]);
        if (str[i].empty()) {
            break;
        }
        count++;
    }

    sort(str, str + count);

    for (int i = 0; i < count; i++) {
        cout << str[i] << endl;
    }

    return 0;
}