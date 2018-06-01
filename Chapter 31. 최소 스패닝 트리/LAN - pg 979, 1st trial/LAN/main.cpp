#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAX_N = 500;
const int MAX_M = 2000;
const int INF = 987654321;

int C, N, M;

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

//크루스칼 최소 스패닝 트리 알고리즘을 이용한 내 풀이

//(연결된 정점, 가중치)
vector<pair<int, double>> adj[MAX_N];
vector<int> xpos, ypos;

double kruskal(DisjointSet& sets) {
	double ret = 0;
	//(가중치, (정점1, 정점2))의 목록을 얻는다.
	vector<pair<double, pair<int, int>>> edges;
	for (int u = 0; u < N; u++)
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			double cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}
	//가중치 순으로 정렬
	sort(edges.begin(), edges.end());
	//처음엔 모든 정점이 서로 분리되어 있다.
	for (int i = 0; i < edges.size(); i++) {
		//간선 (u, v)를 검사한다.
		double cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		//이미 u와 v가 연결되어 있을 경우 무시한다.
		if (sets.find(u) == sets.find(v)) continue;
		//이 둘을 합친다.
		sets.merge(u, v);
		ret += cost;
	}
	return ret;
}

//프림 알고리즘을 사용한 책의 풀이 구현
double prim() {
	//해당 정점이 트리에 포함되어 있나?
	vector<bool> added(N, false);
	//트리에 인접한 간선 중 해당 정점에 닿는 최소 간선의 정보를 저장한다.
	vector<double> minWeight(N, INF);
	vector<int> parent(N, -1);
	//가중치의 합을 저장할 변수
	double ret = 0;
	//0번 정점을 시작점으로: 항상 트리에 먼저 추가된다.
	minWeight[0] = parent[0] = 0;
	//우선순위 큐. (minWeihgt[], 정점의 번호) 쌍을 담는다.
	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(0.0, 0));
	while (!pq.empty()) {
		//다음에 트리에 추가할 정점 u를 찾는다.
		double weight = -pq.top().first;
		int u = pq.top().second;
		pq.pop();
		if (added[u]) continue;

		ret += weight;
		added[u] = true;
		//u에 인접한 간선 (u, v)들을 검사한다.
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			double weight = adj[u][i].second;
			if (!added[v] && minWeight[v] > weight) {
				parent[v] = u;
				minWeight[v] = weight;
				pq.push(make_pair(-weight, v));
			}
		}
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		int input;
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			cin >> input;
			xpos.push_back(input);
		}
		for (int i = 0; i < N; i++) {
			cin >> input;
			ypos.push_back(input);
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (i == j) continue;
				adj[i].push_back(make_pair(j, sqrt(pow(xpos[i] - xpos[j], 2) + pow(ypos[i] - ypos[j], 2))));
			}

		/*
		DisjointSet sets(N);
		vector<pair<int, int>> selected;
		for (int i = 0; i < M; i++) {
			int n1, n2;
			cin >> n1 >> n2;
			sets.merge(n1, n2);
		}
		printf("%.10lf\n", kruskal(sets));
		*/

		for (int i = 0; i < M; i++) {
			int n1, n2;
			cin >> n1 >> n2;
			for(int i=0; i<adj[n1].size(); i++)
				if (adj[n1][i].first == n2) {
					adj[n1][i].second = 0.0;
					break;
				}
			for (int i = 0; i<adj[n2].size(); i++)
				if (adj[n2][i].first == n1) {
					adj[n2][i].second = 0.0;
					break;
				}
		}
		printf("%.10lf\n", prim());

		for (int i = 0; i < N; i++)
			adj[i].clear();
		xpos.clear();
		ypos.clear();
	}
	return 0;
}