#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V, E, T;
const int INF = 987654321;
vector<vector<int>> adj;
vector<vector<int>> maxWeight;
vector<int> nodeWeight;

//���� ���� �ܼ� ������ �ذ��ϴ� �� Ǯ��. �����̴�.
//adj�� ���� ����ġ�� �����ϴ� �ִܰ�θ� �����Ͽ� ��������
//�÷��� ������ �̸� �����ϴ� �˰����� ���������,
//�̴� ����Ǵ� �ִܰ�ΰ� �ᱹ �ִ� ����ġ ������ ����ġ�� ������ ��� �����̹Ƿ�
//�Ŀ� �������� �÷��� �� �ִ� ����ġ ������ �ٲ�� �Ǹ� ������ ���̰� �� ª��
//��ΰ� �ִܰ�ΰ� �ȴ�.
/*
5 5
1 10 30 100 1
1 2 30
1 3 20
2 4 20
3 4 20
4 5 5
1
1 5
*/
//�� �����Է��� �־ �������� ���� ������ �� �ִ�.
void myfloyd() {
	for (int i = 0; i < V; i++)
		adj[i][i] = 0;

	//0~k�� ������ ���������� ����Ѵ�.
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++) {
			//i�� �������� k�� �������� ���� ��ΰ� ���ų� i == k�� ���
			if (adj[i][k] >= INF || i == k)
				continue;
			for (int j = 0; j < V; j++) {
				//j�� �������� k�� �������� ���� ��ΰ� ���ų� j == k�� ���
				if (adj[k][j] >= INF || j == k)
					continue;

				//curmaxW = k�� ������ �����ϴ� ��ο����� ���� ū ����ġ�� ������ ����
				int curmaxW = max(maxWeight[i][k], maxWeight[k][j]);
				curmaxW = max(curmaxW, nodeWeight[k]);

				//ret = k�� ������ �����ϴ� i->j �ִܰ���� ����
				int ret = adj[i][k] + adj[k][j] - maxWeight[i][k] - maxWeight[k][j] + curmaxW;
				//���� �ִܰ�κ��� k�� ������ �����ϴ� ����� ���̰� �� ª�ٸ� �����Ѵ�.
				if (adj[i][j] > ret) {
					adj[i][j] = adj[j][i] = ret;
					maxWeight[i][j] = maxWeight[j][i] = curmaxW;
				}
			}
		}
}

//�÷��̵� �˰����� ������ ���� ���� ������ �ذ��ϴ� å�� �˰����� ����

//�׷����� ���� ��� ǥ��
int V, adj[500][500];
//�� �������� ���� ���� �ܼ��� �� �� �ɸ��� �ð�
int delay[500];
int W[500][500];
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

int main(void) {
	cin >> V >> E;
	nodeWeight.resize(V);
	adj = vector<vector<int>>(V, vector<int>(V, INF));
	maxWeight = vector<vector<int>>(V, vector<int>(V, 0));
	int from, to, weight;
	for (int i = 0; i < V; i++)
		cin >> nodeWeight[i];
	for (int i = 0; i < E; i++) {
		cin >> from >> to >> weight;
		adj[from-1][to-1] = adj[to-1][from-1] = weight;
	}
	myfloyd();

	cin >> T;
	int s, t;
	for (int test = 0; test < T; test++) {
		cin >> s >> t;
		cout << adj[s-1][t-1] << endl;
	}
	return 0;
}