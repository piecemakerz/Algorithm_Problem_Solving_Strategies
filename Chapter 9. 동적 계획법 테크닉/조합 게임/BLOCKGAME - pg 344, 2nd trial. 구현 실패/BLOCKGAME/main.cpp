#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int C;
vector<int> moves;
inline int cell(int y, int x) { return 1 << (y * 5 + x); }

//�����ǿ� ���� �� �ִ� ��ϵ��� ��ġ�� �̸� ����Ѵ�.
void precalc() {
	//�� ĭ¥�� L�� ��� ��ϵ��� ����Ѵ�.
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			vector<int> cells;
			for (int dy = 0; dy < 2; dy++)
				for (int dx = 0; dx < 2; dx++)
					cells.push_back(cell(y + dy, x + dx));

			int square = cells[0] + cells[1] + cells[2] + cells[3];
			for (int i = 0; i < 4; i++)
				moves.push_back(square - cells[i]);
		}
	//�� ĭ¥�� ��ϵ��� ����Ѵ�.
	for(int i=0; i<5; i++)
		for (int j = 0; j < 4; j++) {
			moves.push_back(cell(i, j) + cell(i, j + 1));
			moves.push_back(cell(j, i) + cell(j + 1, i));
		}
}

char cache[1 << 25];
//���� ������ ���°� board�� �� ���� ������ ����� �¸����� ���θ� ��ȯ�Ѵ�.
//���� ������ ����� �¸��ϱ� ���� �ּ��� ���Ѵٰ� �����Ѵ�.
//(y, x)ĭ�� ����� �ִ�. <=> (y*5+x)�� ��Ʈ�� ���� �ִ�.
int play(int board) {
	//�޸������̼�
	char& ret = cache[board];
	if (ret != -1) return ret;
	ret = 0;
	//������ ���� ��� ��ġ�� �� ���� ���� �� �ִ� ��� ���� ����Ѵ�.
	for(int i=0; i<moves.size(); i++)
		//�� ���� �� �����ǿ� ���� �� �ִ°� Ȯ��
		if((moves[i] & board) == 0)
			//������ �ּ��� ������ ������ ���� ��찡 �ִٸ�
			//���� ������ ����� ������ �¸��Ѵ�.
			if (!play(board | moves[i])) {
				ret = 1;
				break;
			}
	return ret;
}

int main(void) {
	precalc();
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		int state = 0;
		char input;
		for(int y=0; y<5; y++)
			for (int x = 0; x < 5; x++) {
				cin >> input;
				if (input == '#')
					state += cell(y, x);
			}
		if (play(state))
			cout << "WINNING" << endl;
		else
			cout << "LOSING" << endl;
	}
}