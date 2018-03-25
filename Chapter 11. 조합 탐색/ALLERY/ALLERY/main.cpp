#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <functional>
using namespace std;

const int INF = 987654321;
int T, n, m;
vector<string> friends;
vector<int> food[50];//i번째 음식을 먹을 수 있는 친구 목록
int checked[50]; //i번째 음식을 확인했는지 여부
int friendEat[50]; //i번째 친구가 이미 먹을 수 있는 음식이 있는지의 여부
int best;
	
//아직 먹을 수 있는 음식이 없는 사람들을 가장 많이 먹게 할 수 있는 음식 순으로 정렬.
/*vector<pair<int,int>> arrangeMostUncommon() {
	vector<pair<int,int>> foodCount(m);//겹치는 음식의 수
	for (int i = 0; i < m; i++)
		foodCount[i] = make_pair(0, i);

	for (int i = 0; i < m; i++) //i번째 음식
		for (int j = 0; j < food[i].size(); j++)
			if(friendEat[food[i][j]] == 0) //아직 i번째 음식을 먹지 않았다면
				foodCount[i].first -= 1;
	sort(foodCount.begin(), foodCount.end());

	return foodCount;
}
*/
void arrangeFood() {
	for (int i = 0; i < m - 1; i++)
		for (int j = i + 1; j < m; j++)
			if (food[i].size() < food[j].size())
				swap(food[i], food[j]);
}

int canEverybodyEat(int * ret) {
	for (int i = 0; i < n; i++)
		if (ret[i] == 0)
			return false;
	return true;
}

/*void allergy(int choose) {
	//기저 사례: 현재 선택한 음식 수가 최적의 답 이상이라면 리턴
	if (choose >= best)
		return;
	//기저 사례: 모든 친구들이 먹을 수 있다면 답 갱신
	if (canEverybodyEat() || choose >= m) {
		best = min(best, choose);
		return;
	}

	vector<pair<int,int>> foodOrder = arrangeMostUncommon();

	for (int i=0; i < foodOrder.size(); i++) {
		int curFood = foodOrder[i].second;
		//이미 음식을 골랐다면 체크 안함
		if (chosen[curFood])
			continue;
		//curFood번 음식 고르기
		for (int i = 0; i < food[curFood].size(); i++)
			friendEat[food[curFood][i]] += 1;
		chosen[curFood] = 1;
		//재귀호출
		allergy(choose + 1);

		chosen[curFood] = 0;
		for (int i = 0; i < food[curFood].size(); i++)
			friendEat[food[curFood][i]] -= 1;
	}
	return;
}
*/
bool heuristic(int curFood) {
	int ret[50];
	for(int i=0; i<n; i++)
		ret[i] = friendEat[i];

	for (int i = curFood; i < m; i++) {
		if (checked[i])
			continue;
		for (int j = 0; j < food[i].size(); j++)
			ret[food[i][j]] += 1;
	}
	return canEverybodyEat(ret);
}

void allergy(int choose, int curFood) {
	//기저 사례: 현재 선택한 음식 수가 최적의 답 이상인 경우 리턴
	if (choose >= best)
		return;
	//기저 사례: 모든 친구들이 먹을 수 있다면 답 갱신
	if (canEverybodyEat(friendEat)) {
		best = min(best, choose);
		return;
	}
	//기저 사례: 모든 음식을 검색해봤을 경우 리턴
	if (curFood >= m)
		return;

	//남은 음식들을 모두 만든다고 해도 모든 친구들이 먹을 수 없을 때 리턴
	if (!heuristic(curFood)) {
		cout << "curFood: " << curFood << endl;
		return;
	}
	checked[curFood] = 1;
	//curFood를 고르는 경우
	for (int i = 0; i < food[curFood].size(); i++)
		friendEat[food[curFood][i]] += 1;
	allergy(choose + 1, curFood + 1);

	//curFood를 고르지 않는 경우
	for (int i = 0; i < food[curFood].size(); i++)
		friendEat[food[curFood][i]] -= 1;
	allergy(choose, curFood + 1);
	return;
}

int main(void) {
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		memset(checked, 0, sizeof(checked));
		memset(friendEat, 0, sizeof(friendEat));
		best = INF;
		string inputStr;
		int canEatCount;
		cin >> n >> m; // n = 친구 수, m = 음식 수

		for (int i = 0; i < n; i++) {
			cin >> inputStr;
			friends.push_back(inputStr);
		}

		for (int i = 0; i < m; i++) {
			cin >> canEatCount;
			for (int j = 0; j < canEatCount; j++) {
				cin >> inputStr;
				for (int k = 0; k < n; k++)
					if (!inputStr.compare(friends[k])) {
						food[i].push_back(k);
						break;
					}
			}
		}

		arrangeFood();
		allergy(0,0);
		cout << best << endl;
		for (int i = 0; i < m; i++)
			food[i].clear();
		friends.clear();
	}
	return 0;
}