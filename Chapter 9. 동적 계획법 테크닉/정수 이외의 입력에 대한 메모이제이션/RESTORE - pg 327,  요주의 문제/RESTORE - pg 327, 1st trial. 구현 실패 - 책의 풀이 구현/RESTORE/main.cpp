#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <bitset>
#define MAX 15
using namespace std;

int k;
string answer;
const int MAX_N = 15;
vector<string> stringParts;
//책의 알고리즘. 전처리 과정으로 아예 다른 문자열에 포함되는 문자열을 지워버렸으며,
//알고리즘 중간에 겹치는 구간을 구했던 내 알고리즘과 달리 두 단어간의 겹치는 구간 길이를 미리 계산하여
//overlap 2차원 배열에 저장했다.

int cache[MAX_N][1 << MAX_N], overlap[MAX_N][MAX_N];

//입력받은 문자열이 다른 문자열에 포함되는지 확인하고 완전히 포함된다면 그 문자열 조각을 벡터에서 삭제하는 함수.
void EraseOverlapped() {
	//문자열 조각들 길이순으로 정렬
	int vectorLen = stringParts.size();
	for (int i = 0; i < vectorLen - 1; i++) {
		for (int j = i + 1; j < vectorLen; j++) {
			if (stringParts[i].length() < stringParts[j].length()) {
				string temp = stringParts[i];
				stringParts[i] = stringParts[j];
				stringParts[j] = temp;
			}
		}
	}

	//포함되는 문자열 조각 삭제
	vector<string>::iterator iter;
	for (int i = 0; i < vectorLen - 1; i++) {
		for (int j = i + 1; j < vectorLen; j++) {
			if (stringParts[i].find(stringParts[j]) != string::npos) {
				iter = stringParts.begin() + j;
				stringParts.erase(iter);
				j--;
				vectorLen--;
			}
		}
	}
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
			bool checking = false;
			string a = stringParts[i], b = stringParts[j];
			string::iterator aiter = a.begin(), biter = b.begin();
			string::iterator tempAiterPos;
			while (aiter != a.end() && biter != b.end()) {
				if (*aiter != *biter) {
					n = 0;
					if (!checking)
						aiter++;
					else
						aiter = tempAiterPos + 1;
					biter = b.begin();
					checking = false;
				}
				else {
					if (!checking)
						tempAiterPos = aiter;
					aiter++;
					biter++;
					n++;
					checking = true;
				}
			}
			overlap[i][j] = n;
		}
	}
}
//마지막에 출현한 조각 last와 지금까지 출현한 조각의 집합 used가 주어질 때, 나머지 조각을 추가해서 얻을 수 있는
//overlaps의 최대 합을 구하는 동적 계획법 알고리즘. 처음 실행될 때 last에 -1, used에 0이 주어진다.
int maxStart;
int restore(int last, int used) {
	//기저사례
	if (used == (1 << k) - 1) return 0;
	//메모이제이션
	if (last == -1) {
		int ret = 0;
		for (int next = 0; next < k; next++) {
			int cand = restore(next, used + (1 << next));
			//cout << "max overlap starting with " << next << ":" << cand << endl;
			if ((ret = max(ret, cand)) == cand)
				maxStart = next;
		}
		return ret;
	}

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
		memset(cache, -1, sizeof(cache));
		memset(overlap, 0, sizeof(overlap));
		cin >> k;
		string inputStr;
		for (int i = 0; i < k; i++) {
			cin >> inputStr;
			stringParts.push_back(inputStr);
		}
		EraseOverlapped();
		k = stringParts.size();
		findOverlappedLength();
		/*for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				cout << overlap[i][j] << ' ';
			}
			cout << endl;
		}
		*/
		restore(-1, 0);
		cout << stringParts[maxStart] + reconstruct(maxStart, 1 << maxStart) << endl;
		stringParts.clear();
		maxStart = -1;
	}
}