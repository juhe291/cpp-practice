#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class oj{
public:
	long long start_t;
	long long end_t;

};

bool cmp(const oj& a, const oj& b) {
	return a.end_t < b.end_t;
}

int main() {
	long long n = 0;
	long long count = 0;
	cin >> n;
	vector<oj> comp(n);
	for (int i = 0; i < n; i++) {
		cin >> comp[i].start_t >> comp[i].end_t;
	}
	sort(comp.begin(), comp.end(), cmp);

	int last_end = -1; 


	for (int i = 0; i < n; i++) {
		if (comp[i].start_t >= last_end) {
			count++;
			last_end = comp[i].end_t;
		}
	}

	cout << count;

}