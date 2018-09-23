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

//�� Ǯ�� 1. �ʺ� �켱 Ž���� ����� �ϳ����� ž �˰���.
//���� ���¸� �� ���� ���� �迭�� ǥ���Ͽ��� ������ �ð��� �ʹ� ���� �ɸ���.
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

//�� Ǯ�� 2. ����� Ž���� ������ �ϳ����� ž �˰���.
//�� ù ��° Ǯ�̺��ٴ� �ξ� ������ ���� �� ���� ���� �迭�� ǥ���� ������ ����
//���ѽð� ���� ������ Ǯ �� ����. ���� ���¸� ǥ���ϱ� ���� �ٸ� ����� ����ؾ� �Ѵ�.
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

//å�� �ϳ����� ž ������ �ذ��ϴ� �ʺ� �켱 Ž�� �ڵ�

const int MAX_DISCS = 12;
int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}
int set(int state, int index, int value) {
	return (state & (3 << (index * 2))) || (value << (index * 2));
}
int c[1 << (MAX_DISCS * 2)];
//discs���� ������ �ְ�, �� ������ ���� ��ġ�� ��ǥ ��ġ��
//begin, end�� �־��� �� �ּ� �������� ���� ����Ѵ�.
int bfs(int discs, int begin, int end) {
	if (begin == end) return 0;
	queue<int> q;
	memset(c, -1, sizeof(c));
	q.push(begin);
	c[begin] = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		//�� ��տ��� ���� ���� �ִ� ������ ��ȣ�� ����Ѵ�.
		int top[4] = { -1, -1, -1, -1 };
		for (int i = discs - 1; i >= 0; i--)
			top[get(here, i)] = i;
		//i�� ����� �� ���� �ִ� ������ j�� ������� �ű��.
		for(int i=0; i<4; i++)
			//i�� ��տ� ������ ������ �� �ȴ�.
			if(top[i] != -1)
				for(int j=0; j<4; j++)
					//j�� ����� ��� �ְų�, �� ���� ������ �� Ŀ�� �Ѵ�.
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						if (c[there] != -1) continue;
						c[there] = c[here] + 1;
					}
	}
}

//�ϳ����� ž ������ �ذ��ϴ� å�� ����� Ž�� ����

//discs���� ������ �ְ�, �� ������ ���� ��ġ�� ��ǥ ��ġ��
//begin, end�� �־��� �� �ּ� �������� ���� ����Ѵ�.
int bidir(int discs, int begin, int end) {
	if (begin == end) return 0;
	queue<int> q;
	//�ʱ�ȭ�� 0���� �ϴ� �� ����
	memset(c, 0, sizeof(c));
	//������ Ž���� �����, ������ Ž���� ������ ǥ���Ѵ�.
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
						//���� �湮���� ���� ������ ���
						if (c[there] == 0) {
							c[there] = incr(c[here]);
							q.push(there);
						}
						//������� ���� ���
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