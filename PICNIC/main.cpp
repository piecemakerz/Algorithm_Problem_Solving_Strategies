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


/*책의 답

#include<cassert>
#include<vector>
#include<iostream>
#include<cstring>
using namespace std;

int n, m;
bool areFriends[10][10];

int countPairings(bool taken[10]){
	int firstFree = -1;
	for(int i=0; i<(n); i++){
		if(!taken[i]){
			firstFree = i;
			break;
		}
	}

	if(firstFree == -1) return 1;
	int ret = 0;
	for(int pairWith = (firstFree+1); pairWith < (n); pairWith++){
		if(!taken[pairWith] && areFwriends[firstFree][pairWith]){
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[pairWith] = false;
		}
	}
	return ret;
}

int main()[
	int cases;
	cin>>cases;
	while(cases--){
		cin>>n>>m;
		assert(n <= 10);
		memset(areFriends, 0, sizeof(areFriends));
		for(int i=0; i<(m); i++){
			int a,b;
			cin>>a>>b;
			assert(0<=a && a<n && 0<=b && b<n);
			assert(!areFriends[a][b]);
			areFriends[a][b] = areFriends[b][a] = true;
		}
		bool taken[10];
		memset(taken, 0, sizeof(taken));
		cout<<countPairings(taken)<<endl;
	}
}

*/

//알고스팟 제출용 답안
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>

#define MAX_NUM_STUDENTS 10

using namespace std;
int testCase;
bool Selected[MAX_NUM_STUDENTS] = { false, };
int numOfSelectedStudents = 0;
int numOfStudents, numOfFriendPairs;

int FindNumOfPairingWays(vector<pair<int, int>>& pairs, int idx = 0);

int main(void) {
	int st1, st2;

	cin >> testCase;

	for (int i = 0; i < testCase; i++) {
		cin >> numOfStudents >> numOfFriendPairs;

		vector<pair<int, int>> pairs;

		for (int i = 0; i < numOfFriendPairs; i++) {
			cin >> st1 >> st2;
			pairs.push_back(make_pair(st1, st2));
		}
		
		cout << FindNumOfPairingWays(pairs) << endl;
		numOfSelectedStudents = 0;
		for (int i = 0; i < MAX_NUM_STUDENTS; i++) {
			Selected[i] = false;
		}
	}
	return 0;
}


//해결하는데 굉장히 오래걸림.
//오류가 발생했던 코드의 경우, 선택되지 않은 학생들을 포함하고 있는 친구쌍에 대하여
//그 친구쌍을 선택하거나 선택하지 않는 두 가지 경우로 나눠 재귀호출을 했다.
//또한 선택된 학생들을 포함하고 있는 친구쌍은 return 0를 이용해 재귀호출을 생략하고 바로 리턴해 주었다.
//이 때 빠뜨린 부분은, 선택된 학생들을 포함하고 있는 친구쌍에 대해서도 선택하지 않는 경우에 대해서도
//재귀호출을 구현했어야 한다는 것이다.
//따라서, <해당 친구쌍이 선택되지 않은 학생들을 포함하고 있는 경우> => 선택하는 경우와 선택하지 않는 경우에 대해 모두 재귀호출 구현
//	      <해당 친구쌍이 선택된 학생을 포함하고 있는 경우> => 선택하지 않는 경우에 대한 재귀호출 구현
//의 형식으로 알고리즘을 구현해야 한다.

int FindNumOfPairingWays(vector<pair<int, int>>& pairs, int idx) {
	int numOfWays = 0;
	
	if (numOfSelectedStudents == numOfStudents)
		return 1;
	
	if (idx >= numOfFriendPairs)
		return 0;
	
	int std1 = pairs[idx].first, std2 = pairs[idx].second;

	if (!Selected[std1] && !Selected[std2]) {
		
		Selected[std1] = true, Selected[std2] = true;
		numOfSelectedStudents += 2;
		numOfWays += FindNumOfPairingWays(pairs, idx + 1);
		numOfSelectedStudents -= 2;
		Selected[std1] = false, Selected[std2] = false;
	}

	numOfWays += FindNumOfPairingWays(pairs, idx+1);

	return numOfWays;
}
