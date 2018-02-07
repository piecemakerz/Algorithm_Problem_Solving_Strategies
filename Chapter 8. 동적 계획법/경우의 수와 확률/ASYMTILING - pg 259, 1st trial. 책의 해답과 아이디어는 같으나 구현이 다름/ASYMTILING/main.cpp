#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int cache[101];
int asymCache[101];
int cache2[101];
const int MOD = 1000000007;

int totalTiles(int curN) {
	if (curN == 1)
		return 1;
	else if (curN == 2)
		return 2;

	int& ret = cache[curN];
	if (ret != -1) return ret;
	return ret = (totalTiles(curN - 1) + totalTiles(curN - 2)) % MOD;
}

int asymTiles(int curN) {
	if (curN == 1 || curN == 0)
		return 1;
	else if (curN == 2)
		return 2;
	else if (curN < 0)
		return 0;

	int& ret = asymCache[curN];
	if (ret != -1) return ret;
	return ret = (asymTiles(curN - 2) + asymTiles(curN - 4)) % MOD;
}

// å�� �� - ��� ����� ������ ��Ī�� ��츦 ���� ���
int asymmetric(int width) {
	if (width % 2 == 1)
		return (totalTiles(width) - totalTiles(width / 2) + MOD) % MOD;
	int ret = totalTiles(width);
	ret = (ret - totalTiles(width / 2) + MOD) % MOD;
	ret = (ret - totalTiles(width / 2 - 1) + MOD) % MOD;
	return ret;
}

//å�� �� 2 - ���Ī�� ��츦 ���� ���� ���
int asymmetric2(int width) {
	//���� ���: �ʺ� 2 ������ ���
	if (width <= 2) return 0;
	int& ret = cache2[width];
	if (ret != -1) return ret;
	ret = asymmetric2(width - 2) % MOD;
	ret = (ret + asymmetric2(width - 4)) % MOD;
	ret = (ret + totalTiles(width - 3)) % MOD;
	ret = (ret + totalTiles(width - 3)) % MOD;
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(cache, -1, sizeof(cache));
		memset(asymCache, -1, sizeof(asymCache));
		cin >> n;
		cout << (totalTiles(n) - asymTiles(n) + MOD)%MOD  << endl;
	}
}