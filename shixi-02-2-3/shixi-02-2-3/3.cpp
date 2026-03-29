#include<iostream>
#include<cstring>
using namespace std;

char* insert(char* string, char c) {
    int len = strlen(string);
    string[len] = c;
    string[len + 1] = '\0';
    len++;
    for (int i = len - 1; i > 0; i--) {
        if (string[i] < string[i - 1]) {
            char temp = string[i];
            string[i] = string[i - 1];
            string[i - 1] = temp;
        }
        else {
            break;
        }
    }

    return string;
}

int main() {
    char str[50], c;
    cin.getline(str, 50);
    cin >> c;
    insert(str, c);
    for (int i = 0; str[i] != '\0'; i++) {
        cout << str[i];
    }
    cout << endl;
    return 0;
}