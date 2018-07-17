#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int C;
int board[5][5];
int block[6][2][2] = {
	{{0,1}, {1,1}},
	{{1,0}, {1,1}},
	{{0,1}, {1,0}},
	{{1, -1}, {1,0}},
	{{0,1}},
	{{1,0}}
};

int cache[1 << 25][2];
int gameplay(int state, bool turn, int curX, int curY) {
	if (curY >= 5)
		return turn;
	else if (curX >= 5)
		return gameplay(state, turn, 0, curY + 1);

	int& ret = cache[state][turn];
	if (ret != -1) return ret;
	ret = false;

	int curBlock = board[curY][curX];
	if (curBlock != 0) 
		return ret = gameplay(state | curBlock, !turn, curX + 1, curY);

	bool blockPlaced = false;
	for (int i = 0; i < 4; i++) {
		int subX1 = block[i][0][1], subX2 = block[i][1][1];
		int subY1 = block[i][0][0], subY2 = block[i][1][0];
		if (board[subY1][subX1] != 0 && board[subY2][subX2] != 0) {
			blockPlaced = true;
			board[subY1][subX1] = 1, board[subY2][subX2] = 1;
			ret = gameplay(state | curBlock, !turn, curX + 1, curY);
			board[subY1][subX1] = 0, board[subY2][subX2] = 0;
			if (ret == true)
				return ret;
		}
	}

	for (int i = 4; i < 6; i++) {
		int subX = block[i][0][1], subY = block[i][0][0];
		if (board[subY][subX] != 0) {
			blockPlaced = true;
			board[subY][subX] = 1;
			ret = gameplay(state | curBlock, !turn, curX + 1, curY);
			board[subY][subX] = 0;
			if (ret == true)
				return ret;
		}
	}

	if (!blockPlaced) {
		board[curY][curX] = 1;
		return ret = gameplay(state | curBlock, !turn, curX + 1, curY);
		board[curY][curX] = 0;
	}

	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		int state = 0;
		char input;
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++) {
				cin >> input;
				if (input == '.')
					board[y][x] = 0;
				else {
					board[y][x] = 1;
					state += (1 << (y * 5 + x));
				}
			}

		if (gameplay(state, false, 0, 0))
			cout << "WINNING" << endl;
		else
			cout << "LOSING" << endl;
	}
	return 0;
}