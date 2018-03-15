#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAX_BUDGET = 1000000000;
int n, m, price[20], pref[20];
int cache[MAX_BUDGET + 1]; // 10억개짜리 배열을 잡을 수는 없다.
//budget만큼의 예산으로 초밥을 먹어서 얻을 수 있는 최대 선호도
int sushi(int budget) {
	//메모이제이션
	int& ret = cache[budget];
	if (ret != -1) return ret;
	ret = 0;
	for (int dish = 0; dish < n; dish++) {
		if (budget < price[dish]) continue;
		ret = max(ret, sushi(budget - price[dish]) + pref[dish]);
	}
	return ret;
}
//반복적 동적 계획법을 적용하여 메모리 사용량을 줄인 알고리즘
//int c[20000 + 1]; // 현재 budget만큼 예산이 남았을 때 가질 수 있는 최대 선호도 합.

int sushi2() {
	int ret = 0;
	for (int budget = 1; budget <= m; budget++) {
		int index = budget % 20001;
		for (int dish = 0; dish < n; dish++) {
			if (budget >= price[dish])
				c[index] = max(c[index], c[(budget - price[dish]) % 20001] + pref[dish]);
		}
		ret = max(ret, c[index]);
	} 
	return ret;
}
//최대 만족도 합을 반환한다.
//m과 price[]는 이미 100으로 나뉘어 있다고 가정한다.
int c[201];
int sushi3() {
	int ret = 0;
	c[0] = 0;
	for (int budget = 1; budget <= m; budget++) {
		int cand = 0;
		for (int dish = 0; dish < n; dish++)
			if (budget >= price[dish])
				cand = max(cand, c[(budget - price[dish]) % 201] + pref[dish]);

		c[budget % 201] = cand;
		ret = max(ret, cand);
	}
	return ret;
}
int main(void) {
	int c;
	cin >> c;
	for (int testCase = 0; testCase < c; testCase++) {
		cin >> n >> m;
		m /= 100;
		for (int i = 0; i < n; i++) {
			cin >> price[i] >> pref[i];
			price[i] /= 100;
		}
		cout << sushi3() << endl;
	}
	return 0;
}