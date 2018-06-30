#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 100;
int C, n;
int triangle[MAX_N][MAX_N];

int findLongestPath() {
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
		}
	}
	return triangle[0][0];
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= i; j++)
				cin >> triangle[i][j];
		cout << findLongestPath() << endl;
	}
	return 0;
}