#include <iostream>
#include <cstring>
using namespace std;

int C, n;
int cache[101];
int symcache[101];
const int MOD = 1000000007;

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

//책의 풀이 1. 비대칭 타일링 문제를 해결하는 동적 계획법 알고리즘.
//내 풀이 2와 같은 방법으로 알고리즘을 설계하였다. 즉,
//비대칭 타일링 방법의 수를 전체 타일링 방법의 수에서 대칭 타일링을
//빼서 얻는 방식으로 설계되었다.
//asymmetric(width) = 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric(int width) {
	//n이 홀수인 경우, 타일링 방법이 대칭이기 위해서는
	//항상 정가운데 있는 세로줄은 세로 타일 하나로 덮어야 하며,
	//왼쪽 절반은 오른쪽 절반과 서로 대칭이어야 한다.
	if (width % 2 == 1)
		return (tiling(width) - tiling(width / 2) + MOD) % MOD;

	//n이 짝수인 경우, 대칭 타일링에는
	//a) 정가운데 세로줄 둘을 가로 타일로 덮고 나머지 절반이 서로 대칭인 경우와
	//b) 절반으로 나뉜 부분들이 서로 대칭인 경우
	//두 종류가 존재한다.
	int ret = tiling(width);
	ret = (ret - tiling(width / 2) + MOD) % MOD;
	ret = (ret - tiling(width / 2 - 1) + MOD) % MOD;
	return ret;
}

//책의 풀이 2. 직접 비대칭 타일링의 수를 세는 동적 계획법 알고리즘
//asymmetric2(width) = 2*width 크기의 사각형을 채우는 비대칭 방법의 수를 반환한다.
int asymmetric2(int width) {
	//기저 사례: 너비가 2 이하인 경우 비대칭일 가능성이 없다.
	if (width <= 2) return 0;
	//메모이제이션
	int& ret = cache[width];
	if (ret != -1) return ret;
	ret = asymmetric2(width - 2) % MOD; //경우 1
	ret = (ret + asymmetric2(width - 4)) % MOD; //경우 2
	ret = (ret + tiling(width - 3)) % MOD; //경우 3
	ret = (ret + tiling(width - 3)) % MOD; // 경우 4
	return ret;
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