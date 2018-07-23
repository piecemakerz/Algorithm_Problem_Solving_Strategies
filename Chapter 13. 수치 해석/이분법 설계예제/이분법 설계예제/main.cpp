#include <algorithm>
using namespace std;

double f(double x);
//�̺й��� ���� ����
double bisection(double lo, double hi) {
	//�ݺ��� �Һ����� �����Ѵ�.
	if (f(lo) > 0)
		swap(lo, hi);
	//�ݺ��� �Һ���: f(lo) <= 0 < f(hi)
	while (fabs(hi - lo) > 2e-7) {
		double mid = (lo + hi) / 2;
		double fmid = f(mid);
		if (fmid <= 0)
			lo = mid;
		else
			hi = mid;
	}
	//��� ���� ��ȯ�Ѵ�.
	return (lo + hi) / 2;
}