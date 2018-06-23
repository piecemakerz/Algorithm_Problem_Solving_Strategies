#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_FENCE 20000
#define MAX_HEIGHT 10000
using namespace std;

// 분할정복을 이용한 풀이가 떠오르지 않아 무식하게 풀어본 알고리즘 1. 앞에서부터 for문으로 하나하나 체크해 차례로 최고값을 구한다.
// 이 방법은 모든 판자의 높이가 같을 때 등의 상황에서 시간초과가 될 것이다.

int CountMaxFenceAlgo1(const vector<int>& fences) {
	int maxValue = 0;
	int n = fences.size();

	for (int i = 0; i < n; i++) {
		int curValue = fences[i];
		int curSum = curValue;

		for (int j = i - 1; j >= 0; j--) {
			if (fences[j] >= curValue)
				curSum += curValue;
			else
				break;
		}
		for (int j = i + 1; j < n; j++) {
			if (fences[j] >= curValue)
				curSum += curValue;
			else
				break;
		}
		if (maxValue < curSum)
			maxValue = curSum;
	}
	return maxValue;
}

//책의 '무식한' 알고리즘
int bruteForce(const vector<int>& h) {
	int ret = 0; // 최대 사각형 넓이
	int N = h.size();

	for (int left = 0; left < N; left++) {
		int minHeight = h[left];
		for (int right = left; right < N; right++) {
			minHeight = min(minHeight, h[right]);
			ret = max(ret, (right - left + 1) * minHeight);
		}
	}
	return ret;
}

//책의 분할정복 알고리즘
vector<int> h;

int solve(int left, int right) {
	if (left == right) return h[left];
	int mid = (left + right) / 2;
	int ret = max(solve(left, mid), solve(mid + 1, right)); // [left, mid], [mid, hi] 부분 문제 분할정복

	// 두 부분에 걸치는 사각형 중 가장 큰 사각형 찾기
	int lo = mid, hi = mid + 1;
	int height = min(h[lo], h[hi]);
	ret = max(ret, height * 2);
	                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	while (left < lo || hi < right) {
		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
			hi++;
			height = min(height, h[hi]);
		}
		else {
			lo--;
			height = min(height, h[lo]);
		}

		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}

int main(void) {
	int C, N;
	cin >> C;

	for (int i = 0; i < C; i++) {
		int input;
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> input;
			h.push_back(input);
		}
		cout << solve(0, h.size()-1) << endl;
		h.clear();
	}
	return 0;
}