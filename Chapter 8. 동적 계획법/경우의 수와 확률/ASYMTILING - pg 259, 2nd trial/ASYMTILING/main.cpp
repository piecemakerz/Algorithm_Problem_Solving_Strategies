#include <iostream>
#include <cstring>
using namespace std;

int C, n;
int cache[101];
int symcache[101];
const int MOD = 1000000007;

int symtiling(int remainW);

int tiling(int width) {
	//기저 사례: width가 1 이하일 때
	if (width <= 1) return 1;
	//메모이제이션
	int& ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;
}

//내가 생각한 답 1. 직사각형을 타일로 채우는 모든 경우의 수에서
//대칭인 타일로 채우는 경우를 빼는 방식으로 구현하고자 하였다.
//대칭 타일이기 위해서는 양쪽 끝이 모두 세로 블럭이거나 가로 블럭이어야 한다.
int symtiling(int remainW) {
	if (remainW == 2)
		return 2;
	if (remainW == 0 || remainW == 1)
		return 1;
	if (remainW < 0)
		return 0;

	int& ret = symcache[remainW];
	if (ret != -1) return ret;
	return ret = (symtiling(remainW - 2) + symtiling(remainW - 4)) % MOD;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n;
		memset(cache, -1, sizeof(cache));
		memset(symcache, -1, sizeof(symcache));
		cout << (tiling(n) - symtiling(n) + MOD) % MOD << endl;

		//내가 생각한 답 2. 굳이 대칭인 타일을 세는 함수를 구현하지 않고
		//기존 함수로 문제를 푸는 방법이다.
		//대칭인 타일은 다음과 같이 생성할 수 있다.

		//1. n이 짝수일 때: 가운데에 길이 2의 가로 블럭 하나를 넣고 왼쪽에서 (n-1)/2 길이의
		//타일을 채우는 경우를 센 후 오른쪽에 뒤집어 붙여넣는 경우와, n/2 길이의 타일을
		//채우는 경우를 센후 오른쪽에 뒤집어 붙여넣는 경우를 더하면 된다.

		//2. n이 홀수일 때: 가운데에 길이 1인 세로 블럭 하나를 넣고 왼쪽에서 n/2 길이의 타일을
		//채우는 경우를 센 후 오른쪽에 뒤집에 붙여넣는 경우를 세면 된다.

		int a = tiling(n);
		int b = (n%2 == 0 ? tiling(n / 2) + tiling((n - 1) / 2) : tiling(n/2)) % MOD;
		cout << (a - b + MOD) % MOD << endl;
	}
	return 0;
}