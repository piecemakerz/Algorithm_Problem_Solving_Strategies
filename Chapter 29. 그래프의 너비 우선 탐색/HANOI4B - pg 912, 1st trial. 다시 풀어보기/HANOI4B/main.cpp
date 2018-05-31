#include <vector>
#include <map>
#include <queue>
#include <functional>
#include <cstring>
#include <iostream>
using namespace std;

//�� Ǯ��
//algospot�� �ش� ������ �������� �ʾ� ����� �۵��ϴ��� Ȯ���� �� ����.
/*
typedef unsigned long long uint64;

unsigned short changeDisk(int disk) {
	unsigned short changedDisk = 1;
	for (int i = 0; i < disk; i++)
		changedDisk = changedDisk << 1;
	return changedDisk;
}
//�������� ���¸� ǥ���Ѵ�.
struct State {
	//�� ����� ���¸� �����Ѵ�.
	uint64 pillarState;

	State() : pillarState(0) {}

	State(uint64 newPillar) : pillarState(newPillar) {}

	//pillar��° ��տ� disk�� ������ �߰��Ѵ�. 
	void addNewDisk(int pillar, unsigned short disk) {
		pillarState |= ((uint64)disk << (16 * pillar));
	}

	vector<State> getAdjacent() {
		vector<State> ret;
		//i�� ����� �� �� ������ j�� ������� �ű� �� �ִٸ�
		//������ ���µ��� ��Ͽ� �����Ѵ�.
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				if (i == j) continue;
				//�ű� ������ �ִ� ���
				unsigned short origPillar = (pillarState >> (16 * i));
				//������ �߰��� ���
				unsigned short movePillar = (pillarState >> (16 * j));
				//origPillar�� ����ִٸ� ���
				//movePillar�� ��������� ������ ������ �ű� �� ������,
				//origPillar�� �� �� ������ movePillar�� �� �� ���ݺ��� �۴ٸ�
				//������ �ű� �� �ִ�.
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
	//���� ���¿� ���ϱ� ���� ������
	bool operator == (const State& rhs) const {
		return pillarState == rhs.pillarState;
	}
};

//x�� ��ȣ�� ��ȯ�Ѵ�.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
//x�� ���밪�� 1 ������Ų��.
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
//start���� finish���� ���� �ִ� ����� ���̸� ��ȯ�Ѵ�.
int bidirectional(State start, State finish) {
	//�� ���������� �ִ� ����� ���̸� �����Ѵ�.
	map<uint64, int> c;
	//������ �湮�� �������� �����Ѵ�.
	queue<State> q;
	//���� ���¿� ��ǥ ���°� ���� ���� ���ܷ� ó���ؾ� �Ѵ�.
	if (start == finish) return 0;
	q.push(start); c[start.pillarState] = 1;
	q.push(finish); c[finish.pillarState] = -1;
	//�ʺ� �켱 �˻�
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		//������ ���µ��� �˻��Ѵ�.
		vector<State> adjacent = here.getAdjacent();
		for (int i = 0; i < adjacent.size(); i++) {
			map<uint64, int>::iterator it = c.find(adjacent[i].pillarState);
			//������ ���¸� �߰��� ���� ���ٸ� �湮�� ���� ��Ͽ� �����Ѵ�.
			if (it == c.end()) {
				c[adjacent[i].pillarState] = incr(c[here.pillarState]);
				q.push(adjacent[i]);
			}
			//����� ���� ���
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
		//������ ����
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

//å�� ��
//�ϳ����� ž ������ �ذ��ϴ� �ʺ� �켱 Ž�� �ڵ�
const int MAX_DISCS = 12;
//index�� ������ �� �� ��տ� �����ִ��� ��ȯ�Ѵ�.
int get(int state, int index) {
	return (state >> (index * 2)) & 3;
}
//state�� index�� ������ value��տ� �����ִ� ���·� �����Ѵ�.
int set(int state, int index, int value) {
	return (state & ~(3 << (index * 2))) | (value << (index * 2));
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
					//j�� ����� ����ְų�, �� ���� ������ �� Ŀ�� �Ѵ�.
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						//there�� ���¸� �̹� �߰��ߴٸ� �ǳʶڴ�.
						if (c[there] != -1) continue;
						c[there] = c[here] + 1;
						if (there == end) return c[there];
						q.push(there);
					}
	}
	return -1;
}

//�ϳ����� ž ������ �ذ��ϴ� ����� Ž���� ����

//x�� ��ȣ�� ��ȯ�Ѵ�.
int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }
//x�� ���밪�� 1 ������Ų��.
int incr(int x) { if (x < 0) return x - 1; return x + 1; }
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
						//����� ���� ���
						else if (sgn(c[there]) != sgn(c[here]))
							return abs(c[there]) + abs(c[here]) - 1;
					}
	}
	return -1;
}