#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define CLOCK_NUM 16

using namespace std;

/* 내 풀이

vector<vector<int>> buttonInfo = {
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

int clockWise[CLOCK_NUM];

void PressButton(int n, bool press) {
	int clockNum = 0;

	if (press) {
		for (int i = 0; i < buttonInfo[n].size(); i++) {
			clockNum = buttonInfo[n][i];
			if (clockWise[clockNum] != 12)
				clockWise[clockNum] += 3;
			else
				clockWise[clockNum] = 3;
		}
	}
	else {
		for (int i = 0; i < buttonInfo[n].size(); i++) {
			clockNum = buttonInfo[n][i];
			if (clockWise[clockNum] != 3)
				clockWise[clockNum] -= 3;
			else
				clockWise[clockNum] = 12;
		}
	}
}

bool CheckEveryClocks(void) {
	for (int i = 0; i < CLOCK_NUM; i++)
		if (clockWise[i] != 12)
			return false;
	return true;
}

int clockSyncCheck(int n = 0, int clickedNum = 0) {
	int ret = 9999;

	if (CheckEveryClocks()) 
		return clickedNum;

	if (n >= 10)
		return ret;

	for (int i = 0; i < 3; i++) {
		PressButton(n, true);
		clickedNum++;
		ret = min<unsigned int>(ret, clockSyncCheck(n+1, clickedNum));
	}

	for (int i = 0; i < 3; i++) {
		PressButton(n, false);
		clickedNum--;
	}

	ret = min(ret, clockSyncCheck(n+1, clickedNum));

	return ret;
}

int main(void) {
	int testtime;
	scanf("%d", &testtime);
	for (int i = 0; i < testtime; i++) {
		int result;
		for (int j = 0; j < CLOCK_NUM; j++) {
			scanf("%d", &(clockWise[j]));
		}
		result = clockSyncCheck();
		if (result == 9999)
			printf("%d\n", -1);
		else
			printf("%d\n", result);

		memset(clockWise, 0, sizeof(int)*CLOCK_NUM);
	}	
}
*/

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;

const char linked[SWITCHES][CLOCKS + 1] = {
	"xxx.............",
	"...x...x.x.x....",
	"....x.....x...xx",
	"x...xxxx........",
	"......xxx.x.x...",
	"x.x...........xx",
	"...x..........xx",
	"....xx.x......xx",
	".xxxxx..........",
	"...xxx...x...x.."
};

bool areAligned(const vector<int>& clocks) {
	for (int i = 0; i < CLOCKS; i++)
		if (clocks[i] != 12)
			return false;
	return true;
}

void push(vector<int>& clocks, int swtch) {
	for(int clock = 0; clock < CLOCKS; ++clock)
		if (linked[swtch][clock] == 'x') {
			clocks[clock] += 3;
			if (clocks[clock] == 15) clocks[clock] = 3;
		}
}
//clocks: 현재 시계들의 상태
//switch: 이번에 누를 스위치의 번호
int solve(vector<int>& clocks, int swtch) {
	if (swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;

	int ret = INF;
	for (int cnt = 0; cnt < 4; cnt++) {
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch);
	}

	return ret;
}