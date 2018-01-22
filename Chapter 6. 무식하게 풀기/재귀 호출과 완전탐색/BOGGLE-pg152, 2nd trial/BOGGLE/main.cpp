#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define BOARD_SIZE 5
using namespace std;

char board[BOARD_SIZE][BOARD_SIZE] = {
	{'U', 'R', 'L', 'P', 'M'},
	{'X', 'P', 'R', 'E', 'T'},
	{'G', 'I', 'A', 'E', 'T'},
	{'X', 'T', 'N', 'Z', 'Y'},
	{'X', 'O', 'Q', 'R', 'S'}
};

bool hasWord(int y, int x, string& word, int curIdx=0) {
	// 기저사례: 보드 상의 현 위치 문자가 현재 비교해야 할 단어의 문자와 같지 않을 때
	// 기저사례2: curIdx가 word-1의 길이와 같아졌을 때
	if (x >= BOARD_SIZE || x < 0 || y >= BOARD_SIZE || y < 0 || board[y][x] != word[curIdx] )
		return false;

	if (curIdx == word.size() - 1)
		return true;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;
			if (hasWord(y + j, x + i, word, curIdx + 1))
				return true;
		}
	}

	return false;

}

int main(void) {
	string str1 = "PRETTY";
	string str2 = "GIRL";
	string str3 = "REPEAT";
	
	cout << hasWord(1, 1, str1) << endl;
	cout << hasWord(2, 0, str2) << endl;
	cout << hasWord(1, 2, str3) << endl;
}