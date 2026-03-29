#include<iostream>
#include<cstring>
using namespace std;

int main() {
	char str[50];
	gets_s(str,50);
	int n = strlen(str);
	char fstr[50];

	for (int i = 0; i < n; i++) {
		fstr[i] = str[n - i - 1];
	}
	fstr[n] = '\0';

	int con = 0;
	for (int i = 0; i < n; i++) {
		if (str[i] == fstr[i]) { con++; }
	}
	if (con == n) { cout << "YES"; }
	else { cout << "NO"; }
	return 0;
}