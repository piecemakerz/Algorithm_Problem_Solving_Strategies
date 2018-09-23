#include <vector>
#include <queue>
#include <iostream>
#include <cstdio>
#include <limits>
using namespace std;

int C, V, E, n, m;
const int INF = 987654321;

vector<vector<pair<int, int>>> adj;
vector<int> firestation, fireplace;

vector<int> dijkstra(int src) {
	vector<int> dist(V+1, INF);
	dist[src] = 0;
	//(경로 길이, 정점 번호)
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		if (dist[here] < cost) continue;
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> V >> E >> n >> m;
		adj = vector<vector<pair<int, int>>>(V+1);
		int a, b, t;
		for (int i = 0; i < E; i++) {
			cin >> a >> b >> t;
			adj[a].push_back(make_pair(b, t));
			adj[b].push_back(make_pair(a, t));
		}
		int input;
		for (int i = 0; i < n; i++) {
			cin >> input;
			fireplace.push_back(input);
		}
		for (int i = 0; i < m; i++) {
			cin >> input;
			firestation.push_back(input);
			adj[0].push_back(make_pair(input, 0));
			adj[input].push_back(make_pair(0, 0));
		}

		vector<int> ret = dijkstra(0);
		int result = 0;
		for (int i = 0; i < fireplace.size(); i++)
			result += ret[fireplace[i]];
		cout << result << endl;

		for (int i = 0; i < adj.size(); i++)
			adj[i].clear();
		fireplace.clear();
		firestation.clear();
	}
}