#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX 10

using namespace std;

const int INF = 987654321;
int n; // 도시의 수
double dist[MAX][MAX];	// 두 도시 간의 거리를 저장하는 배열
double cache[MAX][1 << MAX];

//이전에 설계한 n!개의 경로를 모두 생성하는 완전 탐색 알고리즘.
//n!은 굉장히 빨리 증가하는 함수이기 때문에 n이 15정도만 되더라도
//계산이 거의 불가능하다.
//path: 지금까지 만든 경로
//visited: 각 도시의 방문 여부
//currentLenght: 지금까지 만든 경로의 길이
//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
	if (path.size() == n)
		return currentLength + dist[path[0]][path.back()];
	double ret = INFINITY;
	for (int next = 0; next < n; next++) {
		if (visited[next]) continue;
		int here = path.back();
		path.push_back(next);
		visited[next] = true;

		double cand = shortestPath(path, visited, currentLength + dist[here][next]);

		ret = min(ret, cand);
		visited[next] = false;
		path.pop_back();
	}
	return ret;
}
//메모이제이션과 비트마스크 기법을 적용한 새로운 TSP 알고리즘.
//here: 현재 위치
//visited: 각 도시의 방문 여부
//here에서 시작해 남은 도시들을 방문할 수 있는 최단 경로의 길이를 반환한다.
//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환한다.
//항상 0번 도시에서 시작한다고 가정한다.
double shortestPath2(int here, int visited) {
	// 기저 사례: 모든 도시를 다 방문했을 때는 0번 도시로 돌아가고 종료한다.
	if (visited == (1 << n) - 1) return dist[here][0];
	double& ret = cache[here][visited];
	if (ret >= 0) return ret;
	ret = INF; // 매우 큰 값으로 초기화
	// 다음 방문할 도시를 전부 시도해 본다.
	for (int next = 0; next < n; next++) {
		//이미 방문한 도시인 경우
		if (visited & (1 << next)) continue;
		double cand = dist[here][next] + shortestPath2(next, visited + (1 << next));
		ret = min(ret, cand);
	}
	return ret;
}
