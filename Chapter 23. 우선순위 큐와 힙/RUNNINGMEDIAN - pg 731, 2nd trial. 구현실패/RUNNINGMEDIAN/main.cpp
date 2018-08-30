#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

vector<int> heap;
int C, N, a, b;

struct RNG {
	int seed;
	RNG() : seed(1983) {}
	unsigned next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};

//���� �̿��� ��ȭ�ϴ� �߰� �� ������ �ذ��ϴ� å�� �Լ� ����
int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;
	//�ݺ��� �Һ���:
	//1. maxHeap�� ũ��� minHeap�� ũ��� ���ų� 1 �� ũ��.
	//2. maxHeap.top() <= minHeap.top()
	for (int cnt = 1; cnt <= n; cnt++) {
		//�켱 1�� �Һ��ĺ��� ������Ų��.
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		//2�� �Һ����� ������ ��� ��������.
		if (!minHeap.empty() && !maxHeap.empty() &&
			minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b); minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N >> a >> b;
		cout << runningMedian(N, RNG())<<endl;
	}
}