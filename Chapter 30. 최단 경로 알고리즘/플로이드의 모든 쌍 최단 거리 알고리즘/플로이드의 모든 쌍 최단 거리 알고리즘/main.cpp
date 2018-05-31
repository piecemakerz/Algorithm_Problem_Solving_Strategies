#include <algorithm>
#include <vector>
using namespace std;

//�÷��̵� �˰����� ����

const int MAX_V = 10;
//������ ����
int V;
//�׷����� ���� ��� ǥ��
//adj[u][v] = u���� v�� ���� ������ ����ġ. ������ ������ ���� ū ���� �ִ´�.
int adj[MAX_V][MAX_V];
//via[u][v] = u���� v���� ���� �ִ� ��ΰ� �����ϴ� �� �� ���� ��ȣ�� ū ����
//-1�� �ʱ�ȭ�� �д�.
int via[MAX_V][MAX_V];
//�÷��̵��� ��� �� �ִ� �Ÿ� �˰���
void floyd() {
	for (int i = 0; i < V; i++) adj[i][i] = 0;
	memset(via, -1, sizeof(via));
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				if (adj[i][j] > adj[i][k] + adj[k][j]) {
					via[i][j] = k;
					adj[i][j] = adj[i][k] + adj[k][j];
				}
}
//u���� v�� ���� �ִ� ��θ� ����� path�� �����Ѵ�.
void reconstruct(int u, int v, vector<int>& path) {
	//���� ���
	if (via[u][v] == -1) {
		path.push_back(u);
		if (u != v) path.push_back(v);
	}
	else {
		int w = via[u][v];
		reconstruct(u, w, path);
		path.pop_back(); // w�� �ߺ����� ���Ƿ� �����.
		reconstruct(w, v, path);
	}
}