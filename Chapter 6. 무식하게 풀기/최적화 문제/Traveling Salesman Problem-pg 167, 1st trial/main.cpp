#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX 10

using namespace std;

int n; // ������ ��
double dist[MAX][MAX]; // �� ���� ���� �Ÿ��� �����ϴ� �迭
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
