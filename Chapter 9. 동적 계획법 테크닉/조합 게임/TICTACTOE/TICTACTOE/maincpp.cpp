#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int C;
int board[3][3];
int cache[1 << 9];

int bingoCheck() {
	for (int i = 0; i<3; i++)
		for (int j = 0; j < 3; j++) {
			int cur = board[i][j];
			if (cur == 0)
				continue;

			bool bingo = true;
			for (int k = 0; k < 3; k++)
				if (board[i][k] != cur) {
					bingo = false;
					break;
				}
			if (bingo)
				return cur;

			for (int k = 0; k < 3; k++)
				if (board[k][j] != cur) {
					bingo = false;
					break;
				}
			if (bingo)
				return cur;
		}
	return 0;
}

int tictactoe(int state, int player) {
	int isFinished = bingoCheck();
	if (isFinished)
		return isFinished;

	if (state == (1 << 9) - 1)
		return 0;

	int& ret = cache[state];
	if (ret != -1) return ret;

	ret = (player == 1 ? 2 : 1);

	for(int i=0; i<3; i++)
		for (int j = 0; j < 3; j++) {
			if ((state & (1 << (i * 3 + j))) != 0)
				continue;

			board[i][j] = player;
			int result = tictactoe((state | (1 << (i * 3 + j))), (player == 1 ? 2 : 1));
			board[i][j] = 0;

			if (result == player)
				return ret = player;
			else if (result == 0)
				ret = 0;
		}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		int state = 0, ocount = 0, xcount = 0;
		char input;
		 
		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				cin >> input;
				if (input == 'o') {
					ocount++;
					board[i][j] = 1;
					state += (1 << (i * 3 + j));
				}
				else if (input == 'x') {
					xcount++;
					board[i][j] = 2;
					state += (1 << (i * 3 + j));
				}
				else
					board[i][j] = 0;
			}
		
		int player;
		//'o' = 1, 'x' = 2
		if (xcount > ocount)
			player = 1;
		else
			player = 2;

		int winner = tictactoe(state, player);
		if (winner == 0)
			cout << "TIE" << endl;
		else if (winner == 1)
			cout << "o" << endl;
		else
			cout << "x" << endl;
	}
	return 0;
}