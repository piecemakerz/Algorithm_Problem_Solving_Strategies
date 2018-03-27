#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
//크루스칼 알고리즘은 가중치(거리)가 가장 짧은 선분들을 우선적으로 고르기 때문에 이 문제에 적용할 수 있을 것이다.
//아직 그래프를 배우지 않은 상태에서 구현시도를 했으니, 나중에 크루스칼 알고리즘으로 구현해보자.

int C, N;
// 두 기지 사이의 거리를 미리 계산해둔다.
double dist[100][100];
// 거리가 d 이하인 기지들만을 연결했을 때 모든 기지가 연결되는지 여부를 반환한다.
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
		for (int there = 0; there < N; there++) {
			if (!visited[there] && dist[here][there] <= d) { // 아직 기지를 방문하지 않았고 거리가 d이하일 때
				visited[there] = true;
				q.push(there);
			}
		}
		return seen == N;
	}
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