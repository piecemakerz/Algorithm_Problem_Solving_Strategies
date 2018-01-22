#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;
//중복을 제거하지 않은 이항 계수 알고리즘
int bino(int n, int r) {
	if (r == 0 || n == r) return 1;
	return bino(n - 1, r - 1) + bino(n - 1, r);
}

//메모이제이션을 이용해 (캐시 배열 도입) 중복을 제거한 이항 계수 알고리즘
int cache[30][30];
int bino2(int n, int r) {
	if (r == 0 || n == r) return 1;
	if (cache[n][r] != -1) {
		return cache[n][r];
	}
	return cache[n][r] = bino2(n - 1, r - 1) + bino2(n - 1, r);
}

int main(void) {
	memset(cache, -1, sizeof(cache)); // memset으로 정수 배열에 0 혹은 -1을 채울 수 있다.
	clock_t start, end;
	double duration;

	start = clock();
	cout<<bino(29, 15)<<endl;
	end = clock();
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "걸린 시간 : " << duration << "초"<< endl;

	memset(cache, -1, sizeof(cache));

	start = clock();
	cout << bino2(29, 15) << endl;
	end = clock();
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "걸린 시간 : " << duration << "초" << endl;
	
}