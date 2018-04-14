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

//내 풀이
//부분 일치 테이블을 통해 모든 접두사에 대한 확인을 하는 것은 피할 수 있었으나,
//여전히 일치할 '가능성'이 있는 모든 접두사에 대해 S와의 비교를 하므로
//문제의 제한시간을 맞추지 못해 시간 초과가 발생한다.
vector<int> naming(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);

	int begin = 1, matched = 0;
	int n = s.length();
	ret.push_back(n);

	while (begin < n) {
		if (begin + matched < n && s[begin + matched] == s[matched]) {
			matched++;
			if (begin + matched == n)
				ret.push_back(matched);
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				//matched = pi[matched - 1]; // 이 부분 때문에 내 알고리즘이 동작하지 않았다. 
				//KMP알고리즘에서는 부분 문자열 검색이 목적이고, matched까지는 비교할 필요 없이 무조건 일치하므로
				//matched를 pi[matched-1]로 설정해 두었으나, 이 알고리즘의 목적은 접미사도 되고 접두사도 되는 문자열들의
				//길이를 전부 출력하는 것이므로 matched를 0으로 두어야 한다.
				matched = 0;
			}
		}
	}
	return ret;
}

//책의 답

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

int main(void) {
	string father;
	string mother;
	cin >> father >> mother;
	vector<int> result = naming(father + mother);
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i] << ' ';
	cout << endl;
	return 0;
}