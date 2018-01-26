#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, board[100][100];
int cache[100][100];
int myCache[100][100][2];
// 내가 짠 시간초과 알고리즘. 정답을 찾은 후에도 다른 루트를 찾으므로 중복을 제거하지 못했다.
// ex. 아래 방향을 검사해서 올바른 루트를 찾았으나, 그 이후에도 오른쪽 방향을 검사한다.
// 이 알고리즘이 제거한 중복은 정답을 찾는 과정에서 이전과 같은 보드 칸을 방문했을 때 다시 검사하지 않는 것이다. 
bool JumpGame(int x = 0, int y = 0) {
	if (x >= n ||y >= n)
		return false;
	if (x == n - 1 && y == n - 1)
		return true;

	int& retDown = myCache[y][x][0];
	int& retRight = myCache[y][x][1];
	int jumpSize = board[y][x];
	bool canPass = false;

	if (retDown == 0) {
		if (JumpGame(x, y + jumpSize) == false)
			retDown = -1;
		else
			canPass = true;
	}

	if (retRight == 0) {
		if (JumpGame(x + jumpSize, y) == false)
			retRight = -1;
		else
			canPass = true;
	}

	return canPass;
}

// 책의 답을 본 후 일부 수정해 본 내 알고리즘. 하지만, 캐시 배열을 3차원으로 만들 필요가 없었으며, 쓸데 없는 단계들이 많다.
bool JumpGameFixed(int x = 0, int y = 0) {
	if (x >= n || y >= n)
		return false;
	if (x == n - 1 && y == n - 1)
		return true;

	int& retDown = myCache[y][x][0];
	int& retRight = myCache[y][x][1];
	int jumpSize = board[y][x];

	if (retDown == 0) {
		if (JumpGameFixed(x, y + jumpSize) == false)
			retDown = -1;
		else
			return true;
	}

	if (retRight == 0) {
		if (JumpGameFixed(x + jumpSize, y) == false)
			retRight = -1;
		else
			return true;
	}

	return false;
}

//동적 계획법 알고리즘. 정답을 찾은 이후에는 다른 루트를 거치지 않고 바로 탐색을 종료한다. 또한, 이전에 방문했던 보드칸을 다시 방문했을 때 다시 체크하지도 않는다. 
int jump(int y=0, int x=0) {
	if (y >= n || x >= n) return 0;
	if (y == n - 1 && x == n - 1) return 1;

	int& ret = cache[y][x];
	if (ret != -1) return ret; // ret이 -1이면 아직 체크 안함.
	
	int jumpSize = board[y][x];
	return ret = (jump(y + jumpSize, x) || jump(y, x + jumpSize));
}

int main(void) {
	int C;
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n;
		memset(myCache, 0, sizeof(myCache));
		memset(cache, -1, sizeof(cache));
		for(int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++)
				cin >> board[i][j];
		

		if (JumpGameFixed())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	return 0;
}