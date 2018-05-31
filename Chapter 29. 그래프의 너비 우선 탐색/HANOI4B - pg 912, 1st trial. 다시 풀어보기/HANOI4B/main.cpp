#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <cstring>
#include <iostream>
using namespace std;

//내 풀이
//algospot에 해당 문제가 존재하지 않아 제대로 작동하는지 확인할 수 없다.
/*
typedef unsigned long long uint64;

unsigned short changeDisk(int disk) {
	unsigned short changedDisk = 1;
	for (int i = 0; i < disk; i++)
		changedDisk = changedDisk << 1;
	return changedDisk;
}
//게임판의 상태를 표현한다.
struct State {
	//각 기둥의 상태를 저장한다.
	uint64 pillarState;

	State() : pillarState(0) {}

	State(uint64 newPillar) : pillarState(newPillar) {}

	//pillar번째 기둥에 disk번 원반을 추가한다. 
	void addNewDisk(int pillar, unsigned short disk) {
		pillarState |= ((uint64)disk << (16 * pillar));
	}

	vector<State> getAdjacent() {
		vector<State> ret;
		//i번 기둥의 맨 윗 원반을 j번 기둥으로 옮길 수 있다면
		//인접한 상태들의 목록에 저장한다.
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (i == j) continue;
				//옮길 원반이 있는 기둥
				unsigned short origPillar = (pillarState >> (16 * i));
				//원반을 추가할 기둥
				unsigned short movePillar = (pillarState >> (16 * j));
				//origPillar가 비어있다면 통과
				//movePillar가 비어있으면 무조건 원반을 옮길 수 있으며,
				//origPillar의 맨 윗 원반이 movePillar의 맨 윗 원반보다 작다면
				//원반을 옮길 수 있다.
				if (origPillar && (!movePillar || 
					((origPillar & (~origPillar+1)) < (movePillar & (~movePillar+1))))) {
					unsigned short pillarToMove = (origPillar & (~origPillar+1));
					uint64 newPillar = pillarState;
					newPillar |= ((uint64)pillarToMove << (16 * j));
					newPillar &= ~((uint64)pillarToMove << (16 * i));
					ret.push_back(State(newPillar));
				}
			}
		return ret;
	}
	//종료 상태와 비교하기 위한 연산자
	bool operator == (const State& rhs) const {
		return pillarState == rhs.pillarState;
	}
};

//x의 부호를 반환한다.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
//x의 절대값을 1 증가시킨다.
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
//start에서 finish까지 가는 최단 경로의 길이를 반환한다.
int bidirectional(State start, State finish) {
	//각 정점까지의 최단 경로의 길이를 저장한다.
	map<uint64, int> c;
	//앞으로 방문할 정점들을 저장한다.
	queue<State> q;
	//시작 상태와 목표 상태가 같은 경우는 예외로 처리해야 한다.
	if (start == finish) return 0;
	q.push(start); c[start.pillarState] = 1;
	q.push(finish); c[finish.pillarState] = -1;
	//너비 우선 검색
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		//인접한 상태들을 검사한다.
		vector<State> adjacent = here.getAdjacent();
		for (int i = 0; i < adjacent.size(); i++) {
			map<uint64, int>::iterator it = c.find(adjacent[i].pillarState);
			//인접한 상태를 발견한 적이 없다면 방문할 정점 목록에 저장한다.
			if (it == c.end()) {
				c[adjacent[i].pillarState] = incr(c[here.pillarState]);
				q.push(adjacent[i]);
			}
			//가운데서 만난 경우
			else if (sgn(it->second) != sgn(c[here.pillarState]))
				return abs(it->second) + abs(c[here.pillarState]) - 1;
		}
	}
	return -1;
}

int main(void) {
	int C;
	cin >> C;
	for (int test = 0; test < C; test++) {
		State start, finish;
		int n, diskNum, disk;
		//원반의 갯수
		cin >> n;

		for(int i=0; i<4; i++){
			cin >> diskNum;
			for (int j = 0; j < diskNum; j++) {
				cin >> disk;
				start.addNewDisk(i, changeDisk(disk-1));
			}
		}
		
		for (int i = 0; i < 4; i++) {
			cin >> diskNum;
			for (int j = 0; j < diskNum; j++) {
				cin >> disk;
				finish.addNewDisk(i, changeDisk(disk-1));
			}
		}
		cout << bidirectional(start, finish) << endl;
	}
	return 0;
}
*/

//책의 답
//하노이의 탑 문제를 해결하는 너비 우선 탐색 코드
const int MAX_DISCS = 12;
//index번 원반이 몇 번 기둥에 꽂혀있는지 반환한다.
int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}
//state를 index번 원반이 value기둥에 꽂혀있는 상태로 변경한다.
int set(int state, int index, int value) {
	return (state & ~(3 << (index * 2))) | (value << (index * 2));
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
		//i번 기둥의 맨 위에 있는 선반을 j번 기둥으로 옮긴다.
		for(int i=0; i<4; i++)
			//i번 기둥에 원반이 없으면 안 된다.
			if(top[i] != -1)
				for(int j=0; j<4; j++)
					//j번 기둥은 비어있거나, 맨 위의 원반이 더 커야 한다.
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						//there의 상태를 이미 발견했다면 건너뛴다.
						if (c[there] != -1) continue;
						c[there] = c[here] + 1;
						if (there == end) return c[there];
						q.push(there);
					}
	}
	return -1;
}

//하노이의 탑 문제를 해결하는 양방향 탐색의 구현

//x의 부호를 반환한다.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
//x의 절대값을 1 증가시킨다.
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
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
						//가운데서 만난 경우
						else if (sgn(c[there]) != sgn(c[here]))
							return abs(c[there]) + abs(c[here]) - 1;
					}
	}
	return -1;
}