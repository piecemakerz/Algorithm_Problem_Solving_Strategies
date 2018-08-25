#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 100000;
const int DIV = 20091101;
int C, N, K;
vector<int> dolls;
vector<long long> partialDolls;
int orderWays;

void partialSum() {
	partialDolls.resize(dolls.size());
	partialDolls[0] = dolls[0];
	for (int i = 1; i < dolls.size(); i++)
		partialDolls[i] = partialDolls[i-1] + dolls[i];
}

//여러 번 주문할 수 있다면, 주문이 겹치지 않게 최대 몇 번 주문할 수 있는가?
int cache[100001];

int solve(int startPos) {
	if (startPos >= N) return 0;

	int& ret = cache[startPos+1];
	if (ret != -1) return ret;

	ret = 0;
	if (startPos == -1)
		for (int i = 0; i < N; i++)
			ret = max(ret, solve(i));
	else {
		long long result;
		for (int i = startPos; i < N; i++) {
			if (startPos == 0) result = partialDolls[i];
			else result = partialDolls[i] - partialDolls[startPos-1];
			
			if (result % K == 0) {
				orderWays = (orderWays + 1) % DIV;
				ret = max(ret, solve(i + 1) + 1);
			}
		}
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		orderWays = 0;
		cin >> N >> K;
		dolls.resize(N);
		for (int i = 0; i < N; i++) scanf("%d", &dolls[i]);

		partialSum();
		int result = solve(-1);
		cout << orderWays << ' ' << result << endl;

		dolls.clear();
		partialDolls.clear();
	}
	return 0;
}