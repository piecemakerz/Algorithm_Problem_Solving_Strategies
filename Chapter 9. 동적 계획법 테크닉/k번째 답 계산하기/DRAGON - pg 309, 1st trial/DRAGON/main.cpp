#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;

int n, p, l;
string answer;
const int MAX = 1000000050;
// 내 풀이. 작성하는데 5시간 걸림.
int curveCount(int generation) {
	int num = 0;
	if (n - generation >= 30)
		return MAX;
	for (int i = 0; i < (n - generation); i++)
		num = min<int>(num + 3 * pow<int>(2, i), MAX);
	return num;
}

int dragonCurve(int	curPos = 1, string curPat = "FX", int generation = 0) {
	if (answer.length() < l) {
		for (int i = 0; i < curPat.length(); i++) {
			//cout << curPos << ' ' << curPat << ' ' << curPat[i] << ' ' << generation<<endl;
			//cout << answer << endl;
			if (answer.length() >= l)
				break; 

			if (curPos >= p && !(curPat[i] == 'X' || curPat[i] == 'Y'))
				answer += curPat[i];

			else {
				if (curPat[i] == 'X') {
					if (curPos >= p && generation == n)
						answer += curPat[i];
					else {
						int curvecount = curveCount(generation);
						if (curPos + curvecount < p)
							curPos += curvecount;
						else
							curPos = dragonCurve(curPos, "X+YF", generation + 1) - 1;
					}
				}
				else if (curPat[i] == 'Y') {
					if (curPos >= p && generation == n)
						answer += curPat[i];
					else {
						int curvecount = curveCount(generation);
						if (curPos + curvecount < p)
							curPos += curvecount;
						else
							curPos = dragonCurve(curPos, "FX-Y", generation + 1) - 1;
					}
				}
			}

			curPos++;
		}
		return curPos;
	} 
	return 0;
}

// 책의 드래곤 커브 문자열 생성 재귀 호출 알고리즘
// 초기 문자열 seed를 generations세대 진화한 결과를 출력
void curve(const string& seed, int generations) {
	if (generations == 0) {
		cout << seed;
		return;
	}
	for (int i = 0; i < seed.size(); i++) {
		if (seed[i] == 'X')
			curve("X+YF", generations - 1);
		else if (seed[i] == 'Y')
			curve("FX-Y", generations - 1);
		else
			cout << seed[i];
	}
}
// 책의 답
// const int MAX = 1000000000 + 1;
int length[51]; // length[i] = X나 Y를 i번 치환한 후의 길이
void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++)
		length[i] = min(MAX, length[i - 1] * +2);
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";
//dragonCurve를 generations 진화시킨 결과에서 skip번째 문자를 반환한다.
char expand(const string& dragonCurve, int generations, int skip) {
	if (generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	for (int i = 0; i < dragonCurve.size(); i++) {
		// 문자열이 확장되는 경우
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= length[generations])
				skip -= length[generations];
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, generations - 1, skip);
			else
				return expand(EXPAND_Y, generations - 1, skip);
		}
		// 확장되진 않지만 건너뛰어야 할 경우
		else if (skip > 0)
			skip--;
		else // 답을 찾은 경우
			return dragonCurve[i];

	}
	return '#'; // 이 줄은 수행되지 않음
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n >> p >> l;
		dragonCurve();
		cout << answer << endl;
		answer.clear();
	}
}