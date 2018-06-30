#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 500;
int T, N;
int sequence[MAX_N], cache[MAX_N+1];

//내 풀이. 정상적으로 동작하지 않는다. 이유는 책의 노트 참고.
/*
int maxSeqlen(int idx = 0) {
	if (idx >= N - 1)
		return 1;
	int& ret = cache[idx];
	if (ret != -1)
		return ret;

	int nextIdx = idx + 1;

	//idx번째 번호를 포함하지 않는 부분수열의 최대 길이
	ret = maxSeqlen(nextIdx);

	//idx번째 번호를 포함하는 부분수열의 최대 길이
	while (nextIdx <= N - 1 && sequence[idx] >= sequence[nextIdx])
		nextIdx++;

	if (nextIdx != N)
		ret = max(ret, 1 + maxSeqlen(nextIdx));

	return ret;
}
*/

//책의 답 1. 최대 증가 부분 수열 문제를 해결하는 완전 탐색 알고리즘.
//이 알고리즘은 입력이 정수가 아니라 정수의 배열이므로 메모이제이션을
//적용하기 까다롭다.
int lis(const vector<int>& A) {
	//기저 사례: A가 텅 비어 있을 때
	if (A.empty())	return 0;
	int ret = 0;
	//A[i]를 수열의 첫 숫자로 골랐다고 가정한다.
	for (int i = 0; i < A.size(); i++) {
		vector<int> B; //A[i+1...]의 LIS
		for (int j = i + 1; j < A.size(); j++)
			if (A[i] < A[j])
				B.push_back(A[j]);
		ret = max(ret, 1 + lis(B));
	}
	return ret;
}

//책의 답 2. 최대 증가 부분 수열 문제를 해결하는 동적 계획법 알고리즘
//sequence[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis2(int start) {
	int& ret = cache[start + 1];
	if (ret != -1) return ret;
	//항상 sequence[start]는 존재하므로 길이는 최하 1
	ret = 1;
	for (int next = start + 1; next < N; next++)
		if (start == -1 || sequence[start] < sequence[next])
			ret = max(ret, 1 + lis2(next));
	return ret;
}

//인터넷의 가장 보편적인 O(n^2) 답. 
//책의 답은 재귀호출로 동적계획법을 구현했으나 인터넷의 답은
//중첩반복문으로 이를 구현했으며, 책의 답은 i번째 원소를 시작점으로 하는
//LIS의 길이를 구하는 반면 인터넷의 답은 i번째 원소를 마지막으로
//하는 LIS의 길이를 구한다.

//dp[i] = i번째 원소를 마지막으로 하는 LIS의 길이
//이 함수에서는 dp가 캐시의 역할을 한다.
int dp[MAX_N];

int lisInter() {
	int result = 0;
	for (int i = 0; i < N; i++) {
		//i번째 원소를 부분 수열의 마지막 원소로 반드시 포함하는
		//부분 수열들을 확인한다.
		int here = 0;
		for (int j = 0; j < i; j++)
			if (sequence[i] > sequence[j])
				here = max(here, dp[j]);

		dp[i] = here + 1;
		result = max(result, dp[i]);
	}
	return result;
}

//책의 답 3. 텅 빈 수열에서 시작해 숫자를 하나씩 추가해 나가며 각 길이를 갖는
//증가 수열 중 가장 마지막 수가 작은 것은 무엇인지 추적하는 알고리즘.

//C[i] = 지금까지 만든 부분 배열이 갖는 길이 i인 증가 부분 수열 중 최소의 마지막 값
int C[MAX_N];

int lis3(int start) {
	
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		memset(cache, -1, sizeof(cache));
		memset(C, 0, sizeof(C));

		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> sequence[i];
		//cout << maxSeqlen() << endl;
	}
	return 0;
}