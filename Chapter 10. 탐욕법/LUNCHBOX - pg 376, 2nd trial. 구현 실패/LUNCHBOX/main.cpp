#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_N = 10000;
int n, e[MAX_N], m[MAX_N];
int heat() {
	//어느 순서로 데워야 할지를 정한다.
	vector<pair<int, int>> order;
	for (int i = 0; i < n; i++)
		order.push_back(make_pair(e[i], i));
	sort(order.begin(), order.end(), greater<int>());
	//해당 순서대로 데워먹는 과정을 시뮬레이션한다.
	int ret = 0, beginEat = 0;
	for (int i = 0; i < n; i++) {
		int box = order[i].second;
		beginEat += m[box];
		ret = max(ret, beginEat + e[box]);
	}
	return ret;
}