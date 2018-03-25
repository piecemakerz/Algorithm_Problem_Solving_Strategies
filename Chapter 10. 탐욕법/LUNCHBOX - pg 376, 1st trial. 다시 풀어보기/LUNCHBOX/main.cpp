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
	//�������� ����. �Դ� �ð� ������ �������� ������ ��, �Դ� �ð��� ���ٸ� 
	//����� �ð� ������ �������� �����Ѵ�.
	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (lunchbox[i].first < lunchbox[j].first)
				swap(lunchbox[i], lunchbox[j]);
			else if (lunchbox[i].first == lunchbox[j].first)
				if (lunchbox[i].second > lunchbox[j].second)
					swap(lunchbox[i], lunchbox[j]);
		}
	}

	int timeSpent = lunchbox[0].second; // ������� �Ҹ�� �ð�
	int maxEattime = lunchbox[0].first; // ������� ���� '�Դµ� �ɸ��� �ð�'�� �ִ�
	for (int i = 1; i < n; i++) {
		timeSpent += lunchbox[i].second;
		maxEattime = max(maxEattime - lunchbox[i].second, lunchbox[i].first);
	}
	timeSpent += maxEattime;
	return timeSpent;
}

//å�� Ǯ��. �� Ǯ�̿� ���� ����ϳ�, '�Դ� �ð��� ������ ����� �ð��� ������������ �����Ѵ�'
//�� ������ �����ߴ�. �� ���������� ������� �ʾƵ� �Ǵ� �����̴�.
int heat() {
	//��� ������ ������ ������ ���Ѵ�.
	vector<pair<int, int>> order;
	for (int i = 0; i < n; i++)
		order.push_back(make_pair(-e[i], i));
	//�Դ� �ð��� ������������ �����Ѵ�.
	sort(order.begin(), order.end());
	//�ش� ������� �����Դ� ������ �ùķ��̼��Ѵ�.
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