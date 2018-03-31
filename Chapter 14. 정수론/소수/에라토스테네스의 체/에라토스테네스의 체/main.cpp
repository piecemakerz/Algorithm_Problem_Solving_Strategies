#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX_N = 100;
int n;
bool isPrime[MAX_N + 1];
// 가장 단순한 형태의 에라토스테네스의 체의 구현
// 종료한 뒤 isPrime[i]가 소수인지 확인
void erastosthenes() {
	memset(isPrime, 1, sizeof(isPrime));
	//1은 항상 예외 처리
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(n));
	for (int i = 2; i < sqrtn; i++)
		//이 수가 아직 지워지지 않았다면
		if (isPrime[i])
			//i의 배수 j들에 대해 isPrime[i] = false로 둔다.
			//i*i 미만의 배수는 이미 지워졌으므로 신경 쓰지 않는다.
			for (int j = i*i; j <= n; j += i)
				isPrime[j] = false;
}