#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define CLOCK_NUM 16
#define SWITCH_NUM 10
#define MAX 987654321
using namespace std;

int clockState[CLOCK_NUM];
vector<vector<int>> switches = {
	{0,1,2},
	{3,7,9,11},
	{4,10,14,15},
	{0,4,5,6,7},
	{6,7,8,10,12},
	{0,2,14,15},
	{3,14,15},
	{4,5,7,14,15},
	{1,2,3,4,5},
	{3,4,5,9,13}
};

bool clockCheck() {
	for (int i = 0; i < CLOCK_NUM; i++) {
		if (clockState[i] != 12)
			return false;
	}
	return true;
}

int PressSwitch(int switchToPress = 0, int switchPressed = 0) {
	if (clockCheck())
		return switchPressed;

	if (switchToPress >= SWITCH_NUM)
		return MAX;

	int ret = MAX;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < switches[switchToPress].size(); j++) {
			if (clockState[switches[switchToPress][j]] >= 12)
				clockState[switches[switchToPress][j]] = 3;
			else
				clockState[switches[switchToPress][j]] += 3;
		}

		if (i == 3)
			ret = min(ret, PressSwitch(switchToPress + 1, switchPressed));
		else
			ret = min(ret, PressSwitch(switchToPress + 1, switchPressed + i + 1));
	}

	return ret;
}

int main(void) {
	int C;
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(clockState, 0, CLOCK_NUM);
		int input;
		for (int i = 0; i < CLOCK_NUM; i++) {
			cin >> input;
			clockState[i] = input;
		}
		int result = PressSwitch();
		if (result == MAX)
			cout << -1 << endl;
		else
			cout << result << endl;
	}

	return 0;
}