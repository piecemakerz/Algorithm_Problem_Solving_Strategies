#include <iostream>
#include <algorithm>
using namespace std;

int c, n, p, l;

const int MAX = 1000000051;

int maxcache[51];

int findMaxLength(int ageLeft) {
	int& ret = maxcache[ageLeft];
	if (ret != -1) return ret;

	int length = 1;
	for (int i = 1; i <= ageLeft; i++) {
		length = min(MAX, length + (3 * ageLeft));
	}
	return length;
}

int curve2(string curStr, int curP, int age) {
	if (l <= 0 || curP >= MAX)
		return MAX;

	if (age == n && l > 0 && curP >= p) {
		int idx = 0;
		while (l > 0 && idx < curStr.length()) {
			cout << curStr[idx++];
			l--;
			curP++;
		}
		return curP;
	}

	for (int i = 0; i < curStr.length(); i++) {
		if (curStr[i] == 'X' || curStr[i] == 'Y') {
			if (curP + findMaxLength(n - age) <= p) {
				curP += findMaxLength(n - age) + 1;
				continue;
			}

			if (curStr[i] == 'X')
				curP = curve2("X+YF", curP, age + 1);
			else
				curP = curve2("FX-Y", curP, age + 1);
		}
		else
			if (curP >= p && l > 0) {
				cout << curStr[i];
				l--;
				curP++;
			}
	}
	return curP;
}

//모든 답을 확인해보는 완전탐색 알고리즘. 답은 맞게 나온다.
int curve(string curStr, int curP, int age) {
	if (l <= 0 || curP >= MAX)
		return MAX;

	int len = curStr.length();
	if (age == n){
		if(curP + len <= p)
			return curP + len;
		else{
			int idx = 0;
			while (l > 0 && idx < curStr.length()) {
				if (curP + idx >= p) {
					cout << curStr[idx++];
					l--;
				}
				curP++;
			}
			return curP;
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

int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		memset(maxcache, -1, sizeof(maxcache));
		cin >> n >> p >> l;
		curve2("FX", 1, 0);
		cout << endl;
	}
	return 0;
}