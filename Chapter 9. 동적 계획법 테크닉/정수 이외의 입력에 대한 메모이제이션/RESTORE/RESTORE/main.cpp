#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <bitset>
#define MAX 15
using namespace std;

const int INF = 987654321;
int k;
string answer;
vector<string> stringParts;
int myCache[MAX+1][(1 << MAX)+1];
// 내가 짠 재귀호출 알고리즘. 메모이제이션을 적용할 수 없었다. (애초에 중복조건이 만들어질 수 없는 구조의 알고리즘이다.)
int restore(string curString, int selected = 0) {
	if (selected == (1 << k) - 1) {
		if (curString.length() < answer.length() || answer.empty())
			answer = curString;
		return curString.length();
	}

	int minlength = INF;

	for (int next = 0; next < k; next++) {
		if (selected & (1 << next)) continue;

		string checkStr = stringParts[next];
		if (curString.empty())
			minlength = min(minlength, restore(checkStr, selected + (1 << next)));

		else {
			int addLen;
			bool checked = false;
			for (int i = 0; i < curString.length(); i++) {	
				bool match = true;
				addLen = 1;
				if (checkStr[0] == curString[i]) {
					for (int j = i + 1; j < curString.length() && (j-i) < checkStr.length(); j++) {
						if (checkStr[j - i] != curString[j]) {
							match = false;
							break;
						}
						addLen++;
					}

					if (match) {
						minlength = min(minlength, restore(curString + checkStr.substr(addLen, checkStr.length() - addLen), selected + (1 << next)));
						checked = true;
						break;
					}
				}
			}
			if (!checked)
				minlength = min(minlength, restore(curString + checkStr, selected + (1 << next)));
		}
	}
	return minlength;
}

//책의 답을 보고 메모이제이션을 적용한 내 알고리즘.
int restore2(string curString, int selected = 0, int last=0) {
	if (selected == (1 << k) - 1) {
		//cout << endl<<"endOfLevel:" << curString << endl<<endl;
		if (answer.empty() || curString.length() < answer.length())
			answer = curString;
		return curString.length();
	}

	int minlength = INF;
	//cout << curString << "	selected: "<< bitset<4>(selected)<<endl;
	for (int next = 0; next < k; next++) {
		string checkStr = stringParts[next];

		if (selected & (1 << next))	continue;

		int& ret = myCache[last][selected];
		if (ret != -1) continue;
		if(last != 0)
			ret = INF;

		if (curString.empty())
			minlength = min(minlength, restore2(checkStr, selected + (1 << next), next+1));
		else if (curString.find(checkStr) != string::npos)
			minlength = min(minlength, restore2(curString, selected + (1 << next), next+1));

		else {
			int addLen = 1;
			bool checked = false;
			for (int i = 0; i < curString.length(); i++) {
				bool match = true;
				if (checkStr[0] == curString[i]) {
					for (int j = i + 1; j < curString.length() && (j - i) < checkStr.length(); j++) {
						if (checkStr[j - i] != curString[j]) {
							match = false;
							break;
						}
						addLen++;
					}

					if (match) {
						minlength = min(minlength, restore2(curString + checkStr.substr(addLen, checkStr.length() - addLen), selected + (1 << next), next+1));
						checked = true;
						break;
					}
				}
			}
			if (!checked)
				minlength = min(minlength, restore2(curString + checkStr, selected + (1 << next), next+1));
		}
		if(last != 0)
			ret = min(ret, minlength);
	}
	return minlength;
}

//책의 알고리즘. 전처리 과정으로 아예 다른 문자열에 포함되는 문자열을 지워버렸으며,
//알고리즘 중간에 겹치는 구간을 구했던 내 알고리즘과 달리 두 단어간의 겹치는 구간 길이를 미리 계산하여
//overlap 2차원 배열에 저장했다.

const int MAX_N = 15;
//int k;
//string word[MAX_N]; -> vector<string> stringParts로 대체함
int cache[MAX_N][1 << MAX_N], overlap[MAX_N][MAX_N];
//입력받은 문자열이 다른 문자열에 포함되는지 확인하는 함수
bool EraseOverlapped(string inputStr) {
	for (int i = 0; i < stringParts.size(); i++) {
		if (stringParts[i].find(inputStr) != string::npos)
			return true;
	}
	return false;
}
//두 단어간의 겹치는 구간 길이를 구하여 overlap 배열에 저장하는 함수
void findOverlappedLength() {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (i == j) {
				overlap[i][j] = stringParts[i].size();
				continue;
			}

			int n = 0;
			string a = stringParts[i], b = stringParts[j];
			string::iterator aiter = a.begin(), biter = b.begin();
			while (aiter != a.end() && biter != b.end()) {
				if (*aiter != *biter) {
					n = 0;
					aiter++;
				}
				else {
					aiter++;
					biter++;
					n++;
				}
			}
			overlap[i][j] = n;
		}
	}
}
//마지막에 출현한 조각 last와 지금까지 출현한 조각의 집합 used가 주어질 때, 나머지 조각을 추가해서 얻을 수 있는
//overlaps의 최대 합을 구하는 동적 계획법 알고리즘.
int restore(int last, int used) {
	//기저사례
	if (used == (1 << k) - 1) return 0;
	//메모이제이션
	int& ret = cache[last][used];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = 0; next < k; next++) {
		if ((used & (1 << next)) == 0) {
			int cand = overlap[last][next] + restore(next, used + (1 << next));
			ret = max(ret, cand);
		}
	}
	return ret; 
}
//실제 문제의 답인 문자열을 찾는 알고리즘
//처음 호출 시 last는 restore()가 최댓값을 반환한 시작 단어로, used는 1<<last로 둔다.
string reconstruct(int last, int used) {
	//기저 사례
	if (used == (1 << k) - 1) return "";
	//다음에 올 문자열 조각을 찾는다.
	for (int next = 0; next < k; next++) {
		//next가 이미 사용되었으면 제외
		if (used & (1 << next)) continue;
		//next를 사용했을 경우의 답이 최적해와 같다면 next를 사용한다.
		int ifUsed = restore(next, used + (1 << next)) + overlap[last][next];
		if (restore(last, used) == ifUsed)
			return (stringParts[next].substr(overlap[last][next]) +
				reconstruct(next, used + (1 << next)));
	}
	//뭔가가 잘못된 경우
	return "****oops****";
}
//내 풀이에 대한 main 함수
int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> k;
		memset(myCache, -1, sizeof(myCache));
		string inputStr;
		for (int i = 0; i < k; i++) {
			cin >> inputStr;
			if (EraseOverlapped(inputStr))
				continue;

			stringParts.push_back(inputStr);
		}
		k = stringParts.size();
		restore2("");
		cout << answer << endl;
		answer.clear();
		stringParts.clear();
	}
}
