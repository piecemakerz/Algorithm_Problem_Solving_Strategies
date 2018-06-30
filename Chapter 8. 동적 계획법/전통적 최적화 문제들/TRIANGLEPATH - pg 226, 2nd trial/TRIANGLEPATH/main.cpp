#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 100;
int C, n;
int triangle[MAX_N][MAX_N];

//내 답. 책의 답의 접근방식인 top-down 방식이 아닌 down-top방식을 사용하여
//굳이 캐시배열을 사용하지 않아도 각 위치에 대한 계산을 한번씩만 하도록 하였다.
//삼각형의 맨 아랫줄의 바로 윗줄에서 시작하여, 둘 중 큰 수를 골라 현재 수와 그 수를
//더한 값으로 triangle값을 갱신한다.

int findLongestPath() {
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
		}
	}
	return triangle[0][0];
}

//책의 답. 삼각형 위의 최대 경로 문제를 푸는 동적 계획법 알고리즘
//캐시배열을 사용하므로써 각 위치에 대한 함수호출은 한번씩만 발생한다.
int cache[100][100];
//(y, x) 위치부터 맨 아래줄까지 내려가면서 얻을 수 있는 최대 경로의 합을 반환한다.
int path(int y, int x) {
	//기저 사례
	if (y == n - 1) return triangle[y][x];
	//메모이제이션
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	return ret = triangle[y][x] + max(path(y + 1, x), path(y + 1, x + 1));
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