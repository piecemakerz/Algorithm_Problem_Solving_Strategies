#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

// 답을 보고 수정한 내 풀이

int H, W;
int totalBoard;
int ways = 0;

bool IsInRange(int n1, int n2) {
	if ((H < 2 	|| W < 2))
		return false;
		
	if ((n1 < 0) || (n1 > H - 2))
		return false;
	if ((n2 < 0) || (n2 > W - 1))
		return false;

	return true;
}

bool IsFitInBoard(char ** boardArray, int y, int x, int casenum) {
	switch (casenum) {
	case 0:
		if (!(x >= W - 1)) {
			if ((boardArray[y][x] == '.') && (boardArray[y][x + 1] == '.') && (boardArray[y + 1][x] == '.'))
				return true;
		}
		break;
	case 1:
		if (!(x >= W - 1)) {
			if ((boardArray[y][x] == '.') && (boardArray[y][x + 1] == '.') && (boardArray[y + 1][x + 1] == '.'))
				return true;
		}
		break;
	case 2:
		if (!(x >= W - 1)) {
			if ((boardArray[y][x] == '.') && (boardArray[y + 1][x + 1] == '.') && (boardArray[y + 1][x] == '.'))
				return true;
		}
		break;
	case 3:
		if (!(x <= 0)) {
			if ((boardArray[y][x] == '.') && (boardArray[y + 1][x - 1] == '.') && (boardArray[y + 1][x] == '.'))
				return true;
		}
		break;
	}

	return false;
}

void CheckEveryBoardCoverWays(char ** boardArray, int numOfBlack, int y = 0, int x = 0);

int main(void) {
	int testtime;
	int numOfBlack = 0;
	char ** boardArray;
	char fflush;
	scanf("%d", &testtime);

	for (int i = 0; i < testtime; i++) {
		scanf("%d %d", &H, &W);
		totalBoard = H*W;
		scanf("%c", &fflush);

		boardArray = new char*[H];
		for (int i = 0; i < H; i++) {
			boardArray[i] = new char[W];
			memset(boardArray[i], 0, sizeof(char)*W);
		}

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				scanf("%c", &(boardArray[i][j]));
				if (boardArray[i][j] == '#')
					numOfBlack++;
				if (boardArray[i][j] == '\n') {
					boardArray[i][j] = 0;
					j--;
					continue;
				}
			}
		}

		CheckEveryBoardCoverWays(boardArray, numOfBlack);
		printf("%d\n", ways);

		for (int i = 0; i < H; i++)
			delete[] boardArray[i];

		delete[] boardArray;
		numOfBlack = 0;
		totalBoard = 0;
		H = 0, W = 0;
		ways = 0;
	}
}

void CheckEveryBoardCoverWays(char ** boardArray, int numOfBlack, int y, int x) {
	bool isFit = false;

	if (numOfBlack == totalBoard) {
		ways++;
		return;
	}

	if (!IsInRange(y, x))
		return;

	if (IsFitInBoard(boardArray, y, x, 0)) {
		isFit = true;
		boardArray[y][x] = '#';
		boardArray[y][x + 1] = '#';
		boardArray[y + 1][x] = '#';
		numOfBlack += 3;

		if (x >= W - 1)
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y + 1, 0);
		else
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y, x + 1);

		boardArray[y][x] = '.';
		boardArray[y][x + 1] = '.';
		boardArray[y + 1][x] = '.';
		numOfBlack -= 3;
	}

	if (IsFitInBoard(boardArray, y, x, 1)) {
		isFit = true;
		boardArray[y][x] = '#';
		boardArray[y][x + 1] = '#';
		boardArray[y + 1][x + 1] = '#';
		numOfBlack += 3;
		if (x >= W - 1)
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y + 1, 0);
		else
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y, x + 1);

		boardArray[y][x] = '.';
		boardArray[y][x + 1] = '.';
		boardArray[y + 1][x + 1] = '.';
		numOfBlack -= 3;
	}

	if (IsFitInBoard(boardArray, y, x, 2)) {
		isFit = true;
		boardArray[y][x] = '#';
		boardArray[y + 1][x + 1] = '#';
		boardArray[y + 1][x] = '#';
		numOfBlack += 3;

		if (x >= W - 1)
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y + 1, 0);
		else
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y, x + 1);

		boardArray[y][x] = '.';
		boardArray[y + 1][x + 1] = '.';
		boardArray[y + 1][x] = '.';
		numOfBlack -= 3;
	}

	if(IsFitInBoard(boardArray, y, x, 3)){
		isFit = true;
		boardArray[y][x] = '#';
		boardArray[y + 1][x - 1] = '#';
		boardArray[y + 1][x] = '#';
		numOfBlack += 3;


		if (x >= W - 1)
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y + 1, 0);
		else
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y, x + 1);

		boardArray[y][x] = '.';
		boardArray[y + 1][x - 1] = '.';
		boardArray[y + 1][x] = '.';
		numOfBlack -= 3;
	}

	if (!isFit) {
		if (x >= W - 1)
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y + 1, 0);
		else
			CheckEveryBoardCoverWays(boardArray, numOfBlack, y, x + 1);
	}
	return;
}

/* 책의 풀이
#include <iostream>
#include <cassert>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;

const int coverType[4][3][2] = {
	{{0,0}, {1,0}, {0,1}},
	{{0,0}, {0,1}, {1,1}},
	{{0,0}, {1,0}, {1,1}},
	{{0,0}, {1,0}, {1,-1}} };

bool set(vector<vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 3; i++) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
			ok = false;
		else if ((board[ny][nx] += delta) > 1)
			ok = false;
	}
	return ok;
}

int cover(vector<vector<int>>& board) {
	int y = -1, x = -1;
	for (int i = 0; i < board.size(); i++) {
		for(int j=0; j<board[i].size(); j++)
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if (y != -1) break;
	}

	if (y == -1) return 1;

	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (set(board, y, x, type, 1))
			ret += cover(board);
		set(board, y, x, type, -1);
	}
	return ret;
}

int main() {
	int cases;
	cin >> cases;
	assert(cases <= 30);
	while (cases--) {
		int H, W;
		cin >> H >> W;
		assert(1 <= H && H <= 20 && 1 <= W && W <= 20);
		vector<vector<int>> board(H, vector<int>(W, 0));
		int whites = 0;

		for (int i = 0; i < H; i++) {
			string s;
			cin >> s;
			for (int j = 0; j < W; j++) {
				if (s[j] == '#')
					board[i][j] = 1;
			}
			whites += count(board[i].begin(), board[i].end(), 0);
		}
		assert(whites <= 50);
		int ways = cover(board);
		cout << ways << endl;
	}
}
*/