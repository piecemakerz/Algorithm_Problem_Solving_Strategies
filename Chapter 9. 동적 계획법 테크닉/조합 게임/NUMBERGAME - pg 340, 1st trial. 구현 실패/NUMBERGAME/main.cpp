#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <list>
using namespace std;

const int EMPTY = -987654321;
int n, board[50];
int cache[50][50];
int play(int left, int right) {
	//���� ���: ��� ���� �� �������� ��
	if (left > right) return 0;
	int& ret = cache[left][right];
	if (ret != EMPTY) return ret;
	ret = max(board[left] - play(left + 1, right), board[right] - play(left, right - 1));
	if (right - left + 1 >= 2) {
		ret = max(ret, -play(left + 2, right));
		ret = max(ret, -play(left, right - 2));
	}
	return ret;
}

//�̴ϸƽ� �˰����� ����. (���� ����) - (���� ����)�� �����Ѵ�.
int miniCache[2][50][50];
int play(int left, int right, bool player){ // true = ����, false = ����
	//���� ���: ��� ���� �� �������� ��
	if (left > right) return 0;
	int& ret = miniCache[player][left][right];
	if (ret != EMPTY) return ret;
	if (player) {
		ret = max(board[left] + play(left + 1, right, !player), board[right] + play(left, right - 1, !player));
		if (right - left + 1 >= 2) {
			ret = max(ret, play(left + 2, right, !player));
			ret = max(ret, play(left, right - 2, !player));
		}
	}
	else {
		ret = min(-board[left] + play(left + 1, right, !player), -board[right] + play(left, right - 1, !player));
		if (right - left + 1 >= 2) {
			ret = min(ret, play(left + 2, right, !player));
			ret = min(ret, play(left, right - 2, !player));
		}
	}
	return ret;
}
int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n;
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 50; i++)
				for (int j = 0; j < 50; j++) {
					//cache[i][j] = EMPTY;
					miniCache[k][i][j] = EMPTY;
				}
		}
		for (int i = 0; i < n; i++)
			cin >> board[i];
		//cout << play(0, n - 1) << endl;
		cout << play(0, n - 1, true) << endl;
	}
}