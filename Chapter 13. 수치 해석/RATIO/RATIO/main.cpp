#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

//20��� ���� ������ ���� ������/���� �� ���� �׻� �ùٸ� �ڷ��� ���ÿ� �����ؾ� �Ѵ�.

long long N, M;
int C, curRatio;
int calculateCurRatio(long long winTimes) {
	return (double)(M + winTimes) * 100 / (N + winTimes);
}

int win() {
	int lo = 0, hi = 2000000000;
	if (calculateCurRatio(hi) < curRatio + 1)
		return -1;

	for (int iter = 0; iter < 100; iter++) {
		int mid = (hi+lo) / 2;
		if (calculateCurRatio(mid) >= curRatio + 1)
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> N >> M;
		curRatio = (double)(M * 100) / N;
		cout << win() << endl;
	}
	return 0;
}