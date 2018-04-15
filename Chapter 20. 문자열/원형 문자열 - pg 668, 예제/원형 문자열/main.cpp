#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

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

//접미사 배열을 사용해 원형 문자열 문제를 해결하는 알고리즘의 구현

//사전순으로 가장 앞에 오는 s의 회전 결과를 구한다.
string minShift(const string& s) {
	string s2 = s + s;
	vector<int> a = getSuffixArray(s2);
	for (int i = 0; i < a.size(); i++)
		if (a[i] <= s.size())
			return s2.substr(a[i], s.size());
	//여기로 올 일은 없어야 한다.
	return "__oops__";
}

int main(void) {
	string inputStr;
	cin >> inputStr;
	cout << minShift(inputStr) << endl;
}