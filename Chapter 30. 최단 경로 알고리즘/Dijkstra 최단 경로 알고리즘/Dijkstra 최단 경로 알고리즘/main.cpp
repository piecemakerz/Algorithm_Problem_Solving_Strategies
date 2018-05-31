#include <vector>
#include <queue>
using namespace std;

const int MAX_V = 10;
const int INF = 987654321;
//정점의 개수
int V;
//그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];

//다익스트라의 최단 거리 알고리즘의 구현

vector<int> dijkstra(int src) {
	//dist[i] = src부터 i번째 정점까지의 최단거리
	vector<int> dist(V, INF);
	dist[src] = 0;
	//우선순위 큐. (정점까지의 거리, 정점의 번호) 쌍을 담는다.
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		//만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸 것을 무시한다.
		if (dist[here] < cost) continue;
		//인접한 정점들을 모두 갱신한다.
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			//더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

//우선순위 큐를 사용하지 않는 다익스트라 알고리즘의 구현

vector<int> dijkstra2(int src) {
	vector<int> dist(V, INF);
	//각 정점을 방문했는지 여부를 저장한다.
	vector<bool> visited(V, false);
	dist[src] = 0; visited[src] = true;
	while (true) {
		//아직 방문하지 않은 정점 중 가장 가까운 정점을 찾는다.
		int closest = INF, here;
		for (int i = 0; i < V; i++)
			if (dist[i] < closest && !visited[i]) {
				here = i;
				closest = dist[i];
			}
		if (closest == INF) break;
		//가장 가까운 정점을 방문한다.
		visited[here] = true;
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			if (visited[there]) continue;
			int nextDist = dist[here] + adj[here][i].second;
			dist[there] = min(dist[there], nextDist);
		}
	}
	return dist;
}