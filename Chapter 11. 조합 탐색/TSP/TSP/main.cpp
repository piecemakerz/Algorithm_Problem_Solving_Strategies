#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const double INF = 1e200;
const int MAX = 30;
int n; // ������ ��
double dist[MAX][MAX]; // �� ���ð��� �Ÿ��� �����ϴ� �迭
//���ݱ��� ã�� ������. ���� ������ ���ݱ��� ã�� �������� ���̸�
//������ �θ� Ž�� �߿� �� �����ظ� �߰��� ���ɼ��� ���� ������
//�ĳ��� ��������.
double best;
//TSP�� �ذ��ϴ� ���� Ž���� ����
//path: ���ݱ��� ���� ���
//visited: �� ������ �湮 ����
//currentLength: ���ݱ��� ���� ����� ����
//������ ���õ��� ��� �湮�ϴ� ��ε��� ����� ���� �����ϸ� �����ظ� �����Ѵ�.
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//������ ����ġ��: ���ݱ��� ã�� ���� ���� �� �̻��� ��� �ߴ�
	if (best <= currentLength) return;
	int here = path.back();
	//���� ���: ��� ���ø� �� �湮���� ���� 0�� ���÷� ���ư��� �����Ѵ�.
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//���� �湮�� ���ø� ���� �õ��� ����.
	for (int next = 0; next < n; next++) {
		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		//������ ��θ� ��� ȣ���� ���� �ϼ��Ѵ�.
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}
double solve() {
	//best�� �ſ� ū ������ �ʱ�ȭ
	best = INF;
	vector<bool> visited(n, false);
	vector<int> path(1, 0);
	visited[0] = true;
	search(path, visited, 0);
	return best;
}