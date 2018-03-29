#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//단일 변수 다항식 p의 계수가 주어질 때 미분한 결과 p'의 계수를 반환한다.
vector<double> differentiate(const vector<double>& poly);
//1차 혹은 2차 방정식을 푼다.
vector<double> solveNaive(const vector<double>& poly);
//다항식 f(x)의 계수 poly가 주어질 때, f(x0)를 반환한다.
double evaluate(const vector<double>& poly, double x0);
//방정식의 해의 절대 값은 L 이하여야 한다.
const double L = 25;
//방정식 sum(poly[i]*x^j)=0의 근을 반환한다.
vector<double> solve(const vector<double>& poly) {
	int n = poly.size() - 1;
	//기저 사례: 2차 이하의 방정식들은 풀 수 있다.
	if (n <= 2) return solveNaive(poly);
	//방정식을 미분해서 n-1차 방정식을 얻는다.
	vector<double> derivative = differentiate(poly);
	vector<double> sols = solve(derivative);
	//이 극점들 사이를 하나하나 검사하며 근이 있나 확인한다.
	sols.insert(sols.begin(), -L -1);
	sols.insert(sols.end(), L + 1);
	vector<double> ret;
	for (int i = 0; i < sols.size() - 1; i++) {
		double x1 = sols[i], x2 = sols[i + 1];
		double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
		//f(x1)과 f(x2)의 부호가 같은 경우 답은 없다.
		if (y1*y2 > 0) continue;
		//불변 조건: f(x1) <= 0 < f(x2)
		if (y1 > y2) { swap(y1, y2); swap(x1, x2); }
		//이분법을 사용하자
		for (int iter = 0; iter < 100; iter++) {
			double mx = (x1 + x2) / 2;
			double my = evaluate(poly, my);
			if (y1*my > 0) {
				y1 = my;
				x1 = mx;
			}
			else {
				y2 = my;
				x2 = mx;
			}
		}
		ret.push_back((x1 + x2) / 2);
	}
	sort(ret.begin(), ret.end());
	return ret;
}