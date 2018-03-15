#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

vector<int> moves;

inline int cell(int y, int x) { return 1 << (y * 5 + x); }
//게임판에 놓을 수 있는 블록들의 위치를 미리 계산한다.
void precalc() {
	//세 칸짜리 L자 모양 블록들을 계산해 moves에 추가
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			vector<int> cells;
			for (int dy = 0; dy < 2; dy++)
				for (int dx = 0; dx < 2; dx++)
					cells.push_back(cell(y + dy, x + dx));
			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for (int i = 0; i < 4; i++)
				moves.push_back(square - cells[i]);
		}
	}
	//두 칸짜리 블록들을 계산해 moves에 추가
	for(int i=0; i<5; i++)
		for (int j = 0; j < 4; j++) {
			moves.push_back(cell(i, j) + cell(i, j + 1));
			moves.push_back(cell(j, i) + cell(j + 1, i));
		}
}

char cache[1 << 25];
//현재 게임판 상태가 board일 때 현재 차례인 사람이 승리할지 여부를 반환한다. 이긴다면 1, 진다면 0을 반환한다.
//(y,x)칸에 블록이 있다. <=> (y*5+x)번 비트가 켜져 있다.
char play(int board) {
	//메모이제이션
	char& ret = cache[board];
	if (ret != -1) return ret;
	ret = 0;
	//모든 수를 고려한다.
	for(int i=0; i<moves.size(); i++)
		//이 수를 이 게임판에 놓을 수 있는가 확인
		if ((moves[i] & board) == 0)
			if(!play(board | moves[i])){ // 상대방이 반드시 진다면 이 경우 현재 차례 플레이어가 이긴다.
			ret = 1;
			break;
		}
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	precalc();
	for (int testCase = 0; testCase < C; testCase++) {
		memset(cache, -1, sizeof(cache));
		int board = 0;
		char input;
		for(int y=0; y<5; y++)
			for (int x = 0; x < 5; x++) {
				cin >> input;
				if (input == '#')
					board += cell(y, x);
			}
		//cout << board << endl;
		if (play(board) == 1)
			cout << "WINNING" << endl;
		else
			cout << "LOSING" << endl;
	}
	return 0;
}