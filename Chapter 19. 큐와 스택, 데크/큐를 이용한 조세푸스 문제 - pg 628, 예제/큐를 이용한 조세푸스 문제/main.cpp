#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int C, N, K;

void suicide(queue<int>& soldiers) {
	int next = 0, listSize = soldiers.size();

	while (listSize > 2) {
		soldiers.pop();
		for (int i = 0; i < K - 1; i++) {
			int delNum = soldiers.front();
			soldiers.pop();
			soldiers.push(delNum);
		}
		listSize--;
	}
	int ret1 = soldiers.front(), ret2 = soldiers.back();
	if (ret1 > ret2) swap(ret1, ret2);
	cout << ret1 << ' ' << ret2 << endl;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N >> K;
		queue<int> soldiers;
		for (int i = 1; i <= N; i++)
			soldiers.push(i);
		suicide(soldiers);
	}
}