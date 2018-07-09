#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 10000000;
int C, n;

int cache[101][101];

//내 풀이. 책의 풀이와 동일한 논리구조를 가진다.
//mypoly(curLength, blocks) = 현재 가로줄의 길이가 curLength이고,
//현재까지 사용한 정사각형의 개수가 blocks일 때 만들 수 있는 폴리오미노의 수

int mypoly(int curLength, int blocks) {
	if (blocks == n) return 1;
	int& ret = cache[curLength][blocks];
	if (ret != -1) return ret;

	ret = 0;
	for (int nextLength = 1; nextLength + blocks <= n; nextLength++) {
		int posWays = (blocks == 0 ? 1 : curLength + nextLength - 1);
		ret += ((mypoly(nextLength, blocks + nextLength) % MOD) * (posWays % MOD)) % MOD;
	}

	return ret;
}

//책의 풀이.
//세로 단조 폴리오미노에서, 각 가로줄에 포함된 정사각형들은
//항상 일렬로 연속해 있다는 점을 이용하여, 각 가로줄마다 몇 개의
//정사각형을 넣을지를 결정하고, 이들을 왼쪽-오른쪽으로 적절히 밀어 주어
//모든 폴리오미노를 생성한다.
//n개의 정사각형을 포함하되, 첫 가로줄에 first개의
//정사각형을 포함하는 폴리오미노의 수를 반환한다.
int poly(int n, int first) {
	//기저 사례: n == first
	if (n == first) return 1;
	//메모이제이션
	int& ret = cache[n][first];
	if (ret != -1) return ret;
	ret = 0;
	for (int second = 1; second <= n - first; second++) {
		int add = second + first - 1;
		add *= poly(n - first, second);
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << mypoly(0, 0) % MOD << endl;
	}
}