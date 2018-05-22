#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <iostream>
using namespace std;

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