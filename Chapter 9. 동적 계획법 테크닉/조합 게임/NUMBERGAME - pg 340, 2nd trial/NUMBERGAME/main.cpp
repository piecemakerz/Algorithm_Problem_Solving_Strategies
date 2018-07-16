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

//숫자 게임 문제를 해결하는 내 동적계획법 알고리즘.
//책의 알고리즘과 거의 동일하므로 책의 알고리즘을 따로
//첨부하지는 않았다.

//gameplay(start, end) = 현재 게임판의 왼쪽 끝 위치가
//start이고 오른쪽 끝 위치가 end일 때, 지금부터 마지막까지 게임을 플레이하여
//이번 차례의 플레이어가 얻을 수 있는 최대 점수차이를 반환한다.
int gameplay(int start, int end) {
	if (start > end)
		return 0;

	int& ret = cache[start][end];
	if (ret != MIN) return ret;

	//왼쪽 끝 숫자를 택하는 경우
	ret = max(ret, board[start]-gameplay(start + 1, end));

	//오른쪽 끝 숫자를 택하는 경우
	ret = max(ret, board[end]-gameplay(start, end - 1));

	if (end - start > 0) {
		//왼쪽 끝 2개 숫자를 지우는 경우
		ret = max(ret, -gameplay(start + 2, end));
		//오른쪽 끝 2개의 숫자를 지우는 경우
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
		//현우 = turn 0, 서하 = turn 1
		cout << gameplay(0, board.size() - 1)<<endl;
		board.clear();
	}
	return 0;
}