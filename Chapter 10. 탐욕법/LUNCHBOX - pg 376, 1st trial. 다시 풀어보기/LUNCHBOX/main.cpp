#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int C, n;
int e[10000], m[10000];
int leastTime() {
	vector<pair<int, int>> lunchbox(n);
	for (int i = 0; i < n; i++) {
		lunchbox[i].first = e[i];
		lunchbox[i].second = m[i];
	}
	//내림차순 정렬. 먹는 시간 순으로 내림차순 정렬한 뒤, 먹는 시간이 같다면 
	//데우는 시간 순으로 오름차순 정렬한다.
	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (lunchbox[i].first < lunchbox[j].first)
				swap(lunchbox[i], lunchbox[j]);
			else if (lunchbox[i].first == lunchbox[j].first)
				if (lunchbox[i].second > lunchbox[j].second)
					swap(lunchbox[i], lunchbox[j]);
		}
	}

	int timeSpent = lunchbox[0].second; // 현재까지 소모된 시간
	int maxEattime = lunchbox[0].first; // 현재까지 남은 '먹는데 걸리는 시간'중 최댓값
	for (int i = 1; i < n; i++) {
		timeSpent += lunchbox[i].second;
		maxEattime = max(maxEattime - lunchbox[i].second, lunchbox[i].first);
	}
	timeSpent += maxEattime;
	return timeSpent;
}

//책의 풀이. 내 풀이와 거의 비슷하나, '먹는 시간이 같으면 데우는 시간의 오름차순으로 정렬한다'
//의 과정을 생략했다. 이 문제에서는 고려하지 않아도 되는 조건이다.
int heat() {
	//어느 순서로 데워야 할지를 정한다.
	vector<pair<int, int>> order;
	for (int i = 0; i < n; i++)
		order.push_back(make_pair(-e[i], i));
	//먹는 시간의 오름차순으로 정렬한다.
	sort(order.begin(), order.end());
	//해당 순서대로 데워먹는 과정을 시뮬레이션한다.
	int ret = 0, beginEat = 0;
	for (int i = 0; i < n; i++) {
		int box = order[i].second;
		beginEat += m[box];
		ret += max(ret, beginEat + e[box]);
	}
	return ret;
}
int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> m[i];
		for (int i = 0; i < n; i++)
			cin >> e[i];
		cout << leastTime() << endl;
	}
}