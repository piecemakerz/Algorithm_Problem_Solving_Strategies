#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int C;
vector<int> moves;
inline int cell(int y, int x) { return 1 << (y * 5 + x); }

//게임판에 놓을 수 있는 블록들의 위치를 미리 계산한다.
void precalc() {
	//세 칸짜리 L자 모양 블록들을 계산한다.
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			vector<int> cells;
			for (int dy = 0; dy < 2; dy++)
				for (int dx = 0; dx < 2; dx++)
					cells.push_back(cell(y + dy, x + dx));

			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for (int i = 0; i < 4; i++)
				moves.push_back(square - cells[i]);
		}
	//두 칸짜리 블록들을 계산한다.
	for(int i=0; i<5; i++)
		for (int j = 0; j < 4; j++) {
			moves.push_back(cell(i, j) + cell(i, j + 1));
			moves.push_back(cell(j, i) + cell(j + 1, i));
		}
}

char cache[1 << 25];
//현재 게임판 상태가 board일 때 현재 차례인 사람이 승리할지 여부를 반환한다.
//현재 차례인 사람은 승리하기 위해 최선을 다한다고 가정한다.
//(y, x)칸에 블록이 있다. <=> (y*5+x)번 비트가 켜져 있다.
int play(int board) {
	//메모이제이션
	char& ret = cache[board];
	if (ret != -1) return ret;
	ret = 0;
	//보드의 남은 모든 위치에 각 블럭을 놓을 수 있는 모든 수를 고려한다.
	for(int i=0; i<moves.size(); i++)
		//이 수를 이 게임판에 놓을 수 있는가 확인
		if((moves[i] & board) == 0)
			//상대방이 최선을 다했을 때에도 지는 경우가 있다면
			//현재 차례인 사람은 무조건 승리한다.
			if (!play(board | moves[i])) {
				ret = 1;
				break;
			}
	return ret;
}

int main(void) {
	precalc();
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		int state = 0;
		char input;
		for(int y=0; y<5; y++)
			for (int x = 0; x < 5; x++) {
				cin >> input;
				if (input == '#')
					state += cell(y, x);
			}
		if (play(state))
			cout << "WINNING" << endl;
		else
			cout << "LOSING" << endl;
	}
}