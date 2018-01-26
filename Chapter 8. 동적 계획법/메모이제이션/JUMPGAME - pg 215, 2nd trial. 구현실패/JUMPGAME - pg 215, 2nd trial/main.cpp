#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, board[100][100];
int cache[100][100];
int myCache[100][100][2];
// ���� § �ð��ʰ� �˰���. ������ ã�� �Ŀ��� �ٸ� ��Ʈ�� ã���Ƿ� �ߺ��� �������� ���ߴ�.
// ex. �Ʒ� ������ �˻��ؼ� �ùٸ� ��Ʈ�� ã������, �� ���Ŀ��� ������ ������ �˻��Ѵ�.
// �� �˰����� ������ �ߺ��� ������ ã�� �������� ������ ���� ���� ĭ�� �湮���� �� �ٽ� �˻����� �ʴ� ���̴�. 
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

// å�� ���� �� �� �Ϻ� ������ �� �� �˰���. ������, ĳ�� �迭�� 3�������� ���� �ʿ䰡 ��������, ���� ���� �ܰ���� ����.
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

//���� ��ȹ�� �˰���. ������ ã�� ���Ŀ��� �ٸ� ��Ʈ�� ��ġ�� �ʰ� �ٷ� Ž���� �����Ѵ�. ����, ������ �湮�ߴ� ����ĭ�� �ٽ� �湮���� �� �ٽ� üũ������ �ʴ´�. 
int jump(int y=0, int x=0) {
	if (y >= n || x >= n) return 0;
	if (y == n - 1 && x == n - 1) return 1;

	int& ret = cache[y][x];
	if (ret != -1) return ret; // ret�� -1�̸� ���� üũ ����.
	
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