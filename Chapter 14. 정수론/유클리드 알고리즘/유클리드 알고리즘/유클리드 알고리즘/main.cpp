#include <iostream>
using namespace std;

//����ȭ���� ���� ��Ŭ���� �˰���
int gcd(int p, int q) {
	if (p < q) swap(p, q);
	if (q == 0) return p;
	return gcd(p - q, q);
}

//����ȭ�� ��Ŭ���� �˰���
int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p%q);
}