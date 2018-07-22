#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const double INF = 1e200;
const int MAX = 30;
int n; // 도시의 수
double dist[MAX][MAX]; // 두 도시간의 거리를 저장하는 배열
//지금까지 찾은 최적해. 전역 변수에 지금까지 찾은 최적해의 길이를
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
double solve() {
	//best를 매우 큰 값으로 초기화
	best = INF;
	vector<bool> visited(n, false);
	vector<int> path(1, 0);
	visited[0] = true;
	search(path, visited, 0);
	return best;
}