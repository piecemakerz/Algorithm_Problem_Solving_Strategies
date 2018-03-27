#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//���� ����: ���ĵǾ� �ִ� locations �� cameras�� ������ ��� ī�޶� ���� ������
//gap �̻��� �Ǵ� ����� �ִ����� ��ȯ�Ѵ�.
bool decision(const vector<double>& location, int cameras, double gap) {
	//ī�޶� ��ġ�� �� ���� ������ ��ġ�ϴ� Ž���� �˰���
	double limit = -1;
	int installed = 0;
	for (int i = 0; i < location.size(); i++) {
		if (limit <= location[i]) {
			installed++;
			//location[i] + gap ���Ĵ� �Ǿ�� ī�޶� ��ġ�� �� �ִ�.
			limit = location[i] + gap;
		}
	}
	//��������� cameras�� �̻��� ��ġ�� �� �־����� ����
	return installed >= cameras;
}

//����ȭ ����: ���ĵǾ� �ִ� locations �� cameras�� ������ �ּ� ������ �ִ�ȭ�Ѵ�.
double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	//�ݺ��� �Һ���: desicion(lo) == true. decision(hi) == false
	for (int it; it < 100; it++) {
		double mid = (lo + hi) / 2.0;
		//������ mid �̻��� �ǵ��� �� �� ������ ���� [mid, hi]�� �ִ�.
		if (decision(location, cameras, mid))
			lo = mid;
		//������ mid �̻��� �ǵ��� �� �� ������ ���� [lo, mid]�� �ִ�.
		else
			hi = mid;
	}
	return hi;
}
