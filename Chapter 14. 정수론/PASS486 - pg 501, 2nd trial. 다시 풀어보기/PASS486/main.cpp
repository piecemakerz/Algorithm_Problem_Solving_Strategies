#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10000000;
int c, n, lo, hi;
int divisorNum[MAXN+1];

//내 풀이. 에라토스테네스의 체를 구현하는 알고리즘을 응용하여
//i를 2부터 sqrt(10000000)까지 순회하며 i를 약수로 가지는 천만 이하의
//모든 수의 약수 개수를 갱신한다. 이렇게 모든 수에 대한 약수의 개수를
//미리 계산해두면 테스트 케이스에서 어떤 입력이 주어지던 O(hi-lo)만에
//답을 찾을 수 있다.
void eratosthenes() {
	divisorNum[0] = divisorNum[1] = -1;
	for (int i = 2; i <= MAXN; i++)
		divisorNum[i] = 2;

	int sqrtn = int(sqrt(MAXN));
	for (int i = 2; i <= sqrtn; i++) {
		for (int j = i * 2; j <= MAXN; j += i) {
			if ((j / i) > sqrtn)
				divisorNum[j] += 2;
			else
				divisorNum[j] += 1;
		}
	}
}
int solve() {
	int count = 0;
	for (int i = lo; i <= hi; i++)
		if (divisorNum[i] == n)
			count++;
	return count;
}

//1천만 이하의 모든 수의 약수의 수를 계산하는 책의 알고리즘.

//minFactor[i] = i의 가장 작은 소인수 (i가 소수인 경우 자기 자신)
int minFactor[MAXN + 1];
//minFactorPower[i] = i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는가?
int minFactorPower[MAXN + 1];
//factors[i] = i가 가진 약수의 수
int factors[MAXN + 1];

//에라토스테네스의 체를 이용하여 미리 소인수 분해를 한다.
void eratosthenes2() {
	minFactor[0] = minFactor[1] = -1;
	for (int i = 2; i <= MAXN; i++)
		minFactor[i] = i;
	//에라토스테네스의 체를 수행한다.
	int sqrtn = int(sqrt(MAXN));
	for (int i = 2; i <= sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i * i; j <= MAXN; j += i)
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}
void getFactorsSmart() {
	factors[1] = 1;
	for (int n = 2; n <= MAXN; n++) {
		//소수인 경우 약수가 두 개 밖에 없다
		if (minFactor[n] == n) {
			minFactorPower[n] = 1;
			factors[n] = 2;
		}
		//소수가 아닌 경우, 가장 작은 소인수로 나눈 수(m)의
		//약수의 수를 응용해 n의 약수의 수를 찾는다.
		else {
			int p = minFactor[n];
			int m = n / p;
			//m이 p로 더이상 나누어 지지 않는 경우
			if (p != minFactor[m])
				minFactorPower[n] = 1;
			else
				minFactorPower[n] = minFactorPower[m] + 1;
			int a = minFactorPower[n];
			factors[n] = (factors[m] / a) * (a + 1);
		}
	}
}

//1천만 이하의 모든 수의 약수의 수를 계산하는 책의 단순한 알고리즘.
//내 풀이는 이 알고리즘과 비슷하나 에라토스테네스의 체 알고리즘을 응용하여
//더 빠르게 문제를 해결하였다.
void getFactorsBrute() {
	memset(factors, 0, sizeof(factors));
	for (int div = 1; div <= MAXN; div++)
		for (int multiple = div; multiple <= MAXN; multiple += div)
			factors[multiple] += 1;
}

int main(void) {
	cin >> c;
	eratosthenes();
	//eratosthenes2();
	//getFactorsSmart();
	for (int test = 0; test < c; test++) {
		cin >> n >> lo >> hi;
		cout << solve() << endl;
	}
}