#include <iostream>
#include <vector>
#include <string>
using namespace std;

//단순한 문자열 검색 알고리즘의 구현
//H의 부분 문자열로 N문자열이 출현하는 시작 위치들을 모두 반환한다.
vector<int> naiveSearch(const string& H, const string& N) {
	vector<int> ret;
	//모든 시작 위치를 다 시도해 본다.
	for (int begin = 0; begin + N.size() <= H.size(); begin++) {
		bool matched = true;
		for(int i=0; i<N.size(); i++)
			if (H[begin + i] != N[i]) {
				matched = false;
				break;
			}
		if (matched) ret.push_back(begin);
	}
	return ret;
}

//커누스-모리스-프랫(KMP) 문자열 검색 알고리즘의 구현
//H의 부분 문자열로 N이 출현하는 시작 위치들을 모두 반환한다.
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	//pi[i] = N[..i]의 접미사도 되고 접두사도 되는 문자열의 최대 길이
	vector<int> pi = getPartialMatch(N);
	//begin = matched = 0에서부터 시작하자.
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		//만약 H의 해당 글자가 N의 해당 글자와 같다면
		if (matched < m && H[begin + matched] == N[matched]) {
			matched++;
			//결과적으로 m글자가 모두 일치했다면 답에 추가한다.
			if (matched == m) ret.push_back(begin);
		}
		else{
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
	return ret;
}