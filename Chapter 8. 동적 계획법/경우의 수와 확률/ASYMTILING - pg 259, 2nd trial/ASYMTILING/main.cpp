#include <iostream>
#include <cstring>
using namespace std;

int C, n;
int cache[101];
int symcache[101];
const int MOD = 1000000007;

int tiling(int width) {
	//���� ���: width�� 1 ������ ��
	if (width <= 1) return 1;
	//�޸������̼�
	int& ret = cache[width];
	if (ret != -1) return ret;
	return ret = (tiling(width - 2) + tiling(width - 1)) % MOD;
}

//���� ������ �� 1. ���簢���� Ÿ�Ϸ� ä��� ��� ����� ������
//��Ī�� Ÿ�Ϸ� ä��� ��츦 ���� ������� �����ϰ��� �Ͽ���.
//��Ī Ÿ���̱� ���ؼ��� ���� ���� ��� ���� ���̰ų� ���� ���̾�� �Ѵ�.
int symtiling(int remainW) {
	if (remainW == 2)
		return 2;
	if (remainW == 0 || remainW == 1)
		return 1;
	if (remainW < 0)
		return 0;

	int& ret = symcache[remainW];
	if (ret != -1) return ret;
	return ret = (symtiling(remainW - 2) + symtiling(remainW - 4)) % MOD;
}

//å�� Ǯ�� 1. ���Ī Ÿ�ϸ� ������ �ذ��ϴ� ���� ��ȹ�� �˰���.
//�� Ǯ�� 2�� ���� ������� �˰����� �����Ͽ���. ��,
//���Ī Ÿ�ϸ� ����� ���� ��ü Ÿ�ϸ� ����� ������ ��Ī Ÿ�ϸ���
//���� ��� ������� ����Ǿ���.
//asymmetric(width) = 2*width ũ���� �簢���� ä��� ���Ī ����� ���� ��ȯ�Ѵ�.
int asymmetric(int width) {
	//n�� Ȧ���� ���, Ÿ�ϸ� ����� ��Ī�̱� ���ؼ���
	//�׻� ����� �ִ� �������� ���� Ÿ�� �ϳ��� ����� �ϸ�,
	//���� ������ ������ ���ݰ� ���� ��Ī�̾�� �Ѵ�.
	if (width % 2 == 1)
		return (tiling(width) - tiling(width / 2) + MOD) % MOD;

	//n�� ¦���� ���, ��Ī Ÿ�ϸ�����
	//a) ����� ������ ���� ���� Ÿ�Ϸ� ���� ������ ������ ���� ��Ī�� ����
	//b) �������� ���� �κе��� ���� ��Ī�� ���
	//�� ������ �����Ѵ�.
	int ret = tiling(width);
	ret = (ret - tiling(width / 2) + MOD) % MOD;
	ret = (ret - tiling(width / 2 - 1) + MOD) % MOD;
	return ret;
}

//å�� Ǯ�� 2. ���� ���Ī Ÿ�ϸ��� ���� ���� ���� ��ȹ�� �˰���
//asymmetric2(width) = 2*width ũ���� �簢���� ä��� ���Ī ����� ���� ��ȯ�Ѵ�.
int asymmetric2(int width) {
	//���� ���: �ʺ� 2 ������ ��� ���Ī�� ���ɼ��� ����.
	if (width <= 2) return 0;
	//�޸������̼�
	int& ret = cache[width];
	if (ret != -1) return ret;
	ret = asymmetric2(width - 2) % MOD; //��� 1
	ret = (ret + asymmetric2(width - 4)) % MOD; //��� 2
	ret = (ret + tiling(width - 3)) % MOD; //��� 3
	ret = (ret + tiling(width - 3)) % MOD; // ��� 4
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n;
		memset(cache, -1, sizeof(cache));
		memset(symcache, -1, sizeof(symcache));
		cout << (tiling(n) - symtiling(n) + MOD) % MOD << endl;

		//���� ������ �� 2. ���� ��Ī�� Ÿ���� ���� �Լ��� �������� �ʰ�
		//���� �Լ��� ������ Ǫ�� ����̴�.
		//��Ī�� Ÿ���� ������ ���� ������ �� �ִ�.

		//1. n�� ¦���� ��: ����� ���� 2�� ���� �� �ϳ��� �ְ� ���ʿ��� (n-1)/2 ������
		//Ÿ���� ä��� ��츦 �� �� �����ʿ� ������ �ٿ��ִ� ����, n/2 ������ Ÿ����
		//ä��� ��츦 ���� �����ʿ� ������ �ٿ��ִ� ��츦 ���ϸ� �ȴ�.

		//2. n�� Ȧ���� ��: ����� ���� 1�� ���� �� �ϳ��� �ְ� ���ʿ��� n/2 ������ Ÿ����
		//ä��� ��츦 �� �� �����ʿ� ������ �ٿ��ִ� ��츦 ���� �ȴ�.

		int a = tiling(n);
		int b = (n%2 == 0 ? tiling(n / 2) + tiling((n - 1) / 2) : tiling(n/2)) % MOD;
		cout << (a - b + MOD) % MOD << endl;
	}
	return 0;
}