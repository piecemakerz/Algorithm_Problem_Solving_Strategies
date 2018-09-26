#include <vector>
#include <queue>
using namespace std;

const int INF = 987654321;
const int MAX_V = 100;
int V;
//capacity[u][v] = u에서 v로 보낼 수 있는 용량
//flow[u][v] = u에서 v로 흘러가는 유량 (반대 방향인 경우 음수)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
//flow[][]를 계산하고 총 유량을 반환한다.
int networkFlow(int source, int sink) {
	//flow를 0으로 초기화한다.
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		//너비 우선 탐색으로 증가 경로를 찾는다.
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int there = 0; there < V; there++) {
				//잔여 용량이 남아 있는 간선을 따라 탐색한다.
				if (capacity[here][there] - flow[here][there] > 0 &&
					parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		//증가 경로가 없으면 종료한다.
		if (parent[sink] == -1) break;
		//증가 경로를 통해 유량을 얼마나 보낼지 결정한다.
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		//증가 경로를 통해 유량을 보낸다.
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

//네트워크 유량을 통해 승부 조작 문제를 해결하는 함수의 구현
int n, m;
int wins[20], match[200][2];
//0번 선수가 총 totalWins승으로 우승할 수 있는지 여부를 확인한다.
bool canWinWith(int totalWins) {
	//이미 totalWins승 이상 한 선수가 있으면 안된다.
	if (*max_element(wins + 1, wins + n) >= totalWins)
		return false;
	//0번은 소스, 1번은 싱크
	V = 2 + m + n;
	memset(capacity, 0, sizeof(capacity));
	for (int i = 0; i < m; i++) {
		//소스에서 각 경기로 가는 간선
		capacity[0][2 + i] = 1;
		//각 경기에서 두 선수로 가는 간선
		for (int j = 0; j < 2; j++)
			capacity[2 + i][2 + m + match[i][j]] = 1;
	}
	//각 선수에서 싱크로, 가능한 최대 승수를 용량으로 하는 간선을 추가
	for (int i = 0; i < n; i++) {
		int maxWin = (i == 0 ? totalWins : totalWins - 1);
		capacity[2 + m + i][1] = maxWin - wins[i];
	}
	//이때 모든 경기에 승자를 지정할 수 있는가?
	return networkFlow(0, 1) == m;
}