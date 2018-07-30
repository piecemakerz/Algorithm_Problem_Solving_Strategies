#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int T, N, K;
int L[5000], M[5000], G[5000];
int numOfSigns[8030001];

//캐나다 여행 문제를 해결하는 내 무식한 알고리즘
//시간초과가 발생한다.
int simpleSolve() {
	//이 부분에서 시간초과가 발생한다.
	//numOfSigns의 값을 갱신하는 과정은 총 표지판 갯수만큼 이루어지는데,
	//총 표지판 갯수는 적어도 k 이상이며 k만 해도 최댓값이 2^31-1이기 때문이다. 
	for (int i = 0; i < N; i++)
		for (int j = L[i] - M[i]; j <= L[i]; j += G[i])
			numOfSigns[j]++;

	int curSigns = 0;
	for (int i = 0; i < 8030001; i++) {
		curSigns += numOfSigns[i];
		if (curSigns >= K)
			return i;
	}
	return -1;
}

//캐나다 여행 문제를 결정 문제로 바꿔 푸는 이분법 알고리즘

//결정 문제: dist 지점까지 가면서 k개 이상의 표지판을 만날 수 있는가?
bool decision(int dist) {
	int ret = 0;
	for (int i = 0; i < N; i++)
		//i번째 도시 표지판을 하나 이상 보게 되는가?
		if (dist >= L[i] - M[i])
			ret += (min(dist, L[i]) - (L[i] - M[i])) / G[i] + 1;
	return ret >= K;
}
//k번째 표지판을 만나는 지점의 위치를 계산한다.
int optimize() {
	//반복적 불변식: !decision(lo) && decision(hi)
	int lo = -1, hi = 8030001;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		memset(numOfSigns, 0, sizeof(numOfSigns));
		cin >> N >> K;
		for (int i = 0; i < N; i++)
			scanf("%d %d %d", &L[i],  &M[i], &G[i]);
		cout << simpleSolve() << endl;
	}
}