#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int INF = 987654321;
const double pi = 2.0 * acos(0);
int n;
double y[100], x[100], r[100];
pair<double, double> ranges[100];
//�̳��� �Ƴ븣 ������ ������ �߽ɰ��� �������� �ٲٱ�
void convertToRange() {
	for (int i = 0; i < n; i++) {
		double loc = fmod(2 * pi + atan2(y[i], x[i]), 2 * pi);
		double range = 2.0 * asin(r[i] / 2.0 / 8.0);
		ranges[i] = make_pair(loc - range, loc + range);
	}
}

//������ ���� �ּ� ���� ���� ����ϴ� Ž���� �˰���
//[begin, end]������ ���� ���� ������ �ּ����� ���� ���� ��ȯ�Ѵ�.
//ranges�� ���� ��ġ�� ������������ ���ĵǾ� �ִٰ� ��������.
int solveLinear(double begin, double end) {
	int used = 0, idx = 0;
	//���� ���� ������ ���� �ִ� ���� ����Ѵ�.
	while (begin < end) {
		//begin���� ������ �����ϴ� ���� �� ���� �ʰ� ������ ������ ã�´�.
		double maxCover = -1;
		while (idx < n && ranges[idx].first <= begin) {
			maxCover = max(maxCover, ranges[idx].second);
			idx++;
		}
		//���� ������ ã�� ���� ���
		if (maxCover <= begin) return INF;
		//������ ���� �κ��� �߶󳽴�.
		begin = maxCover;
		used++;
	}
	return used;
}

//�̳��� �Ƴ븣 ������ ���� ������ ��ȯ�ؼ� Ǫ�� �˰���
//0�� ���� ������ �����ϰ� �������� �������� Ǭ��.
int solveCircular() {
	int ret = INF;
	//�� ������ ���� ��ġ�� ������������ �����Ѵ�.
	sort(ranges, ranges + n);
	//0�� ���� ������ ��������
	for(int i=0; i<n; i++)
		if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
			//�� ������ ���� �κ��� ���� ���� �߽ɰ��� ������ ������ ����.
			double begin = fmod(ranges[i].second, 2 * pi);
			double end = fmod(ranges[i].first + 2 * pi, 2 * pi);
			//[begin, end]������ �־��� ������ ����ؼ� ���´�.
			ret = min(ret, 1 + solveLinear(begin, end));
		}
	return ret;
}