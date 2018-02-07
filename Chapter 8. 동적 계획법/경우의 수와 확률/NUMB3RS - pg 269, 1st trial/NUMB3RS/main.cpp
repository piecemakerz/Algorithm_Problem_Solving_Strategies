#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N, D, P; // N = ������ ���Ե� ������ ��, D = Ż�� �� ���ݱ��� ���� �ϼ�, P = �����Ұ� �ִ� ������ ��ȣ
int T; // T = Ȯ���� ����� ������ ��
vector<vector<int>> villagePath; // ���� �� ����
vector<vector<int>> connectedVillage; // �� �������� ����Ǿ� �ִ� ������ ����
double cache[101][51]; // cache[����][����]

double villagePerCounter(int day, int curPos) { // day �Ŀ� curPos�� ���� Ȯ��. ����ϰ��� �ϴ� ������������ �����Ұ� �ִ� �������� ���� ��θ� �Ųٷ� ��¤�´�.
	if (day == 0) { // �������: �����Ұ� �ִ� �������� �����ϴ� ��� 1.0 �ƴϸ� 0.0
		if (curPos == P)
			return 1.0;
		else
			return 0.0;
	}
	double& ret = cache[day][curPos];
	if (ret != -1.0) return ret;
	ret = 0.0;

	for (int i = 0; i < connectedVillage[curPos].size(); i++) {
		int nextPos = connectedVillage[curPos][i];
		ret += villagePerCounter(day - 1, nextPos) / connectedVillage[nextPos].size(); // ���ȣ���� ������� ������ �湮�� ������ �ִ� ���� ����ŭ���� ������
	}
	return ret;
}

// å�� �� 1. �޸������̼��� �������� ���� ���� Ž�� �˰���
int Q;
//connected[i][j] = ���� i,j�� ����Ǿ� �ֳ� ����
//deg[i] = ���� i�� ����� ������ ����
int connected[51][51], deg[51];
double search(vector<int>& path) {
	if (path.size() == D + 1) {
		if (path.back() != Q) return 0.0;
		double ret = 1.0;
		//path�� ���� Ȯ�� ���
		for (int i = 0; i + 1 < path.size(); i++)
			ret /= deg[path[i]];
		return ret;
	}
	double ret = 0;
	// ����� ���� ��ġ ����
	for (int there = 0; there < N; there++) {
		if (connected[path.back()][there]) {
			path.push_back(there);
			ret += search(path);
			path.pop_back();
		}
	}
	return ret;
}

// å�� �� 2. �޸����̼��� ������ ���� ��ȹ�� �˰���
// double cache[51][101] - cache[���� ��ġ][����]
double search2(int here, int days) {
	//�������: d���� ���� ���
	if (days == D) return (here == Q ? 1.0 : 0.0);
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < N; there++) {
		if (connected[here][there])
			ret += search2(there, days + 1) / deg[here];
	}
	return ret;
}

// å�� �� 3. ����� ������ �ݴ� �������� �ٲ� �˰���. �� �˰���� �ذ� ����� ����.
double search3(int here, int days) {
	if (days == 0) return (here == P ? 1.0 : 0.0);
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < N; there++)
		if (connected[here][there])
			ret += search3(there, days - 1) / deg[there];
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		for(int i=0; i<101; i++)
			for (int j = 0; j < 51; j++)
				cache[i][j] = -1.0;

		int input;
		cin >> N >> D >> P;
		villagePath = vector<vector<int>>(N);
		connectedVillage = vector<vector<int>>(N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> input;
				villagePath[i].push_back(input);
				if (input == 1)
					connectedVillage[i].push_back(j);
			}
		}
		cin >> T;
		for (int i = 0; i < T; i++) {
			cin >> input;
			printf("%.8f ", villagePerCounter(D, input));
		}
		cout << endl;
	}
	return 0;
}