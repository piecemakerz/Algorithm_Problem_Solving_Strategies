#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C;

//내 답. 시간초과가 발생한다.
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

/*
bool kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	//pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
	vector<int> pi = getPartialMatch(N);
	//begin = matched = 0에서부터 시작하자.
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		//만약 H의 해당 글자가 N의 해당 글자와 같다면
		if (matched < m && H[begin + matched] == N[matched]) {
			matched++;
			//결과적으로 m글자가 모두 일치했다면 답에 추가한다.
			if (matched == m) return true;
		}
		else {
			//예외: matched가 0인 경우에는 다음 칸에서부터 계속
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				//begin을 옮겼다고 처음부터 다시 비교할 필요가 없다.
				//옮긴 후에도 pi[matched-1]만큼은 항상 일치하기 때문이다.
				matched = pi[matched - 1];
			}
		}
	}
	return false;
}

int palindromize(const string& str) {
	int n = str.length();
	string revStr = str;
	reverse(revStr.begin(), revStr.end());
	int maxPand = 0;
	for (int i = 1; i <= n; i++) {
		string partialStr = revStr.substr(0, i);
		int m = partialStr.length();
		if (!kmpSearch(str, partialStr))
			break;

		maxPand = max(m, maxPand);
	}
	return 2 * n - maxPand;
}*/

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
