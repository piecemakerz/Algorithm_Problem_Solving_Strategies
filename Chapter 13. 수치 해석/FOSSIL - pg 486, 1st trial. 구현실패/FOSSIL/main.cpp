#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int c, n, m;
//�Է¿� �־��� ���� �ٰ����� ������ �����ϱ�
struct point {
	point(double inputy, double inputx) : y(inputy), x(inputx) {}
	double y, x;
};
//�Է¿� �־��� ���� �ٰ���
vector<point> hull1, hull2;
//�� ������ ���ϴ� ���е�� �Ʒ� ������ ���ϴ� ���е�
vector<pair<point, point>> upper, lower;
//hull�� �ݽð�������� �־����Ƿ�, ������ �� ���� ���� x��
//�����ϴ� �����̸� �Ʒ��� ����, x�� �����ϴ� �����̸� ���� �����̴�.
void decompose(const vector<point>& hull) {
	int n = hull.size();
	for (int i = 0; i < n; i++) {
		if (hull[i].x < hull[(i + 1) % n].x)
			lower.push_back(make_pair(hull[i], hull[(i + 1) % n]));
		else if (hull[i].x > hull[(i + 1) % n].x)
			upper.push_back(make_pair(hull[i], hull[(i + 1) % n]));
	}
}

//�ɰ��� ȭ�� ������ �ذ��ϴ� ��� Ž�� �˰���
//[a.x, b.x] ���� �ȿ� x�� ���Եǳ� Ȯ���Ѵ�.
bool between(const point& a, const point& b, double x) {
	return (a.x <= x && x <= b.x) || (b.x <= x && x <= a.x);
}
//(a, b) ���а� �־��� ��ġ�� �������� �����ϴ� ��ġ�� ��ȯ�Ѵ�.
double at(const point& a, const point& b, double x) {
	double dy = b.y - a.y, dx = b.x - a.x;
	//���� (a, b)�� ������ ��츦 ���� ó���Ѵ�.
	if (fabs(dx) < 1e-9) return a.y;
	return a.y + dy * (x - a.x) / dx;
}

//hull�� �ִ� x��ǥ ���� ��ȯ�Ѵ�.
double maxX(const vector<point>& hull) {
	double ret = -1e20;
	for (int i = 0; i < hull.size(); i++) ret = max(ret, hull[i].x);
	return ret;
}
//hull�� �ּ� x��ǥ ���� ��ȯ�Ѵ�.
double minX(const vector<point>& hull) {
	double ret = 1e20;
	for (int i = 0; i < hull.size(); i++) ret = min(ret, hull[i].x);
	return ret;
}
//�� �ٰ����� �������� ���������� �߶��� �� �ܸ��� ���̸� ��ȯ�Ѵ�.
double vertical(double x){
	double minUp = 1e20, maxLow = -1e20;
	//�� ������ ������ ��ȸ�ϸ� �ּ� y ��ǥ�� ã�´�.
	for (int i = 0; i < upper.size(); i++)
		if (between(upper[i].first, upper[i].second, x))
			minUp = min(minUp, at(upper[i].first, upper[i].second, x));
	//�Ʒ� ������ ������ ��ȸ�ϸ� �ִ� y��ǥ�� ã�´�.
	for (int i = 0; i < lower.size(); i++)
		if (between(lower[i].first, lower[i].second, x))
			maxLow = max(maxLow, at(lower[i].first, lower[i].second, x));
	return minUp - maxLow;
}
double solve() {
	//�������� �� �ٰ����� ��� ������ x��ǥ�� ������ ���Ѵ�.
	double lo = max(minX(hull1), minX(hull2));
	double hi = min(maxX(hull1), maxX(hull2));
	//���� ó��: �� �ٰ����� �ƿ� ��ġ�� �ʴ� ���
	if (hi < lo) return 0;
	//��� �˻�
	for (int iter = 0; iter < 100; iter++) {
		double aab = (lo * 2 + hi) / 3.0;
		double abb = (lo + hi * 2) / 3.0;
		if (vertical(aab) < vertical(abb))
			lo = aab;
		else
			hi = abb;
	}
	return max(0.0, vertical(hi));
}

int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		cin >> n >> m;
		double inputx, inputy;
		for (int i = 0; i < n; i++) {
			cin >> inputx >> inputy;
			hull1.push_back(point(inputy, inputx));
		}
		for (int i = 0; i < m; i++) {
			cin >> inputx >> inputy;
			hull2.push_back(point(inputy, inputx));
		}
		decompose(hull1); decompose(hull2);
		printf("%.10f\n", max(0.0, solve()));
		hull1.clear(); hull2.clear();
		upper.clear(); lower.clear();
	}
}