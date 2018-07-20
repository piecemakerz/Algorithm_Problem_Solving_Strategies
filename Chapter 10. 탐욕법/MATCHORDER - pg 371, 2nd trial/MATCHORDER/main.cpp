#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int C, N;
vector<int> koreanScore;
vector<int> russianScore;

//���� ���� ���ϱ� ������ �ذ��ϴ� �� Ž���� �˰���
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

//���� ���� ���ϱ� ������ �ذ��ϴ� å�� Ž���� �˰���
//���� �������� ���� �������� �������� ���� �˻� Ʈ���� multiset<int>
//�� �����Ͽ� �̱� �� �ִ� ���� �������� ���� ������ ã�� �۾���
//������ ������ �������� �����ϴ� �۾� ���� ��� O(lgn)�� ������ �� �ִ�.
int order(const vector<int>& russian, const vector<int>& korean) {
	int n = russian.size(), wins = 0;
	//���� ���� �ִ� �������� ������
	multiset<int> ratings(korean.begin(), korean.end());
	for (int rus = 0; rus < n; rus++) {
		//���� �������� ���� �ѱ� ������ �̱� �� ���� ���
		//���� �������� ���� ������ ����Ų��.
		if (*ratings.rbegin() < russian[rus])
			ratings.erase(ratings.begin());
		//�� ���� ��� �̱� �� �ִ� ���� �� ���� �������� ���� ������ ����Ų��.
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