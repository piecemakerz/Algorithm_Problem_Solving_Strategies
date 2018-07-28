#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

int C, N, M;
//결정 문제: 정렬되어 있는 locations 중 cameras를 선택해 모든 카메라 간의 간격이
//gap 이상이 되는 방법이 있는지를 반환한다.
bool decision(const vector<double>& location, int cameras, double gap) {
	//카메라를 설치할 수 있을 때마다 설치하는 탐욕적 알고리즘
	double limit = -1;
	int installed = 0;
	for (int i = 0; i < location.size(); i++) {
		if (limit <= location[i]) {
			installed++;
			//location[i] + gap 이후는 되어야 카메라를 설치할 수 있다.
			limit = location[i] + gap;
		}
	}
	//결과적으로 cameras대 이상을 설치할 수 있었으면 성공
	return installed >= cameras;
}

//최적화 문제: 정렬되어 있는 locations 중 cameras를 선택해 최소 간격을 최대화한다.
double optimize(const vector<double>& location, int cameras) {
	double lo = 0, hi = 241;
	//반복문 불변식: desicion(lo) == true. decision(hi) == false
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2.0;
		//간격이 mid 이상이 되도록 할 수 있으면 답은 [mid, hi]에 있다.
		if (decision(location, cameras, mid))
			lo = mid;
		//간격이 mid 이상이 되도록 할 수 없으면 답은 [lo, mid]에 있다.
		else
			hi = mid;
	}
	return hi;
}

//동적 계획법으로 해결한 DARPA 문제
vector<double> cameraLocation;
const double MAX = 987654321.0;
double cache[201][101];
//현재 위치가 curPos이고 left개의 카메라를 더 설치해야 할 때,
//남은 카메라를 모두 설치하여 얻을 수 있는 두 카메라 간의 최대 간격을
//반환한다.
double darpaDynamic(int curPos, int left) {
	if (left == 0)
		return MAX;

	double& ret = cache[curPos + 1][left];
	if (ret != -1.0) return ret;
	ret = 0;

	int maxNext = M - left;
	for (int i = curPos + 1; i <= maxNext; i++) {
		double nextResult = darpaDynamic(i, left - 1);
		if (curPos != -1)
			nextResult = min(cameraLocation[i] - cameraLocation[curPos], nextResult);
		ret = max(ret, nextResult);
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		for (int i = 0; i < 201; i++)
				for (int j = 0; j < 101; j++)
					cache[i][j] = -1.0;
		double input;
		cin >> N >> M;
		for (int i = 0; i < M; i++) {
			cin >> input;
			cameraLocation.push_back(input);
		}
		printf("%.2f\n", darpaDynamic(-1, N));
		cameraLocation.clear();
	}
}