#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int C;

//KMP 알고리즘을 이용해 부분 일치 테이블 생성
vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	//KMP로 자기 자신을 찾는다.
	//N을 N에서 찾는다. begin=0이면 자기 자신을 찾아버리니 제외한다.
	int begin = 1, matched = 0;
	//비교할 문자가 N의 끝에 도달할 때까지 찾으면서 부분 일치를 모두 기록한다.
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

//팰린드롬 만들기 문제를 해결하는 내 알고리즘.
//KMP 문자열 검색 알고리즘을 응용하였다.
int solve(const string& str) {
	string revStr = str;
	reverse(revStr.begin(), revStr.end());
	vector<int> pi = getPartialMatch(revStr);

	int begin = 0, matched = 0;
	int n = revStr.length();

	while ((begin + matched) < n) {
		if (matched < n && str[begin + matched] == revStr[matched]) {
			matched++;
			if (begin + matched == n)
				return matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}

//팰린드롬 만들기 문제를 해결하는 책의 KMP 알고리즘의 변형
//a의 접미사이면서 b의 접두사인 문자열의 최대 길이를 구한다.
int maxOverlap(const string& a, const string& b) {
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);
	//begin = matched = 0에서부터 시작하자.
	int begin = 0, matched = 0;
	while (begin < n) {
		//만약 짚더미의 해당 글자가 바늘의 해당 글자와 같다면
		if (matched < m && a[begin + matched] == b[matched]) {
			matched++;
			if (begin + matched == n)
				return matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		string inputStr;
		cin >> inputStr;
		cout << 2 * inputStr.length() - solve(inputStr) << endl;
	}
}