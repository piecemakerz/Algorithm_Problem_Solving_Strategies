#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int C, n;
int board[100][100];
int isReachable[100][100];

bool checkReachable(int curX, int curY) {
	if (curX >= n || curY >= n)
		return false;
	int& ret = isReachable[curY][curX];

	if (ret != -1)
		return ret;

	int moveAmount = board[curY][curX];
	if (moveAmount == 0)
		return true;

	return ret = (checkReachable(curX + moveAmount, curY) || checkReachable(curX, curY + moveAmount));
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(isReachable, -1, sizeof(isReachable));
		int input;
		cin >> n;
		for (int x = 0; x < n; x++)
			for (int y = 0; y < n; y++) {
				cin >> input;
				board[y][x] = input;
			}
		if (checkReachable(0, 0))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}