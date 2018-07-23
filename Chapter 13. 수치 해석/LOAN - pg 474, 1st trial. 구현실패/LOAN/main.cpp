#include <iostream>
using namespace std;

int T, N, M, P;
//������ �յ��ȯ ������ �ذ��ϴ� å�� �̺й��� ����
//amount���� �� ���� rates�ۼ�Ʈ�� duration�� �� �� �޿�
//monthlyPayment�� ������ �� ���� �ܱ���?
double balance(double amount, int duration, double rates,
	double monthlyPayment) {
	double balance = amount;
	for (int i = 0; i < duration; i++) {
		//���ڰ� �ٴ´�.
		balance *= (1.0 + (rates / 12.0) / 100.0);
		//��ȯ���� �ܱݿ��� ���Ѵ�.
		balance -= monthlyPayment;
	}
	return balance;
}
//amount���� �� ���� rates�ۼ�Ʈ�� duration�� �� �������� �� �޿�
//�󸶾� ���ƾ� �ϳ�?
double payment(double amount, int duration, double rates) {
	//�Һ� ����:
	//1. lo���� ������ duration���� �ȿ� ���� �� ����.
	//   ���� �ƿ� ���� ���� ������ �����Ѵ�.
	//2. hi���� ������ duration���� �ȿ� ���� �� �ִ�.
	//   �� �� �Ŀ� ������ ��ȯ�ϴ� ������ �����Ѵ�.
	double lo = 0, hi = amount * (1.0 + (rates / 12.0) / 100.0);
	for (int iter = 0; iter < 100; iter++) {
		double mid = (lo + hi) / 2.0;
		if (balance(amount, duration, rates, mid) <= 0)
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		cin >> N >> M >> P;
		printf("%.10f\n", payment(N, M, P));
	}
	return 0;
}