#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 50000000;
const long long mod = pow<long long>(2, 32);

int C, K, N;
unsigned int A[MAXN];
int signal[MAXN];
int numOfK;

void generateSignal() {
	A[0] = 1983;
	for (int i = 1; i < MAXN; i++)
		A[i] = ((long long)A[i-1] * 214013LL + 2531011LL) % mod;
}

void generateProcessedSignal() { 
	for (int i = 0; i < MAXN; i++) {
		signal[i] = A[i] % 10000LL + 1;
	}
}

void calPartialSeq() {
	queue<int> ret; // 아직 선택되지 않은 신호들
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		ret.push(signal[i]);
		sum += signal[i];
		while (!ret.empty() && sum >= K) {
			if (sum == K) {
				numOfK++;
				while (!ret.empty())
					ret.pop();
				sum = 0;
				break;
			}
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
		else
			break;
	}
}

int main(void) {
	generateSignal();
	generateProcessedSignal();
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		numOfK = 0;
		cin >> K >> N;
		calPartialSeq();
		cout << numOfK << endl;
	}
}