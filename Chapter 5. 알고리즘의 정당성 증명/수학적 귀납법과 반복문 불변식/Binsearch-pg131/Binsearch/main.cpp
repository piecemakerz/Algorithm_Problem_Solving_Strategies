#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binsearch(const vector<int>& A, int x) {
	int n = A.size();
	int lo = -1, hi = n;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (A[mid] < x)
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

int main(void) {
	vector<int> A{ 0,1,2,3,4,5,6,7,8,9 };
	cout << binsearch(A, 0) << endl;
	cout << binsearch(A, 9) << endl;
	cout << binsearch(A, 5) << endl;
	return 0;
}