#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
/*
// 내 풀이
// 처음에 ret, checked를 factor()함수 안의 벡터로 정의했고, selectedNum벡터도 for문 내부에서 선언하여
// for문이 종료하면 자동으로 벡터가 메모리에서 해제되고 다시 할당하는 방식으로 알고리즘을 작성했다.
// 하지만, for문이 최대 백만번을 돌고, 또 벡터 생성 자체가 배열 생성보다 훨씬 오래 걸리는 작업이기 때문에
// 시간초과가 났었다. 이는 ret과 checked벡터를 전역배열로 정의하고, selectedNum벡터를 for문 밖에 정의하여
// for문의 끝에서 clear()해주는 것으로 해결할 수 있었다.

const int MAX = 10000001;
int minFactor[MAX];
int ret[MAX]; // 소인수 출현 횟수
bool checked[MAX]; // 해당 소인수 체크 여부
int C, hi, lo, n;

void eratosthenes() {
	minFactor[0] = minFactor[1] = -1;
	for (int i = 2; i <= MAX; i++)
		minFactor[i] = i;
	int sqrtn = int(sqrt(MAX));
	for (int i = 2; i <= sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i*i; j <= MAX; j += i)
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}

int factor() {
	int passwordCount = 0;
	vector<int> selectedNum; // 해당 숫자의 소인수 밑수들
	for (int i = lo; i <= hi; i++) {
		int num = i;
		while (num > 1) {
			if (!checked[minFactor[num]]) { // 해당 밑수를 체크하지 않았다면
				checked[minFactor[num]] = true;
				selectedNum.push_back(minFactor[num]); // 밑수 결과에 저장
			}
			ret[minFactor[num]]++; // 지수 증가
			num /= minFactor[num];
		}
		int numOfdivisor = 1;
		for (int i = 0; i < selectedNum.size(); i++) {
			numOfdivisor *= (ret[selectedNum[i]] + 1);
			checked[selectedNum[i]] = false;
			ret[selectedNum[i]] = 0;
		}

		if (numOfdivisor == n)
			passwordCount++;
		selectedNum.clear();
	}
	return passwordCount;
}

int main(void) {
	eratosthenes();
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n >> lo >> hi;
		cout << factor() << endl;
	}
	return 0;
}
*/

//책의 풀이
const int TM = 10000000;
int minFactor[TM + 1];
//minFactorPower[i] = i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는가?
int minFactorPower[TM + 1];
//factors[i] = i가 가진 약수의 수
int factors[TM + 1];

void getFactorSmart() {
	factors[1] = 1;
	for (int n = 2; n <= TM; n++) {
		//소수인 경우 약수가 두 개 밖에 없다.
		if (minFactor[n] == n) {
			minFactorPower[n] = 1;
			factors[n] = 2;
		}
		//소수가 아닌 경우, 가장 작은 소인수로 나눈 수(m)의
		//약수의 수를 응용해 n의 약수의 수를 찾는다.
		else {
			int p = minFactor[n];
			int m = n / p;
			//m이 p로 더이상 나누어지지 않는 경우
			if (p != minFactor[m])
				minFactorPower[n] = 1;
			else
				minFactorPower[n] = minFactorPower[m] + 1;
			int a = minFactorPower[n];
			factors[n] = (factors[m] / a) * (a + 1);
		}
	}
}

//책의 풀이 2 - 모든 수의 약수의 수를 계산하는 단순한 알고리즘
void getFactorsBrute() {
	memset(factors, 0, sizeof(factors));
	for (int div = 1; div <= TM; div++)
		for (int multiple = div; multiple <= TM; multiple += div)
			factors[multiple] += 1;
}