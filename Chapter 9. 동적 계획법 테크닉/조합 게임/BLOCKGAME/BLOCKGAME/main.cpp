#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int C;
int board[5][5];
int block[6][2][2] = {
	{{0,1}, {1,1}},
	{{1,0}, {1,1}},
	{{0,1}, {1,0}},
	{{1, -1}, {1,0}},
	{{0,1}},
	{{1,0}}
};

bool gameplay(int state, bool turn) {

}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		int state = 0;
		char input;
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++) {
				cin >> input;
				if (input == '.')
					board[y][x] = 0;
				else {
					board[y][x] = 1;
					state += (1 << (y * 5 + x));
				}
			}

		if (gameplay(state, true))
			cout << "WINNING" << endl;
		else
			cout << "LOSING" << endl;
	}
	return 0;
}