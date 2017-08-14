#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

/*int bruteForce(const vector<int>& h) {
	int ret = 0;
	int N = h.size();
	for (int left = 0; left < N; left++) {
		int minHeight = h[left];
		for (int right = left; right < N; right++) {
			minHeight = min(minHeight, h[right]);
			ret = max(ret, (right - left + 1)*minHeight);
		}
	}
	return ret;
}
*/

// 각 판자의 높이를 저장하는 배열
vector<int> h;
//h[left..right]구간에서 찾아낼 수 있는 가장 큰 사각형의 넓이 반환
int solve(int left, int right) {
	if (left == right) return h[left];
	int mid = (left + right) / 2;
	// [left, mid], [mid+1, right]의 두 구간에서 가장 큰 사각형의 넓이 반환
	int ret = max(solve(left, mid), solve(mid + 1, right));
	int lo = mid, hi = mid + 1;
	int height = min(h[lo], h[hi]);
	ret = max(ret, height * 2);
	//두 부분에 모두 걸치는 사각형 중 가장 큰 것의 넓이 반환
	while (left < lo || hi < right) {
		if (hi < right && (lo == left || h[lo - 1] < h[hi + 1])) {
			++hi;
			height = min(height, h[hi]);
		}
		else {
			--lo;
			height = min(height, h[lo]);
		}

		ret = max(ret, height*(hi - lo + 1));
	}
	return ret;
}
int main(void) {
	int testtime;
	int input;
	scanf("%d", &testtime);
	for (int i = 0; i < testtime; i++) {
		int fenceNum;
		scanf("%d", &fenceNum);
		for (int j = 0; j < fenceNum; j++) {
			scanf("%d", &input);
			h.push_back(input);
		}
		printf("%d\n", solve(0, fenceNum));
		h.clear();
	}
}

