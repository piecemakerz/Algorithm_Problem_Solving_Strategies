#include <vector>
#include <queue>
#include <iostream>
#include <cstdio>
#include <limits>
using namespace std;

const double INF = numeric_limits<double>::infinity();
int t;
//컴퓨터의 수, 회선의 수
int n, m;
//그래프의 인접 리스트 (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<vector<pair<int, double>>> adj;

vector<double> routing(int src) {
	//dist[i] = src부터 i번째 정점까지의 최단거리
	vector<double> dist(n, INF);
	dist[src] = 1.0;
	//우선순위 큐. (정점까지의 거리, 정점의 번호) 쌍을 담는다.
	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(1.0, src));
	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		//만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
		if (dist[here] < cost) continue;
		//인접한 정점들을 모두 갱신한다.
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			double nextDist = cost * adj[here][i].second;
			//더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 삽입한다.
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

int main(void) {
	cin >> t;
	for (int test = 0; test < t; test++) {
		cin >> n >> m;
		int from, to;
		double weight;
		adj = vector<vector<pair<int, double>>>(n);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %lf", &from, &to, &weight);
			adj[from].push_back(make_pair(to,weight));
			adj[to].push_back(make_pair(from, weight));
		}
		printf("%f\n", -routing(0)[n - 1]);
	}
	return 0;
}