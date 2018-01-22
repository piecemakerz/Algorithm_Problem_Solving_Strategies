#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
#include <algorithm>

using namespace std;

const int MIN = numeric_limits<int>::min();

int inefficientMaxSum(const vector<int>& A) {
	int N = A.size(), ret = MIN;
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			int sum = 0;
			for (int k = i; k <= j; k++)
				sum += A[k];
			ret = max(ret, sum);
		}
	}
	return ret;
}

int betterMaxSum(const vector<int>& A) {
	int N = A.size(), ret = MIN;
	for (int i = 0; i < N; i++) {
		int sum = 0;
		for (int j = i; j < N; j++) {
			sum += A[j];
			ret = max(ret, sum);
		}
	}
	return ret;
}

int fastMaxSum(const vector<int>& A, int lo, int hi) {
	if (lo == hi) return A[lo];
	int mid = (lo + hi) / 2;
	int left = MIN, right = MIN, sum = 0;
	for (int i = mid; i >= lo; i--) {
		sum += A[i];
		left = max(left, sum);
	}
	sum = 0;
	for (int i = mid + 1; i <= hi; i++) {
		sum += A[i];
		right = max(right, sum);
	}

	int single = max(fastMaxSum(A, lo, mid), fastMaxSum(A, mid + 1, hi));
	return max(left + right, single);
}

int fastestMaxSum(const vector<int>& A) {
	int N = A.size(), ret = MIN, psum = 0;
	for (int i = 0; i < N; i++) {
		psum = max(psum, 0) + A[i];
		ret = max(psum, ret);
	}
	return ret;
}

int main(void) {
	vector<int> A(100);
	for (int i = 0; i < A.size(); i++) {
		A[i] = rand() % 100 + 1;
	}
	cout<<inefficientMaxSum(A)<<endl;
	cout<<betterMaxSum(A)<<endl;
	cout<<fastMaxSum(A, 0, A.size() - 1)<<endl;
	cout<<fastestMaxSum(A)<<endl;
}