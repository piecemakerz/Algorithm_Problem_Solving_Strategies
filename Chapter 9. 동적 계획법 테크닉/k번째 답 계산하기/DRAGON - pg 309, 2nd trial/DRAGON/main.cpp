#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

int c, n, p, l;

//p의 최댓값이 10억, l의 최댓값이 50이므로 출력해야 하는 글자는
//최대 문자열의 1000000049번째 문자이다.
const long long MAX = 1000000050;

//'X'나 'Y'가 ageLeft의 세대를 거쳤을 때 치환되는 드래곤 커브 문자열의
//길이를 구한다.
int maxcache[51];
int findMaxLength(int ageLeft) {
	int& ret = maxcache[ageLeft];
	if (ret != -1) return ret;

	ret = 1;
	long long numOfXandY = 1;

	for (int i = 1; i <= ageLeft; i++) {
		ret = min(MAX, (long long)ret + (3 * numOfXandY));
		numOfXandY = min(MAX, numOfXandY * 2);
	}
	return ret;
}

//내 풀이 2. 각 경우마다 치환되는 문자열의 길이를 미리 계산하여
//더 빠르게 뛰어넘어 답을 계산하는 알고리즘.
int curve2(string curStr, int curP, int age) {
	//기저사례: 이미 모든 글자들을 출력한 경우
	if (l <= 0)
		return curP + 1;

	int len = curStr.length();

	if (age == n) {
		if (curP + len <= p)
			return curP + len;
		else {
			int idx = 0;
			while (l > 0 && idx < len) {
				if (curP + idx >= p) {
					cout << curStr[idx];
					l--;
				}
				idx++;
			}
			return curP + len;
		}
	}

	for (int i = 0; i < len; i++) {
		if (curStr[i] == 'X' || curStr[i] == 'Y') {	
			//만일 'X'나 'Y'가 현재 세대부터 n세대까지의 치환을 거쳤을 때
			//치환된 문자열이 우리가 출력하려는 범위의 문자열이 아니라면
			//굳이 치환과정을 거치지 않고 치환되는 문자열의 길이 만큼 건너뛴다.
			if (curP + findMaxLength(n - age) <= p) {
				curP += findMaxLength(n - age);
				continue;
			}

			if (curStr[i] == 'X')
				curP = curve2("X+YF", curP, age + 1);
			else
				curP = curve2("FX-Y", curP, age + 1);
		}
		else {
			if (l > 0 && curP >= p) {
				cout << curStr[i];
				l--;
			}
			curP++;
		}
	}
	return curP;
}

//내 풀이 1. 모든 답을 확인해보는 재귀 호출 알고리즘. 답은 맞게 나오나
//당연히도 시간초과가 발생한다.
int curve(string curStr, int curP, int age) {
	if (l <= 0)
		return curP + 1;

	int len = curStr.length();

	if (age == n){
		if(curP + len <= p)
			return curP + len;

		else{
			int idx = 0;
			while (l > 0 && idx < len) {
				if (curP + idx >= p) {
					cout << curStr[idx];
					l--;
				}
				idx++;
			}
			return curP + len;
		}
	}

	for (int i = 0; i < curStr.length(); i++) {
		if (curStr[i] == 'X') {
			curP = curve("X+YF", curP, age + 1);
		}
		else if (curStr[i] == 'Y') {
			curP = curve("FX-Y", curP, age + 1);
		}
		else {
			if (curP >= p && l > 0) {
				cout << curStr[i];
				l--;
			}
			curP++;
		}
	}
	return curP;
}

//책의 풀이 1. 드래곤 커브 문자열을 생성하는 재귀 호출 알고리즘
//초기 문자열 seed를 generations세대 진화시킨 결과를 출력한다.
//이 코드에서 p번째 글자만을 출력하도록 하려면, 건너뛰어야 하는 글자의 수
//skip을 전역 변수에 유지하면서, 문자열 혹은 문자를 출력할 때마다 skip과
//출력할 부분의 길이를 비교하면 된다.
void curve(const string& seed, int generations) {
	//기저 사례
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

//책의 풀이 2. 문자열의 길이를 미리 계산하여 원하는 문자열을
//빠르게 찾아내는 알고리즘.
const int bMAX = 1000000000 + 1;
//length[i] = X나 Y를 i번 치환한 후의 길이
int length[51];
void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++)
		length[i] = min(bMAX, length[i - 1] * 2 + 2);
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";
//dragonCurve를 generations 진화시킨 결과에서 skip번째 문자를 반환한다.
//따라서 원하는 문자열을 전부 출력하기 위해서는 expand를 l번 반복 호출해야 한다.
char expand(const string& dragonCurve, int generations, int skip) {
	//기저 사례
	if (generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	for (int i = 0; i < dragonCurve.size(); i++) {
		//문자열이 확장되는 경우
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= length[generations])
				skip -= length[generations];
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, generations - 1, skip);
			else
				return expand(EXPAND_Y, generations - 1, skip);
		}
		//확장되진 않지만 건너뛰어야 할 경우
		else if (skip > 0)
			skip--;
		//답을 찾은 경우
		else
			return dragonCurve[i];
	}
	return '#';
}

int main(void) {
	cin >> c;
	//memset(maxcache, -1, sizeof(maxcache));
	precalc();
	for (int test = 0; test < c; test++) {
		cin >> n >> p >> l;
		//curve2("FX", 1, 0);
		for (int skip = p-1; skip < p + l - 1; skip++)
			cout << expand("FX", n, skip);
		cout << endl;
	}
	return 0;
}