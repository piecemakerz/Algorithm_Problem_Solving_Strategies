#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int cache[101], S[100];

int lis(const vector<int>& A) {
	if (A.empty())
		return 0;

	int ret = 0;
	for (int i = 0; i < A.size(); i++) {
		vector<int> B;
		for (int j = i + 1; j < A.size(); j++) {
			if (A[i] < A[j])
				B.push_back(A[j]);
		}
		ret = max(ret, lis(B) + 1);
	}
	return ret;
}

int lis2(int start) {
	int& ret = cache[start];
	if (ret != -1) return ret;
	ret = 1;

	for (int i = start + 1; i < n; i++) {
		if (start == -1 || S[start] < S[i])
			ret = max(ret, 1 + lis2(i));
	}
	return ret;
}