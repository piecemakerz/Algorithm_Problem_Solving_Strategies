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

int main(void) {
	printf("%d\n", hasWord(2, 2, "YES"));
	printf("%d\n", hasWordMine(2, 2, "YES"));
	return 0;
}

//알고스팟 채점용 함수. 너무 느려서 문제 해결은 할 수 없으나 입력에 따른 출력은 맞게 나온다.
/*
#include <iostream>
#include <cstdio>
#include <string>

#define BOGGLE_LEN 5
using namespace std;

char box[BOGGLE_LEN][BOGGLE_LEN];
int testCase;
int words;
bool hasWord(int, int, const string&);
void CheckingProcedure(const string& inputString);

int main()
{
	cin >> testCase;

	for (int t = 0; t < testCase; t++) {

		for (int i = 0; i < BOGGLE_LEN; i++)
			for (int j = 0; j < BOGGLE_LEN; j++)
				cin >> box[i][j];

		cin >> words;

		string * inputStrings = new string[words];

		for (int i = 0; i < words; i++)
			cin >> inputStrings[i];

		for (int i = 0; i < words; i++) {
			CheckingProcedure(inputStrings[i]);
		}
	}

	return 0;
}

void CheckingProcedure(const string& inputString) {
	int startx, starty;

	for (int i = 0; i < BOGGLE_LEN; i++) {
		for (int j = 0; j < BOGGLE_LEN; j++) {
			if (inputString[0] == box[i][j]) {
				starty = i, startx = j;
				if (hasWord(starty, startx, inputString)) {
					cout << inputString << " " << "YES" << endl;
					return;
				}
			}
		}
	}

	cout << inputString << " " << "NO" << endl;
}

bool hasWord(int y, int x, const string& word) {
	if ((y >= BOGGLE_LEN || y < 0) || (x >= BOGGLE_LEN || x < 0)) {
		return false;
	}

	if (word[0] == box[y][x]) {

		if (word.size() == 1)
			return true;

		else {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (i == 0 && j == 0)
						continue;
					if (hasWord(y + i, x + j, word.substr(1)))
						return true;
				}
			}
		}
	}

	return false;
}
*/