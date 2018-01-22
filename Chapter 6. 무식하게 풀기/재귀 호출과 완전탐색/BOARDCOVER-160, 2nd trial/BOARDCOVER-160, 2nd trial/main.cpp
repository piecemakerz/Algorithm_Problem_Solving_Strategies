#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int H, W;
int whiteSpaces;

//≥ª «Æ¿Ã
int checkPos[4][2][2] = {
	{{1,0}, {0,1}},
	{{0,1}, {1,1}},
	{{0,1}, {-1,1}},
	{{1,0}, {1,1}}
};

int countCoveringWays(vector<vector<int>>& arr, int curX = 0, int curY = 0) {
	if (whiteSpaces == 0)
		return 1;

	if (curX >= W) {
		curY++;
		curX = 0;
	}

	if (curY >= H) {
		return 0;
	}

	int ret = 0;
	if (arr[curY][curX] == 0) {
		for (int i = 0; i < 4; i++) {
			int checkY1 = curY + checkPos[i][0][1], checkY2 = curY + checkPos[i][1][1];
			int checkX1 = curX + checkPos[i][0][0], checkX2 = curX + checkPos[i][1][0];

			if (checkY1 < 0 || checkY1 >= H || checkY2 < 0 || checkY2 >= H
				|| checkX1 < 0 || checkX1 >= W || checkX2 < 0 || checkX2 >= W)
				continue;

			if (arr[checkY1][checkX1] == 0 && arr[checkY2][checkX2] == 0) {
				arr[curY][curX] = arr[checkY1][checkX1] = arr[checkY2][checkX2] = 1;
				whiteSpaces -= 3;
				ret += countCoveringWays(arr, curX + 1, curY);
				arr[curY][curX] = arr[checkY1][checkX1] = arr[checkY2][checkX2] = 0;
				whiteSpaces += 3;
			}
		}
	}

	else {
		ret += countCoveringWays(arr, curX + 1, curY);
	}

	return ret;
}

//√•¿« ¥‰
/*const int coverType[4][3][2] = {
	{ { 0,0 },{ 1,0 },{ 0,1 } },
	{ { 0,0 },{ 0,1 },{ 1,1 } },
	{ { 0,0 },{ 1,0 },{ 1,1 } },
	{ { 0,0 },{ 1,0 },{ 1,-1 } }
};

bool set(vector<vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 3; i++) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size()) // π¸¿ß∏¶ π˛æÓ≥µ¿ª ∂ß
			ok = false;
		else if ((board[ny][nx] += delta) > 1)
			ok = false; // ∞À¿∫ ƒ≠¿ª µ§¿ª ∂ß && ∞„√∆¿ª ∂ß
	}
	return ok;
}

int cover(vector<vector<int>>& board) {
	int y = -1, x = -1;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
			if (y != -1) break;
		}
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
*/
int main(void) {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		whiteSpaces = 0;
		char input;
		cin >> H >> W;
		vector<vector<int>> arr(H, vector<int>(W, 0));
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				cin >> input;

				if (input == '#')
					arr[y][x] = 1;

				else if (input == '\n') {
					x--;
					continue;
				}

				else {
					arr[y][x] = 0;
					whiteSpaces++;
				}

			}
		}
		if (whiteSpaces % 3 != 0)
			cout << 0 << endl;
		else
			cout << countCoveringWays(arr) << endl;
	}
	return 0;
}