#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 10000000;
int C, n;

int cache[101][101];

//�� Ǯ��. å�� Ǯ�̿� ������ �������� ������.
//curLength = ���� �������� ����
//blocks = ������� ����� ���簢���� ����
int mypoly(int curLength, int blocks) {
	if (blocks == n) return 1;
	int& ret = cache[curLength][blocks];
	if (ret != -1) return ret;

	ret = 0;
	for (int nextLength = 1; nextLength + blocks <= n; nextLength++) {
		int posWays = (blocks == 0 ? 1 : curLength + nextLength - 1);
		ret += ((mypoly(nextLength, blocks + nextLength) % MOD) * (posWays % MOD)) % MOD;
	}

	return ret;
}

//å�� Ǯ��.
//n���� ���簢������ �̷������, �� �� �����ٿ� first����
//���簢���� �����ϴ� �������̳��� ���� ��ȯ�Ѵ�.
int poly(int n, int first) {
	//���� ���: n == first
	if (n == first) return 1;
	//�޸������̼�
	int& ret = cache[n][first];
	if (ret != -1) return ret;
	ret = 0;
	for (int second = 1; second <= n - first; second++) {
		int add = second + first - 1;
		add *= poly(n - first, second);
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << mypoly(0, 0) % MOD << endl;
	}
}