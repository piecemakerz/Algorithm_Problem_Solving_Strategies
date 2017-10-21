/* 내 풀이
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define CLOCK_NUM 16

using namespace std;

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

//다시 풀어본 내 풀이
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

const double INF = 1e200;
const int CLOCK_NUM = 16;
const int SWITCH_NUM = 10;

vector<vector<int>> switches = { { 0,1,2 },
{ 3,7,9,11 },
{ 4,10,14,15 },
{ 0,4,5,6,7 },
{ 6,7,8,10,12 },
{ 0,2,14,15 },
{ 3,14,15 },
{ 4,5,7,14,15 },
{ 1,2,3,4,5 },
{ 3,4,5,9,13 } };


double CalMinSwitch(vector<int>& clocks, int switchNum = 0, double totalClicked = 0) {

	bool isSet = true;
	double ret = INF;
	for (int i = 0; i < CLOCK_NUM; i++) {
		if (clocks[i] != 12) {
			isSet = false;
			break;
		}
	}

	if (isSet)
		return totalClicked;

	if (switchNum >= SWITCH_NUM)
		return ret;

	//해당 버튼 누르지 않고 통과
	double cand = CalMinSwitch(clocks, switchNum + 1, totalClicked);
	ret = min(ret, cand);

	//해당 버튼 1~3번 누르기
	for (int i = 1; i <= 3; i++) {
		for (int j = 0; j < switches[switchNum].size(); j++) {
			clocks[switches[switchNum][j]] += 3;
			if (clocks[switches[switchNum][j]] > 12)
				clocks[switches[switchNum][j]] = 3;
		}
		cand = CalMinSwitch(clocks, switchNum + 1, totalClicked + i);
		ret = min(ret, cand);
	}

	// 시계 초기화
	for (int j = 0; j < switches[switchNum].size(); j++) {
		clocks[switches[switchNum][j]] += 3;
		if (clocks[switches[switchNum][j]] > 12)
			clocks[switches[switchNum][j]] = 3;
	}

	return ret;
}

int main() {
	int cases;
	cin >> cases;
	assert(cases <= 30);
	while (cases--) {
		int input;
		double result;
		vector<int> clocks;
		for (int i = 0; i < CLOCK_NUM; i++) {
			cin >> input;
			assert(input == 3 || input == 6 || input == 9 || input == 12);
			clocks.push_back(input);
		}
		result = CalMinSwitch(clocks);
		if (result == INF)
			result = -1;
		cout << result << endl;
	}
}


/* 책의 풀이

#include<iostream>
#include<vector>
using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
const char linked[SWITCHES][CLOCKS+1] = {
  "xxx.............",
  "...x...x.x.x....",
  "....x.....x...xx",
  "x...xxxx........",
  "......xxx.x.x...",
  "x.x...........xx",
  "...x..........xx",
  "....xx.x......xx",
  ".xxxxx..........",
  "...xxx...x...x.."};

// 모든 시계가 12시를 가리키고 있는지 확인
bool areAligned(const vector<int>& clocks){
	for(int i=0; i<CLOCKS; i++){
		if(clocks[i] % 4 != 0) return false;
	return true;
}

//switch번 스위치를 누른다.
void push(vector<int>& clocks, int switch){
	for(int clock = 0; clock < CLOCKS; clock++)
		if(linked[switch][clock] == 'x')
			clocks[clock] += 3;
}

int solve(vector<int>& clocks, int switch){
	if(switch == SWITCHES) return areAligned(clocks) ? 0 : INF;
	int ret = INF;
	for(int cnt = 0; cnt < 4; cnt++){
		ret = min(ret, cnt + solve(clocks, switch+1));
		push(clocks, switch);
	}
	return ret;
}

int main(){
	int cases;
	cin >> cases;
	for(int cc = 0; cc < (cases); cc++){
		vector<int> clocks(16, 0);
		for(int i=0; i< 16; i++)
			cin>>clocks[i];
		int ret = solve(clocks, 0);
		cout<< (ret >= INF ? -1 : ret) << endl;
	}
}
*/