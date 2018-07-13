#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX 10

using namespace std;

const int INF = 987654321;
int n; // ������ ��
double dist[MAX][MAX];	// �� ���� ���� �Ÿ��� �����ϴ� �迭
double cache[MAX][1 << MAX];

//������ ������ n!���� ��θ� ��� �����ϴ� ���� Ž�� �˰���.
//n!�� ������ ���� �����ϴ� �Լ��̱� ������ n�� 15������ �Ǵ���
//����� ���� �Ұ����ϴ�.
//path: ���ݱ��� ���� ���
//visited: �� ������ �湮 ����
//currentLenght: ���ݱ��� ���� ����� ����
//������ ���õ��� ��� �湮�ϴ� ��ε� �� ���� ª�� ���� ���̸� ��ȯ�Ѵ�.
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
	if (path.size() == n)
		return currentLength + dist[path[0]][path.back()];
	double ret = INFINITY;
	for (int next = 0; next < n; next++) {
		if (visited[next]) continue;
		int here = path.back();
		path.push_back(next);
		visited[next] = true;

		double cand = shortestPath(path, visited, currentLength + dist[here][next]);

		ret = min(ret, cand);
		visited[next] = false;
		path.pop_back();
	}
	return ret;
}
//�޸������̼ǰ� ��Ʈ����ũ ����� ������ ���ο� TSP �˰���.
//here: ���� ��ġ
//visited: �� ������ �湮 ����
//here���� ������ ���� ���õ��� �湮�� �� �ִ� �ִ� ����� ���̸� ��ȯ�Ѵ�.
//������ ���õ��� ��� �湮�ϴ� ��ε� �� ���� ª�� ���� ���̸� ��ȯ�Ѵ�.
//�׻� 0�� ���ÿ��� �����Ѵٰ� �����Ѵ�.
double shortestPath2(int here, int visited) {
	// ���� ���: ��� ���ø� �� �湮���� ���� 0�� ���÷� ���ư��� �����Ѵ�.
	if (visited == (1 << n) - 1) return dist[here][0];
	double& ret = cache[here][visited];
	if (ret >= 0) return ret;
	ret = INF; // �ſ� ū ������ �ʱ�ȭ
	// ���� �湮�� ���ø� ���� �õ��� ����.
	for (int next = 0; next < n; next++) {
		//�̹� �湮�� ������ ���
		if (visited & (1 << next)) continue;
		double cand = dist[here][next] + shortestPath2(next, visited + (1 << next));
		ret = min(ret, cand);
	}
	return ret;
}
