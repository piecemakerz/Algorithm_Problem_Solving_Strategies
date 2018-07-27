#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int MAX = 987654321;
int T, n, m;
vector<string> friends;
vector<vector<int>> foods;
int maxKind;
int minRes;

//여태까지 음식을 못 먹은 친구들 중 해당 음식을 먹을 수 
//있는 친구가 한 명이라도 있다면 true를 반환한다.
bool canAnyoneEat(int curFood, long long friendState) {
	for (int i = 0; i < foods[curFood].size(); i++) {
		if ((friendState & (1ULL << foods[curFood][i])) == 0)	
			return true;
	}
	return false;
}

void findMinFoods(int curFood, long long curFriendState, int selected) {
	//기저 사례: 모든 친구들이 음식을 먹을 수 있을 경우
	if (curFriendState == ((1ULL << n) - 1)) {
		minRes = min(minRes, selected);
		return;
	}
	//기저 사례: 모든 음식을 체크했을 경우
	if (curFood == m)
		return;

	int friendsRemaining = 0;
	for (int i = 0; i < n; i++)
		if ((curFriendState & (1ULL << i)) == 0)
			friendsRemaining++;

	//간단한 가지치기: 
	if (selected + ceil((double)friendsRemaining / maxKind) >= minRes)
		return;

	//해당 음식을 만드는 경우
	if (canAnyoneEat(curFood, curFriendState)) {
		long long nextState = curFriendState;
		for (int i = 0; i < foods[curFood].size(); i++)
			nextState |= (1ULL << foods[curFood][i]);
		findMinFoods(curFood + 1, nextState, selected + 1);
	}

	//해당 음식을 만들지 않는 경우
	findMinFoods(curFood + 1, curFriendState, selected);
}

//알러지 문제를 해결하는 책의 첫 번째 조합 탐색 알고리즘

//eaters[food] = food를 먹을 수 있는 친구들의 번호
vector<int> eaters[50];
int best;
//food: 이번에 고려해야 할 음식의 번호
//edible: 지금까지 고른 음식 중 i번 친구가 먹을 수 있는 음식의 수
//chosen: 지금까지 고른 음식의 수
void slowSearch(int food, vector<int>& edible, int chosen) {
	//간단한 가지치기
	if (chosen >= best) return;
	//기저 사례: 모든 음식에 대해 만들지 여부를 결정했으면,
	//모든 친구가 음식을 먹을 수 있는지 확인하고 그렇다면 최적해를 갱신한다.
	if (food == m) {
		if (find(edible.begin(), edible.end(), 0) == edible.end())
			best = chosen;
		return;
	}
	//food를 만들지 않는 경우
	slowSearch(food + 1, edible, chosen);
	//food를 만드는 경우
	for (int j = 0; j < eaters[food].size(); j++)
		edible[eaters[food][j]]++;
	slowSearch(food + 1, edible, chosen + 1);

	for (int j = 0; j < eaters[food].size(); j++)
		edible[eaters[food][j]]--;
}

//알러지 문제를 해결하는 두 번째 조합 탐색 알고리즘
int n, m;
//canEat[i]: i번 친구가 먹을 수 있는 음식의 집합
//eaters[i]: i번 음식을 먹을 수 있는 친구들의 집합
vector<int> canEat[50], eaters[50];
int best;
//chosen: 지금까지 선택한 음식의 수
//edible[i]: 지금까지 고른 음식 중 i번 친구가 먹을 수 있는 음식의 수
void search(vector<int>& edible, int chosen) {
	//간단한 가지치기
	if (chosen >= best) return;
	//아직 먹을 음식이 없는 첫 번째 친구를 찾는다.
	int first = 0;
	while (first < n && edible[first]>0) first++;
	//모든 친구가 먹을 음식이 있는 경우 종료한다.
	if (first == n) { best = chosen; return; }
	//이 친구가 먹을 수 있는 음식을 하나 만든다.
	for (int i = 0; i < canEat[first].size(); i++) {
		int food = canEat[first][i];
		for (int j = 0; j < eaters[food].size(); j++)
			edible[eaters[food][j]]++;
		search(edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); j++)
			edible[eaters[food][j]]--;
	}
}
int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		maxKind = 0, minRes = MAX;
		int kinds; string name;
		cin >> n >> m;
		friends = vector<string>(n);
		foods = vector<vector<int>>(m);

		for (int i = 0; i < n; i++)
			cin >> friends[i];
		for(int i = 0; i < m; i++) {
			cin >> kinds;
			maxKind = max(maxKind, kinds);
			for (int j = 0; j < kinds; j++) {
				cin >> name;
				foods[i].push_back(find(friends.begin(), friends.end(), name) - friends.begin());
			}
		}

		findMinFoods(0, 0, 0);
		cout << minRes << endl;
		friends.clear();
		for (int i = 0; i < foods.size(); i++)
			foods[i].clear();
		foods.clear();
	}
}