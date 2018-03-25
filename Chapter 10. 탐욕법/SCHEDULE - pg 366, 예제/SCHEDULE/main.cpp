#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//각 회의는 [begin, end) 구간 동안 회의실을 사용한다.
int n;
int meetBegin[100], meetEnd[100];
//탐욕법을 사용한 알고리즘
int schedule() {
	//일찍 끝나는 순서대로 정렬한다.
	vector<pair<int, int>> order;
	for (int i = 0; i < n; i++)
		order.push_back(make_pair(meetEnd[i], meetBegin[i]));
	sort(order.begin(), order.end()); // order의 첫 번째 원소인 meetEnd[]를 기준으로 정렬
	//earliest: 다음 회의가 시작할 수 있는 가장 빠른 시간
	//selected: 지금까지 선택한 회의의 수
	int earliest = 0, selected = 0;
	for (int i = 0; i < order.size(); i++) {
		int meetingBegin = order[i].second, meetingEnd = order[i].first;
		if (earliest <= meetingBegin) {
			//earliest를 마지막 회의가 끝난 시간 이후로 갱신한다.
			earliest = meetingEnd;
			++selected;
		}
	}
	return selected;
}

int before[100];
//동적 계획법을 사용한 알고리즘
//schedule(int idx) = order[idx] 혹은 그 이전에 끝나는 회의들 중 선택할 수 있는 최대 회의의 수.
int schedule(int idx) { // n-1부터 시작
	if (idx == -1)
		return 0;

	int ret = 0;
	if(idx > 0)
		ret = schedule(idx - 1); // order[idx] 선택하지 않음
	ret = max(ret, 1 + schedule(before[idx])); // order[idx] 선택
	return ret;
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> meetBegin[i] >> meetEnd[i];

	/*vector<pair<int, int>> myorder;
	for (int i = 0; i < n; i++)
		myorder.push_back(make_pair(meetEnd[i], meetBegin[i]));
	sort(myorder.begin(), myorder.end());
	memset(before, -1, sizeof(before));
	for (int i = n - 1; i >= 0; i--)
		for (int j = i - 1; j >= 1; j--) {
			if (myorder[j].first <= myorder[i].second) {
				before[i] = j;
				break;
			}
		}
	*/
	cout << schedule() << endl;
}