#include <iostream>
#include <cstring>
#include <cmath>
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