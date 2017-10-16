#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>

#define BOGGLE_LEN 5
using namespace std;

const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };

char board[5][5] = { 'N', 'N', 'N', 'N', 'S',
'N', 'E', 'E', 'E', 'N',
'N', 'E', 'Y', 'E', 'N',
'N', 'E', 'E', 'E', 'N',
'N', 'N', 'N', 'N', 'N' };

bool inRange(int y, int x) {
	return ((y >= 0 && y <= 4) && (x >= 0 && x <= 4));
}

//함수 hasWord, 책의 풀이

bool hasWord(int y, int x, const string& word) {
	if (!inRange(y, x)) return false;

	if (board[y][x] != word[0])	return false;

	if (word.size() == 1) return true;

	for (int direction = 0; direction < 8; direction++) {
		int nextY = y + dy[direction], nextX = x + dx[direction];
		if (hasWord(nextY, nextX, word.substr(1)))
			return true;
	}
	return false;
}

//함수 hasWordMine, 직접 구현한 함수
bool hasWordMine(int y, int x, char * word, int picked = 1) {

	if (!inRange(y, x)) return false;

	if ((strlen(word) == picked) && (word[picked - 1] == board[y][x]))
		return true;

	if (word[picked - 1] != board[y][x])
		return false;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0)
				continue;

			if (hasWordMine(y + j, x + i, word, picked + 1))
				return true;
		}
	}

	return false;
}

// 직접 구현한 함수2
/*char box[BOGGLE_LEN][BOGGLE_LEN] = { { 'N','N','N','N','S' },
{ 'N','E','E','E','N' },
{ 'N','E','Y','E','N' },
{ 'N','E','E','E','N' },
{ 'N','N','N','N','N' } };

bool checked[BOGGLE_LEN][BOGGLE_LEN] = { false, };

bool hasWord(int, int, string);
void ShowBoard();

int main()
{
	int x = 2, y = 2;
	string word;
	ShowBoard();
	printf("\nType Word to Find : ");
	cin >> word;
	cout<<hasWord(y, x, word)<<endl;
	return 0;
}

bool hasWord(int y, int x, string word) {
	bool hasword = false;

	if ((y >= BOGGLE_LEN || y < 0) || (x >= BOGGLE_LEN || x < 0)) {
		return false;
	}

	checked[y][x] = true;

	if (word[0] == box[y][x]) {

		if (word.size() == 1)
			return true;

		else {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if ((i == 0 && j == 0) || checked[y+i][x+j] == true)
						continue;
					if (hasWord(y + i, x + j, word.substr(1)))
						hasword = true;
				}
			}
		}
	}

	return hasword;
}

void ShowBoard() {
	for (int i = 0; i < BOGGLE_LEN; i++) {
		for (int j = 0; j < BOGGLE_LEN; j++) {
			printf("%c ", box[i][j]);
		}
		printf("\n");
	}
}
*/

int main(void) {
	printf("%d\n", hasWord(2, 2, "YES"));
	printf("%d\n", hasWordMine(2, 2, "YES"));
	return 0;
}

