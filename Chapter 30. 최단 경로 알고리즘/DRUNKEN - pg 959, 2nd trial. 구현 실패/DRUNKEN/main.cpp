#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int V, E, T;
const int INF = 987654321;
vector<vector<int>> adj;
vector<vector<int>> maxWeight;
vector<int> nodeWeight;

//음주 운전 단속 문제를 해결하는 내 풀이. 오답이다.
//adj에 정점 가중치를 포함하는 최단경로를 저장하여 경유점을
//늘려갈 때마다 이를 갱신하는 알고리즘을 고안했으나,
//이는 저장되는 최단경로가 결국 최대 가중치 정점의 가중치를 포함한 경로 길이이므로
//후에 경유점을 늘렸을 때 최대 가중치 정점이 바뀌게 되면 간선의 길이가 더 짧은
//경로가 최단경로가 된다.
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
//위 예제입력을 넣어서 돌려보면 쉽게 이해할 수 있다.
void myfloyd() {
	for (int i = 0; i < V; i++)
		adj[i][i] = 0;

	//0~k번 정점을 경유점으로 사용한다.
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++) {
			//i번 정점에서 k번 정점으로 가는 경로가 없거나 i == k인 경우
			if (adj[i][k] >= INF || i == k)
				continue;
			for (int j = 0; j < V; j++) {
				//j번 정점에서 k번 정점으로 가는 경로가 없거나 j == k인 경우
				if (adj[k][j] >= INF || j == k)
					continue;

				//curmaxW = k번 정점을 포함하는 경로에서의 가장 큰 가중치를 가지는 정점
				int curmaxW = max(maxWeight[i][k], maxWeight[k][j]);
				curmaxW = max(curmaxW, nodeWeight[k]);

				//ret = k번 정점을 포함하는 i->j 최단경로의 길이
				int ret = adj[i][k] + adj[k][j] - maxWeight[i][k] - maxWeight[k][j] + curmaxW;
				//기존 최단경로보다 k번 정점을 포함하는 경로의 길이가 더 짧다면 갱신한다.
				if (adj[i][j] > ret) {
					adj[i][j] = adj[j][i] = ret;
					maxWeight[i][j] = maxWeight[j][i] = curmaxW;
				}
			}
		}
}

//플로이드 알고리즘을 개선해 음주 운전 문제를 해결하는 책의 알고리즘의 구현

//그래프의 인접 행렬 표현
int V, adj[500][500];
//각 정점에서 음주 운전 단속을 할 때 걸리는 시간
int delay[500];
int W[500][500];
//입력을 받을 때 1부터 시작하는 정점 번호를 0부터 시작하도록 변경했다고 가정한다.
void solve() {
	//모든 정점들을 예상 시간 별로 정렬한다.
	vector<pair<int, int>> order;
	for (int i = 0; i < V; i++)
		order.push_back(make_pair(delay[i], i));
	sort(order.begin(), order.end());
	//정점을 하나도 거치지 않고 얻을 수 있는 최단 경로
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			if (i == j)
				W[i][j] = 0;
			else
				W[i][j] = adj[i][j];

	for (int k = 0; k < V; k++) {
		//k번째로 예상 시간이 적게 걸리는 정점 w까지를 지나서 얻을 수 있는 최단 거리
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