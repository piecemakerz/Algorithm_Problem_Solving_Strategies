#include <iostream>
#include <vector>
using namespace std;

//부분합을 계산하는 함수와 이를 이용해 구간합을 계산하는 함수의 구현
//C++의 경우 STL에 포함되어 있는 partial_sum()을 이용할 수 있다.

//주어진 벡터 a의 부분합을 계산한다.
vector<int> partialSum(const vector<int>& a) {
	vector<int> ret(a.size());
	ret[0] = a[0];
	for (int i = 1; i < a.size(); i++)
		ret[i] = ret[i - 1] + a[i];
	return ret;
}
//어떤 벡터의 부분합 psum[]이 주어질 때 원래 벡터의 a부터 b까지의 합을 구한다.
int rangeSum(const vector<int>& psum, int a, int b) {
	if (a == 0)	return psum[b];
	return psum[b] - psum[a - 1];
}

//배열의 부분합과 제곱의 부분합을 입력받고 특정 구간의 분산을 계산하는 함수의 구현

//A[]의 제곱의 부분 합 벡터 sqpsum, A[]의 부분 합 벡터 psum이 주어질 때
//A[a...b]의 분산을 반환한다.
double variance(const vector<int>& sqpsum, const vector<int>& psum, int a, int b) {
	//우선 해당 구간의 평균을 계산한다.
	double mean = rangeSum(psum, a, b) / double(b - a + 1);
	double ret = rangeSum(sqpsum, a, b) - 2 * mean*rangeSum(psum, a, b)
		+ (b - a + 1)*mean*mean;
	return ret / (b - a + 1);
}

//부분 합을 이용해 2차원 배열의 구간 합을 구하는 함수의 구현

//어떤 2차원 배열 A[][]의 부분합 psum[][]이 주어질 때,
//A[y1, x1]과 A[y2, x2]를 양 끝으로 갖는 부분 배열의 합을 반환한다.
int gridSum(const vector<vector<int>>& psum, int y1, int x1, int y2, int x2) {
	int ret = psum[y2][x2];
	if (y1 > 0)	ret -= psum[y1 - 1][x2];
	if (x1 > 0)	ret -= psum[y2][x1 - 1];
	if (y1 > 0 && x1 > 0)	ret += psum[y1 - 1][x1 - 1];
	return ret;
}

