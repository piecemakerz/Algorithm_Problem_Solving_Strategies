#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int C, N, M;
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
	for (int it = 0; it < 100; it++) {
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

//���� ��ȹ������ �ذ��� DARPA ����
vector<double> cameraLocation;
const double MAX = 987654321.0;
double cache[201][101];
//���� ��ġ�� curPos�̰� left���� ī�޶� �� ��ġ�ؾ� �� ��,
//���� ī�޶� ��� ��ġ�Ͽ� ���� �� �ִ� �� ī�޶� ���� �ִ� ������
//��ȯ�Ѵ�.
double darpaDynamic(int curPos, int left) {
	if (left == 0)
		return MAX;

	double& ret = cache[curPos + 1][left];
	if (ret != -1.0) return ret;
	ret = 0;

	int maxNext = M - left;
	for (int i = curPos + 1; i <= maxNext; i++) {
		double nextResult = darpaDynamic(i, left - 1);
		if (curPos != -1)
			nextResult = min(cameraLocation[i] - cameraLocation[curPos], nextResult);
		ret = max(ret, nextResult);
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		for (int i = 0; i < 201; i++)
				for (int j = 0; j < 101; j++)
					cache[i][j] = -1.0;
		double input;
		cin >> N >> M;
		for (int i = 0; i < M; i++) {
			cin >> input;
			cameraLocation.push_back(input);
		}
		printf("%.2f\n", darpaDynamic(-1, N));
		cameraLocation.clear();
	}
}