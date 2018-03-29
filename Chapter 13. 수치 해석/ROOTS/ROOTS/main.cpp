#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//���� ���� ���׽� p�� ����� �־��� �� �̺��� ��� p'�� ����� ��ȯ�Ѵ�.
vector<double> differentiate(const vector<double>& poly);
//1�� Ȥ�� 2�� �������� Ǭ��.
vector<double> solveNaive(const vector<double>& poly);
//���׽� f(x)�� ��� poly�� �־��� ��, f(x0)�� ��ȯ�Ѵ�.
double evaluate(const vector<double>& poly, double x0);
//�������� ���� ���� ���� L ���Ͽ��� �Ѵ�.
const double L = 25;
//������ sum(poly[i]*x^j)=0�� ���� ��ȯ�Ѵ�.
vector<double> solve(const vector<double>& poly) {
	int n = poly.size() - 1;
	//���� ���: 2�� ������ �����ĵ��� Ǯ �� �ִ�.
	if (n <= 2) return solveNaive(poly);
	//�������� �̺��ؼ� n-1�� �������� ��´�.
	vector<double> derivative = differentiate(poly);
	vector<double> sols = solve(derivative);
	//�� ������ ���̸� �ϳ��ϳ� �˻��ϸ� ���� �ֳ� Ȯ���Ѵ�.
	sols.insert(sols.begin(), -L -1);
	sols.insert(sols.end(), L + 1);
	vector<double> ret;
	for (int i = 0; i < sols.size() - 1; i++) {
		double x1 = sols[i], x2 = sols[i + 1];
		double y1 = evaluate(poly, x1), y2 = evaluate(poly, x2);
		//f(x1)�� f(x2)�� ��ȣ�� ���� ��� ���� ����.
		if (y1*y2 > 0) continue;
		//�Һ� ����: f(x1) <= 0 < f(x2)
		if (y1 > y2) { swap(y1, y2); swap(x1, x2); }
		//�̺й��� �������
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