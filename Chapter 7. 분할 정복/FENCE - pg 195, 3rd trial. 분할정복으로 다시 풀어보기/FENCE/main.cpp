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

//책의 답을 참고한 내 알고리즘. 책과 동일하게 n개의 판자를 절반으로 나눠 두 개의
//부분 문제를 만들되, 부분 문제 경계에 있는 두 판자 대신 두 부분 문제에 포함되는
//하나의 판자를 중심으로 분할 정복을 하였다. 예를 들어, 7개의 판자가 주어진다면
//3번 판자를 중심으로 0~3, 3~6의 두 부분문제로 나눠 재귀호출하고, 3번 판자로부터
//시작하는 직사각형 중 가장 큰 직사각형을 찾아 두 부분문제와 비교한다.
//이 방법의 문제점은 n개의 판자를 두 개의 부분문제로 나눌 때 중복되는 가운데 판자로 인해
//재귀호출의 너비가 넓어진다는 것과, 두 개의 판자가 남았을 때 이를 절반으로 나누지 못해
//예외처리를 해주어야 하기 때문에 코드가 길어진다는 단점이 있다. 

int mySolve(int left, int right) {
	int mid = (left + right) / 2;
	if (left == right)
		return fences[left];
	else if (right - left == 1)
		return max(max(fences[left], fences[right]), min(fences[left], fences[right]) * 2);

	int ret = max(mySolve(left, mid), mySolve(mid, right));
	int lo = mid, hi = mid;
	int length = 1, height = fences[mid];
	ret = max(ret, fences[mid]);

	while (left < lo || right > hi) {
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

//책의 알고리즘. n개의 판자를 절반으로 나눠 두 개의 부분 문제를 만든다. 이 때,
//1. 가장 큰 직사각형을 왼쪽 부분 문제에서만 잘라낼 수 있는 경우
//2. 가장 큰 직사각형을 오른쪽 부분 문제에서만 잘라낼 수 있는 경우
//3. 가장 큰 직사각형이 왼쪽 부분 문제와 오른쪽 부분 문제에 걸쳐있는 경우
//중에 우리가 찾으려는 최대 직사각형이 존재한다.
//나도 분할 정복으로 문제를 해결해보기 위해 이 방법을 생각했으나, 중간에 존재하는
//판자 하나를 기준으로 왼쪽과 오른쪽을 나눴을 때 중간에 존재하는 판자를 양쪽 부분문제에서
//제외시키면 재귀호출 시 놓치는 부분이 존재하고, 양쪽 부분문제에 모두 포함시키면 재귀호출의
//너비가 넓어진다는 이유로 방법을 보류했었다. (중간 판자를 한쪽 부분문제에만 포함시키면
//양쪽 부분 문제에 걸쳐있는 직사각형을 모두 찾을 수 없다)
//즉, 부분 문제 경계에 있는 두 판자를 중심으로 분할 정복을 하면 된다는 아이디어를 생각해내지 못했다.

int solve(int left, int right) {
	//기저 사례: 판자가 하나밖에 없는 경우
	if (left == right)	return fences[left];
	//[left, mid], [mid+1, right]의 두 구간으로 문제를 분할한다.
	int mid = (left + right) / 2;
	//분할한 문제를 각개격파
	int ret = max(solve(left, mid), solve(mid + 1, right));
	//부분 문제 3: 두 부분에 모두 걸치는 사각형 중 가장 큰 것을 찾는다.
	int lo = mid, hi = mid + 1;
	int height = min(fences[lo], fences[hi]);
	//[mid, mid+1]만 포함하는 너비 2인 사각형을 고려한다.
	ret = max(ret, height * 2);

	//사각형이 입력 전체를 덮을 때까지 확장해 나간다.
	while (left < lo || hi < right) {
		//항상 높이가 더 높은 쪽으로 확장한다.
		if (hi < right && (lo == left || fences[hi + 1] > fences[lo - 1]))
			height = min(height, fences[++hi]);
		else
			height = min(height, fences[--lo]);
		//확장한 후 사각형의 넓이
		ret = max(ret, height * (hi - lo + 1));
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
		//cout << mySolve(0, fences.size()-1) << endl;
		//maxSquare();
		//cout << maxArea <<  endl;
		fences.clear();
	}
}