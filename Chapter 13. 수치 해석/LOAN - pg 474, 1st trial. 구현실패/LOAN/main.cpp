#include <iostream>
using namespace std;

int T, N, M, P;
//전세금 균등상환 문제를 해결하는 책의 이분법의 구현
//amount원을 연 이율 rates퍼센트로 duration월 간 한 달에
//monthlyPayment로 남았을 때 대출 잔금은?
double balance(double amount, int duration, double rates,
	double monthlyPayment) {
	double balance = amount;
	for (int i = 0; i < duration; i++) {
		//이자가 붙는다.
		balance *= (1.0 + (rates / 12.0) / 100.0);
		//상환액을 잔금에서 제한다.
		balance -= monthlyPayment;
	}
	return balance;
}
//amount원을 연 이율 rates퍼센트로 duration월 간 갚으려면 한 달에
//얼마씩 갚아야 하나?
double payment(double amount, int duration, double rates) {
	//불변 조건:
	//1. lo원씩 갚으면 duration개월 안에 갚을 수 없다.
	//   돈을 아예 갚지 않을 경우부터 시작한다.
	//2. hi원씩 갚으면 duration개월 안에 갚을 수 있다.
	//   한 달 후에 전액을 상환하는 경우부터 시작한다.
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