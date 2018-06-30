#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int C, N;

//내 풀이. 책의 풀이 1과 유사하나 책의 풀이보다 더 복잡하다.
vector<string> matched;
string wildcard;
string str;

//isMatchable[i][j] = str[j...]를 wildcard[i...]로 표현할 수 있는가
int isMatchable[100][100];

int checkWildcard(int wildIdx, int strIdx) {
	if (wildIdx >= wildcard.length() || strIdx >= str.length())
		return 0;

	int& ret = isMatchable[wildIdx][strIdx];
	if (ret != -1)
		return ret;

	while (wildIdx < wildcard.length() && strIdx < str.length()) {
		char curWild = wildcard[wildIdx], curStr = str[strIdx];
		//문자가 같거나 ?로 처리할 수 있을 때
		if (curWild == curStr || curWild == '?') {
			wildIdx++;
			strIdx++;
		}
		//문자 * 처리하기
		//*로 0개의 문자부터 str의 끝까지 처리하는 모든 경우를 재귀호출로 처리한다.
		//다만 0개의 문자를 처리하는 경우는 현재 호출문에서 처리할 수 있으므로 
		//따로 재귀호출로 처리하지 않는다.
		else if (curWild == '*') {
			if (wildIdx == wildcard.length() - 1) {
				return ret = 1;
			}
			int passed = 1;
			while (strIdx + passed < str.length()) {
				if (checkWildcard(wildIdx + 1, strIdx + passed))
					return ret = 1;
				passed++;
			}
			wildIdx++;
		}
		//이 외의 경우에는 모두 대응되지 않는다.
		else
			break;
	}

	if (wildIdx == wildcard.length() && strIdx == str.length())
		return ret = 1;
	else
		return ret = 0;
}

//책의 답 1. 와일드카드 문제를 해결하는 동적 계획법 알고리즘

//-1은 아직 답이 계산되지 않았음을 의미한다.
//1은 해당 입력들이 서로 대응됨을 의미한다.
//0은 해당 입력들이 서로 대응되지 않음을 의미한다.
int cache[101][101];
//패턴과 문자열
string W, S;
//와일드카드 패턴 W[w...]가 문자열 S[s...]에 대응되는지 여부를 반환한다.
bool matchMemoized(int w, int s) {
	//메모이제이션
	int& ret = cache[w][s];
	if (ret != -1) return ret;
	//W[w]와 S[s]를 맞춰나간다.
	while (s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s])) {
		w++;
		s++;
	}
	//더이상 대응할 수 없으면 왜 while문이 끝났는지 확인한다.
	//패턴 끝에 도달해서 끝난 경우 : 문자열도 끝났어야 참이다.
	if (w == W.size()) return ret = (s = S.size());
	//*를 만나서 끝난 경우: *에 몇 글자를 대응해야 할지 재귀 호출하면서 확인한다.
	if (W[w] == '*')
		for (int skip = 0; skip + s <= S.size(); skip++)
			if (matchMemoized(w + 1, s + skip))
				return ret = 1;
	//이 외의 경우에는 모두 대응되지 않는다.
	return ret = 0;
}

//책의 답 2. 분해 방법을 변경하여 문제를 O(n^3)이 아닌 O(n^2) 시간에 푸는 방법.
bool matchMemoized2(int w, int s) {
	//메모이제이션
	int& ret = cache[w][s];
	if (ret != -1) return ret;
	//첫 한 글자씩을 떼고 이들이 서로 대응되는지 재귀호출로 확인한다.
	if (s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s])) {
		return ret = matchMemoized2(w + 1, s + 1);	
	}
	//더이상 대응할 수 없으면 왜 while문이 끝났는지 확인한다.
	//패턴 끝에 도달해서 끝난 경우 : 문자열도 끝났어야 참이다.
	if (w == W.size()) return ret = (s = S.size());
	//*를 만나서 끝난 경우: *에 몇 글자를 대응해야 할지 재귀 호출하면서 확인한다.
	if (W[w] == '*')
		//매 단계에서 *에 아무 글자도 대응시키지 않을 것인지, 아니면 한 글자를 더 대응시킬 것인가를 결정.
		if (matchMemoized2(w + 1, s) || matchMemoized2(w, s+1))
			return ret = 1;
	//이 외의 경우에는 모두 대응되지 않는다.
	return ret = 0;
}
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> wildcard >> N;
		for (int i = 0; i < N; i++) {
			memset(isMatchable, -1, sizeof(isMatchable));
			cin >> str;
			if (checkWildcard(0, 0))
				matched.push_back(str);
		}
		sort(matched.begin(), matched.end());
		for (int i = 0; i < matched.size(); i++)
			cout << matched[i] << endl;

		matched.clear();
	}
}