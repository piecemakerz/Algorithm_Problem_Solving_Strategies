#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_N = 100;

// 주어진 정수 n을 소인수분해하는 간단한 알고리즘
vector<int> factorSimple(int n) {
	vector<int> ret;
	int sqrtn = int(sqrt(n));
	for (int div = 2; div <= sqrtn; div++)
		while (n % div == 0) {
			n /= div;
			ret.push_back(div);
		}
	if (n > 1) ret.push_back(n);
	return ret;
}

//에라토스테네스의 체를 이용한 빠른 소인수 분해
//minFactor[i] = i의 가장 작은 소인수(i가 소수인 경우 자기 자신
int minFactor[MAX_N];
//에라토스테네스의 체를 수행하면서 소인수분해를 위한 정보도 저장한다.
void eratosthenes2(int n) {
	//1은 항상 예외 처리
	minFactor[0] = minFactor[1] = -1;
	//모든 숫자를 처음에는 소수로 표시해 둔다.
	for (int i = 2; i <= n; i++)
		minFactor[i] = i;
	//에라토스테네스의 체를 수행한다.
	int sqrtn = int(sqrt(n));
	for (int i = 2; i < sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i*i; i <= n; j += i)
				//아직 약수를 본 적 없는 숫자인 경우 i를 써 둔다.
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}

}
// 2 이상의 자연수 n을 소인수분해한 결과를 반환한다.
vector<int> factor(int n) {
	vector<int> ret;
	//n이 1이 될 때까지 가장 작은 소인수로 나누기를 반복한다.
	while (n > 1) {
		ret.push_back(minFactor[n]);
		n /= minFactor[n];
	}
	return ret;
}