#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int main(){
	string s1, s2, s3;
	int a1[210] = { 0 }, a2[210] = { 0 }, a3[210] = { 0 };
	getline(cin, s1);
	getline(cin, s2);
	bool swith = false;
	if (s2.size() > s1.size()) {
		swap(s1, s2);
		swith = true;
	}
	else if (s2.size() == s1.size()) {
		for(int i=0;i<s1.size();i++)
		if (s2[i] > s1[i]) { 
			swap(s1, s2); 
			swith = true;
			break;
		}
	}

	for (int i = 0; i < s1.size(); i++) {
		a1[s1.size() - 1 - i] = s1[i] - '0';
	}
	for (int i = 0; i < s2.size(); i++) {
		a2[s2.size() - 1 - i] = s2[i] - '0';
	}
	int len = max(s1.size(), s2.size());

	for (int i = 0; i < len; i++) {
		a3[i] = a1[i] - a2[i];
	}
	for (int i = 0; i < len; i++) {
		if (a3[i] < 0) {
			a3[i + 1] = a3[i + 1] - 1;
			a3[i] = a3[i] + 10;
		}
	}
	while (len > 1 && a3[len - 1] == 0) {
		len--;
	}
	if (swith == false) {
		for (int i = len - 1; i >= 0; i--) {
			cout << a3[i];
		}
		return 0;
	}
	else if (swith == true) {
		for (int i = len - 1; i >= 0; i--) {
			cout << "-"<< a3[i];
		}
		return 0;
	}
	if (len == 0) {
		cout << 0;
		return 0;
	}
}