#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MIN = -987654321;
int C, n;
vector<int> board;

int player[2];
int cache[50][50];

//���� ���� ������ �ذ��ϴ� �� ������ȹ�� �˰���.
//å�� �˰���� ���� �����ϹǷ� å�� �˰����� ����
//÷�������� �ʾҴ�.

//gameplay(start, end) = ���� �������� ���� �� ��ġ��
//start�̰� ������ �� ��ġ�� end�� ��, ���ݺ��� ���������� ������ �÷����Ͽ�
//�̹� ������ �÷��̾ ���� �� �ִ� �ִ� �������̸� ��ȯ�Ѵ�.
int gameplay(int start, int end) {
	if (start > end)
		return 0;

	int& ret = cache[start][end];
	if (ret != MIN) return ret;

	//���� �� ���ڸ� ���ϴ� ���
	ret = max(ret, board[start]-gameplay(start + 1, end));

	//������ �� ���ڸ� ���ϴ� ���
	ret = max(ret, board[end]-gameplay(start, end - 1));

	if (end - start > 0) {
		//���� �� 2�� ���ڸ� ����� ���
		ret = max(ret, -gameplay(start + 2, end));
		//������ �� 2���� ���ڸ� ����� ���
		ret = max(ret, -gameplay(start, end - 2));
	}

	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 50; j++)
				cache[i][j] = MIN;

		player[0] = 0, player[1] = 0;
		int input;
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> input;
			board.push_back(input);
		}
		//���� = turn 0, ���� = turn 1
		cout << gameplay(0, board.size() - 1)<<endl;
		board.clear();
	}
	return 0;
}