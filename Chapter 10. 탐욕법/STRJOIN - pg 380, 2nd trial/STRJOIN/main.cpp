#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int c, n;
vector<int> strlist;

//문자열 합치기 문제를 해결하는 내 탐욕적 알고리즘
int strjoin() {
	int result = 0;
	while (strlist.size() != 1) {
		sort(strlist.begin(), strlist.end(), greater<int>());
		int len = strlist.size() - 1;
		int sum = strlist[len] + strlist[len - 1];
		result += sum;
		strlist.pop_back(); strlist.pop_back();
		strlist.push_back(sum);
	}
	return result;
}

//문자열 합치기 문제를 해결하는 책의 탐욕적 알고리즘
//우선순위 큐를 사용하여 알고리즘의 동작시간을 최적화했다.

//문자열들의 길이가 주어질 때 하나로 합치는 최소 비용을 반환한다.
int concat(const vector<int>& lengths) {
	//최소 큐를 선언한다.
	priority_queue<int, vector<int>, greater<int>()> pq;
	for (int i = 0; i < lengths.size(); i++)
		pq.push(lengths[i]);
	int ret = 0;
	//원소가 하나 남은 동안 반복한다.
	while (pq.size() > 1) {
		//가장 짧은 문자열 두 개를 찾아서 합치고 큐에 넣는다.
		int min1 = pq.top(); pq.pop();
		int min2 = pq.top(); pq.pop();
		pq.push(min1 + min2);
		ret += min1 + min2;
	}
	return ret;
}

int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		cin >> n;
		int input;
		for (int i = 0; i < n; i++) {
			cin >> input;
			strlist.push_back(input);
		}
		cout << strjoin() << endl;
		strlist.clear();
	}
	return 0;
}