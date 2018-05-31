#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;
//V = 장소의 수, E = 도로의 수, n = 화재 장소의 수, m = 소방서의 수
int C, V, E, n, m;

//그래프의 인접 리스트 (연결된 정점 번호, 간산 가중치)
vector<vector<pair<int, int>>> adj;
//각 소방서에 대해 해당 정점으로 가기까지 걸리는 최소 시간
vector<vector<int>> shortestPaths;

/*
//내 풀이
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
*/

//책의 답
vector<int> dijkstraBook(int src) {
	//dist[i] = src부터 i번째 정점까지의 최단거리
	vector<int> dist(V+1, INF);
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
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		//V = 장소의 수, E = 도로의 수, n = 화재 장소의 수, m = 소방서의 수
		cin >> V >> E >> n >> m;
		adj = vector<vector<pair<int, int>>>(V+1);
		//shortestPaths = vector<vector<int>>(V);
		/*
		int from, to, weight;
		for (int i = 0; i < E; i++) {
			cin >> from >> to >> weight;
			adj[from-1].push_back(make_pair(to-1, weight));
			adj[to - 1].push_back(make_pair(from - 1, weight));
		}

		vector<int> placeOnFire(n);
		for (int i = 0; i < n; i++) {
			cin >> placeOnFire[i];
			placeOnFire[i] -= 1;
		}

		vector<int> fireStation(m);
		for (int i = 0; i < m; i++) {
			cin >> fireStation[i];
			fireStation[i] -= 1;
		}

		//각 소방서에 대해 각 정점으로의 최단거리를 구한다.
		for (int i = 0; i < m; i++) {
			vector<int> result = dijkstra(fireStation[i]);
			for (int j = 0; j < n; j++) 
				shortestPaths[placeOnFire[j]].push_back(result[placeOnFire[j]]);
		}

		long timeSum = 0;
		for (int i = 0; i < n; i++) {
			int goal = placeOnFire[i];
			sort(shortestPaths[goal].begin(), shortestPaths[goal].end());
			timeSum += shortestPaths[goal].front();
		}
		cout << timeSum << endl;
		*/
		int from, to, weight;
		for (int i = 0; i < E; i++) {
			cin >> from >> to >> weight;
			adj[from].push_back(make_pair(to, weight));
			adj[to].push_back(make_pair(from, weight));
		}

		vector<int> placeOnFire(n);
		for (int i = 0; i < n; i++)
			cin >> placeOnFire[i];

		vector<int> fireStation(m);
		for (int i = 0; i < m; i++) {
			cin >> fireStation[i];
			adj[0].push_back(make_pair(fireStation[i], 0));
		}
		
		long timeSum = 0;
		vector<int> result = dijkstraBook(0);
		for (int i = 0; i < n; i++)
			timeSum += result[placeOnFire[i]];
		cout << timeSum << endl;
	}
	return 0;
}