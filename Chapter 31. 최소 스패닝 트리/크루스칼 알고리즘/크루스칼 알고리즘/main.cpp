#include <vector>
#include <algorithm>
using namespace std;

//최적화된 상호 배타적 집합의 구현
struct DisjointSet {
	vector<int> parent, rank;
	DisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	//u가 속한 트리의 루트의 번호를 반환한다.
	//한번 u에 대해 find를 호출하면 parent[u]가 트리의 루트를 가리키게
	//되므로 다음번 호출할 때 경로를 따라 올라갈 것 없이 바로 루트를 찾을 수 있다.
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}
	//u가 속한 트리와 v가 속한 트리를 합친다.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		//u와 v가 이미 같은 집합에 속하는 경우를 걸러낸다.
		if (u == v) return;
		if (rank[u] > rank[v]) swap(u, v);
		//rank[v]가 항상 rank[u] 이상이므로 u를 v의 자식으로 넣는다. 
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}
};

//크루스칼 최소 스패닝 트리 알고리즘

//트리를 이용해 상호 배타적 집합을 구현한다.
const int MAX_V = 100;
//정점의 개수
int V;
//그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<pair<int, int>> adj[MAX_V];

//주어진 그래프에 대해 최소 스패닝 트리에 포함된 간선의 목록을 
//selected에 저장하고, 가중치의 합을 반환한다.
int kruskal(vector<pair<int, int>>& selected) {
	int ret = 0;
	selected.clear();
	//(가중치, (정점1, 정점2))의 목록을 얻는다.
	vector<pair<int, pair<int, int>>> edges;
	for (int u = 0; u < V; u++)
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}
	//가중치 순으로 정렬
	sort(edges.begin(), edges.end());
	//처음엔 모든 정점이 서로 분리되어 있다.
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); i++) {
		//간선 (u, v)를 검사한다.
		int cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		//이미 u와 v가 연결되어 있을 경우 무시한다.
		if (sets.find(u) == sets.find(v)) continue;
		//이 둘을 합친다.
		sets.merge(u, v);
		selected.push_back(make_pair(u, v));
		ret += cost;
	}
	return ret;
}