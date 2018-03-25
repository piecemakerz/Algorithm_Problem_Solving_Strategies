#include <iostream>
#include <cstdlib>
using namespace std;

bool whosFirst, curTurn; // false = 'x', true = 'o'
int board[3][3]; // 0 = '.', 1 = 'x', 2 = 'o'

void calculateWhosTurn() {
	int xCount = 0, yCount = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0)
				continue;
			else if (board[i][j] == 1)
				xCount++;
			else
				yCount++;
		}
	if ((xCount % 2) == (yCount % 2)) {
		whosFirst = false; // 'x' turn
		curTurn = false;
	}
	else {
		whosFirst = true; // 'o' turn
		curTurn = true;
	}
}

bool canWin() {
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < 3; y++) {
			if (board[y][x] == '.') {
				if (curTurn)
					board[y][x] = 'o';
				else
					board[y][x] = 'x';
				if(canWin() == false);
				board[y][x] = '.';
			}
		}
	}
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		char input;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cin >> input;
				if (input == '.')
					board[i][j] = 0;
				else if (input == 'x')
					board[i][j] = 1;
				else
					board[i][j] = 2;
			}
		}
		calculateWhosTurn();
		bool result = canWin();
		if (whosFirst && result)
			cout << 'o' << endl;
		else
			cout << 'x' << endl;
	}
}