#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//digits: e의 자릿수들을 정렬한 것
string e, digits;
int n, m;
const int MOD = 1000000007;

//웨브바짐 문제의 답을 모두 찾는 완전 탐색 알고리즘
//e의 자릿수로 만들 수 있는 숫자들을 모두 출력한다.
//price: 지금까지 만든 가격
//taken: 각 자릿수의 사용 여부
void generate(string price, bool taken[15]) {
	//기저 사례
	if (price.size() == n) {
		if (price < e)
			cout << price << endl;
		return;
	}
	for(int i=0; i<n; i++)
		if (!taken[i] && (i == 0 || digits[i - 1] != digits[i] || taken[i - 1])) {
			taken[i] = true;
			generate(price + digits[i], taken);
			taken[i] = false;
		}
}

//웨브바짐 문제를 해결하는 동적 계획법 알고리즘

int cache[1 << 14][20][2];
//과거 가격을 앞 자리부터 채워나가고 있다.
//index: 이번에 채울 자리의 인덱스
//taken: 지금까지 사용한 자릿수들의 집합
//mod: 지금까지 만든 가격의 m에 대한 나머지
//less: 지금까지 만든 가격이 이미 e보다 작으면 1, 아니면 0
int price(int index, int taken, int mod, int less) {
	//기저 사례
	if (index == n)
		return (less && mod == 0) ? 1 : 0;
	//메모이제이션
	int& ret = cache[taken][mod][less];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = 0; next < n; next++) 
		if ((taken & (1 << next)) == 0) {
			//과거 가격은 새 가격보다 항상 작아야만 한다.
			if (!less && e[index] < digits[next])
				continue;
			//같은 숫자는 한 번만 선택한다.
			if (next > 0 && digits[next - 1] == digits[next] && (taken & (1 << (next - 1))) == 0)
				continue;
			int nextTaken = taken | (1 << next);
			int nextMod = (mod * 10 + digits[next] - '0') % m;
			int nextLess = less || e[index] > digits[next];
			ret += price(index + 1, nextTaken, nextMod, nextLess);
			ret %= MOD;
		}
	return ret;
}