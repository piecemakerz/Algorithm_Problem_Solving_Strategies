#include <iostream>
using namespace std;

//�־��� �ڿ��� n�� �Ҽ����� Ȯ���Ѵ�.
bool isPrime(int n) {
	//���� ó��: 1�� 2�� ���ܷ� ó���Ѵ�.
	if (n <= 1) return false;
	if (n == 2) return true;
	//2�� ������ ��� ¦���� �Ҽ��� �ƴϴ�.
	if (n % 2 == 0) return false;
	//2�� ���������� 3 �̻��� ��� Ȧ���� �������.
	int sqrtn = int(sqrt(n));
	for (int div = 3; div <= sqrtn; div += 2)
		if (n%div == 0)
			return false;
	return true;
}