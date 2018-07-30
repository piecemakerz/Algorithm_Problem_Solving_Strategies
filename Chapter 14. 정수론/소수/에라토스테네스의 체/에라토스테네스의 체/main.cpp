#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

const int MAX_N = 100;
int n;
bool isPrime[MAX_N + 1];
// ���� �ܼ��� ������ �����佺�׳׽��� ü�� ����
// ������ �� isPrime[i]�� �Ҽ����� Ȯ��
void erastosthenes() {
	memset(isPrime, 1, sizeof(isPrime));
	//1�� �׻� ���� ó��
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(n));
	for (int i = 2; i < sqrtn; i++)
		//�� ���� ���� �������� �ʾҴٸ�
		if (isPrime[i])
			//i�� ��� j�鿡 ���� isPrime[i] = false�� �д�.
			//i*i �̸��� ����� �̹� ���������Ƿ� �Ű� ���� �ʴ´�.
			for (int j = i*i; j <= n; j += i)
				isPrime[j] = false;
}

//�����佺�׳׽��� ü�� �̿��� ���� ���μ� ����

//minFactor[i] = i�� ���� ���� ���μ�(i�� �Ҽ��� ��� �ڱ� �ڽ�)
int minFactor[MAX_N];
//�����佺�׳׽��� ü�� �����ϸ鼭 ���μ����ظ� ���� ������ �����Ѵ�.
void eratosthenes() {
	//1�� �׻� ���� ó��
	minFactor[0] = minFactor[1] = -1;
	//��� ���ڸ� ó������ �Ҽ��� ǥ���� �д�.
	for (int i = 2; i <= n; i++)
		minFactor[i] = i;
	//�����佺�׳׽��� ü�� �����Ѵ�.
	int sqrtn = int(sqrt(n));
	for (int i = 2; i <= sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i * i; j <= n; j++)
				//���� ����� �� �� ���� ������ ��� i�� �� �д�.
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}
//2 �̻��� �ڿ��� n�� ���μ������� ����� ��ȯ�Ѵ�.
vector<int> factor(int n) {
	vector<int> ret;
	//n�� 1�� �� ������ ���� ���� ���μ��� �����⸦ �ݺ��Ѵ�.
	while (n > 1) {
		ret.push_back(minFactor[n]);
		n /= minFactor[n];
	}
	return ret;
}