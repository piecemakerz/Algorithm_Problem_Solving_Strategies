//��� �˻��� ����

//�츮�� �ִ�ġ�� ã�� �;��ϴ� �Լ�
double f(double x);
//[lo, hi]�������� f(x)�� �ִ�ġ�� ���� x�� ��ȯ�Ѵ�.
double ternary(double lo, double hi) {
	for (int iter = 0; iter < 100; iter++) {
		double a = (2 * lo + hi) / 3.0;
		double b = (lo + 2 * hi) / 3.0;
		if (f(a) > f(b))
			hi = b;
		else
			lo = a;
	}
	return (lo + hi) / 2.0;
}