#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

int C, N, K;

void suicide(list<int>& soldiers) {
	int next = 0, listSize = soldiers.size();
	list<int>::iterator iter = soldiers.begin();

	while (listSize > 2) {
		iter = soldiers.erase(iter);
		if (iter == soldiers.end())
			iter = soldiers.begin();

		for (int i = 0; i < K - 1; i++) {
			iter++;
			if (iter == soldiers.end())
				iter = soldiers.begin();
		}
		listSize--;
	}
	cout << soldiers.front() << ' ' << soldiers.back() << endl;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N >> K;
		list<int> soldiers;
		for (int i = 1; i <= N; i++)
			soldiers.push_back(i);
		suicide(soldiers);
		soldiers.clear();
	}
}