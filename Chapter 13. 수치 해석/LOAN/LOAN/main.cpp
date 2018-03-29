#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

// amount���� �� ���� rates�ۼ�Ʈ�� duration���� �Ѵ޿� monthlyPayment��
// ������ �� ���� �ܱ���?
double balance(double amount, int duration, double rates, double monthlyPayment) {
	double balance = amount;
	for (int i = 0; i < duration; i++) {
		// ���ڰ� �ٴ´�
		balance *= (1.0 + (rates / 12.0) / 100.0);
		// ��ȯ���� �ܱݿ��� ���Ѵ�
		balance -= monthlyPayment;
	}
	return balance;
}

// amount���� �� ���� rates�ۼ�Ʈ�� duration���� �������� �� �޿�
// �󸶾� ���ƾ� �ϳ�?
double payment(double amount, int duration, double rates) {
	// �Һ� ����:
	// 1. lo���� ������ duration���� �ȿ� ���� �� ����
	// 2. hi���� ������ duration���� �ȿ� ���� �� �ִ�
	double lo = 0, hi = amount * (1.0 + (rates / 12.0) / 100);
	for (int iter = 0; iter < 100; iter++) {
		double mid = (lo + hi) / 2.0;
		if (balance(amount, duration, rates, mid) <= 0)
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}