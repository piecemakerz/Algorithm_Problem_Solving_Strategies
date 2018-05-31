#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX_V = 100;
const int INF = 987654321;

//벨만 포드 알고리즘을 이용해 시간여행 문제 해결하기
int V;
vector<pair<int, int>> adj[MAX_V];
//reachable[u][v] = u에서 v로 가는 경로가 있는가?
bool reachable[MAX_V][MAX_V];
//src에서 target으로 가는 최단 거리를 계산한다.
//가중치가 음의 무한대인 경로가 있으면 -INF를 반환한다.
int bellman2(int src, int target) {
	//시작점을 제외한 모든 정점까지의 최단 거리 상한을 INF로 둔다.
	vector<int> upper(V, INF);
	upper[src] = 0;
	//V-1번 순회한다.
	for(int iter=0; iter<V-1; iter++)
		for(int here = 0; here < V; here++)
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				//(here, there) 간선을 따라 완화를 시도한다.
				upper[there] = min(upper[there], upper[here] + cost);
			}
	//음수 사이클의 존재 여부를 확인하자.
	for (int here = 0; here < V; here++)
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