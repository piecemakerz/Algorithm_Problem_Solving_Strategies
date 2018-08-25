#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX = 50000000;
const long long MOD = pow<long long>(2, 32);
int C, K, N;

//�� Ǯ��.
int solve(int k) {
	int ret = 0, curSum = 0;
	queue<int> inputSignal;
	long long curSignal = 1983;
	int curInput = 1984;

	for (int i = 0; i < N; i++) {
		inputSignal.push(curInput);
		curSum += inputSignal.back();
		while (curSum >= k) {
			if (curSum == k)
				ret++;
			curSum -= inputSignal.front();
			inputSignal.pop();
		}
		curSignal = ((long long)curSignal * 214013LL + 2531011LL) % MOD;
		curInput = curSignal % 10000 + 1;
	}
	return ret;
}

//å�� �ܰ� ��ȣ �м� ������ �ذ��ϴ� ���� �ܼ��� �˰���.
//��� �κ� ������ �˻��ϸ鼭 ���� K�� ���� ã�´�.
int simple(const vector<int>& signals, int k) {
	int ret = 0;
	for (int head = 0; head < signals.size(); head++) {
		int sum = 0;
		for (int tail = head; tail < signals.size(); tail++) {
			//sum�� [head, tail] ������ ���̴�.
			sum += signals[tail];
			if (sum == k) ret++;
			if (sum >= k) break;
		}
	}
	return ret;
}

//å�� �ܰ� ��ȣ �м� ������ �ذ��ϴ� ����ȭ�� �˰���
int optimized(const vector<int>& signals, int k) {
	int ret = 0, tail = 0, rangeSum = signals[0];
	for (int head = 0; head < signals.size(); head++) {
		//rangeSum�� k �̻��� ������ ������ ���� ������ tail�� �ű��.
		while (rangeSum < k && tail + 1 < signals.size())
			rangeSum += signals[++tail];
		if (rangeSum == k) ret++;

		//signals[head]�� ���� �������� ������.
		rangeSum -= signals[head];
	}
	return ret;
}

//å�� �ܰ� ��ȣ �м� ������ �ذ��ϴ� �¶��� �˰���.

//�ܰ� ��ȣ �м� �������� ����ϴ� ���� �յ� ���� �������� ����
//���������� unsigned �ڷ����� ��������ν� 2^32�� ���� �������� ���ϴ�
//������ �� �ʿ䰡 ����.
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
	RNG rng; //��ȣ���� �����ϴ� ���� ������
	queue<int> range; //���� ������ ��� �ִ� ���ڵ��� �����ϴ� ť
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
	for (int test = 0; test < C; test++) {
		cin >> K >> N;
		cout << solve(K) << endl;
	}
}