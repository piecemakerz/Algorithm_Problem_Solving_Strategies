#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

const int MAX_N = 1000;
int n, m; // n = 우물의 깊이, m = 장마 기간의 길이
double cache[MAX_N][2 * MAX_N + 1];

double climb2(int days=0, int climbed=0) {
	if (days == m) return climbed >= n ? 1.0 : 0.0;

	double& ret = cache[days][climbed];
	if (ret != -1.0) return ret;

	return ret = 0.75 * climb2(days + 1, climbed + 2) + 0.25 * climb2(days + 1, climbed + 1);
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		for (int i = 0; i < MAX_N; i++)
			for (int j = 0; j < 2 * MAX_N + 1; j++)
				cache[i][j] = -1.0;

		cin >> n >> m;
		printf("%.10f\n", climb2());
	}
}