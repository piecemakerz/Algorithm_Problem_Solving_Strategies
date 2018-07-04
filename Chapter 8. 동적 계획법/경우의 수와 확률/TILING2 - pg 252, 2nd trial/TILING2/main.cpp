#include <iostream>
#include <cstring>
using namespace std;

int C, n;

int cache[101];
const int MOD = 1000000007;
//내 풀이. 책의 풀이보다 더 복잡하다. 예외처리를 바꾸면 코드가 더
//간단해질 수 있었다.
//tileWays(len) = 타일로 채우지 못한 사각형의 가로 길이가 len일 때,
//남은 공간을 채울 수 있는 방법의 수
int tileWays(int len) {
	if (len == 0)
		return 1;
	int& ret = cache[len];
	if (ret != -1) return ret;

	ret = 0;
	if (len >= 1)
		ret += tileWays(len - 1) % MOD;
	if (len >= 2)
		ret += tileWays(len - 2) % MOD;

	return ret %= MOD;
}

//책의 답. 타일링의 수를 세는 동적 계획법 알고리즘.
//2*width 크기의 사각형을 채우는 방법의 수를 MOD로 나눈 나머지를 반환한다.
int tiling(int width) {
	//기저 사례: width가 1 이하일 때
	if (width <= 1) return 1;
	//메모이제이션
	int& ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << tileWays(n) << endl;
	}
	return 0;
}