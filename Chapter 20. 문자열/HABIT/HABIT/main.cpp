#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int C, K;

//첫 t글자로 묶인 그룹 정보를 이용해 첫 2t글자를 비교하는 비교자의 구현

//각 접미사들의 첫 t글자를 기준으로 한 그룹 번호가 주어질 때,
//주어진 두 접미사를 첫 2*t글자를 기준으로 비교한다.
//group[]은 길이가 0인 접미사도 포함한다.
struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
	bool operator() (int a, int b) {
		//첫 t글자가 다르면 이들을 이용해 비교한다.
		if (group[a] != group[b]) return group[a] < group[b];
		//아니라면 S[a+t...]와 S[b+t...]의 첫 t글자를 비교한다.
		return group[a + t] < group[b + t];
	}
};

//접미사 배열을 계산하는 맨버와 마이어스의 알고리즘

//s의 접미사 배열을 계산한다.
vector<int> getSuffixArray(const string& s) {
	int n = s.size();
	//group[i] = 접미사들을 첫 t글자를 기준으로 정렬했을 때,
	//			 S[i...]가 들어가는 그룹 번호.
	//t=1일 때는 정렬할 것 없이 S[i...]의 첫 글자로 그룹 번호를
	//정해 줘도 같은 효과가 있다.
	int t = 1;
	vector<int> group(n + 1);
	for (int i = 0; i < n; i++) group[i] = s[i];
	group[n] = -1;
	//결과적으로 접미사 배열이 될 반환 값. 이 배열을 lg(n)번 정렬한다.
	vector<int> perm(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	while (t < n) {
		//group[]은 첫 t글자를 기준으로 계산해 뒀다.
		//첫 2t글자를 기준으로 접미사 배열 perm을 다시 정렬한다.
		//접미사들을 2t기준으로 사전 순 정렬한 접미사들의 길이 배열 
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		//2t글자가 n을 넘는다면 이제 접미사 배열 완성
		t *= 2;
		if (t >= n) break;
		//2t글자를 기준으로 한 그룹 정보를 만든다.
		//newGroup[i] = 접미사들을 첫 2t글자를 기준으로 정렬했을 때,
		//			 S[i...]가 들어가는 그룹 번호.
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0; // 첫 2t글자 기준으로 사전순으로 정렬했을 때 가장 앞에 오는 접미사의
							   //그룹 번호를 0으로 설정한다. 이후 첫 2t글자가 같다면 같은 그룹번호로, 다르다면 그룹 번호를
							   //1만큼 더 올린다.
		for (int i = 1; i < n; i++)
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		group = newGroup;
	}
	return perm;
}

//한 부분 문자열이 두번 이상 출현할 경우 이를 접두사를 갖는 접미사들은 항상 인접해 있다.
//따라서 인접한 접미사들의 접두사가 동일하다면 이는 중복 출현하는 부분 문자열이다.

int	longestPartialArray(const string& str) {
	int n = str.length();
	vector<int> suffix = getSuffixArray(str); // suffix = str의 사전순으로 정렬된 접미사 배열
	vector<int> length(n+1, 1); //길이가 i인 부분집합들 중 가장 자주 등장하는 부분집합의 수. 
	//기본적으로 str의 모든 접미사는 str의 부분집합이므로 length배열의 원소들을 1로 초기화한다. (최소 길이가 i인 부분집합이 하나는 존재한다)
	vector<int> lengthCount(n + 1, 1); // 현재까지 같아온 길이가 i인 부분 문자열의 수

	int maxSameCount = 0; // 현재까지 같아온 부분 문자열의 최대 길이
	for (int i = 1; i < suffix.size(); i++) { // str의 모든 접미사에 대해 순회
		int curSuffix = suffix[i], prevSuffix = suffix[i - 1];
		int sameCount = 0; // 부분 문자열의 길이
		while (curSuffix < n && prevSuffix < n) {
			if (str[curSuffix] == str[prevSuffix]) {
				lengthCount[++sameCount]++;
				curSuffix++; prevSuffix++;
				maxSameCount = max(maxSameCount, sameCount);
				//비교하는 두 개의 접미사들 중 하나의 접미사가 다른 접미사의 접두사일 때,(ex - ana, anana)
				//else문을 거치지 않고 while문을 빠져나가기 때문에 maxSameCount에 현재까지 같아온 부분 문자열의 최대 길이를
				//저장해놓지 않는다면 다음 순회에서 length배열을 갱신할 때 갱신해야 할 원소들 중 일부를 빼먹을 수 있다.
			}
			else {
				for (int i = sameCount + 1; i <= maxSameCount; i++) //현재 순회에서도 같았던 부분집합에 대해서는 length배열을 갱신하지 않는다.
					length[i] = max(length[i], lengthCount[i]); // 이전에 구한 부분집합의 수가 더 클 수도 있으므로 max연산을 한다.
				for (int i = sameCount + 1; i <= maxSameCount; i++)
					lengthCount[i] = 1;
				maxSameCount = sameCount;
				break;
			}
		}
	}
	
	//else문을 순회하지 않으므로써 갱신되지 못한 length배열을 완전히 갱신
	for (int i = 1; i <= n; i++)
		length[i] = max(length[i], lengthCount[i]);

	//K번 이상 등장하는 부분 문자열의 최대 길이 반환
	for (int i = n; i > 0; i--) {
		if (length[i] >= K)
			return i;
	}
	//K번 이상 등장하는 부분 문자열이 없을 경우 0 반환
	return 0;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> K;
		string inputStr;
		cin >> inputStr;
		cout << longestPartialArray(inputStr) << endl;
	}
}