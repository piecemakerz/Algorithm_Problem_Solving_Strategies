#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>
using namespace std;

//turn이 한 줄을 만들었는지를 반환한다.
bool isFinished(const vector<string>& board, char turn) {
	//가로 줄 체크
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
	//세로 줄 체크
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
	//대각선 체크
	if ((board[0][0] == turn && board[1][1] == turn && board[2][2] == turn) ||
		(board[0][2] == turn && board[1][1] == turn && board[2][0] == turn))
		return true;

	return false;
}

//틱택토 게임판이 주어질 때 [0, 19682] 범위의 정수로 변환한다.
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
//cache[]는 -2로 초기화한다.
int cache[19683];
//내가 이길 수 있으면 1을, 비길 수 있으면 0을, 지면 -1을 리턴한다.
int canWin(vector<string>& board, char turn) {
	//기저 사례: 마지막에 상대가 둬서 한 줄이 만들어진 경우
	if (isFinished(board, 'o' + 'x' - turn)) return -1;
	int& ret = cache[bijection(board)];
	if (ret != -2) return ret;
	//모든 반환 값의 min을 취한다.
	int minValue = 2;
	for (int y = 0; y<3; y++)
		for (int x = 0; x < 3; x++) {
			if (board[y][x] == '.') {
				board[y][x] = turn;
				minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
				board[y][x] = '.';
			}
		}

	//플레이 할 수 없거나, 어떻게 해도 비기는 것이 최선인 경우
	if (minValue == 2 || minValue == 0) return ret = 0;
	//최선이 상대가 이기는 것이라면 난 무조건 지고, 상대가 지는 거라면 난 이긴다.
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
