#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 10000000;
int c, n, lo, hi;
int divisorNum[MAXN+1];

void erastosthenes() {
	divisorNum[0] = divisorNum[1] = -1;
	for (int i = 2; i <= MAXN; i++)
		divisorNum[i] = 2;

	int sqrtn = int(sqrt(MAXN));
	for (int i = 2; i <= sqrtn; i++) {
		for (int j = i * 2; j <= MAXN; j += i) {
			if ((j / i) > sqrtn)
				divisorNum[j] += 2;
			else
				divisorNum[j] += 1;
		}
	}
}
int solve() {
	int count = 0;
	for (int i = lo; i <= hi; i++)
		if (divisorNum[i] == n)
			count++;
	return count;
}

int main(void) {
	cin >> c;
	erastosthenes();
	for (int test = 0; test < c; test++) {
		cin >> n >> lo >> hi;
		cout << solve() << endl;
	}
}