#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10000000;
int c, n, lo, hi;
int divisorNum[MAXN+1];

//�� Ǯ��. �����佺�׳׽��� ü�� �����ϴ� �˰����� �����Ͽ�
//i�� 2���� sqrt(10000000)���� ��ȸ�ϸ� i�� ����� ������ õ�� ������
//��� ���� ��� ������ �����Ѵ�. �̷��� ��� ���� ���� ����� ������
//�̸� ����صθ� �׽�Ʈ ���̽����� � �Է��� �־����� O(hi-lo)����
//���� ã�� �� �ִ�.
void eratosthenes() {
	divisorNum[0] = divisorNum[1] = -1;
	for (int i = 2; i <= MAXN; i++)
		divisorNum[i] = 2;

	int sqrtn = int(sqrt(MAXN));
	for (int i = 2; i <= sqrtn; i++) {
		for (int j = i * 2; j <= MAXN; j += i) {
			if ((j / i) > sqrtn)
				divisorNum[j] += 2;
			else
				divisorNum[j] += 1;
		}
	}
}
int solve() {
	int count = 0;
	for (int i = lo; i <= hi; i++)
		if (divisorNum[i] == n)
			count++;
	return count;
}

//1õ�� ������ ��� ���� ����� ���� ����ϴ� å�� �˰���.

//minFactor[i] = i�� ���� ���� ���μ� (i�� �Ҽ��� ��� �ڱ� �ڽ�)
int minFactor[MAXN + 1];
//minFactorPower[i] = i�� ���μ� ���ؿ��� minFactor[i]�� �� ���� ���ԵǾ� �ִ°�?
int minFactorPower[MAXN + 1];
//factors[i] = i�� ���� ����� ��
int factors[MAXN + 1];

//�����佺�׳׽��� ü�� �̿��Ͽ� �̸� ���μ� ���ظ� �Ѵ�.
void eratosthenes2() {
	minFactor[0] = minFactor[1] = -1;
	for (int i = 2; i <= MAXN; i++)
		minFactor[i] = i;
	//�����佺�׳׽��� ü�� �����Ѵ�.
	int sqrtn = int(sqrt(MAXN));
	for (int i = 2; i <= sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i * i; j <= MAXN; j += i)
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}
void getFactorsSmart() {
	factors[1] = 1;
	for (int n = 2; n <= MAXN; n++) {
		//�Ҽ��� ��� ����� �� �� �ۿ� ����
		if (minFactor[n] == n) {
			minFactorPower[n] = 1;
			factors[n] = 2;
		}
		//�Ҽ��� �ƴ� ���, ���� ���� ���μ��� ���� ��(m)��
		//����� ���� ������ n�� ����� ���� ã�´�.
		else {
			int p = minFactor[n];
			int m = n / p;
			//m�� p�� ���̻� ������ ���� �ʴ� ���
			if (p != minFactor[m])
				minFactorPower[n] = 1;
			else
				minFactorPower[n] = minFactorPower[m] + 1;
			int a = minFactorPower[n];
			factors[n] = (factors[m] / a) * (a + 1);
		}
	}
}

//1õ�� ������ ��� ���� ����� ���� ����ϴ� å�� �ܼ��� �˰���.
//�� Ǯ�̴� �� �˰���� ����ϳ� �����佺�׳׽��� ü �˰����� �����Ͽ�
//�� ������ ������ �ذ��Ͽ���.
void getFactorsBrute() {
	memset(factors, 0, sizeof(factors));
	for (int div = 1; div <= MAXN; div++)
		for (int multiple = div; multiple <= MAXN; multiple += div)
			factors[multiple] += 1;
}

int main(void) {
	cin >> c;
	eratosthenes();
	//eratosthenes2();
	//getFactorsSmart();
	for (int test = 0; test < c; test++) {
		cin >> n >> lo >> hi;
		cout << solve() << endl;
	}
}