#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 50000000;
const long long mod = pow<long long>(2, 32);

int C, K, N;
unsigned int A[2];
//int signal[MAXN];
int numOfK;

//내 답. 스택 오버플로우가 떠서 책의 답을 참고하여
//신호를 미리 생성하여 저장해놓은 signal배열을 없애고
//반복문 내에서 그때마다 신호를 생성한다.
int generateSignal(int i) {
	if (i == 0)
		return A[0];

	A[i % 2] = ((long long)A[(i - 1) % 2] * 214013LL + 2531011LL) % mod;
	return A[i % 2] % 10000 + 1;
}

//sum에 이전까지 계산한 후보 구간의 합을 저장하므로 tail이 증가한 후에
//구간합을 새로 계산할 필요 없이 sum에서 head에 해당하는 원소만 빼면 된다.

void calPartialSeq() {
	queue<int> ret; // 아직 선택되지 않은 신호들
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		int signalNum = generateSignal(i);
		ret.push(signalNum);
		sum += signalNum;
		//while문의 내부가 실행될 때마다 head가 증가하므로
		//while문은 최대 N번 수행된다.
		while (sum >= K && !ret.empty()) {
			if (sum == K)
				numOfK++;
			sum -= ret.front();
			ret.pop();
		}
	}

	while (!ret.empty()) {
		if (sum >= K) {
			if (sum == K) {
				numOfK++;
				break;
			}
			sum -= ret.front();
			ret.pop();
		}
	}
}

//책의 답
//내 답과 풀이과정이 완전히 동일하나 난수 생성기의 도입과
//내 알고리즘보다 훨씬 깔끔한 구현을 참고하자.

struct RNG {
	unsigned seed;
	RNG() : seed(1983) {}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};

int countRanges(int k, int n) {
	RNG rng; // 신호값을 생성하는 난수 생성기
	queue<int> range; // 현재 구간에 들어 있는 숫자들을 저장하는 큐
	int ret = 0, rangeSum = 0;
	for (int i = 0; i < n; i++) {
		//구간에 숫자를 추가한다.
		int newSignal = rng.next();
		rangeSum += newSignal;
		range.push(newSignal);

		//구간의 합이 k를 초과하는 동안 구간에서 숫자를 뺀다.
		while (rangeSum > k) {
			rangeSum -= range.front();
			range.pop();
		}
		if (rangeSum == k) ret++;
	}
	return ret;
}
int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		A[0] = 1983;
		numOfK = 0;
		cin >> K >> N;
		calPartialSeq();
		cout << numOfK << endl;
	}
}