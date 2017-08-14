#include <cstdio>
#include <cstring>

int n, board[100][100];
int cache[100][100];

bool Jumpgame(int y = 0, int x = 0) {
	if (y >= n || x >= n) return 0;
	if (y == n - 1 && x == n - 1) return 1;
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	int jumpSize = board[y][x];
	return ret = (Jumpgame(y + jumpSize, x) || Jumpgame(y, x + jumpSize));
}