#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

int C;
int board[3][3];
int mycache[19683];

//���忡 ���� �����ϴ��� Ȯ���ϰ� �����Ѵٸ�
//���� ���� �÷��̾��� ��ȣ�� ��ȯ�ϴ� �˰���.
//�������� �ʴ´ٸ� 0�� ��ȯ�Ѵ�.
int bingoCheck() {
	//���� �� üũ
	for (int i = 0; i < 3; i++)
		if (board[i][0] != 0 && (board[i][0] == board[i][1]) &&
			(board[i][1] == board[i][2]) && (board[i][0] == board[i][2]))
			return board[i][0];

	//���� �� üũ
	for (int i = 0; i < 3; i++)
		if (board[0][i] != 0 && (board[0][i] == board[1][i]) &&
			(board[1][i] == board[2][i]) && (board[0][i] == board[2][i]))
			return board[0][i];

	//�밢�� üũ
	if (board[0][0] != 0 && (board[0][0] == board[1][1]) &&
		(board[1][1] == board[2][2]) && (board[0][0] == board[2][2]))
		return board[0][0];

	if (board[0][2] != 0 && (board[0][2] == board[1][1]) &&
		(board[1][1] == board[2][0]) && (board[0][2] == board[2][0]))
		return board[0][2];

	return 0;
}

//å�� Ǯ�̸� ������ �� �˰���. å�� �˰����� �̹� ������ �����
//�̱� �� �ִ����� ���� ������ ��ȯ�ϴ� �Ͱ� �޸�, �� �˰��� tictactoe��
//���� ���� ���°� state�� ��, �� �÷��̾ �ּ��� ���� ������ �÷������� ���
//�̱�� �÷��̾��� ��ȣ�� ��ȯ�Ѵ�. (��� ��� 0 ��ȯ)
int tictactoe(int state, int player) {
	int& ret = mycache[state];
	if (ret != -1) return ret;

	int isFinished = bingoCheck();
	if (isFinished)
		return ret = isFinished;
	
	//���� player�� �̱�ų� ���� ��찡 ���� ���� ���
	//�ٸ� player�� �̱��.
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

			//���� player�� �̱�� ���
			if (result == player)
				return ret = player;
			//�̱��� ���� ��쿡�� �ּ��� ���� ��츦 �����Ѵ�.
			else if (result == 0)
				ret = 0;
		}
	//��� ���尡 ä�������� ���� ������ ���� ��� ��� ���� �����Ѵ�.
	if (filled)
		return ret = 0;

	return ret;
}

//ƽ���並 �ذ��ϴ� å�� ���� ��ȹ�� �˰���.
//turn�� �� ���� ����������� ��ȯ�Ѵ�.
bool isFinished(const vector<string>& board, char turn);

//ƽ���� �������� �־��� �� [0, 3^9-1]������ ������ ��ȯ�Ѵ�.
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
//cache[]�� -2�� �ʱ�ȭ�Ѵ�.
int cache[19683];
//canWin(board, turn) = ƽ���� �������� ���� board�� �� �̹� ������ ��� turn��
//�̱� �� ������ 1��, ��� �� ������ 0��, ���� -1�� �����Ѵ�.
int canWin(vector<string>& board, char turn) {
	//���� ���: �������� ��밡 �ּ� �� ���� ������� ���
	if (isFinished(board, 'o' + 'x' - turn)) return -1;
	int& ret = cache[bijection(board)];
	if (ret != -2) return ret;
	//��� ���� min�� ������.
	int minValue = 2;
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++)
			if (board[y][x] == '.') {
				board[y][x] = turn;
				minValue = min(minValue, canWin(board, 'o' + 'x' - turn));
				board[y][x] = '.';
			}
	//�÷����� �� ���ų�, ��� �ص� ���� ���� �ּ��� ���
	if (minValue == 2 || minValue == 0) return ret = 0;
	//�ּ��� ��밡 �̱�� �Ŷ�� �� ������ ����, ��밡 ���� �Ŷ�� �� �̱��.
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