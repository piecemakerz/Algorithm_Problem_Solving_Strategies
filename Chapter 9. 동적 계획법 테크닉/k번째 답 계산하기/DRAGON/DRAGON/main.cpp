#include <iostream>
using namespace std;

int c, n, p, l;

int curve(string curStr, int curP, int age) {
	if (age == n && curP >= p) {
		int idx = 0;
		while (l != 0 && idx < curStr.length()) {
			cout << curStr[idx++];
			l--;
			curP++;
		}
		return curP;
	}

	for (int i = 0; i < curStr.length(); i++) {
		if (curStr[i] == 'X') {
			curP = curve("+YF", curP + 1, age + 1);
		}
		else if (curStr[i] == 'Y') {
			curP = curve("FX-Y", curP, age + 1);
		}
		else {
			if (curP >= p && l >= 0) {
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
		cin >> n >> p >> l;
		curve("FX", 1, 0);
		cout << endl;
	}
	return 0;
}