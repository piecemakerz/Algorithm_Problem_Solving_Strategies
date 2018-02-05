#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int N;
vector<vector<int>> triangle;
int cache[101][101];
int counterCache[101][101];

int Tripath(int y=0, int x=0) {
	if (y == N-1)
		return triangle[y][x];
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	int down = Tripath(y + 1, x);
	int right = Tripath(y + 1, x + 1);
	return ret = triangle[y][x] + (down > right ? down : right);
}

int TripathCount(int y=0, int x=0) {
	if (y == N-1)
		return 1;
	int& ret = counterCache[y][x];
	if (ret != -1) return ret;
	int down = Tripath(y + 1, x);
	int right = Tripath(y + 1, x + 1);
	int pathCount = 0;

	if (down >= right)
		pathCount += TripathCount(y + 1, x);
	if (down <= right)
		pathCount += TripathCount(y + 1, x + 1);
	return ret = pathCount;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(cache, -1, sizeof(cache));
		memset(counterCache, -1, sizeof(counterCache));
		
		cin >> N;
		int input;
		triangle = vector<vector<int>>(N);
		for (int i = 0; i < N; i++) {
			triangle[i] = vector<int>(i + 1);
			for (int j = 0; j <= i; j++) {
				cin >> input;
				triangle[i][j] = input;
			}
		}
		cout << TripathCount() << endl;
	}
	return 0;
}