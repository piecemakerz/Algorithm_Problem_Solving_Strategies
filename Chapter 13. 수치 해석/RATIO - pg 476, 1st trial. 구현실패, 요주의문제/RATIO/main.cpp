#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

int T, Z;
long long N, M;

//책의 풀이를 참고하여 작성한 내 알고리즘.
//이유는 모르겠으나 알고리즘이 불안정하다.
const int MAX = 2000000000;
int findMinWins() {
	long long lo = 0;
	long long hi = MAX;

	if (Z == (int)((((double)M + MAX) / ((double)N + MAX)) * 100))
		return -1;

	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		int result = (((double)M + mid) / ((double)N + mid)) * 100;
		if (result > Z)
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

//승률 올리기 문제를 해결하는 책의 이분법 알고리즘
long long L = 2000000000;
//b게임 중 a게임 승리했을 때의 승률
int ratio(long long b, long long a) {
	return (a * 100) / b;
}
//최소 몇 연승해야 승률이 올라갈까?
int neededGames(long long games, long long won) {
	//불가능한 경우를 미리 걸러낸다.
	if (ratio(games, won) == ratio(games + L, won + L))
		return -1;
	long long lo = 0, hi = L;
	//반복적 불변식:
	//1. lo게임 이기면 승률은 변하지 않는다.
	//2. hi게임 이기면 승률은 변한다.
	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		if (ratio(games, won) == ratio(games + mid, won + mid))
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

//책의 수학공식을 사용해 상수 시간에 문제를 해결하는 알고리즘
int findMinWinsMath() {
	if (Z == ratio(N + L, M + L))
		return -1;

	int aimZ = Z + 1;
	return ceil((double)((aimZ * N) - (100 * M)) / (100 - aimZ));
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		cin >> N >> M;
		//c++에서는 long double과 double형이 같은 바이트수와 유효숫자를 가지는
		//자료형이나, M을 double로 캐스팅하면 오답이 나오고, long double로 캐스팅하면
		//정답이 나온다. 책에 나온 방식대로 100을 먼저 곱한 후 나누는 것이
		//안전할 듯 하다.
		Z = ((long double)M / N) * 100;
		cout << findMinWins() << endl;
	}
	return 0;
}