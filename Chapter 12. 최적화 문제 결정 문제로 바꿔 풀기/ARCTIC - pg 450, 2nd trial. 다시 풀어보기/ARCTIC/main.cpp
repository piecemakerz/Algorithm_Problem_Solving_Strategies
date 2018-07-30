#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

int C, N;
//mindis = 기지를 연결하는 모든 간선 중 가장 짧은 간선
//maxdis = 기지를 연결하는 모든 간선 중 가장 긴 간선
double mindis, maxdis;
const double MAX = 987654321.0;
//coord[i] = (i의 y좌표, i의 x좌표)
vector<pair<double, double>> coord;
//dist[i][j] = i번 기지와 j번 기지를 연결하는 간선의 길이
double dist[100][100];

vector<pair<double, pair<int, int>>> edges;
int visited[100];

//각 기지 사이의 길이를 계산하고, mindis와 maxdis를 갱신한다.
void generateDistance() {
	mindis = MAX, maxdis = 0;
	for (int i = 0; i < N; i++) {
		double x1 = coord[i].second, y1 = coord[i].first;
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			double x2 = coord[j].second, y2 = coord[j].first;
			dist[i][j] = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			if (mindis > dist[i][j]) mindis = dist[i][j];
			if (maxdis < dist[i][j]) maxdis = dist[i][j];
			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
		}
	}
	sort(edges.begin(), edges.end());
}

//모든 기지를 하나로 연결하되, 가장 먼 두 기지 간의 거리가 d
//이하인 연락망이 있는가?
bool solve(double gap) {
	int selected[100];
	memset(selected, 0, sizeof(selected));
	queue<int> q;
	q.push(0);
	selected[0] = 1;

	while(!q.empty()) {
		int curPos = q.front();
		for (int i = 0; i < N; i++) {
			if (i == curPos || selected[i]) continue;

			if (dist[curPos][i] <= gap) {
				selected[i] = 1;
				q.push(i);
			}
		}
		q.pop();
	}
	for (int i = 0; i < N; i++)
		if (!selected[i])
			return false;
	return true;
}

//가능한 최소 통신 반경을 반환한다.
double myoptimize() {
	double lo = mindis, hi = maxdis;
	//반복적 불변식: !solve(lo) && solve(hi)
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2.0;
		//반경이 mid일 때 모든 기지가 통신할 수 있다면 답은 [lo, mid]에 있다.
		if (solve(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

//크루스칼의 최소 스패닝 트리 알고리즘으로 해결한 방법
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

double MSTsolve() {
	UnionFind sets(N);
	double maxLen = 0;
	for (int i = 0; i < edges.size(); i++) {
		int a = edges[i].second.first, b = edges[i].second.second;
		if (sets.merge(a, b))
			maxLen = max(maxLen, edges[i].first);
	}
	return maxLen;
}

//책의 남극 기지 문제를 결정 문제로 바꿔 해결하는 이분법 알고리즘
//그래프의 너비 우선 탐색 알고리즘을 이용한다. 서로 거리가 d 이하인
//기지들 간에 간선이 있다고 가정하고 그래프를 만든 뒤, 한 기지에서
//시작해 탐색 알고리즘을 이용해 다른 기지에도 전부 방문할 수 있는지를 확인한다.

//거리 d 이하인 기지들만을 연결했을 때 모든 기지가 연결되는지 여부를 반환한다.
bool decision(double d) {
	vector<bool> visited(N, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		seen++;
		for(int there = 0; there < N; there++)
			if (!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
	}
	return seen == N;
}
//모든 기지를 연결할 수 있는 최소의 d를 반환한다.
double optimize() {
	double lo = 0, hi = 1416.00;
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2;
		//mid가 가능하다면, 더 좋은 (작은) 답을 찾는다.
		if (decision(mid))
			hi = mid;
		//mid가 불가능하다면, 더 나쁜 (큰) 답을 찾는다.
		else
			lo = mid;
	}
	return hi;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N;
		coord = vector<pair<double, double>>(N);
		double x, y;
		for (int i = 0; i < N; i++) {
			cin >> x >> y;
			coord[i] = make_pair(y, x);
		}
		generateDistance();
		printf("%.2f\n", MSTsolve());
		coord.clear();
		edges.clear();
	}
}