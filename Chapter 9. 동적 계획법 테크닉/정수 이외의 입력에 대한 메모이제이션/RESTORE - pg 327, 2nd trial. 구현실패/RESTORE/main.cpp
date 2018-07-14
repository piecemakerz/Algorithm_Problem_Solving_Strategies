#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int C, k;
const int MAX = 987654321;

string strParts[16];
int overlap[16][16];
int cache[16][1 << 16];

//책의 실험 데이터 복구 문제를 해결하는 동적 계획법 알고리즘.
//마지막에 출현한 조각 last와 지금까지 출현한 조각의 집합 used가
//주어질 때, 나머지 조각을 추가해서 얻을 수 있는 overlaps()의 최대 합을
//반환한다.
int restore(int last, int used) {
	//기저 사례: 마지막 문자열 조각을 골랐을 때
	if (used == (1 << k) - 1) return 0;
	int& ret = cache[last][used];
	if (ret != -1) return ret;
	ret = 0;

	for (int next = 0; next < k; next++) {
		if ((used & (1 << next)) == 0) {
			int cand = overlap[last][next] +
				restore(next, used + (1 << next));
			ret = max(ret, cand);
		}
	}
	return ret;
}

//restore의 반환값을 변경한 알고리즘. 나머지 조각을 추가해서 얻을 수 있는
//overlaps()의 최대 합을 반환하는 restore과 달리 나머지 조각을 추가해서 얻을
//수 있는 최소 문자열 길이를 반환한다.
int restore2(int last, int used) {
	//기저 사례: 마지막 문자열 조각을 골랐을 때
	if (used == (1 << k) - 1) strParts[last].length();

	int& ret = cache[last][used];
	if (ret != -1) return ret;
	ret = MAX;

	int cand;
	for (int next = 0; next < k; next++) {
		if ((used & (1 << next)) == 0) {
			int cand = restore2(next, used + (1 << next)) - overlap[last][next];
			ret = min(ret, cand);
		}
	}
	return ret;
}

//실험 데이터 복구 문제의 실제 답을 계산하는 알고리즘
//restore함수에 대한 답 역추적 알고리즘. 가상의 시작위치 last = k
//에서부터 시작한다.
string reconstruct(int last, int used) {
	//기저 사례
	if (used == (1 << k) - 1) return "";
	//다음에 올 문자열 조각을 찾는다.
	for (int next = 0; next < k; next++) {
		//next가 이미 사용되었으면 제외
		if ((used & (1 << next))) continue;
		//next를 사용했을 경우의 답이 최적해와 같다면 next를 사용한다.
		int ifUsed = restore(next, used + (1 << next)) + overlap[last][next];
		if (restore(last, used) == ifUsed)
			return (strParts[next].substr(overlap[last][next]) +
				reconstruct(next, used + (1 << next)));
	}
	//뭔가 잘못된 경우
	return "****oops****";
}

//restore2함수에 대한 답 역추적 알고리즘. 가상의 시작위치 last = k
//에서부터 시작한다.
string reconstruct2(int last, int used) {
	//기저 사례
	if (used == (1 << k) - 1) return "";
	//다음에 올 문자열 조각을 찾는다.
	for (int next = 0; next < k; next++) {
		//next가 이미 사용되었으면 제외
		if (used & (1 << next)) continue;
		//next를 사용했을 경우의 답이 최적해와 같다면 next를 사용한다.
		int ifUsed = restore2(next, used + (1 << next)) - overlap[last][next];
		if (restore2(last, used) == ifUsed)
			return (strParts[next].substr(overlap[last][next]) +
				reconstruct2(next, used + (1 << next)));
	}
	//뭔가 잘못된 경우
	return "****oops****";
}

//단어 a와 b간의 겹치는 부분 길이를 계산하는 알고리즘.
//겹치는 부분이 없다면 0을 반환한다.
int getOverlap(const string& a, const string& b) {
	for (int len = min(a.size(), b.size()); len > 0; len--) {
		if (a.substr(a.size() - len) == b.substr(0, len))
			return len;
	}
	return 0;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		cin >> k;
		for (int i = 0; i < k; i++) cin >> strParts[i];
		//한 문자열 조각이 다른 문자열에 포함될 경우 문자열 조각 목록에서
		//아예 제외시켜버리는 전처리 과정을 거친다.
		while (true) {
			bool removed = false;
			//중간에 문자열 조각이 삭제되었다면 처음부터 다시 체크한다.
			for (int i = 0; i < k && !removed; i++) {
				for(int j=0; j<k; j++)
					//strParts[j]가 strParts[i]에 완전히 포함될 경우 제외시킨다.
					if (i != j && strParts[i].find(strParts[j]) != string::npos) {
						strParts[j] = strParts[k - 1];
						k--;
						removed = true;
					}
			}
			//더 이상 전처리 과정을 거칠 필요가 없다면 과정을 끝낸다.
			if (!removed) break;
		}
		strParts[k] = "";
		//사전상 앞에 오는 문자열을 우선으로 구하기 위해 정렬.
		sort(strParts, strParts + k);
		//가상의 k번째 문자열에 대한 overlap도 계산해놓는다. 문제 해결 알고리즘의
		//시작 위치로써 사용되기 때문. (overlap[k][i]와 overlap[i][k]는 무조건 0이다)
		for (int i = 0; i <= k; i++)
			for (int j = 0; j <= k; j++)
				overlap[i][j] = getOverlap(strParts[i], strParts[j]);

		//가상의 시작 문자열 k로부터 시작한다.
		restore2(k, 0);
		cout << reconstruct2(k, 0) << endl;
	}
	return 0;
}