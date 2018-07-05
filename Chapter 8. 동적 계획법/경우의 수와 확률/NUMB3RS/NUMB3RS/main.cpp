#include <iostream>
#include <vector>
using namespace std;

//n = ������ ��, d = Ż�� �� ���ݱ��� ���� �ϼ�
//p = �����Ұ� �ִ� ����, t = Ȯ���� ����� ���� ��
//q = Ȯ���� ����� ������ ��ȣ
int c, n, d, p, t, q;
//cache[i][j] = i�� �������� j�� ���Ŀ� p������ ������ Ȯ��
int A[50][50];
double cache[50][101];

//�� Ǯ��. å�� �� 2�� ���� ��� ������ �ݴ� �������� �ٲ�
//ĳ�ø� ��� �׽�Ʈ ���̽��� ���� Ȱ���� �� �ְ� �������.
vector<vector<int>> canVisit;
//village�� �������� days�� ���Ŀ� p������ ������ �� �ִ� Ȯ���� �����Ѵ�.
double possibility(int village, int days) {
	if (days == 0)	return (village == p ? 1 : 0);

	double& ret = cache[village][days];
	if (ret != -1) return ret;
	
	ret = 0;
	int ways = canVisit[village].size();

	for (int i = 0; i < ways; i++) {
		int nextVillage = canVisit[village][i];
		ret += possibility(nextVillage, days - 1) / canVisit[nextVillage].size();
	}
	return ret;
}

//å�� �� 1. �δϹ� �ڻ��� Ż�� ������ �ذ��ϴ� ���� ��ȹ�� �˰���.
//connected[i][j] = ���� i, j�� ����Ǿ� �ֳ� ����
//deg[i] = ���� i�� ����� ������ ����
int connected[51][51], deg[51];
//search2(here, days) = �δϹ� �ڻ簡 days��°�� here�� ������ ���� ���� ��,
//������ ���� q�� ������ ���� ���Ǻ� Ȯ���� ��ȯ�Ѵ�.
//days��°�� here�� ������ ���� �ִٰ� �����ϰ�,
//������ ���� q�� ������ ���� ���� ���Ǻ� Ȯ���� ��ȯ�Ѵ�.
double search2(int here, int days) {
	//���� ���: d���� ���� ���
	if (days == d) return (here == q ? 1.0 : 0.0);
	//�޸������̼�
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < n; there++)
		if (connected[here][there])
			ret += search2(there, days + 1) / deg[here];
	return ret;
}

//å�� �� 2. ����� ������ �ݴ� �������� �ٲ� �� ������ ������ �˰���.
//search3(here, days) = Ż�� �� days��°�� �δϹ� �ڻ簡 here�� ������
//���� ���� Ȯ��
double search3(int here, int days) {
	//���� ���: 0��°
	if (days == 0) return (here == p ? 1.0 : 0.0);
	//�޸������̼�
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < n; there++)
		if (connected[here][there])
			ret += search3(there, days - 1) / deg[there];
	return ret;
}
int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 101; j++)
				cache[i][j] = -1;

		cin >> n >> d >> p;
		canVisit = vector<vector<int>>(n);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> A[i][j];
				if (A[i][j] == 1)
					canVisit[i].push_back(j);
			}

		cin >> t;
		for (int i = 0; i < t; i++) {
			cin >> q;
			printf("%.8f ", possibility(q, d));
		}
		cout << endl;
		canVisit.clear();
	}
}