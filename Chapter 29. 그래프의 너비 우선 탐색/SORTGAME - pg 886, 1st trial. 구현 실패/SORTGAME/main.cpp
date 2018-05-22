#include <vector>
#include <queue>
#include <map>
using namespace std;

//Sorting Game 문제를 해결하는 너비 우선 탐색 알고리즘

//perm을 정렬하기 위해 필요한 최소 뒤집기 연산의 수를 계산한다.
int bfs(const vector<int>& perm) {
	int n = perm.size();
	//목표 정점을 미리 계산한다.
	vector<int> sorted = perm;
	sort(sorted.begin(), sorted.end());
	//방문 목록(큐)와 시작점부터 각 정점까지의 거리
	queue<vector<int>> q;
	map<vector<int>, int> distance;
	//시작점을 큐에 넣는다.
	distance[perm] = 0;
	q.push(perm);
	while (!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		//목표 정점을 발견했으면 곧장 종료한다.
		if (here == sorted) return distance[here];
		int cost = distance[here];
		//가능한 모든 부분 구간을 뒤집어 본다.
		for (int i = 0; i < n; i++)
			for (int j = i + 2; j <= n; j++) {
				reverse(here.begin() + i, here.begin() + j);
				//부분 구간을 뒤집은 배열이 그래프에서 새로운 정점이 된다면 이를 큐에 넣는다.
				if (distance.count(here) == 0) {
					distance[here] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
	}
	return -1;
}

//Sorting Game 문제를 빠르게 해결하는 너비 우선 탐색의 구현

//toSort[] = 해당 순열을 만드는데 필요한 뒤집기 연선의 수
map<vector<int>, int> toSort;
//[0, ..., n-1]의 모든 순열에 대해 toSort[]를 계산해 저장한다.
void precalc(int n) {
	vector<int> perm(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	queue<vector<int>> q;
	q.push(perm);
	toSort[perm] = 0;
	while (!q.empty()) {
		vector<int> here = q.front();
		q.pop();
		int cost = toSort[here];
		for (int i = 0; i < n; i++) {
			for (int j = i + 2; j <= n; j++) {
				reverse(here.begin() + i, here.begin() + j);
				if (toSort.count(here) == 0) {
					toSort[here] = cost + 1;
					q.push(here);
				}
				reverse(here.begin() + i, here.begin() + j);
			}
		}
	}
}
int solve(const vector<int>& perm) {
	//perm을 [0, ..., n-1]의 순열로 변환한다.
	int n = perm.size();
	vector<int> fixed(n);
	for (int i = 0; i < n; i++) {
		int smaller = 0;
		for (int j = 0; j < n; j++)
			if (perm[j] < perm[i])
				smaller++;
		fixed[i] = smaller;
	}
	return toSort[fixed];
}