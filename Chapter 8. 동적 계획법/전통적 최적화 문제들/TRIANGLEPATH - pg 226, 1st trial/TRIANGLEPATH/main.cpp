#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n;
int triangle[100][100];
int cache[100][100];
// 메모이제이션을 적용한 내 풀이
int sum(int y, int x) {
	int sumNum = triangle[y][x];
	if (y >= n-1)
		return sumNum;

	int& ret = cache[y][x];
	if (ret != -1)
		return ret;

	int pathSum1 = sum(y + 1, x), pathSum2 = sum(y + 1, x + 1);
	sumNum += max(pathSum1, pathSum2);

	ret = sumNum;
	return sumNum;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < i; j++) {
				cin >> triangle[i - 1][j];
			}
		}
		int result = sum(0, 0);
		cout << result << endl;
	}
}