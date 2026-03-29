#include<iostream>
using namespace std;

char* find_last_str(char* pSource, char* pSub) {
	char* it1 = pSource;
	char* it2 = pSub;
	char* ret =NULL;

	while (*pSource!='\0') {
		it1 = pSource;
		it2 = pSub;
		while (*it1==*it2) {
			it1++;
			it2++;
			if (*it2=='\0') {
				ret = pSource;
				break;
			}
			if (*it1 == '\0') {
				return ret;
			}
		}
		++pSource;
	}
	return ret;
}

int main() {
	char source[] = "This is a test. This test is only a test.";
	char sub[] = "test";

	char* result = find_last_str(source, sub);
	if (result) {
		cout << "Last occurrence of substring found at position: " << (result - source) << endl;
	}
	else {
		cout << "Substring not found." << endl;
	}

	return 0;
}