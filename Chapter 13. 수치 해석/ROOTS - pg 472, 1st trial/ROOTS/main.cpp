#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int C, n;

//�ܺ��� ���� �������� �ظ� ã�� �� �˰���
//2���������� �ظ� ���ǰ����� ����Ͽ� ����ϰ� ��ȯ�Ѵ�.
vector<double> f2Value(const vector<double>& func) {
	vector<double> value;
	double a = func[2], b = func[1], c = func[0];
	double result = (-b - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
	value.push_back(result);
	result += 2 * ((sqrt(pow(b, 2) - (4 * a * c))) / (2 * a));
	value.push_back(result);
	return value;
}

//�Լ� f�� �̺��� fprime�� ��ȯ�Ѵ�.
vector<double> prime(const vector<double>& f) {
	vector<double> fprime(f.size() - 1);
	for (int i = 1; i < f.size(); i++)
		fprime[i - 1] = f[i] * i;
	return fprime;
}

//func(x)�� ���� ����Ͽ� ��ȯ�Ѵ�.
double functionResult(const vector<double>& func, double x) {
	double result = 0.0;
	for (int i = 0; i < func.size(); i++) {
		result += (func[i] * pow(x, i));
	}
	return result;
}

//�̺й��� ����Ͽ� lo�� hi ���̿� �ִ� func�� �ظ� ��ȯ�Ѵ�.
double bisection(const vector<double>& func, double lo, double hi) {
	//�ݺ��� �Һ����� �����Ѵ�.
	if (functionResult(func, lo) > 0)
		swap(lo, hi);
	//�ݺ��� �Һ���: f(lo) <= 0 f(hi)
	for (int i = 0; i < 100; i++) {
		double mid = (lo + hi) / 2;
		double fmid = functionResult(func, mid);
		if (fmid <= 0)
			lo = mid;
		else
			hi = mid;
	}
	return (lo + hi) / 2;
}

//func(x)�� �ظ� ��� ã�� ��ȯ�Ѵ�.
vector<double> findValue(const vector<double>& func) {
	//�־��� ������ 2���������� ���� ���� ������ ����Ͽ� ���� ��´�.
	if (func.size() == 3)
		return f2Value(func);

	vector<double> resultValue;

	vector<double> POI = findValue(prime(func));
	double lo, hi;
	for (int i = 0; i <= POI.size(); i++) {
		if (i == 0)
			lo = -10.0;
		else
			lo = POI[i - 1];

		if (i == POI.size())
			hi = 10.0;
		else
			hi = POI[i];

		resultValue.push_back(bisection(func, lo, hi));
	}
	sort(resultValue.begin(), resultValue.end());
	return resultValue;
}

//å�� Ǯ��

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		double input;
		cin >> n;
		vector<double> fx(n + 1);
		for (int i = n; i >= 0; i--) {
			scanf("%lf", &input);
			fx[i] = input;
		}
		vector<double> result = findValue(fx);
		for (int i = 0; i < result.size(); i++)
			printf("%.12f ", result[i]);
		cout << endl;
	}
}