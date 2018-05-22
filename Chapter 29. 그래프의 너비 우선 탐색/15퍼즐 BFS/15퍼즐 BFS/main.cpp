#include <vector>
#include <map>
#include <queue>
using namespace std;

const int dy[4] = { 0,1,0,-1 };
const int dx[4] = { 1,0,-1,0 };

typedef unsigned long long uint64;

//64��Ʈ ������ 4��Ʈ ���� 16���� �迭�� ����ϱ� ���� �Լ���

//idx��° ���ڸ� val�� �ٲ۴�. val�� [0, 15]�� ����
//�ٲ� �κ��� ��Ʈ�� ��� 0���� �ٲ� ��, val�� �ش��ϴ� ��Ʈ�� �� �κп� �ִ´�.
uint64 setArray(uint64 array, int idx, uint64 val) {
	return (array & ~(15ULL << (4 * idx))) | (val << (4 * idx));
}

//idx��° ���ڸ� ��ȯ�Ѵ�. ��ȯ���� [0, 15]�� ����
int getArray(uint64 array, int idx) {
	return (array >> (4 * idx)) & 15;
}

//�������� ���¸� ǥ���Ѵ�.
struct State {
	//�� ĭ�� ��ǥ
	int by, bx;
	//�� ĭ�� ���� ���ڸ� �����Ѵ�.
	uint64 tiles;
	//���� estimate
	int estimate;

	State() {

	}

	//�������� ���·κ��� ����
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

	//��ĭ�� ��ǥ�� �� ĭ�� ���� ���ڷκ��� ����
	State(int by, int bx, uint64 tiles, int estimate) :
		by(by), bx(bx), tiles(tiles), estimate(estimate) {}

	inline int manhattan(uint64 tiles, int y, int x) const {
		// (y,x)�� �ִ� �� num�� ���Ѵ�.
		int num = getArray(tiles, y * 4 + x);
		if (num == 0) return 0;
		//num�� ���������� ���� �� ��ġ�� ����Ѵ�.
		//ord = 4x4 ���ڿ��� num�� ���������� ��ġ�ؾ� �� �ڸ�
		int ord = (num + 15) % 16;
		return abs(y - ord / 4) + abs(x - ord % 4);
	}
	//���� ���¿��� ��ǥ ���±��� �ʿ��� �������� ������ ����Ѵ�.
	//�� ���ڿ� ���� ���� ��ġ�� ���� ��ġ ������ ����ư �Ÿ��� ���� ����Ѵ�.
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

	//������ ���µ��� ����� ��ȯ�Ѵ�.
	vector<State> getAdjacent() const {
		vector<State> ret;
		for (int k = 0; k < 4; k++)
			if (canMove(k))
				ret.push_back(move(k));
		return ret;
	}

	//��ĭ�� direction �������� ������ �� �ִ��� ���θ� ��ȯ
	bool canMove(int direction) const {
		int blankY = by + dy[direction];
		int blankX = bx + dx[direction];
		return 0 <= blankY && blankY < 4 && 0 <= blankX && blankX < 4;
	}

	//��ĭ�� direction �������� ������ ��� ���¸� ��ȯ�Ѵ�.
	State move(int direction) const {
		//(y1, x1) = ���� ��ĭ ��ġ
		int y1 = by, x1 = bx;
		//(y2, x2) = ���ο� ��ĭ ��ġ
		int y2 = y1 + dy[direction], x2 = x1 + dx[direction];
		int v1 = get(y1, x1), v2 = get(y2, x2);
		uint64 newtiles = setArray(tiles, y1 * 4 + x1, v2);
		newtiles = setArray(newtiles, y2 * 4 + x2, v1);
		return State(y2, x2, newtiles, estimate - manhattan(tiles, y2, x2) + manhattan(newtiles, y1, x1));
	}

	//(y,x) ��ǥ�� ���ڸ� ��ȯ�Ѵ�.
	int get(int y, int x) const {
		return getArray(tiles, y * 4 + x);
	}
	//map�� State�� �ֱ� ���� �� ������
	bool operator < (const State& rhs) const {
		return tiles < rhs.tiles;
	}
	//���� ���¿� ���ϱ� ���� ������
	bool operator == (const State& rhs) const {
		return tiles == rhs.tiles;
	}
};

//15-������ �ذ��ϴ� �ʺ� �켱 Ž�� �˰���

typedef map<State, int> StateMap;

const int goal[4][4] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,0} };
//start���� finish���� ���� �ִ� ����� ���̸� ��ȯ�Ѵ�.
int bfs(State start, State finish) {
	//����: start == finish�� ���
	if (start == finish) return 0;
	//�� ���������� �ִ� ����� ���̸� �����Ѵ�.
	StateMap c;
	//������ �湮�� �������� �����Ѵ�.
	queue<State> q;
	q.push(start);
	c[start] = 0;
	//�ʺ� �켱 Ž��
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		int cost = c[here];
		//������ �������� ��ȣ�� ����.
		vector<State> adjacent = here.getAdjacent();
		for (int i = 0; i < adjacent.size(); i++) {
			if (c.count(adjacent[i]) == 0) {
				//���� ã�ҳ�?
				if (adjacent[i] == finish) return cost + 1;
				c[adjacent[i]] = cost + 1;
				q.push(adjacent[i]);
			}
		}
	}
	//���� ã�� ���� ���
	return -1;
}

//15-���� ������ �ذ��ϴ� ����� Ž�� �˰���

//x�� ��ȣ�� ��ȯ�Ѵ�.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
//x�� ���밪�� 1 ������Ų��.
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
//start���� finish���� ���� �ִ� ����� ���̸� ��ȯ�Ѵ�.
int bidirectional(State start, State finish) {
	//�� ���������� �ִ� ����� ���̸� �����Ѵ�.
	map<State, int> c;
	//������ �湮�� �������� �����Ѵ�.
	queue<State> q;
	//���� ���¿� ��ǥ ���°� ���� ���� ���ܷ� ó���ؾ� �Ѵ�.
	if (start == finish) return 0;
	q.push(start); c[start] = 1;
	q.push(finish); c[finish] = -1;
	//�ʺ� �켱 Ž��
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		//������ ���µ��� �˻��Ѵ�.
		vector<State> adjacent = here.getAdjacent();
		for (int i = 0; i < adjacent.size(); i++) {
			map<State, int>::iterator it = c.find(adjacent[i]);
			//������ ���¸� �߰��� �� ���ٸ� �湮�� ���� ��Ͽ� �����Ѵ�.
			if (it == c.end()) {
				c[adjacent[i]] = incr(c[here]);
				q.push(adjacent[i]);
			}
			//����� ���� ���
			else if (sgn(it->second) != sgn(c[here]))
				return abs(it->second) + abs(c[here]) - 1;
		}
	}
	//���� ã�� ���� ���
	return -1;
}

//15-���� ������ �ذ��ϴ� ���� ������� Ž�� �˰���

//���ݱ��� ã�Ƴ� �ִ� ����� ����
int best;
//���� �켱 Ž��
void dfs(State here, const State& finish, int steps) {
	//���ݱ��� ���� �����غ��� �� ���� ���ɼ��� ������ ������.
	if (steps + here.getEstimate() >= best) return;
	//��ǥ ���¿� ������ ���
	if (here == finish) { best = steps; return; }
	//���� ���µ��� ���� �켱 Ž������
	vector<State> adjacent = here.getAdjacent();
	for (int i = 0; i < adjacent.size(); i++)
		dfs(adjacent[i], finish, steps + 1);
}
//���� ������� Ž��
int ids(State start, State finish, int growthStep) {
	for (int limit = 4; ; limit += growthStep) {
		best = limit + 1;
		dfs(start, finish, 0);
		if (best <= limit) return best;
	}
	return -1;
}