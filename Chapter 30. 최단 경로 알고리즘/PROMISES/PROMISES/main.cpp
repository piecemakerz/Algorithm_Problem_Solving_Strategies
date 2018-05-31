#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int T;
//도시의 수, 현재 존재하는 고속도로의 수, 앞으로 건설될 고속도로의 수
int V, M, N;
const int MAX_V = 200;
const int INF = 987654321;
vector<vector<int>> adj; //u에서 v로 가는 간선의 가중치
//vector<vector<int>> subadj;

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

//내 풀이. 시간초과가 발생한다.
/*
void subfloyd(int u, int v) {
	int k1 = min(u, v);

	//adj[i][j]가 k1-k2 고속도로를 추가함으로써 더 짧게 갱신되려면
	//경유점으로 k1과 k2를 무조건 지나야 한다. 따라서 k를 0번 정점부터
	//확인하는 것이 아니라 k1부터 확인해도 무방하다.
	for (int k = k1; k < V; k++) {
		for (int i = 0; i < V; i++) {
			if (subadj[i][k] >= INF)
				continue;
			for (int j = 0; j < V; j++)
				if (subadj[i][j] > subadj[i][k] + subadj[k][j])
					subadj[i][j] = subadj[i][k] + subadj[k][j];
		}
	}
}
*/

//책의 답

//간선 (a, b)를 추가했을 때 그래프의 최단 거리 배열 adj를
//적절히 갱신한다. 간선이 아무런 의미가 없을 경우 false를 반환한다.
bool update(int a, int b, int c) {
	if (adj[a][b] <= c) return false;
	for (int x = 0; x < V; x++)
		for (int y = 0; y < V; y++)
			//x-y 최단경로가 (a, b)를 이용하려면
			//x-a-b-y 혹은 x-b-a-y의 형태를 가져야 한다.
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

		int u, v;
		for (int i = 0; i < M; i++) {
			cin >> u >> v;
			cin >> adj[u][v];
			adj[v][u] = adj[u][v]; 
		}
		floyd();

		int newHighway;
		//bool useful = false;
		for (int i = 0; i < N; i++) {
			cin >> u >> v >> newHighway;

			/*if (adj[u][v] > newHighway) {
				for (int i = 0; i < V; i++)
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
					for (int i = 0; i < V; i++)
						adj = subadj;
				else
					uselessHighway++;
			}

			else
				uselessHighway++;
			*/

			if (!update(u, v, newHighway))
				uselessHighway++;
		}
		cout << uselessHighway << endl;
	}
	return 0;
}