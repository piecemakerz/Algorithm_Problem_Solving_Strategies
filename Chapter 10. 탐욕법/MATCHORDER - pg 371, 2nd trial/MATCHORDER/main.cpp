#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int C, N;
vector<int> koreanScore;
vector<int> russianScore;

//출전 순서 정하기 문제를 해결하는 내 탐욕적 알고리즘
int matchorder() {
	int kStart = 0, rStart = 0;
	int kEnd = N-1, rEnd = N-1;
	int wins = 0;

	while(kStart <= kEnd && rStart <= rEnd){
		if (koreanScore[kStart] >= russianScore[rStart]) {
			kStart++; rStart++;
			wins++;
		}
		else {
			kStart++; rEnd--;
		}
	}
	return wins;
}	

//출전 순서 정하기 문제를 해결하는 책의 탐욕적 알고리즘
//아직 출전하지 않은 선수들의 레이팅을 이진 검색 트리인 multiset<int>
//에 저장하여 이길 수 있는 가장 레이팅이 낮은 선수를 찾는 작업과
//선택한 선수의 레이팅을 삭제하는 작업 등을 모두 O(lgn)에 수행할 수 있다.
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
	for (int test = 0; test < C; test++) {
		int input;
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> input;
			russianScore.push_back(input);
		}
		for (int i = 0; i < N; i++) {
			cin >> input;
			koreanScore.push_back(input);
		}
		sort(russianScore.begin(), russianScore.end());
		sort(koreanScore.begin(), koreanScore.end());
		cout << matchorder() << endl;

		russianScore.clear();
		koreanScore.clear();
	}
	return 0;
}