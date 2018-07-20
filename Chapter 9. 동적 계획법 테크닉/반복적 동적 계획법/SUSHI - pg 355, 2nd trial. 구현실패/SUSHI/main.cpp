#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int C, n, m;
vector<int> preference;
vector<int> prices;

//int cache[21474837];

//회전초밥 문제를 해결하는 내 메모이제이션 동적 계획법 알고리즘
//현재까지 curPrice의 금액을 사용했을 때, 남은 금액을 모두 
//사용하여 얻을 수 있는 최대 선호도 합을 반환한다.
//이 풀이는 대략 20억개의 int를 포함하는 배열을 잡아야하기 때문에
//스택 오버플로가 발생한다.
/*
int sushi(int curPrice) {
	int& ret = cache[curPrice];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < n; i++)
		if (curPrice + prices[i] <= m)
			ret = max(ret, preference[i] + sushi(curPrice + prices[i]));

	return ret;
}
*/

//책의 회전초밥 문제를 해결하는 반복적 동적 계획법 알고리즘
int c[200];
//최대 만족도의 합을 반환한다.
//m과 price[]는 이미 100으로 나뉘어 있다고 가정한다.
int sushi3() {
	int ret = 0;
	c[0] = 0;
	for (int budget = 1; budget <= m; budget++) {
		//c[budget % 201]은 현재 계산할 답이 저장될 공간이므로 0으로 초기화한다.
		//c[budget % 201]을 계산하기 위해 c[budget % 201]의 값을 사용할 일은 없으므로 0으로 초기화해도
		//게산에 영향을 미치지 않는다.
		c[budget % 201] = 0;
		for (int dish = 0; dish < n; dish++)
			if (budget >= prices[dish])
				c[budget % 201] = max(c[budget % 201], c[(budget - prices[dish]) % 201] + preference[dish]);
		ret = max(ret, c[budget % 201]);
	}
	return ret;
}
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(c, 0, sizeof(c));
		cin >> n >> m;
		m /= 100;
		int price, pref;
		for (int i = 0; i < n; i++) {
			cin >> price >> pref;
			price /= 100;
			prices.push_back(price);
			preference.push_back(pref);
		}
		cout << sushi3() << endl;
		prices.clear();
		preference.clear();
	}
	return 0;
}