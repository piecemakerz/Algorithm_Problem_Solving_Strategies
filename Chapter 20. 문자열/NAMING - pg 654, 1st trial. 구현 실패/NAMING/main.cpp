#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

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

//s의 접두사도 되고 접미사도 되는 문자열들의 길이를 반환한다.
vector<int> getPrefixSuffix(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);
	int k = s.size();
	while (k > 0) {
		//s[...k-1]는 답이다.
		ret.push_back(k);
		k = pi[k - 1];
	}
	return ret;
}