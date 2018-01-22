#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#define MENU_NUM 6
#define PEOPLE_NUM 4

using namespace std;
const int INF = 987654321;

int people[PEOPLE_NUM][MENU_NUM] = {
	{ 0,1,1,1,0,0 },
	{ 0,0,0,0,1,1 },
	{ 1,0,1,0,1,0 },
	{ 1,1,0,0,0,1 }
};

bool canEverybodyEat(const vector<int>& menu) {
	int canEatNum = 0;

	for (int i = 0; i < PEOPLE_NUM; i++) {
		for (int j = 0; j < menu.size(); j++) {
			if (people[i][menu[j]] == 1) {
				canEatNum++;
				break;
			}
		}
	}

	if (canEatNum == PEOPLE_NUM)
		return true;
	else
		return false;
}

int selectMenu(vector<int>& menu, int food) {
	if (food == MENU_NUM) {
		if (canEverybodyEat(menu)) return menu.size();
		return INF;
	}

	int ret = selectMenu(menu, food + 1);
	menu.push_back(food);
	ret = min(ret, selectMenu(menu, food + 1));
	menu.pop_back();
	return ret;
}

int main(void) {
	vector<int> menu;
	cout << selectMenu(menu, 0) << endl;
	return 0;
}