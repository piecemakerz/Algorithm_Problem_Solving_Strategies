#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cstring>
using namespace std;

vector<int> moves;

inline int cell(int y, int x) { return 1 << (y * 5 + x); }
//�����ǿ� ���� �� �ִ� ��ϵ��� ��ġ�� �̸� ����Ѵ�.
void precalc() {
	//�� ĭ¥�� L�� ��� ��ϵ��� ����� moves�� �߰�
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			vector<int> cells;
			for (int dy = 0; dy < 2; dy++)
				for (int dx = 0; dx < 2; dx++)
					cells.push_back(cell(y + dy, x + dx));
			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for (int i = 0; i < 4; i++)
				moves.push_back(square - cells[i]);
		}
	}
	//�� ĭ¥�� ��ϵ��� ����� moves�� �߰�
	for(int i=0; i<5; i++)
		for (int j = 0; j < 4; j++) {
			moves.push_back(cell(i, j) + cell(i, j + 1));
			moves.push_back(cell(j, i) + cell(j + 1, i));
		}
}

char cache[1 << 25];
//���� ������ ���°� board�� �� ���� ������ ����� �¸����� ���θ� ��ȯ�Ѵ�. �̱�ٸ� 1, ���ٸ� 0�� ��ȯ�Ѵ�.
//(y,x)ĭ�� ����� �ִ�. <=> (y*5+x)�� ��Ʈ�� ���� �ִ�.
char play(int board) {
	//�޸������̼�
	char& ret = cache[board];
	if (ret != -1) return ret;
	ret = 0;
	//��� ���� ����Ѵ�.
	for(int i=0; i<moves.size(); i++)
		//�� ���� �� �����ǿ� ���� �� �ִ°� Ȯ��
		if ((moves[i] & board) == 0)
			if(!play(board | moves[i])){ // ������ �ݵ�� ���ٸ� �� ��� ���� ���� �÷��̾ �̱��.
			ret = 1;
			break;
		}
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	precalc();
	for (int testCase = 0; testCase < C; testCase++) {
		memset(cache, -1, sizeof(cache));
		int board = 0;
		char input;
		for(int y=0; y<5; y++)
			for (int x = 0; x < 5; x++) {
				cin >> input;
				if (input == '#')
					board += cell(y, x);
			}
		//cout << board << endl;
		if (play(board) == 1)
			cout << "WINNING" << endl;
		else
			cout << "LOSING" << endl;
	}
	return 0;
}