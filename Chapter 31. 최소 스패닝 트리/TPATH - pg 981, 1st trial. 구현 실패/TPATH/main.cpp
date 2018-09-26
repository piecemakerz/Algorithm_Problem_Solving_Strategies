#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//minUpperBound()를 이용해 여행 경로 문제 해결하기

const int INF = 987654321;
const int MAX_V = 2000;
int V, E;
//그래프의 연결 리스트 표현
vector<pair<int, int>> adj[MAX_V];
//모든 간선의 가중치 목록. 정렬해 둔다.
vector<int> weights;
//가중치가 weights[low] 이상인 간선으로 시작점과 도착점을 연결하는
//경로를 만들기 위해 필요한 경로의 최소 상한을 계산한다. 두 정점을
//연결할 수 없을 경우 큰 값을 반환한다.
int minUpperBound(int low);
//0과 V-1을 연결하는 경로 중 가중치의 상한과 하한 차이의
//최소 값을 계산한다.
int minWeightDifference() {
	int ret = INF;
	for(int i=0; i < weights.size(); i++)
		ret = min(ret, minUpperBound(i) - weights[i]);
	return ret;
}

//이분 검색으로 minUpperBound() 구현하기

//0과 V-1을 잇는 경로 중 사용 가중치 범위가 [lo, hi] 안인
//경로가 있는가?
//깊이 우선 탐색이나 너비 우선 탐색으로 구현한다.
bool hasPath(int lo, int hi) {
	vector<bool> discovered(V, false);
	queue<int> q;
	vector<int> order;
	discovered[0] = true;
	q.push(0);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		order.push_back(here);
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first, edge = adj[here][i].second;
			if (!discovered[there] && edge >= lo && edge <= hi) {
				q.push(there);
				discovered[there] = true;
			}
		}
		if (discovered[V - 1])
			return true;
	}
	return false;
}
int binarySearchMinUpperBound(int low) {
	//반복문 불변식:
	//1. 가중치가 [weights[low], weights[lo]]
	//범위에 있는 간선을 사용하면 두 정점을 연결할 수 없다.
	//2. 가중치가 [weights[low], weights[hi]] 범위에 있는
	//간선을 사용하면 두 정점을 연결할 수 있다.
	int lo = low - 1, hi = weights.size();
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (hasPath(weights[low], weights[mid]))
			hi = mid;
		else
			lo = mid;
	}
	if (hi == weights.size()) return INF;
	return weights[hi];
}

//변형한 크루스칼 알고리즘으로 여행 경로 문제 해결하기

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

//(가중치,(정점1, 정점2))의 목록. 미리 정렬해 둔다.
vector<pair<int, pair<int, int>>> edges;
int kruskalMinUpperBound(int low) {
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].first < weights[low]) continue;
		//edges[i]를 그래프에 추가하자.
		sets.merge(edges[i].second.first, edges[i].second.second);
		//0과 V-1이 연결되었다면 마지막에 추가한 간선의 가중치를 반환한다.
		if (sets.find(0) == sets.find(V - 1))
			return edges[i].first;
	}
	return INF;
}

//여행 경로 문제를 해결하는 가장 무식한 알고리즘

//모든 상한/하한의 쌍에 대해 경로가 존재하는지 전부 확인해
//보고, 경로가 존재하는 최소 너비를 반환한다.
int brute() {
	int ret = INF;
	for(int lo = 0; lo < weights.size(); lo++)
		for (int hi = lo; hi < weights.size(); hi++) {
			//상한/하한의 쌍이 주어질 때, 두 점을 잇는 경로가 존재하는가?
			if (hasPath(weights[lo], weights[hi])) {
				ret = min(ret, weights[hi] - weights[lo]);
				break;
			}
		}
	return ret;
}

//여행 경로 문제를 해결하는 무식한 알고리즘을 최적화하기

//brute()를 더 빠르게 개선한 알고리즘
int optimized() {
	//foundPathUsing = 경로를 찾기 위해 마지막으로 사용했던 상한의 위치
	int ret = INF, foundPathUsing = 0;
	for (int lo = 0; lo < weights.size(); lo++) {
		//이 하한에 대해 경로를 발견했는가?
		bool foundPath = false;
		for (int hi = foundPathUsing; hi < weights.size(); hi++) {
			if (hasPath(weights[lo], weights[hi])) {
				ret = min(ret, weights[hi] - weights[lo]);
				foundPath = true;
				foundPathUsing = hi;
				break;
			}
		}
		//경로가 없다면 곧장 종료한다.
		if (!foundPath) break;
	}
	return ret;
}

//여행 경로 문제를 해결하는 간결한 알고리즘

//가중치 범위를 훑어나가며 경로가 존재하는 가중치 범위의 최소 크기를 찾는다.
int scanning() {
	int lo = 0, hi = 0, ret = INF;
	while (lo < weights.size() && hi < weights.size()) {
		if (hasPath(weights[lo], weights[hi])) {
			ret = min(ret, weights[hi] - weights[lo]);
			lo++;
		}
		else
			hi++;
	}
}