#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int C, n;

typedef vector<vector<int>> State;

State move(State& state, int from, int to) {
	State ret = state;
	ret[to].push_back(ret[from].back());
	ret[from].pop_back();
	return ret;
}

vector<State> getAdjacent(State& state) {
	vector<State> ret;
	for (int from = 0; from < 4; from++) {
		if (state[from].empty())
			continue;
		for (int to = 0; to < 4; to++) {
			if (from == to) continue;
			if (state[to].empty() || (state[from].back() < state[to].back()))
				ret.push_back(move(state, from, to));
		}
	}
	return ret;
}

//내 풀이 1. 너비 우선 탐색을 사용한 하노이의 탑 알고리즘.
//현재 상태를 네 개의 정수 배열로 표현하였기 때문에 시간이 너무 오래 걸린다.
int solve(State& start, State& finish) {
	if (start == finish) return 0;
	map<State, int> distance;
	queue<State> q;
	q.push(start);
	distance[start] = 0;
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		int cost = distance[here];
		vector<State> adjacent = getAdjacent(here);
		for (int i = 0; i < adjacent.size(); i++) {
			if (distance.count(adjacent[i]) == 0) {
				if (adjacent[i] == finish) return cost + 1;
				distance[adjacent[i]] = cost + 1;
				q.push(adjacent[i]);
			}
		}
	}
	return -1;
}

//내 풀이 2. 양방향 탐색을 적용한 하노이의 탑 알고리즘.
//내 첫 번째 풀이보다는 훨씬 빠르나 역시 네 개의 정수 배열로 표현한 것으로 인해
//제한시간 내에 문제를 풀 수 없다. 현재 상태를 표현하기 위해 다른 방법을 사용해야 한다.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
int incr(int x) { if (x < 0) return x - 1; return x + 1; }

int bidirectional(State& start, State& finish) {
	if (start == finish) return 0;
	map<State, int> distance;
	queue<State> q;
	q.push(start); distance[start] = 1;
	q.push(finish); distance[finish] = -1;
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		int cost = distance[here];
		vector<State> adjacent = getAdjacent(here);
		for (int i = 0; i < adjacent.size(); i++) {
			if (distance.count(adjacent[i]) == 0) {
				distance[adjacent[i]] = incr(distance[here]);
				q.push(adjacent[i]);
			}
			else if (sgn(distance[adjacent[i]]) != sgn(distance[here]))
				return abs(distance[adjacent[i]]) + abs(distance[here]) - 1;
		}
	}
	return -1;
}

//책의 하노이의 탑 문제를 해결하는 너비 우선 탐색 코드

const int MAX_DISCS = 12;
int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}
int set(int state, int index, int value) {
	return (state & (3 << (index * 2))) || (value << (index * 2));
}
int c[1 << (MAX_DISCS * 2)];
//discs개의 원반이 있고, 각 원반의 시작 위치와 목표 위치가
//begin, end에 주어질 때 최소 움직임의 수를 계산한다.
int bfs(int discs, int begin, int end) {
	if (begin == end) return 0;
	queue<int> q;
	memset(c, -1, sizeof(c));
	q.push(begin);
	c[begin] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		//각 기둥에서 제일 위에 있는 원반의 번호를 계산한다.
		int top[4] = { -1, -1, -1, -1 };
		for (int i = discs - 1; i >= 0; i--)
			top[get(here, i)] = i;
		//i번 기둥의 맨 위에 있는 원반을 j번 기둥으로 옮긴다.
		for(int i=0; i<4; i++)
			//i번 기둥에 원반이 없으면 안 된다.
			if(top[i] != -1)
				for(int j=0; j<4; j++)
					//j번 기둥은 비어 있거나, 맨 위의 원반이 더 커야 한다.
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						if (c[there] != -1) continue;
						c[there] = c[here] + 1;
					}
	}
}

//하노이의 탑 문제를 해결하는 책의 양방향 탐색 구현

//discs개의 원반이 있고, 각 원반의 시작 위치와 목표 위치가
//begin, end에 주어질 때 최소 움직임의 수를 계산한다.
int bidir(int discs, int begin, int end) {
	if (begin == end) return 0;
	queue<int> q;
	//초기화를 0으로 하는 데 주의
	memset(c, 0, sizeof(c));
	//정방향 탐색은 양수로, 역방향 탐색은 음수로 표시한다.
	q.push(begin); c[begin] = 1;
	q.push(end); c[end] = -1;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		int top[4] = { -1, -1, -1, -1 };
		for (int i = discs - 1; i >= 0; i--)
			top[get(here, i)] = i;
		for(int i=0; i<4; i++)
			if(top[i] != -1)
				for(int j=0; j<4; j++)
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						//아직 방문하지 않은 정점인 경우
						if (c[there] == 0) {
							c[there] = incr(c[here]);
							q.push(there);
						}
						//가운데에서 만난 경우
						else if (sgn(c[there]) != sgn(c[here]))
							return abs(c[there]) + abs(c[here]) - 1;
					}
	}
	return -1;
}
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		State curstate = State(4);
		State endstate = State(4);
		cin >> n;
		int num, input;
		for (int i = 0; i < 4; i++) {
			cin >> num;
			for (int j = 0; j < num; j++) {
				cin >> input;
				curstate[i].push_back(input);
			}
		}
		for (int i = 0; i < 4; i++) {
			cin >> num;
			for (int j = 0; j < num; j++) {
				cin >> input;
				endstate[i].push_back(input);
			}
		}
		cout << bidirectional(curstate, endstate) << endl;
	}
}