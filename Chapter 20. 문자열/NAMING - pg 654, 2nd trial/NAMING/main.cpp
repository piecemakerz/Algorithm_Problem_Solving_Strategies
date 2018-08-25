#include <iostream>
#include <string>
#include <vector>
using namespace std;

//KMP 알고리즘을 이용해 부분 일치 테이블 생성
vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	//KMP로 자기 자신을 찾는다.
	//N을 N에서 찾는다. begin = 0이면 자기 자신을 찾아버리므로 안됨.
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
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

//내 풀이. 부분 일치 테이블을 구했다면 str의 접두사도 되고 접미사도 되는
//문자열들을 구할 수 있다.
vector<int> solve(const string& str) {
	int n = str.length();
	vector<int> names;
	vector<int> pi = getPartialMatch(str);
	names.push_back(n);

	int curSize = n;
	while (true) {
		curSize = pi[curSize - 1];
		if (curSize == 0)
			break;
		names.push_back(curSize);
	}
	return names;
}

//S의 접두사도 되고 접미사도 되는 모든 문자열의 길이를 계산하는 책의 알고리즘
vector<int> getPrefixSuffix(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);
	int k = s.size();
	while (k > 0) {
		//s[...k-1]는 답이다.
		ret.push_back(k);
		//s[...k-1]의 접미사도 되고 접두사도 되는 문자열도 답이다.
		k = pi[k - 1];
	}
	return ret;
}

int main(void) {
	string father, mother;
	cin >> father >> mother;
	vector<int> result = solve(father + mother);
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i] << ' ';
	cout << endl;
	return 0;
}