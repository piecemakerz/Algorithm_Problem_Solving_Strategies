#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_FENCE = 20000;
int C, N;
//int maxArea;
vector<int> fences;

/*
//내가 짠 알고리즘. 최악의 경우는 울타리가 길이가 같은 울타리 없이
//오름차순으로 정렬되어 배치되있는 경우로, 모든 울타리들이 fences안에
//저장되기 때문이 O(n^2)의 시간복잡도를 가진다. 제출 시 시간 안에는 돌아간다.

//numOfFences[i] = 연결이 끊어지지 않은 i길이의 판자 갯수
int numOfFences[MAX_FENCE];


void maxSquare() {
	//현재까지 연결이 끊어지지 않은 울타리 목록
	vector<int> curFences;
	int fenceSize = fences.size();

	for (int i = 0; i < fenceSize; i++) {
		int curfence = fences[i];

		//만약 현재 확인하는 울타리가 curFences의 가장 큰 울타리보다 작다면
		//연결이 끊어지는 울타리가 존재할 것이다. 
		//현재 확인하는 울타리와 curFences의 가장 큰 울타리의 길이가 같은 경우도
		//예외처리 해준다.
		while (!curFences.empty() && curFences.back() >= curfence) {
			numOfFences[curfence] = max(numOfFences[curfence], numOfFences[curFences.back()]);
				
			if (curFences.back() > curfence)
				numOfFences[curFences.back()] = 0;

			curFences.pop_back();	
		}

		curFences.push_back(curfence);
		sort(curFences.begin(), curFences.end());

		for (int j = 0; j < curFences.size(); j++) {
			numOfFences[curFences[j]]++;
			maxArea = max(maxArea, numOfFences[curFences[j]] * curFences[j]);
		}
	}
}
*/

//책의 알고리즘. n개의 판자를 절반으로 나눠 두 개의 부분 문제를 만든다. 이 때,
//1. 가장 큰 직사각형을 왼쪽 부분 문제에서만 잘라낼 수 있는 경우
//2. 가장 큰 직사각형을 오른쪽 부분 문제에서만 잘라낼 수 있는 경우
//3. 가장 큰 직사각형이 왼쪽 부분 문제와 오른쪽 부분 문제에 걸쳐있는 경우
//중에 우리가 찾으려는 최대 직사각형이 존재한다.
//나도 분할 정복으로 문제를 해결해보기 위해 이 방법을 생각했으나, 중간에 존재하는
//판자 하나를 기준으로 왼쪽과 오른쪽을 나눴을 때 

int solve(int left, int right) {
	int mid = (left + right) / 2;
	if (left == right)
		return fences[left];
	else if (right - left == 1)
		return max(max(fences[left], fences[right]), min(fences[left], fences[right]) * 2);
	
	int ret = max(solve(left, mid), solve(mid, right));
	int lo = mid, hi = mid;
	int length = 1, height = fences[mid];
	ret = max(ret, fences[mid]);

	while(left < lo || right > hi) {
		if (hi < right && (lo == left || fences[lo - 1] < fences[hi + 1])) {
			height = min(height, fences[++hi]);
			ret = max(ret, height * ++length);
		}
		else {
			height = min(height, fences[--lo]);
			ret = max(ret, height * ++length);
		}
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		int input;
		cin >> N;
		//memset(numOfFences, 0, sizeof(numOfFences));
		//maxArea = 0;
		for (int i = 0; i < N; i++) {
			cin >> input;
			fences.push_back(input);
		}
		cout << solve(0, fences.size()-1) << endl;
		//maxSquare();
		//cout << maxArea <<  endl;
		fences.clear();
	}
}