#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_N = 100;

// �־��� ���� n�� ���μ������ϴ� ������ �˰���
vector<int> factorSimple(int n) {
	vector<int> ret;
	int sqrtn = int(sqrt(n));
	for (int div = 2; div <= sqrtn; div++)
		while (n % div == 0) {
			n /= div;
			ret.push_back(div);
		}
	if (n > 1) ret.push_back(n);
	return ret;
}

//�����佺�׳׽��� ü�� �̿��� ���� ���μ� ����
//minFactor[i] = i�� ���� ���� ���μ�(i�� �Ҽ��� ��� �ڱ� �ڽ�
int minFactor[MAX_N];
//�����佺�׳׽��� ü�� �����ϸ鼭 ���μ����ظ� ���� ������ �����Ѵ�.
void eratosthenes2(int n) {
	//1�� �׻� ���� ó��
	minFactor[0] = minFactor[1] = -1;
	//��� ���ڸ� ó������ �Ҽ��� ǥ���� �д�.
	for (int i = 2; i <= n; i++)
		minFactor[i] = i;
	//�����佺�׳׽��� ü�� �����Ѵ�.
	int sqrtn = int(sqrt(n));
	for (int i = 2; i < sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i*i; i <= n; j += i)
				//���� ����� �� �� ���� ������ ��� i�� �� �д�.
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}

}
// 2 �̻��� �ڿ��� n�� ���μ������� ����� ��ȯ�Ѵ�.
vector<int> factor(int n) {
	vector<int> ret;
	//n�� 1�� �� ������ ���� ���� ���μ��� �����⸦ �ݺ��Ѵ�.
	while (n > 1) {
		ret.push_back(minFactor[n]);
		n /= minFactor[n];
	}
	return ret;
}