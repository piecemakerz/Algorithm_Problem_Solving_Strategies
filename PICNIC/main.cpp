#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <cstring>

using namespace std;

/* 내가 푼 풀이 
vector<pair<int, int>> friendList;
int studentNum, friendNum;
int ways = 0;
int FindFriendsLineWay(vector<pair<int, int>>& list, int * prevSelected, int selectedNum = 0, int current = 0);

int main(void) {
	int testtime;
	int f1, f2;
	scanf("%d", &testtime);
	//테스트 케이스 시작
	for (int i = 0; i < testtime; i++) {

		scanf("%d %d", &studentNum, &friendNum);
		int * selected = new int[studentNum];

		for (int i = 0; i<studentNum; i++)
			selected[i] = 0;

		for (int i = 0; i < friendNum; i++) {
			scanf("%d %d", &f1, &f2);
			friendList.push_back(make_pair(f1, f2));
		}

		printf("%d\n", FindFriendsLineWay(friendList, selected));
		ways = 0;
		friendList.clear();
		delete[] selected;
	}

	return 0;
}

int FindFriendsLineWay(vector<pair<int, int>>& list, int * prevSelected, int selectedNum, int current) {

	if (current >= friendNum)
		return ways;

	int * currentSelected = new int[studentNum];
	memcpy(currentSelected, prevSelected, studentNum * sizeof(int));

	if ((currentSelected[list[current].first] != 1) && (currentSelected[list[current].second] != 1)) {
		currentSelected[list[current].first] = 1;
		currentSelected[list[current].second] = 1;
		selectedNum++;

		if (selectedNum == (studentNum / 2)) {
			ways++;
			return ways;
		}

		FindFriendsLineWay(list, currentSelected, selectedNum, current + 1);

		currentSelected[list[current].first] = 0;
		currentSelected[list[current].second] = 0;
		selectedNum--;
	}

	FindFriendsLineWay(list, currentSelected, selectedNum, current + 1);
	delete[] currentSelected;
	return ways;
}
*/

// 책의 답
int n;
bool areFriends[10][10];

int countPairings(bool taken[10]) {
	int firstFree = -1;
	for (int i = 0; i < n; i++) {
		if (!taken[i]) {
			firstFree = i;
			break;
		}
	}
	if (firstFree == -1) return 1;
	int ret = 0;

	for (int pairWith = firstFree + 1; pairWith < n; ++pairWith) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[pairWith] = false;
		}
	}
	return ret;
}