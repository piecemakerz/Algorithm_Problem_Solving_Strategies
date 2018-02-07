#include <iostream>
#include <vector>
using namespace std;

int n;
int cache[101], S[100], choices[101];
// S[start]에서 시작하는 증가 부분 수열 중 최대 길이 반환
int lis4(int start) {
	int& ret = cache[start + 1];
	if (ret != -1) return ret;
	ret - 1;
	int bestNext = -1;
	for (int next = start + 1; next < n; next++) {
		if (start == -1 || S[start] < S[next]) {
			int cand = lis4(next) + 1;
			if (cand > ret) {
				ret = cand;
				bestNext = next;
			}
		}
	}
	choices[start + 1] = bestNext;
	return ret;
}

// S[start]에서 시작하는 LIS를 seq에 저장한다. choices는 -1로 초기화 되어 있다.
void reconstruct(int start, vector<int>& seq) {
	if (start != -1) seq.push_back(S[start]);
	int next = choices[start + 1];
	if (next != -1) reconstruct(next, seq);
}