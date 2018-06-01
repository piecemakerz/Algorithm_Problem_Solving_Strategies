#include <vector>
#include <queue>
using namespace std;

const int MAX_V = 100;
const int INF = 987654321;
//정점의 개수
int V;
//그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];
//주어진 그래프에 대해 최소 스패닝 트리에 포함된 간선의 목록을 selected에
//저장하고, 가중치의 합을 반환한다.
int prim(vector<pair<int, int>>& selected) {
	selected.clear();
	//해당 정점이 트리에 포함되어 있나?
	vector<bool> added(V, false);
	//트리에 인접한 간선 중 해당 정점에 닿는 최소 간선의 정보를 저장한다.
	vector<int> minWeight(V, INF), parent(V, -1);
	//가중치의 합을 저장할 변수
	int ret = 0;
	//0번 정점을 시작점으로: 항상 트리에 먼저 추가된다.
	minWeight[0] = parent[0] = 0;
	//우선순위 큐. (minWeihgt[], 정점의 번호) 쌍을 담는다.
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, 0));
	while(!pq.empty()) {
		//다음에 트리에 추가할 정점 u를 찾는다.
		int weight = -pq.top().first;
		int u = pq.top().second;
		pq.pop();
		if (added[u]) continue;

		//parent([u], u)를 트리에 추가한다.
		if (parent[u] != u)
			selected.push_back(make_pair(parent[u], u));

		ret += weight;
		added[u] = true;
		//u에 인접한 간선 (u, v)들을 검사한다.
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, weight = adj[u][i].second;
			if (!added[v] && minWeight[v] > weight) {
				parent[v] = u;
				minWeight[v] = weight;
				pq.push(make_pair(-weight, v));
			}
		}
	}
	return ret;
}