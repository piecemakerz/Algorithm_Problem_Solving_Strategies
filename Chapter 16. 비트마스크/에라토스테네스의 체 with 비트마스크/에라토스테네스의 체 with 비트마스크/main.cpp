#include <iostream>
using namespace std;

const int MAX_N = 100;
int n;
unsigned char sieve[(MAX_N + 7) / 8];
//k가 소수인지 확인한다.
inline bool isPrime(int k) {
	return sieve[k >> 3] & (1 << (k & 7));
}
//k가 소수가 아니라고 표시한다.
inline void setComposite(int k) {
	sieve[k >> 3] &= ~(1 << (k & 7)); // 해당 비트만 꺼지고 나머지는 모두 켜진 숫자와 AND연산
}
//비트마스크를 사용하는 에라토스테네스의 체의 구현
//이 함수를 수행하고 난 뒤, isPrime()을 이용해 각 수가 소수인지 알 수 있다.
void eratosThenes() {
	memset(sieve, 255, sizeof(sieve));
	setComposite(0);
	setComposite(1);
	int sqrtn = int(sqrt(n));
	for (int i = 2; i <= sqrtn; i++)
		//이 수가 아직 지워지지 않았다면
		if (isPrime(i))
			//i의 배수 j들에 대해 isPrime[j] = false로 둔다.
			//i*i 미만의 배수는 이미 지워졌으므로 신경 쓰지 않는다.
			for (int j = i*i; j <= n; j += i)
				setComposite(j);
}