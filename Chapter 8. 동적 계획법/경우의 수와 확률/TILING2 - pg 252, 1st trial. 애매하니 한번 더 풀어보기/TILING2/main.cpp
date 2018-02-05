#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1000000007;
int cache[101];

int TILING(int n) {
	if (n == 1)
		return 1;
	else if (n == 2)
		return 2;
	int& ret = cache[n];
	if (ret != -1) return ret;

	return ret = (TILING(n - 1) + TILING(n - 2))%MOD;
}