#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

vector<int> PINum;
int cache[100000];
const int INF = 987654321;
string N;

// 내가 짠 알고리즘
bool Difficulty1(const vector<int>& currentSelected) {
	int num = currentSelected[0];
	for (int i = 1; i < currentSelected.size(); i++)
		if (num != currentSelected[i])
			return false;
	return true;
}

bool Difficulty2(const vector<int>& currentSelected) {
	int difference;
	if (currentSelected[0] + 1 == currentSelected[1])
		difference = 1;
	else if (currentSelected[0] - 1 == currentSelected[1])
		difference = -1;
	else
		return false;
	
	for (int i = 1; i < currentSelected.size() - 1; i++)
		if (currentSelected[i] + difference != currentSelected[i + 1])
			return false;
	return true;
}

bool Difficulty4(const vector<int>& currentSelected) {
	int num1 = currentSelected[0];
	int num2 = currentSelected[1];
	for (int i = 2; i < currentSelected.size(); i++) {
		if (i % 2 == 0) {
			if (currentSelected[i] != num1)
				return false;
		}
		else {
			if (currentSelected[i] != num2)
				return false;
		}
	}
	return true;
}

bool Difficulty5(const vector<int>& currentSelected) {
	int difference = currentSelected[0] - currentSelected[1];
	for (int i = 1; i < currentSelected.size() - 1; i++) {
		if (currentSelected[i] - currentSelected[i + 1] != difference)
			return false;
	}
	return true;
}

int judgeDifficulty(const vector<int>& currentSelected) {
	if (Difficulty1(currentSelected))
		return 1;
	else if (Difficulty2(currentSelected))
		return 2;
	else if (Difficulty4(currentSelected))
		return 4;
	else if (Difficulty5(currentSelected))
		return 5;
	else
		return 10;
}

int PI(int curIdx) { // curIdx에서부터 끝까지의 난이도를 리턴한다.
	int size = PINum.size();
	if (curIdx == size)
		return 0;

	if (curIdx >= size-2)
		return INF;

	int& ret = cache[curIdx];
	if (ret != -1)
		return ret;

	ret = INF;
	vector<int> curSelected;
	for(int i=0; i<3; i++)
		curSelected.push_back(PINum[curIdx++]);
	int diff3 = judgeDifficulty(curSelected);
	ret = min(ret, PI(curIdx)+diff3);

	if (curIdx < size) {
		curSelected.push_back(PINum[curIdx++]);
		int diff4 = judgeDifficulty(curSelected);
		ret = min(ret, PI(curIdx) + diff4);
	}
	if (curIdx < size) {
		curSelected.push_back(PINum[curIdx++]);
		int diff5 = judgeDifficulty(curSelected);
		ret = min(ret, PI(curIdx) + diff5);
	}
	return ret;
}

//책의 답 - 최소 난이도 결정 함수가 내가 짠 함수보다 훨씬 간결하다. 또한, 최소 합 출력 함수도 훨씬 간결하다.
int classify(int a, int b) {
	string M = N.substr(a, b - a + 1);
	if (M == string(M.size(), M[0])) return 1;

	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++) {
		if (M[i + 1] - M[i] != M[1] - M[0])
			progressive = false;
	}
	if (progressive && abs(M[1] - M[0]) == 1)
		return 2;

	bool alternating = true;
	for (int i = 0; i < M.size(); i++)
		if (M[i] != M[i % 2])
			alternating = false;
	if (alternating) return 4;
	if (progressive) return 5;
	return 10;
}

// int cache[10002];
int memorize(int begin) {
	if (begin == N.size()) return 0; // 수열의 끝에 도달했을 경우
	int& ret = cache[begin];
	if (ret != -1) return ret;
	ret = INF;
	for (int L = 3; L <= 5; L++) {
		if (begin + L <= N.size())
			ret = min(ret, memorize(begin + L) + classify(begin, begin + L - 1));
	}
	return ret;
}
int main(void) {
	int C;
	char inputchar;
	scanf("%d", &C);
	scanf("%c", &inputchar);
	for (int testCase = 0; testCase < C; testCase++) {
		int input;
		while(true){
			scanf("%c", &inputchar);
			if (inputchar == '\n')
				break;
			input = inputchar - '0';
			PINum.push_back(input);
		}
		memset(cache, -1, sizeof(cache));
		cout<<PI(0)<<endl;
		PINum.clear();
	}
}