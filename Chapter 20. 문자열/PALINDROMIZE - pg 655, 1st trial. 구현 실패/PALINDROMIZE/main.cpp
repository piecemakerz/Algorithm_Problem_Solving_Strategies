#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C;

//pi[i] = N[...i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
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


//내 답.
int kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> pi = getPartialMatch(N);
	int begin = 0, matched = 0;
	while (begin < n) {
		if ((begin + matched) < n && H[begin + matched] == N[matched]) {
			matched++;
			if (begin + matched == n) return matched;
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

int palindromize(const string& str) {
	int n = str.length();
	string revStr = str;
	reverse(revStr.begin(), revStr.end());
	return 2 * n - kmpSearch(str, revStr);
}

//책의 답
//a의 접미사이면서 b의 접두사인 문자열의 최대 길이를 구한다.
int maxOverlap(const string& a, const string& b) {
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);
	//begin = matched = 0에서부터 시작하자.
	int begin = 0, matched = 0;
	while (begin < n) {
		//만약 a의 해당 글자가 b의 해당 글자와 같다면
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
	for (int testCase = 0; testCase < C; testCase++) {
		string inputStr;
		cin >> inputStr;
		cout << palindromize(inputStr) << endl;
	}
	return 0;
}