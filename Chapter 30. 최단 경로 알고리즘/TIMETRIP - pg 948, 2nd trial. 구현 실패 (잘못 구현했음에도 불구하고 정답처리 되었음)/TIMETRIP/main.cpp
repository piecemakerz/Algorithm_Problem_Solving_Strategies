#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int C, G, W;

const int INF = 987654321;
//그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담는다.
vector<vector<pair<int, int>>> adj;

bool upperInf, lowerInf;

//시간여행 문제를 해결하는 내 풀이.
//분명 모든 정점의 쌍에 대해 한 정점에서 다른 정점으로
//가는 경로의 존재 여부를 확인하지 않았음에도 제출시 정답이 나오는
//것으로 보아, 우연히 정답 처리가 된 것 같다. 즉, 이 알고리즘은 틀렸다.
void bellmanFord(vector<int>& upper, vector<int>& lower, int src) {
	upper[src] = 0, lower[src] = 0;
	bool upperUpdated = false, lowerUpdated = false;
	//G번 순회한다.
	for (int iter = 0; iter < G; iter++) {
		upperUpdated = false, lowerUpdated = false;
		for(int here = 0; here < G; here++)
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[there] > upper[here] + cost) {
					upper[there] = upper[here] + cost;
					upperUpdated = true;
				}
				if (lower[there] < lower[here] + cost) {
					lower[there] = lower[here] + cost;
					lowerUpdated = true;
				}
			}
		if (!upperUpdated && !lowerUpdated) break;
	}
	if (upperUpdated) upperInf = true;
	if (lowerUpdated) lowerInf = true;
}

//시간여행 문제를 해결하는 책의 벨만 포드 알고리즘
int V;
const int MAX_V = 100;
vector<pair<int, int>> adj[MAX_V];
//reachable[u][v] = u에서 v로 가는 경로가 있는가?
bool reachable[MAX_V][MAX_V];
//src에서 target으로 가는 최단 거리를 계산한다.
//가중치가 음의 무한대인 경로가 있으면 -INF를 반환한다.
//가중치의 부호를 모두 바꾼 다음 최단 경로를 구하면
//시작점부터 종착점까지 가는 최장 경로를 찾을 수 있다.
int bellman2(int src, int target) {
	//시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다.
	vector<int> upper(V, INF);
	upper[src] = 0;
	//V-1번 순회한다.
	for(int iter = 0; iter < V-1; iter++)
		for(int here = 0; here < V; here++)
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				//(here, there) 간선을 따라 완화를 시도한다.
				upper[there] = min(upper[there], upper[here] + cost);
			}
	//음수 사이클의 존재 여부를 확인하자.
	for(int here = 0; here < V; here++)
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;
			//완화가 성공한다면 here는 음수 사이클에 들어 있다.
			if (upper[here] + cost < upper[there])
				//이 음수 사이클을 포함하는 경로가 있는가?
				if (reachable[src][here] && reachable[here][target])
					return -INF;
		}
	return upper[target];
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> G >> W;
		adj = vector<vector<pair<int, int>>>(G);
		upperInf = false, lowerInf = false;
		int a, b, d;

		for (int i = 0; i < W; i++) {
			cin >> a >> b >> d;
			adj[a].push_back(make_pair(b, d));
		}
		vector<int> upper(G, INF), lower(G, -INF);
		bellmanFord(upper, lower, 0);
		
		if (upper[1] > INF - 1000000)
			cout << "UNREACHABLE" << endl;
		else {
			if (upperInf)
				cout << "INFINITY ";
			else
				cout << upper[1] << ' ';

			if (lowerInf)
				cout << "INFINITY" << endl;
			else
				cout << lower[1] << endl;
		}
		adj.clear();
	}
}