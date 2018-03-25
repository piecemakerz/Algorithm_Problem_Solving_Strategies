#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <cstdlib>
using namespace std;
int C, n;

//완전탐색 알고리즘.
int brute(const vector<int>& russian, vector<int> korean) {
	sort(korean.begin(), korean.end());
	int ret = 0;
	do {
		int wins = 0;
		for (int i = 0; i < korean.size(); i++)
			if (korean[i] >= russian[i])
				wins++;
		ret = max(wins, ret);
	} while (next_permutation(korean.begin(), korean.end())); // 모든 순서 조합 생성
	return ret;
}

//동적계획법 알고리즘
//각 한국팀 선수를 이미 순서에 추가했는지의 여부가 taken에 주어질 때,
//남은 선수들을 직접 배치해서 얻을 수 있는 최대 승수
int cache[(1 << 20)+1]; // n<=100인데, 이런 형태의 캐시를 사용하면 메모리가 너무 많이 필요하다. 이 경우 bool 타입의 캐시 배열을 사용하는 것이 좋다.
int order(const vector<int>& russian, const vector<int>& korean, int taken) {
	if (taken == (1 << n) - 1)
		return 0;

	int& ret = cache[taken];
	if (ret != -1)
		return ret;

	ret = 0;
	int curRus = 0;
	for (int i = 0; i < n; i++)
		if ((taken >> i) % 2 == 1)
			curRus++;

	for (int i = 0; i < n; i++)
		if ((taken >> i) % 2 == 0) {
			ret = max(ret, (russian[curRus] <= korean[i] ? 1 : 0) + order(russian, korean, taken + (1 << i)));
		}
	return ret;
}

//내가 짠 알고리즘. 한국팀과 러시아팀의 레이팅 배열을 각각 오름차순으로 정렬한 후,
//한국팀의 최고 레이팅이 러시아의 최고 레이팅보다 더 작다면 더 커질때 까지 한국팀의 최소 레이팅과
//러시아의 최고 레이팅이 경기를 치르게 하고, 이후에는 한국의 남은 선수들 모두가 우승을
//한다라고 생각했기 때문이 이 알고리즘을 작성했다.
//하지만 이 알고리즘은 russian = {3,3,4,7,8}, korean = {1,2,3,8,9}의 예에서처럼 정상적인 값을 반환하지 않는다.
int matchorder(vector<int>& russian, vector<int>& korean) {
	sort(russian.begin(), russian.end());
	sort(korean.begin(), korean.end());
	int cmpPos = 0;
	while (cmpPos <= n-1 && russian[n - 1 - cmpPos] > korean[n - 1])
		cmpPos++;
	return n - cmpPos;
}

//책의 답.
int order(const vector<int>& russian, const vector<int>& korean) {
	int n = russian.size(), wins = 0;
	//아직 남아 있는 선수들의 레이팅
	multiset<int> ratings(korean.begin(), korean.end());
	for (int rus = 0; rus < n; rus++) {
		//가장 레이팅이 높은 한국 선수가 이길 수 없는 경우
		//가장 레이팅이 낮은 선수와 경기시킨다.
		if (*ratings.rbegin() < russian[rus])
			ratings.erase(ratings.begin());
		//이 외의 경우 이길 수 있는 선수 중 가장 레이팅이 낮은 선수와 경기시킨다.
		else {
			ratings.erase(ratings.lower_bound(russian[rus]));
			wins++;
		}
	}
	return wins;
}
int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		vector<int> russian, korean;
		cin >> n;
		int input;
		for (int i = 0; i < n; i++) {
			cin >> input;
			russian.push_back(input);
		}
		for (int i = 0; i < n; i++) {
			cin >> input;
			korean.push_back(input);
		}
		memset(cache, -1, sizeof(cache));
		cout << brute(russian, korean) << endl;
		cout << order(russian, korean,0) << endl;
		russian.clear();
		korean.clear();
	}
}