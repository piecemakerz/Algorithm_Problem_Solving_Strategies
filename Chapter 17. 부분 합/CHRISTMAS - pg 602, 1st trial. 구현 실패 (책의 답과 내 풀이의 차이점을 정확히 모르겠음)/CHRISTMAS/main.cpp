#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

//�� Ǯ�� - �ð� �ʰ��� �߻��Ѵ�.
/*
const int MAXN = 100000;
int C, N, K;
int box[MAXN];
vector<int> psum; // �κ���
//vector<vector<int>> psumsum; // ������ - ��� �� �ִ� MAXN * MAXN ũ���� ���Ͱ� ��������Ƿ� 
//���� �����÷ο찡 �߻��Ѵ�.
int cache[MAXN+1];

//�迭 box�� �κ����� ����Ѵ�.
vector<int> partialSum() {
	vector<int> ret(N);
	ret[0] = box[0];
	for (int i = 1; i < N; i++)
		ret[i] = ret[i - 1] + box[i];
	return ret;
}

//���� ��
int rangeSum(int a, int b) {
	if (a == 0) return psum[b];
	return psum[b] - psum[a - 1];
}

//1�� ���� - �� ���� �ֹ��� �� ���� �� ������ �ֹ� ���
int numOfWays() {
	int ways = 0;
	for (int i = 0; i < N; i++)
		for (int j = i; j < N; j++)
			if (rangeSum(i, j) % K == 0)
				ways = (ways+1)%20091101;
	return ways;
}

//2�� ���� - ���� �� �ֹ� ���� �� �ֹ��� ��ġ�� �ʰ� �ֹ��� �� �ִ� �ִ� ����� ��
//select = �̹��� ������ ����
int maxOrders(int select = 0) {
	if (select >= N)
		return 0;

	int& ret = cache[select]; // select�� ���ں��� �ֹ��� ��� �ֹ��� �� �ִ� �ִ� �ֹ� ��
	if (ret != -1)
		return ret;
	
	ret = 0;
	// �̹� ���ں��� �ֹ��� ���
	for (int i = select; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (rangeSum(i,j) % K == 0)
				ret = max(ret, 1 + maxOrders(j + 1));
		}
	}
	return ret;
}
*/


//å�� ��
int C, N, K;
const int MAXN = 100000;
int D[MAXN];

void partialSum(vector<int>& psum) {
	psum[1] = D[0]%K;
	for (int i = 2; i < psum.size(); i++)
		psum[i] = (psum[i - 1] + D[i-1])%K;
}
//D[]�� �κ� �� �迭 psum[]�� k�� �־��� ��, �� ���� ������� �� �� �ִ��� ��ȯ�Ѵ�.
//psum[]�� ù ��° ���� ���� 0�� �����ߴٰ� �����Ѵ�.
int waysToBuy(const vector<int>& psum, int k) {
	const int MOD = 20091101;
	int ret = 0;
	//psum[]�� �� ���� �� ���̳� �� �� �ִ��� ����Ѵ�.
	vector<long long> count(k, 0);
	for (int i = 0; i < psum.size(); i++)
		count[psum[i]]++;

	for (int i = 0; i < K; i++)
		if (count[i] >= 2)
			ret = (ret + ((count[i] * (count[i] - 1)) / 2)) % MOD;
	return ret;
}
//D[]�� �κ� �� �迭 psum[]�� k�� �־��� ��, �� ���̳� �� �� �ִ��� ��ȯ�Ѵ�.
//psum[]�� ù ��° ���� ���� 0�� �����ߴٰ� �����Ѵ�.
int maxBuys(const vector<int>& psum, int k) {
	//ret[i] = ù ��° ���ں��� i��° ���ڱ��� ������� �� �� �� �ִ� �ִ� Ƚ��
	vector<int> ret(psum.size(), 0);
	//prev[s] = psum[]�� s���� ������ ��ġ
	vector<int> prev(k, -1);
	for (int i = 0; i < psum.size(); i++) {
		//i��° ���ڸ� �ƿ� ������� �ʴ� ���
		if (i > 0)
			ret[i] = ret[i - 1];
		else
			ret[i] = 0;
		//psum[i]�� ������ �� ���� ������, prev[psum[i]] + 1���� ������� �� �� ����.
		int loc = prev[psum[i]];
		if (loc != -1) ret[i] = max(ret[i], ret[loc] + 1);
		//prev[]�� ���� ��ġ�� ����Ѵ�.
		prev[psum[i]] = i;
	}
	return ret.back();
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(D, 0, sizeof(D));

		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++)
			scanf("%d", &D[i]);

		vector<int> psum(N + 1, 0);
		psum[0] = 0;
		partialSum(psum);
		vector<int>::iterator iter = psum.begin();

		printf("%d %d\n", waysToBuy(psum, K), maxBuys(psum, K));
	}
	return 0;
}