#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, triangle[100][100];
int C[100][100];
int C2[2][10000];
int iterative() {
	//기저 사례를 계산한다.
	for (int x = 0; x < n; x++)
		C[n - 1][x] = triangle[n - 1][x];
	//다른 부분을 계산한다.
	for (int y = n-2; y >= 0; y--)
		for (int x = 0; x < y + 1; x++) {
			C[y][x] = max(C[y + 1][x], C[y + 1][x + 1]) + triangle[y][x];
		}
	return C[0][0];
}

int iterative2() {
	//ㅣ기저 사례를 계산한다.
	for (int x = 0; x < n; x++)
		C2[(n - 1) % 2][x] = triangle[n - 1][x];
	//다른 부분을 계산한다.
	for(int y=n-2; y>=0; y--)
		for (int x = 0; x < y + 1; x++) {
			C2[y % 2][x] = max(C2[(y + 1) % 2][x], C2[(y + 1) % 2][x + 1]) + triangle[y][x];
		}
	return C2[0][0];
}