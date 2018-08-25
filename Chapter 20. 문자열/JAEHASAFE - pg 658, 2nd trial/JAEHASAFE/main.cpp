#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int C, N;

//내 풀이. 반시계 방향으로 돌리는 경우는 단순히 dial에서 nextState를
//찾는 연산으로 표현할 수 있으나, 시계 방향으로 돌리는 경우는 dial과 
//nextState를 뒤집어 계산하는 것으로 표현하였다.
int solve(int n) {
	int ret = 0;
	string curState, nextState, dial;
	cin >> curState;
	for (int i = 0; i < n; i++) {
		cin >> nextState;
		dial = curState + curState;
		curState = nextState;

		if (i % 2 == 0) {
			reverse(dial.begin(), dial.end());
			reverse(nextState.begin(), nextState.end());
		}
		ret += dial.find(nextState);
	}
	return ret;
}

//KMP 알고리즘을 이용해 부분 일치 테이블을 생성하기
//N에서 자기 자신을 찾으면서 나타나는 부분 일치를 이용해 pi[]를 계산한다.
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
	return ret;
}

//재하의 금고 문제를 해결하는 책의 알고리즘.
//original을 반시계 방향으로 돌려 target을 만들기 위해 
//금고를 돌려야 하는 수를 반환한다. KMP 알고리즘을 직접적으로 사용하였다.
int shift(const string& original, const string& target) {
	return kmpSearch(original + original, target)[0];
}

int bookSolve(int n) {
	int ret = 0;
	string curState, nextState;
	cin >> curState;
	for (int i = 0; i < n; i++) {
		cin >> nextState;
		//시계 방향으로 회전할 경우
		if (i % 2)
			ret += shift(nextState, curState);
		//반시계 방향으로 회전할 경우
		else
			ret += shift(curState, nextState);

		curState = nextState;
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N;
		cout << solve(N) << endl;
	}
}