#include <iostream>
#include <cstring>
using namespace std;

int C, n;

int cache[101];
const int MOD = 1000000007;
//�� Ǯ��. å�� Ǯ�̺��� �� �����ϴ�. ����ó���� �ٲٸ� �ڵ尡 ��
//�������� �� �־���.
//tileWays(len) = Ÿ�Ϸ� ä���� ���� �簢���� ���� ���̰� len�� ��,
//���� ������ ä�� �� �ִ� ����� ��
int tileWays(int len) {
	if (len == 0)
		return 1;
	int& ret = cache[len];
	if (ret != -1) return ret;

	ret = 0;
	if (len >= 1)
		ret += tileWays(len - 1) % MOD;
	if (len >= 2)
		ret += tileWays(len - 2) % MOD;

	return ret %= MOD;
}

//å�� ��. Ÿ�ϸ��� ���� ���� ���� ��ȹ�� �˰���.
//2*width ũ���� �簢���� ä��� ����� ���� MOD�� ���� �������� ��ȯ�Ѵ�.
int tiling(int width) {
	//���� ���: width�� 1 ������ ��
	if (width <= 1) return 1;
	//�޸������̼�
	int& ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << tileWays(n) << endl;
	}
	return 0;
}