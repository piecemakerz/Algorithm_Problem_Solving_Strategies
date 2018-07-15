#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>
using namespace std;

//turn�� �� ���� ����������� ��ȯ�Ѵ�.
bool isFinished(const vector<string>& board, char turn) {
	//���� �� üũ
	for (int y = 0; y < 3; y++) {
		int turncount = 0;
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == turn)
				turncount++;
			else
				break;
		}
		if (turncount == 3)
			return true;
	}
	//���� �� üũ
	for (int x = 0; x < 3; x++) {
		int turncount = 0;
		for (int y = 0; y < 3; y++) {
			if (board[y][x] == turn)
				turncount++;
			else
				break;
		}
		if (turncount == 3)
			return true;
	}
	//�밢�� üũ
	if ((board[0][0] == turn && board[1][1] == turn && board[2][2] == turn) ||
		(board[0][2] == turn && board[1][1] == turn && board[2][0] == turn))
		return true;

	return false;
}

//ƽ���� �������� �־��� �� [0, 19682] ������ ������ ��ȯ�Ѵ�.
int bijection(const vector<string>& board) {
	int ret = 0;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			ret *= 3;
			if (board[y][x] == 'o') ret++;
			else if (board[y][x] == 'x') ret += 2;
		}
	}
	return ret;
}
//cache[]�� -2�� �ʱ�ȭ�Ѵ�.
int cache[19683];
//���� �̱� �� ������ 1��, ��� �� ������ 0��, ���� -1�� �����Ѵ�.
int canWin(vector<string>& board, char turn) {
	//���� ���: �������� ��밡 �ּ� �� ���� ������� ���
	if (isFinished(board, 'o' + 'x' - turn)) return -1;
	int& ret = cache[bijection(board)];
	if (ret != -2) return ret;
	//��� ��ȯ ���� min�� ���Ѵ�.
	int minValue = 2;
	for (int y = 0; y<3; y++)
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == '.') {
				board[y][x] = turn;
				minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
				board[y][x] = '.';
			}
		}

	//�÷��� �� �� ���ų�, ��� �ص� ���� ���� �ּ��� ���
	if (minValue == 2 || minValue == 0) return ret = 0;
	//�ּ��� ��밡 �̱�� ���̶�� �� ������ ����, ��밡 ���� �Ŷ�� �� �̱��.
	return ret = -minValue;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		vector<string> inputArr;
		string inputStr;
		int xCount = 0, oCount = 0;
		for (int i = 0; i < sizeof(cache) / sizeof(int); i++)
			cache[i] = -2;

		for (int i = 0; i < 3; i++) {
			cin >> inputStr;
			inputArr.push_back(inputStr);
		}

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				if (inputArr[y][x] == 'x')
					xCount++;
				else if (inputArr[y][x] == 'o')
					oCount++;
			}
		}
		char turn = (xCount == oCount ? 'x' : 'o');
		int result = canWin(inputArr, turn);
		if (result == 1) cout << turn << endl;
		else if (result == -1) cout << (char)('x' + 'o' - turn) << endl;
		else cout << "TIE" << endl;
	}
	return 0;
