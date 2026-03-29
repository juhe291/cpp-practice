#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	string s1 = " ";
	string s2;
	int k = 0;
	int count = 0;
	getline(cin, s1);
	cin >> k;
	
	for (char c : s1) {
		while (k > 0 && !s2.empty() && s2.back() > c) {
			s2.pop_back();
			--k;
		}
		s2.push_back(c);
	}
	while (k > 0 && !s2.empty()) {
		s2.pop_back();
		k--;
	}
	size_t pos = 0;
	while (pos<s2.size()&&s2[pos] == '0') {
		pos++;
	}
	s2 = s2.substr(pos);
	if (s2.empty()) { cout << "0"; }
	else {cout << s2;}
	system("pause");
}