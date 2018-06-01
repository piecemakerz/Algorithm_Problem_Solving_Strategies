#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T;
//������ ��, ���� �����ϴ� ��ӵ����� ��, ������ �Ǽ��� ��ӵ����� ��
int V, M, N;
const int MAX_V = 200;
const int INF = 987654321;
vector<vector<int>> adj; //u���� v�� ���� ������ ����ġ
vector<vector<int>> subadj;

void floyd() {
	for (int i = 0; i < V; i++) adj[i][i] = 0;

	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++) {
			if (adj[i][k] >= INF)
				continue;
			for (int j = 0; j < V; j++)
				if (adj[i][j] > adj[i][k] + adj[k][j])
					adj[i][j] = adj[i][k] + adj[k][j];
		}
				
}

//�� Ǯ��

void subfloyd(int u, int v) {
	int k1 = min(u, v);
	int k2 = max(u, v);
	//adj[i][j]�� k1-k2 ��ӵ��θ� �߰������ν� �� ª�� ���ŵǷ���
	//���������� k1�� k2�� ������ ������ �Ѵ�. ���� k�� 0�� ��������
	//Ȯ���ϴ� ���� �ƴ϶� k1�� k2�� ���������� ������ ��츸 Ȯ���ϸ� �ȴٰ�
	//�����ߴ�.
	
	for (int i = 0; i < V; i++) {
		if (subadj[i][k1] >= INF)
			continue;
		for (int j = 0; j < V; j++)
			if (subadj[i][j] > subadj[i][k1] + subadj[k1][j])
				subadj[i][j] = subadj[i][k1] + subadj[k1][j];
	}
	
	for (int i = 0; i < V; i++) {
		if (subadj[i][k2] >= INF)
			continue;
		for (int j = 0; j < V; j++)
			if (subadj[i][j] > subadj[i][k2] + subadj[k2][j])
				subadj[i][j] = subadj[i][k2] + subadj[k2][j];
	}
}


//å�� ��

//���� (a, b)�� �߰����� �� �׷����� �ִ� �Ÿ� �迭 adj��
//������ �����Ѵ�. ������ �ƹ��� �ǹ̰� ���� ��� false�� ��ȯ�Ѵ�.
bool update(int a, int b, int c) {
	if (adj[a][b] <= c) return false;
	for (int x = 0; x < V; x++)
		for (int y = 0; y < V; y++)
			//x-y �ִܰ�ΰ� (a, b)�� �̿��Ϸ���
			//x-a-b-y Ȥ�� x-b-a-y�� ���¸� ������ �Ѵ�.
			adj[x][y] = min(adj[x][y], min(adj[x][a] + c + adj[b][y],
				adj[x][b] + c + adj[a][y]));
	return true;
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		int uselessHighway = 0;

		cin >> V >> M >> N;
		adj = vector<vector<int>>(V, vector<int>(V, INF));

		int u, v, c;
		for (int i = 0; i < M; i++) {
			cin >> u >> v >> c;
			adj[u][v] = adj[v][u] = min(adj[u][v], c); 
		}
		floyd();

		int newHighway;
		bool useful = false;
		for (int i = 0; i < N; i++) {
			cin >> u >> v >> newHighway;

			if (adj[u][v] > newHighway) {
				subadj = adj;
				subadj[u][v] = subadj[v][u] = newHighway;
				subfloyd(u, v);
				for (int i = 0; i < V; i++) {
					for (int j = 0; j < V; j++) {
						if (subadj[i][j] < adj[i][j]) {
							useful = true;
							break;
						}
					}
					if (useful)
						break;
				}
				if (useful)
					adj = subadj;
				else
					uselessHighway++;
			}

			else
				uselessHighway++;
			
			//if (!update(u, v, newHighway))
			//	uselessHighway++;
		}
		cout << uselessHighway << endl;
	}
	return 0;
}