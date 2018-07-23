#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int C, n;

//단변수 다항 방적식의 해를 찾는 내 알고리즘
//2차방정식의 해를 근의공식을 사용하여 계산하고 반환한다.
vector<double> f2Value(const vector<double>& func) {
	vector<double> value;
	double a = func[2], b = func[1], c = func[0];
	double result = (-b - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
	value.push_back(result);
	result += 2 * ((sqrt(pow(b, 2) - (4 * a * c))) / (2 * a));
	value.push_back(result);
	return value;
}

//함수 f를 미분한 fprime을 반환한다.
vector<double> prime(const vector<double>& f) {
	vector<double> fprime(f.size() - 1);
	for (int i = 1; i < f.size(); i++)
		fprime[i - 1] = f[i] * i;
	return fprime;
}

//func(x)의 값을 계산하여 반환한다.
double functionResult(const vector<double>& func, double x) {
	double result = 0.0;
	for (int i = 0; i < func.size(); i++) {
		result += (func[i] * pow(x, i));
	}
	return result;
}

//이분법을 사용하여 lo와 hi 사이에 있는 func의 해를 반환한다.
double bisection(const vector<double>& func, double lo, double hi) {
	//반복적 불변식을 강제한다.
	if (functionResult(func, lo) > 0)
		swap(lo, hi);
	//반복적 불변식: f(lo) <= 0 f(hi)
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

//func(x)의 해를 모두 찾아 반환한다.
vector<double> findValue(const vector<double>& func) {
	//주어진 공식이 2차방정식일 때는 근의 공식을 사용하여 값를 얻는다.
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

//책의 풀이

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