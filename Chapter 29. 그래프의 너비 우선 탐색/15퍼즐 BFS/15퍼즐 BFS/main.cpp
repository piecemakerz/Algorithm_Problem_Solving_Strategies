#include <vector>
#include <map>
#include <queue>
using namespace std;

const int dy[4] = { 0,1,0,-1 };
const int dx[4] = { 1,0,-1,0 };

typedef unsigned long long uint64;

//64비트 정수를 4비트 정수 16개의 배열로 사용하기 위한 함수들

//idx번째 숫자를 val로 바꾼다. val은 [0, 15]의 정수
//바꿀 부분의 비트를 모두 0으로 바꾼 후, val에 해당하는 비트를 그 부분에 넣는다.
uint64 setArray(uint64 array, int idx, uint64 val) {
	return (array & ~(15ULL << (4 * idx))) | (val << (4 * idx));
}

//idx번째 숫자를 반환한다. 반환값은 [0, 15]의 정수
int getArray(uint64 array, int idx) {
	return (array >> (4 * idx)) & 15;
}

//게임판의 상태를 표현한다.
struct State {
	//빈 칸의 좌표
	int by, bx;
	//각 칸에 쓰인 숫자를 저장한다.
	uint64 tiles;
	//현재 estimate
	int estimate;

	State() {

	}

	//게임판의 상태로부터 생성
	State(const int board[4][4]) {
		tiles = 0;
		for(int y=3; y>=0; y--)
			for (int x = 3; x >= 0; x--) {
				tiles = (tiles * 16) + board[y][x];
				if (board[y][x] == 0) {
					by = y;
					bx = x;
				}
			}
		estimate = calcEstimate();
	}

	//빈칸의 좌표와 각 칸에 씌인 숫자로부터 생성
	State(int by, int bx, uint64 tiles, int estimate) :
		by(by), bx(bx), tiles(tiles), estimate(estimate) {}

	inline int manhattan(uint64 tiles, int y, int x) const {
		// (y,x)에 있는 수 num을 구한다.
		int num = getArray(tiles, y * 4 + x);
		if (num == 0) return 0;
		//num이 최종적으로 가야 할 위치를 계산한다.
		//ord = 4x4 격자에서 num이 최종적으로 위치해야 할 자리
		int ord = (num + 15) % 16;
		return abs(y - ord / 4) + abs(x - ord % 4);
	}
	//현재 상태에서 목표 상태까지 필요한 움직임의 하한을 계산한다.
	//각 숫자에 대해 현재 위치와 최종 위치 사이의 맨해튼 거리의 합을 계산한다.
	int calcEstimate() const {
		int ret = 0;
		for(int y=0; y<4; y++)
			for (int x = 0; x < 4; x++) {
				ret += manhattan(tiles, y, x);
			}
		return ret;
	}

	int getEstimate() const {
		return estimate;
	}

	//인접한 상태들의 목록을 반환한다.
	vector<State> getAdjacent() const {
		vector<State> ret;
		for (int k = 0; k < 4; k++)
			if (canMove(k))
				ret.push_back(move(k));
		return ret;
	}

	//빈칸을 direction 방향으로 움직일 수 있는지 여부를 반환
	bool canMove(int direction) const {
		int blankY = by + dy[direction];
		int blankX = bx + dx[direction];
		return 0 <= blankY && blankY < 4 && 0 <= blankX && blankX < 4;
	}

	//빈칸을 direction 방향으로 움직인 결과 상태를 반환한다.
	State move(int direction) const {
		//(y1, x1) = 기존 빈칸 위치
		int y1 = by, x1 = bx;
		//(y2, x2) = 새로운 빈칸 위치
		int y2 = y1 + dy[direction], x2 = x1 + dx[direction];
		int v1 = get(y1, x1), v2 = get(y2, x2);
		uint64 newtiles = setArray(tiles, y1 * 4 + x1, v2);
		newtiles = setArray(newtiles, y2 * 4 + x2, v1);
		return State(y2, x2, newtiles, estimate - manhattan(tiles, y2, x2) + manhattan(newtiles, y1, x1));
	}

	//(y,x) 좌표의 숫자를 반환한다.
	int get(int y, int x) const {
		return getArray(tiles, y * 4 + x);
	}
	//map에 State를 넣기 위한 비교 연산자
	bool operator < (const State& rhs) const {
		return tiles < rhs.tiles;
	}
	//종료 상태와 비교하기 위한 연산자
	bool operator == (const State& rhs) const {
		return tiles == rhs.tiles;
	}
};

//15-퍼즐을 해결하는 너비 우선 탐색 알고리즘

typedef map<State, int> StateMap;

const int goal[4][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0} };
//start에서 finish까지 가는 최단 경로의 길이를 반환한다.
int bfs(State start, State finish) {
	//예외: start == finish인 경우
	if (start == finish) return 0;
	//각 정점까지의 최단 경로의 길이를 저장한다.
	StateMap c;
	//앞으로 방문할 정점들을 저장한다.
	queue<State> q;
	q.push(start);
	c[start] = 0;
	//너비 우선 탐색
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		int cost = c[here];
		//인접한 정점들의 번호를 얻어낸다.
		vector<State> adjacent = here.getAdjacent();
		for (int i = 0; i < adjacent.size(); i++) {
			if (c.count(adjacent[i]) == 0) {
				//답을 찾았나?
				if (adjacent[i] == finish) return cost + 1;
				c[adjacent[i]] = cost + 1;
				q.push(adjacent[i]);
			}
		}
	}
	//답을 찾지 못한 경우
	return -1;
}

//15-퍼즐 문제를 해결하는 양방향 탐색 알고리즘

//x의 부호를 반환한다.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
//x의 절대값을 1 증가시킨다.
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
//start에서 finish까지 가는 최단 경로의 길이를 반환한다.
int bidirectional(State start, State finish) {
	//각 정점까지의 최단 경로의 길이를 저장한다.
	map<State, int> c;
	//앞으로 방문할 정점들을 저장한다.
	queue<State> q;
	//시작 상태와 목표 상태가 같은 경우는 예외로 처리해야 한다.
	if (start == finish) return 0;
	q.push(start); c[start] = 1;
	q.push(finish); c[finish] = -1;
	//너비 우선 탐색
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		//인접한 상태들을 검사한다.
		vector<State> adjacent = here.getAdjacent();
		for (int i = 0; i < adjacent.size(); i++) {
			map<State, int>::iterator it = c.find(adjacent[i]);
			//인접한 상태를 발견한 적 없다면 방문할 정점 목록에 저장한다.
			if (it == c.end()) {
				c[adjacent[i]] = incr(c[here]);
				q.push(adjacent[i]);
			}
			//가운데서 만난 경우
			else if (sgn(it->second) != sgn(c[here]))
				return abs(it->second) + abs(c[here]) - 1;
		}
	}
	//답을 찾지 못한 경우
	return -1;
}

//15-퍼즐 문제를 해결하는 점점 깊어지는 탐색 알고리즘

//지금까지 찾아낸 최단 경로의 길이
int best;
//깊이 우선 탐색
void dfs(State here, const State& finish, int steps) {
	//지금까지 구한 최적해보다 더 좋을 가능성이 없으면 버린다.
	if (steps + here.getEstimate() >= best) return;
	//목표 상태에 도달한 경우
	if (here == finish) { best = steps; return; }
	//인접 상태들을 깊이 우선 탐색으로
	vector<State> adjacent = here.getAdjacent();
	for (int i = 0; i < adjacent.size(); i++)
		dfs(adjacent[i], finish, steps + 1);
}
//점점 깊어지는 탐색
int ids(State start, State finish, int growthStep) {
	for (int limit = 4; ; limit += growthStep) {
		best = limit + 1;
		dfs(start, finish, 0);
		if (best <= limit) return best;
	}
	return -1;
}