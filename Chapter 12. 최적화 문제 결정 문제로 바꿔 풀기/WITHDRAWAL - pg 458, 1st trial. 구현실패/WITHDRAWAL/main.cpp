#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T, n, k;
int c[1000], r[1000];

//���� ����: ���� ��� average�� �ǵ��� �� �� �ֳ�?
bool decision(double average) {
	//v[i] = x*r[i]-c[i]�� ����Ѵ�.
	vector<double> v;
	for (int i = 0; i < n; i++)
		v.push_back(average * c[i] - r[i]);
	sort(v.begin(), v.end());
	//�� ������ v�� k���� ���� 0 �̻��� �� �� �ִ����� �ٲ��.
	//Ž������� �ذ�����.
	double sum = 0;
	for (int i = n - k; i < n; i++)
		sum += v[i];
	return sum >= 0;
}
//����ȭ ����: ���� �� �ִ� �ּ��� ���� ����� ����Ѵ�.
double optimize() {
	//���� ����� [0, 1]������ �Ǽ��̴�.
	//�ݺ��� �Һ���: !decision(lo) && decision(hi)
	double lo = -1e-9, hi = 1;
	for (int iter = 0; iter < 100; iter++) {
		double mid = (lo + hi) / 2;
		//���� ��� mid�� �޼��� �� �ֳ�?
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		cin >> n >> k;
		for (int i = 0; i < n; i++)
			cin >> r[i] >> c[i];
		printf("%.10f\n", optimize());
	}
}