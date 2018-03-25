#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <bitset>
using namespace std;

const double INF = 1e200;
const int MAX = 30;
int n; // 도시의 수
double dist[MAX][MAX]; //두 도시간의 거리를 저장하는 배열
//지금까지 찾은 최적해
double best;
//각 도시에 인접한 간선 중 가장 짧은 것을 미리 찾아 둔다.
double minEdge[MAX];
//가장 단순한 형태의 휴리스틱
double simpleHeuristic(vector<bool>& visited) {
	double ret = minEdge[0]; //마지막에 시작점으로 돌아갈 때 사용할 간선
	for (int i = 0; i < n; i++)
		if (!visited[i])
			ret += minEdge[i];
	return ret;
}

//각 도시마다 다른 도시들을 가까운 순서대로 정렬해 둔다.
vector<int> nearest[MAX];

//path의 마지막 네 개의 도시 중 가운데 있는 도시의 두 순서를 바꿨을 때
//경로가 더 짧아지는지 여부를 반환한다.
bool pathSwapPruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}
//시작 도시와 현재 도시를 제외한 path의 부분 경로를
//뒤집어 보고 더 짧아지는지 확인한다.
bool pathReversePruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	for (int i = 0; i + 3 < path.size(); i++) {
		int p = path[i];
		int a = path[i + 1];
		//[..,p,a,...,b,q]를 [..,p,b,...,a,q]로 바꿔본다.
		if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
			return true;
	}
	return false;
}

//상호 배타적 집합 자료 구조를 구현한다.
struct DisjointSet {
	int n, components;
	vector<int> parent, rank;
	//n개의 원소로 구성된 집합 자료 구조를 만든다.
	DisjointSet(int n) : n(n), components(n), parent(n), rank(n) {
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}
	//here가 포함된 집합의 대표를 반환한다.
	int find(int here) {
		return parent[here] == here ? here : (parent[here] = find(parent[here]));
	}
	//a가 포함된 집합과 b가 포함된 집합을 합친다.
	bool merge(int a, int b) {
		a = find(a); b = find(b);
		if (a == b) return false;
		if (rank[a] > rank[b])
			parent[b] = a;
		else {
			parent[a] = b;
			if (rank[a] == rank[b]) rank[b]++;
		}
		--components;
		return true;
	}
};
//모든 도시 간의 도로를 길이 순으로 정렬해 저장해 둔다.
vector <pair<double, pair<int, int>>> edges;
//here와 시작점, 아직 방문하지 않은 도시들을 모두 연결하는 MST를 찾는다.
double mstHeuristic(int here, const vector<bool>& visited) {
	//Kruskal's MST
	DisjointSet sets(n);
	double taken = 0; // 경로 길이의 합(간선 가중치의 합)
	for (int i = 0; i < edges.size(); i++) {
		int a = edges[i].second.first, b = edges[i].second.second;
		if (a != 0 && a != here && visited[a]) continue;
		if (b != 0 && b != here && visited[b]) continue;
		if (sets.merge(a, b))
			taken += edges[i].first;
	}
	return taken;
}

//남은 도시의 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다.
const int CACHED_DEPTH = 5;
//dp(here, visited) = cache[here][남은 도시의 수][visited]
map<int, double> cache[MAX][CACHED_DEPTH + 1];
//here: 현재 위치
//visited: 각 도시의 방문 여부
//일 때, 나머지 도시를 모두 방문하고 시작점으로 돌아가는 최단 경로의 길이를 반환한다.
int popcount(int n) {
	int count = 0;
	while (n > 0) {
		if (n & 1)
			count++;
		n >>= 1;
	}
	return count;
}
double dp(int here, int visited) {
	//기저 사례: 더 방문할 도시가 없으면 시작점으로 돌아간다.
	if (visited == (1 << n) - 1) return dist[here][0];
	//메모이제이션
	int remaining = n - popcount(visited);
	double& ret = cache[here][remaining][visited];
	if (ret > 0) return ret;
	ret = INF;
	//다음 도시를 하나씩 시도한다.
	for (int next = 0; next < n; next++) {
		if (visited & (1 << next)) continue;
		ret = min(ret, dp(next, visited + (1 << next)) + dist[here][next]);
	}
	return ret;
}

//path: 지금까지 만든 경로
//visited: 각 도시의 방문 여부
//currentLength: 지금까지 만든 경로의 길이
//나머지 도시들을 모두 방문하는 경로들을 만들어 보고 가능하면 최적해를 갱신한다.
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	int here = path.back();
	//기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다.
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//간단한 가지치기: 지금까지 찾은 가장 좋은 답 이상일 경우 중단
	//if (best <= currentLength) return;

	//단순한 휴리스틱을 이용한 가지치기
	//if (best <= currentLength + simpleHeuristic(visited))	return;

	//기저 사례: 남은 도시 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다.
	if (path.size() + CACHED_DEPTH >= n) {
		int mask = 0;
		for (int i = 0; i < n; i++) if (visited[i]) mask += (1 << i);
		best = min(best, currentLength + dp(path.back(), mask));
		return;
	}

	//다음 방문할 도시를 전부 시도해 본다.
	/*
	가까운 정점부터 방문하는 최적화를 적용했을 때
	for(int i = 0; i < nearest[here].size(); i++){
		int next = nearest[here][i];
	*/

	for (int next = 0; next < n; next++) {
		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		//나머지 경로를 재귀 호출을 통해 완성한다.
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

double solve() {
	/*
	//simpleHeuristic()을 위한 초기화
	for (int i = 0; i < n; i++) {
		minEdge[i] = INF;
		for (int j = 0; j < n; j++)
			if (i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
	}
	*/

	/*
	//nearest 초기화
	for (int i = 0; i < n; i++) {
		vector<pair<double, int>> order;
		for (int j = 0; j < n; j++)
			if (i != j)
				order.push_back(make_pair(dist[i][j], j));
		sort(order.begin(), order.end());
		nearest[i].clear();
		for (int j = 0; j < n - 1; j++)
			nearest[i].push_back(order[j].second);
	}
	*/

	//edges 초기화
	edges.clear();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
	sort(edges.begin(), edges.end());

	//cache 초기화
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j <= CACHED_DEPTH; j++)
			cache[i][j].clear();

	//best를 매우 큰 값으로 초기화
	best = INF;
	vector<bool> visited(n, false);
	vector<int> path(1, 0);
	visited[0] = true;
	search(path, visited, 0);
	return best;
}