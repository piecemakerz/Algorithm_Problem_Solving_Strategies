#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

//내 풀이 - 시간 초과가 발생한다.
/*
const int MAXN = 100000;
int C, N, K;
int box[MAXN];
vector<int> psum; // 부분합
//vector<vector<int>> psumsum; // 구간합 - 사용 시 최대 MAXN * MAXN 크기의 벡터가 만들어지므로 
//스택 오버플로우가 발생한다.
int cache[MAXN+1];

//배열 box의 부분합을 계산한다.
vector<int> partialSum() {
	vector<int> ret(N);
	ret[0] = box[0];
	for (int i = 1; i < N; i++)
		ret[i] = ret[i - 1] + box[i];
	return ret;
}

//구간 합
int rangeSum(int a, int b) {
	if (a == 0) return psum[b];
	return psum[b] - psum[a - 1];
}

//1번 문제 - 한 번만 주문할 수 있을 시 가능한 주문 방법
int numOfWays() {
	int ways = 0;
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (rangeSum(i, j) % K == 0)
				ways = (ways+1)%20091101;
	return ways;
}

//2번 문제 - 여러 번 주문 가능 시 주문이 겹치지 않게 주문할 수 있는 최대 방법의 수
//select = 이번에 선택할 상자
int maxOrders(int select = 0) {
	if (select >= N)
		return 0;

	int& ret = cache[select]; // select번 상자부터 주문할 경우 주문할 수 있는 최대 주문 수
	if (ret != -1)
		return ret;
	
	ret = 0;
	// 이번 상자부터 주문할 경우
	for (int i = select; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (rangeSum(i,j) % K == 0)
				ret = max(ret, 1 + maxOrders(j + 1));
		}
	}
	return ret;
}
*/


//책의 답
int C, N, K;
const int MAXN = 100000;
int D[MAXN];

void partialSum(vector<int>& psum) {
	psum[1] = D[0]%K;
	for (int i = 2; i < psum.size(); i++)
		psum[i] = (psum[i - 1] + D[i-1])%K;
}
//D[]의 부분 합 배열 psum[]과 k가 주어질 때, 몇 가지 방법으로 살 수 있는지 반환한다.
//psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정한다.
int waysToBuy(const vector<int>& psum, int k) {
	const int MOD = 20091101;
	int ret = 0;
	//psum[]의 각 값을 몇 번이나 본 적 있는지 기록한다.
	vector<long long> count(k, 0);
	for (int i = 0; i < psum.size(); i++)
		count[psum[i]]++;

	for (int i = 0; i < K; i++)
		if (count[i] >= 2)
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
	return ret;
}
//D[]의 부분 합 배열 psum[]과 k가 주어질 때, 몇 번이나 살 수 있는지 반환한다.
//psum[]의 첫 번째 원소 전에 0을 삽입했다고 가정한다.
int maxBuys(const vector<int>& psum, int k) {
	//ret[i] = 첫 번째 상자부터 i번째 상자까지 고려했을 때 살 수 있는 최대 횟수
	vector<int> ret(psum.size(), 0);
	//prev[s] = psum[]이 s였던 마지막 위치
	vector<int> prev(k, -1);
	for (int i = 0; i < psum.size(); i++) {
		//i번째 상자를 아예 고려하지 않는 경우
		if (i > 0)
			ret[i] = ret[i - 1];
		else
			ret[i] = 0;
		//psum[i]를 전에도 본 적이 있으면, prev[psum[i]] + 1부터 여기까지 쭉 사 본다.
		int loc = prev[psum[i]];
		if (loc != -1) ret[i] = max(ret[i], ret[loc] + 1);
		//prev[]에 현재 위치를 기록한다.
		prev[psum[i]] = i;
	}
	return ret.back();
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(D, 0, sizeof(D));

		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++)
			scanf("%d", &D[i]);

		vector<int> psum(N + 1, 0);
		psum[0] = 0;
		partialSum(psum);
		vector<int>::iterator iter = psum.begin();

		printf("%d %d\n", waysToBuy(psum, K), maxBuys(psum, K));
	}
	return 0;
}