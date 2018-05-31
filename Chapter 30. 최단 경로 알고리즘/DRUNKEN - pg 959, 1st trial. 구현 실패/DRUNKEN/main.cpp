#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_V = 500;
const int INF = 987654321;
int T; //테스트 케이스
int V, E; // 장소의 수, 도로의 수
int adj[MAX_V][MAX_V]; //adj[u][v] = u에서 v로 가는 간선의 가중치. 간선이 없으면 아주 큰 값을 넣는다.

//내 풀이
//maxDrunken[i][j] = i에서 j로 가는 최단경로에서 가장 큰 가중치를 가지는 경유점의 가중치.
int maxDrunken[MAX_V][MAX_V];
//drunken[i] = 정점 i의 가중치
int drunken[MAX_V];
//W[i][j] = i에서 j로 가는 최단경로의 길이 (최대 경유점 가중치 포함) 
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
//책의 답
//각 정점에서 음주 운전 단속을 할 때 걸리는 시간
int delay[MAX_V];

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
	int ret = INF;
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
*/

int main(void) {
	memset(adj, INF, sizeof(adj));
	cin >> V >> E;
	//음주 정점 가중치 입력
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