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

//�� ��. ���� �����÷ο찡 ���� å�� ���� �����Ͽ�
//��ȣ�� �̸� �����Ͽ� �����س��� signal�迭�� ���ְ�
//�ݺ��� ������ �׶����� ��ȣ�� �����Ѵ�.
int generateSignal(int i) {
	if (i == 0)
		return A[0];

	A[i % 2] = ((long long)A[(i - 1) % 2] * 214013LL + 2531011LL) % mod;
	return A[i % 2] % 10000 + 1;
}

//sum�� �������� ����� �ĺ� ������ ���� �����ϹǷ� tail�� ������ �Ŀ�
//�������� ���� ����� �ʿ� ���� sum���� head�� �ش��ϴ� ���Ҹ� ���� �ȴ�.

void calPartialSeq() {
	queue<int> ret; // ���� ���õ��� ���� ��ȣ��
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		int signalNum = generateSignal(i);
		ret.push(signalNum);
		sum += signalNum;
		//while���� ���ΰ� ����� ������ head�� �����ϹǷ�
		//while���� �ִ� N�� ����ȴ�.
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

//å�� ��
//�� ��� Ǯ�̰����� ������ �����ϳ� ���� �������� ���԰�
//�� �˰��򺸴� �ξ� ����� ������ ��������.

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
	RNG rng; // ��ȣ���� �����ϴ� ���� ������
	queue<int> range; // ���� ������ ��� �ִ� ���ڵ��� �����ϴ� ť
	int ret = 0, rangeSum = 0;
	for (int i = 0; i < n; i++) {
		//������ ���ڸ� �߰��Ѵ�.
		int newSignal = rng.next();
		rangeSum += newSignal;
		range.push(newSignal);

		//������ ���� k�� �ʰ��ϴ� ���� �������� ���ڸ� ����.
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