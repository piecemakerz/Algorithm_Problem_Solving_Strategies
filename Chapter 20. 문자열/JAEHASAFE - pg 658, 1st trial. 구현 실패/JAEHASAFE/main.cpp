#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C, N;

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
//내 풀이. 예제에서는 잘 동작하나 제출 시 오답이다.
//나는 두 문자열을 비교할 때 원 문자열(H)과 비교할 문자열(N)을 H의 시작위치를 증가해가며 비교하여
//문자열 N의 접두사가 원 문자열 H의 접미사에 포함될 때 돌려야 하는 횟수를 찾았다고 간주하는 알고리즘을 작성하였다.
//(ex. H = babab이고 N = abbab일 때, H[3...]와 N[...1]이 동일하므로 시계 방향으로 3(5-2)번만 돌리면 된다.)
//하지만 이와 같은 알고리즘을 사용할 경우 N의 오른쪽 끝 부분과 H의 왼쪽 끝 부분이 일치하지 않는 경우가
//발생할 수 있다.
//(ex. H = aabaa이고 N = aaaba일 때, H[3...]와 N[...1]이 동일하므로 내 알고리즘을 사용할 경우
//시계 방향으로 3(5-2)번만 돌리면 된다는 결과가 나오나, 3번만 돌릴 경우 N = abaaa가 되므로 일치하지 않는다.
//즉, H[3...]와 N[...1]이 동일하다고 해서 남은 부분 H[...2]와 N[[2...]가 동일하다는 것을 보장하지는
//않는다는 것이다.)
//따라서 H의 비교하지 않은 접두사 부분(H[...2])과 N의 비교하지 않은 접미사 부분(N[2...])이 같은지를
//확인하는 코드도 추가해야 오답이 발생하지 않는다.

int kmpSearch(const string& H, const string& N, const vector<int>& pi) {
	int n = H.length();
	int begin = 1, matched = 0;
	while (begin + matched < n) {
		//만약 H의 해당 글자가 N의 해당 글자와 같다면
		if (H[begin + matched] == N[matched]) {
			matched++;
			if (begin + matched == n) return matched;
		}
		else {
			//예외: matched가 0인 경우에는 다음 칸에서부터 계속
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 1;
}

int unlockSafe(const vector<string>& strArr, const vector<vector<int>>& pi) {
	int shiftCount = 0;
	int strN = strArr[0].length();
	bool clockWise = true;

	for (int i = 0; i < N; i++) {
		if (clockWise)
			//시계 방향으로 회전
			shiftCount += strN - (kmpSearch(strArr[i + 1], strArr[i], pi[i]));
		else
			//반시계 방향으로 회전
			shiftCount += strN - (kmpSearch(strArr[i], strArr[i+1], pi[i+1]));
		clockWise = !clockWise;
	}
	return shiftCount;
}
*/

//책의 답
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

//shift(original, tarrget) = 문자열 original을 target으로 만들기 위해 환형 시프트를 몇 번이나 해야 하는지 반환
int shifts(const string& original, const string& target) {
	return kmpSearch(original + original, target)[0];
}

int unlockSafe(const vector<string>& strArr) {
	int shiftCount = 0;
	int strN = strArr[0].length();
	bool clockWise = true;

	for (int i = 0; i < N; i++) {
		if (clockWise)
			//시계 방향으로 회전
			shiftCount += shifts(strArr[i+1], strArr[i]);
		else
			//반시계 방향으로 회전
			shiftCount += shifts(strArr[i], strArr[i+1]);
		clockWise = !clockWise;
	}
	return shiftCount;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> N;
		vector<string> strArr(N+1);
		for (int i = 0; i < N + 1; i++)
			cin >> strArr[i];
		cout << unlockSafe(strArr) << endl;
	}
	return 0;
}