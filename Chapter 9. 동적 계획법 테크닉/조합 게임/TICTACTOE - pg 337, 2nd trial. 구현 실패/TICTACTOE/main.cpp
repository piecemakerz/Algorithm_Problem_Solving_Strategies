#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int C;
int board[3][3];
int mycache[19683];

//보드에 빙고가 존재하는지 확인하고 존재한다면
//빙고를 만들 플레이어의 번호를 반환하는 알고리즘.
//존재하지 않는다면 0을 반환한다.
int bingoCheck() {
	//가로 줄 체크
	for (int i = 0; i < 3; i++)
		if (board[i][0] != 0 && (board[i][0] == board[i][1]) &&
			(board[i][1] == board[i][2]) && (board[i][0] == board[i][2]))
			return board[i][0];

	//세로 줄 체크
	for (int i = 0; i < 3; i++)
		if (board[0][i] != 0 && (board[0][i] == board[1][i]) &&
			(board[1][i] == board[2][i]) && (board[0][i] == board[2][i]))
			return board[0][i];

	//대각선 체크
	if (board[0][0] != 0 && (board[0][0] == board[1][1]) &&
		(board[1][1] == board[2][2]) && (board[0][0] == board[2][2]))
		return board[0][0];

	if (board[0][2] != 0 && (board[0][2] == board[1][1]) &&
		(board[1][1] == board[2][0]) && (board[0][2] == board[2][0]))
		return board[0][2];

	return 0;
}

//책의 풀이를 참고한 내 알고리즘. 책의 알고리즘이 이번 차례인 사람이
//이길 수 있는지에 대한 정보를 반환하는 것과 달리, 내 알고리즘 tictactoe는
//현재 보드 상태가 state일 때, 양 플레이어가 최선을 다해 게임을 플레이했을 경우
//이기는 플레이어의 번호를 반환한다. (비길 경우 0 반환)
int tictactoe(int state, int player) {
	int& ret = mycache[state];
	if (ret != -1) return ret;

	int isFinished = bingoCheck();
	if (isFinished)
		return ret = isFinished;
	
	//현재 player가 이기거나 비기는 경우가 전혀 없을 경우
	//다른 player가 이긴다.
	ret = ((player == 1) ? 2 : 1);

	bool filled = true;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != 0)
				continue;

			filled = false;
			board[i][j] = player;
			int result = tictactoe(state + (player * pow<int>(3, (i * 3 + j))), ((player == 1) ? 2 : 1));
			board[i][j] = 0;

			//현재 player가 이기는 경우
			if (result == player)
				return ret = player;
			//이기지 못할 경우에는 최소한 비기는 경우를 선택한다.
			else if (result == 0)
				ret = 0;
		}
	//모든 보드가 채워졌으며 빙고를 만들지 못한 경우 비긴 경우로 간주한다.
	if (filled)
		return ret = 0;

	return ret;
}

//틱택토를 해결하는 책의 동적 계획법 알고리즘.
//turn이 한 줄을 만들었는지를 반환한다.
bool isFinished(const vector<string>& board, char turn);

//틱택토 게임판이 주어질 때 [0, 3^9-1]범위의 정수로 변환한다.
int bijection(const vector<string>& board) {
	int ret = 0;
	for(int y=0; y<3; y++)
		for (int x = 0; x < 3; x++) {
			ret *= 3;
			if (board[y][x] == 'o') ret++;
			else if (board[y][x] == 'x') ret += 2;
		}
	return ret;
}
//cache[]는 -2로 초기화한다.
int cache[19683];
//canWin(board, turn) = 틱택토 게임판이 현재 board일 때 이번 차례인 사람 turn이
//이길 수 있으면 1을, 비길 수 있으면 0을, 지면 -1을 리턴한다.
int canWin(vector<string>& board, char turn) {
	//기저 사례: 마지막에 상대가 둬서 한 줄이 만들어진 경우
	if (isFinished(board, 'o' + 'x' - turn)) return -1;
	int& ret = cache[bijection(board)];
	if (ret != -2) return ret;
	//모든 값의 min을 취하자.
	int minValue = 2;
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++)
			if (board[y][x] == '.') {
				board[y][x] = turn;
				minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
				board[y][x] = '.';
			}
	//플레이할 수 없거나, 어떻게 해도 비기는 것이 최선인 경우
	if (minValue == 2 || minValue == 0) return ret = 0;
	//최선이 상대가 이기는 거라면 난 무조건 지고, 상대가 지는 거라면 난 이긴다.
	return ret = -minValue;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		int xCount = 0, oCount = 0, state = 0;
		char input;
		memset(mycache, -1, sizeof(mycache));

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				cin >> input;
				if (input == 'x') {
					xCount++;
					board[y][x] = 2;
					state += (2 * pow<int>(3, (y * 3 + x)));
				}
				else if (input == 'o') {
					oCount++;
					board[y][x] = 1;
					state += pow<int>(3, (y * 3 + x));
				}
				else if (input == '.')
					board[y][x] = 0;
				else
					x--;
			}
		}
		
		int player = (xCount > oCount ? 1 : 2);
		int winner = tictactoe(state, player);
		if (winner == 0)
			cout << "TIE" << endl;
		else if (winner == 1)
			cout << "o" << endl;
		else
			cout << "x" << endl;;
	}
	return 0;
}