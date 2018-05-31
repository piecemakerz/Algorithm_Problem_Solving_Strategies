#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_V = 500;
const int INF = 987654321;
int T; //�׽�Ʈ ���̽�
int V, E; // ����� ��, ������ ��
int adj[MAX_V][MAX_V]; //adj[u][v] = u���� v�� ���� ������ ����ġ. ������ ������ ���� ū ���� �ִ´�.

//�� Ǯ��
//maxDrunken[i][j] = i���� j�� ���� �ִܰ�ο��� ���� ū ����ġ�� ������ �������� ����ġ.
int maxDrunken[MAX_V][MAX_V];
//drunken[i] = ���� i�� ����ġ
int drunken[MAX_V];
//W[i][j] = i���� j�� ���� �ִܰ���� ���� (�ִ� ������ ����ġ ����) 
int W[MAX_V][MAX_V];

void findShortestPath() {
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++) {
			if (i == j)
				W[i][j] = 0;
			else
				W[i][j] = adj[i][j];
		}

	for (int k = 0; k < V; k++) {
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++) {
				int curMaxDrunken = (maxDrunken[i][k], maxDrunken[k][j]);
				curMaxDrunken = max(curMaxDrunken, drunken[k]);
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

				if (W[i][j] > adj[i][k] + adj[k][j] + curMaxDrunken) {
					W[i][j] = adj[i][k] + adj[k][j] + curMaxDrunken;
					maxDrunken[i][j] = max(maxDrunken[i][j], drunken[k]);
				}
			}
	}
}

/*
//å�� ��
//�� �������� ���� ���� �ܼ��� �� �� �ɸ��� �ð�
int delay[MAX_V];

//�Է��� ���� �� 1���� �����ϴ� ���� ��ȣ�� 0���� �����ϵ��� �����ߴٰ� �����Ѵ�.
void solve() {
	//��� �������� ���� �ð� ���� �����Ѵ�.
	vector<pair<int, int>> order;
	for (int i = 0; i < V; i++)
		order.push_back(make_pair(delay[i], i));
	sort(order.begin(), order.end());
	//������ �ϳ��� ��ġ�� �ʰ� ���� �� �ִ� �ִ� ���
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			if (i == j)
				W[i][j] = 0;
			else
				W[i][j] = adj[i][j];
	int ret = INF;
	for (int k = 0; k < V; k++) {
		//k��°�� ���� �ð��� ���� �ɸ��� ���� w������ ������ ���� �� �ִ� �ִ� �Ÿ�
		int w = order[k].second;
		for(int i=0; i<V; i++)
			for (int j = 0; j < V; j++) {
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(adj[i][w] + delay[w] + adj[w][j], W[i][j]);
			}
	}
}
*/

int main(void) {
	memset(adj, INF, sizeof(adj));
	cin >> V >> E;
	//���� ���� ����ġ �Է�
	for (int i = 0; i < V; i++)
		cin >> drunken[i];

	int u, v;
	for (int i = 0; i < E; i++) {
		cin >> u >> v;
		cin >> adj[u - 1][v - 1];
		adj[v - 1][u - 1] = adj[u - 1][v - 1];
	}
	findShortestPath();
	cin >> T;
	for (int test = 0; test < T; test++) {
		cin >> u >> v;
		cout << W[u - 1][v - 1] << endl;
	}
	
}