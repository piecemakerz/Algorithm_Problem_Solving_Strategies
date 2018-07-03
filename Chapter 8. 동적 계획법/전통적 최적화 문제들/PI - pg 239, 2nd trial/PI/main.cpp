#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

int C;
string PI;
int cache[10000];
const int INF = 987654321;

//내 풀이. 책의 답과 같은 방식으로 구현되었으나,
//책의 풀이가 더 간결하다.
int calDiff(const vector<char>& sel) {
	bool case1 = true, case2 = true, 
		case3 = true, case4 = true;
	int n = sel.size();
	int diff = sel[0] - sel[1];
	if (abs(diff) != 1)
		case2 = false;

	for (int i = 0; i < n - 1; i++) {
		if (case1 && sel[i] != sel[i + 1])
			case1 = false;
		if (case2 && sel[i] - sel[i + 1] != diff)
			case2 = false;
		if (case3 && i < n-2 && sel[i] != sel[i + 2])
			case3 = false;
		if (case4 && sel[i] - sel[i + 1] != diff)
			case4 = false;
	}
	if (case1)
		return 1;
	if (case2)
		return 2;
	if (case3)
		return 4;
	if (case4)
		return 5;

	return 10;
}

int piDiff(int start) {
	if (start >= PI.length())
		return 0;

	else if (start > PI.length() - 3)
		return 10;

	int& ret = cache[start];
	if (ret != INF) return ret;

	vector<char> sel;
	sel.push_back(PI[start]);
	sel.push_back(PI[start + 1]);

	for (int i = 2; i < 5; i++) {
		if (start + i >= PI.length())
			break;
		sel.push_back(PI[start + i]);
		ret = min(ret, calDiff(sel) + piDiff(start + 1 + i));
	}
	sel.clear();
	return ret;
}

//책의 풀이. 원주율 외우기 문제를 해결하는 동적 계획법 알고리즘
//PI[a..b] 구간의 난이도를 반환한다.
int classify(int a, int b) {
	//숫자 조각을 가져온다.
	string M = PI.substr(a, b - a + 1);
	//첫 글자만으로 이루어진 문자열과 같으면 난이도는 1
	if (M == string(M.size(), M[0])) return 1;
	//등차수열인지 검사한다.
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++)
		if (M[i + 1] - M[i] != M[1] - M[0])
			progressive = false;
	//등차수열이고 공차가 1 혹은 -1이면 난이도는 2
	if (progressive && abs(M[1] - M[0]) == 1)
		return 2;
	//두 수가 번갈아 등장하는지 확인한다.
	bool alternating = true;
	for (int i = 0; i < M.size(); i++)
		if (M[i] != M[i % 2])
			alternating = false;
	//두 수가 번갈아 등장하면 난이도는 4
	if (alternating) return 4;
	//공차가 1 아닌 등차수열의 난이도는 5
	if (progressive) return 5;
	//이 외는 모두 난이도 10
	return 10;
}
//수열 PI[begin...]를 외우는 방법 중 난이도의 최소 합을 출력한다.
int memorize(int begin) {
	//기저 사례: 수열의 끝에 도달했을 경우
	if (begin == PI.size()) return 0;
	//메모이제이션
	int& ret = cache[begin];
	if (ret != -1) return ret;
	ret = INF;
	for (int L = 3; L <= 5; L++)
		if (begin + L <= PI.size())
			ret = min(ret, memorize(begin + L) +
				classify(begin, begin + L - 1));
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		for (int i = 0; i < 10000; i++)
			cache[i] = INF;
		cin >> PI;
		cout << piDiff(0) << endl;
	}
	return 0;
}