#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>
using namespace std;

const double INF = 1e200;
const int MAX = 30;
int n; // 도시의 수
double dist[MAX][MAX]; // 두 도시간의 거리를 저장하는 배열

//best: 지금까지 찾은 최적해. 전역 변수에 지금까지 찾은 최적해의 길이를
//저장해 두면 탐색 중에 더 최적해를 발견할 가능성이 없는 가지를
//쳐내기 쉬워진다.
double best;

//TSP를 해결하는 완전 탐색의 구현

//path: 지금까지 만든 경로
//visited: 각 도시의 방문 여부
//currentLength: 지금까지 만든 경로의 길이
//나머지 도시들을 모두 방문하는 경로들을 만들어 보고 가능하면 최적해를 갱신한다.
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//간단한 가지치기: 지금까지 찾은 가장 좋은 답 이상일 경우 중단
	if (best <= currentLength) return;
	int here = path.back();
	//기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다.
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//다음 방문할 도시를 전부 시도해 본다.
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

//단순한 휴리스틱을 이용한 가지치기의 구현

//각 도시에 인접한 간선 중 가장 짧은 것을 미리 찾아 둔다.
double minEdge[MAX];
//가장 단순한 형태의 휴리스틱. 아직 방문하지 않은 도시들에 대해
//인접한 간선 중 가장 짧은 간선의 길이를 더한다. 한 간선의 중복선택도
//가능하다.
double simpleHeuristic(vector<bool>& visited) {
	double ret = minEdge[0]; //마지막에 시작점으로 돌아갈 때 사용할 간선
	for (int i = 0; i < n; i++)
		if (!visited[i])
			ret += minEdge[i];
	return ret;
}
//단순한 휴리스틱을 적용한 search 알고리즘
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//단순한 휴리스틱을 이용한 가지치기
	if (best <= currentLength + simpleHeuristic(visited)) return;
	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	for (int next = 0; next < n; next++) {
		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

//가까운 정점부터 방문하는 최적화의 구현. 도시를 번호 순서대로 방문하는 대신,
//더 가까운 것부터 방문하면 좋은 답을 더 빨리 찾아낼 수 있는 경우가 있다.
vector<int> nearest[MAX];
//가까운 정점부터 방문하는 최적화를 적용한 search 알고리즘
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//단순한 휴리스틱을 이용한 가지치기
	if (best <= currentLength + simpleHeuristic(visited)) return;
	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//다음 방문할 도시를 전부 시도해 본다.
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];

		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

//지나온 경로를 이용하는 두 가지 가지치기 전략의 구현

//path의 마지막 네 개의 도시 중 가운데 있는 두 도시의 순서를 바꿨을 때
//경로가 더 짧아지는지 여부를 반환한다. 더 짧아진다면 참을 반환한다.
bool pathSwapPruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}
//시작 도시와 현재 도시를 제외한 path의 모든 부분 경로를
//뒤집어 보고 더 짧아지는지 확인한다. 더 짧아진다면 참을 반환한다.
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

//지나온 경로를 이용해 가지치기를 하는 최적화를 적용한 search 알고리즘
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//단순한 휴리스틱을 이용한 가지치기
	if (best <= currentLength + simpleHeuristic(visited)) return;
	//부분 경로를 뒤집었을 때 경로 길이가 짧아진다면 최적해가 아니므로 바로 종료한다.
	if (pathReversePruning(path)) return;

	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//다음 방문할 도시를 전부 시도해 본다.
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];

		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

//MST 휴리스틱의 구현. 

//Union-Find 상호 배제적 집합 (공통 원소가 없는 집합)자료 구조를 구현한다.
//Union-Find는 Disjoint Set으로도 불리는 상호 배터적으로
//이루어진 집합을 효율적으로 표현하기 위해 만들어진 자료구조로,
//크루스칼 알고리즘에서 원소 간의 연결 여부를 판단하는데 사용한다.
//
struct UnionFind
{
	//n = 노드의 총 개수, componenets = 집합의 개수
	int n, components;
	//parent[i] = i가 속한 집합의 트리에서의 i의 부모 노드 번호
	//rank[i] = i가 속한 집합의 트리 높이
	vector<int> parent, rank;
	//상호 배제적 집합을 초기화할 때는 각 노드에 대응하는 집합을 하나씩 생성한다.
	UnionFind(int n) : n(n), components(n), parent(n), rank(n)
	{
		for (int i = 0; i < n; ++i) { parent[i] = i; rank[i] = 0; }
	}
	//find(here) = here이 속한 집합의 트리 루트 노드 번호를 반환한다.
	int find(int here) { return parent[here] == here ? here : (parent[here] = find(parent[here])); }
	//merge(a, b) = a가 속한 집합과 b가 속한 집합을 합친다.
	//a와 b가 같은 집합에 속해있다면 false를 반환한다.
	bool merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return false;
		//a 집합의 높이가 b 집합보다 높다면 b 집합을 a 집합 루트의 아래에 합친다.
		if (rank[a] > rank[b])
			parent[b] = a;
		else
		{
			parent[a] = b;
			//합치려는 두 집합의 높이가 서로 같다면 합쳐진 집합 트리의 높이를 하나 증가시킨다.
			if (rank[a] == rank[b]) rank[b]++;
		}
		--components;
		return true;
	}
};

//모든 도시 간의 도로를 길이 순으로 정렬해 저장해 둔다.
vector<pair<double, pair<int, int>>> edges;
//here와 시작점, 아직 방문하지 않은 도시들을 모두 연결하는 MST를 찾고
//MST의 길이를 반환한다.
double mstHeuristic(int here, const vector<bool>& visited) {
	//Kruskal's MST
	UnionFind sets(n);
	double taken = 0;
	for (int i = 0; i < edges.size(); i++) {
		int a = edges[i].second.first, b = edges[i].second.second;
		if (a != 0 && a != here && visited[a]) continue;
		if (b != 0 && b != here && visited[b]) continue;
		if (sets.merge(a, b))
			taken += edges[i].first;
	}
}

//MST 휴리스틱을 이용한 가지치기를 적용한 search 알고리즘
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//MST 휴리스틱을 이용한 가지치기
	if (best <= currentLength + mstHeuristic(path.back(), visited)) return;
	//부분 경로를 뒤집었을 때 경로 길이가 짧아진다면 최적해가 아니므로 바로 종료한다.
	if (pathReversePruning(path)) return;

	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//다음 방문할 도시를 전부 시도해 본다.
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];

		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

//부분적으로 메모이제이션을 사용하는 최적화의 구현

//남은 도시의 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다.
const int CACHED_DEPTH = 5;
//dp()에서 cache는 현재 위치, 남은 정점의 수를 인덱스로 갖는 map의 2차원 배열로,
//사실상 3차원 배열이다. map에 접근하는 비용은 원소의 수가 커지면 커질수록 늘어나므로,
//남은 도시의 수별로 map을 나누면 접근하는 데 드는 시간을 조금이나마 줄일 수 있다.
//dp(here, visited) = cache[here][남은 도시의 수][visited]
map<int, double> cache[MAX][CACHED_DEPTH + 1];
//here: 현재 위치
//visited: 각 도시의 방문 여부
//일 때, 나머지 도시를 모두 방문하고 시작점으로 돌아가는 최단 경로의 길이를 반환한다.
double dp(int here, int visited) {
	bitset<24> bitVisited(visited);
	//기저 사례: 더 방문할 도시가 없으면 시작점으로 돌아간다.
	if (visited == (1 << n) - 1) return dist[here][0];
	//메모이제이션
	//__builtin_popcount(i)는 i에 포함된 1비트의 수를 반환하는 함수로,
	//GCC에 존재하는 기능으로 visual c++에서는 사용할 수 없다. 따라서
	//visited를 bitset으로 변환하여 bitset의 내장함수를 사용하였다.
	int remaining = n - bitVisited.count();
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

//부분적 메모이제이션을 적용한 search 알고리즘
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	if (best <= currentLength + mstHeuristic(path.back(), visited)) return;
	//기저 사례: 남은 도시 수가 CACHED_DEPTH 이하면 동적 계획법으로 바꾼다.
	/*if (path.size() + CACHED_DEPTH >= n) {
		best = min(best, currentLength + dp(path.back(), visited));
		return;
	}
	*/
	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];

		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}
double solve() {
	//cache 초기화
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j <= CACHED_DEPTH; j++)
			cache[i][j].clear();

	//edges 초기화
	edges.clear();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
	sort(edges.begin(), edges.end());

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

	//simpleHeuristic()을 위한 초기화
	for (int i = 0; i < n; i++) {
		minEdge[i] = INF;
		for (int j = 0; j < n; j++)
			if (i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
	}

	//best를 매우 큰 값으로 초기화
	best = INF;
	vector<bool> visited(n, false);
	vector<int> path(1, 0);
	visited[0] = true;
	search(path, visited, 0);
	return best;
}