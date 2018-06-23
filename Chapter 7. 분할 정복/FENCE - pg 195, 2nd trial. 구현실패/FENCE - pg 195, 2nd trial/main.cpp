#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_FENCE 20000
#define MAX_HEIGHT 10000
using namespace std;

// ���������� �̿��� Ǯ�̰� �������� �ʾ� �����ϰ� Ǯ� �˰��� 1. �տ������� for������ �ϳ��ϳ� üũ�� ���ʷ� �ְ��� ���Ѵ�.
// �� ����� ��� ������ ���̰� ���� �� ���� ��Ȳ���� �ð��ʰ��� �� ���̴�.

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

//å�� '������' �˰���
int bruteForce(const vector<int>& h) {
	int ret = 0; // �ִ� �簢�� ����
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

//å�� �������� �˰���
vector<int> h;

int solve(int left, int right) {
	if (left == right) return h[left];
	int mid = (left + right) / 2;
	int ret = max(solve(left, mid), solve(mid + 1, right)); // [left, mid], [mid, hi] �κ� ���� ��������

	// �� �κп� ��ġ�� �簢�� �� ���� ū �簢�� ã��
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