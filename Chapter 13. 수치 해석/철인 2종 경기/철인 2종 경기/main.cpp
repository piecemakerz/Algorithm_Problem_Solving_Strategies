#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

double t; // 총 구간 거리
vector<double> runSpeed, cycleSpeed;
//달리기 구간의 길이가 run일 때, i번 선수가 걸리는 시간
double time(int i, double run) {
	double cycle = t - run;
	return run / runSpeed[i] + cycle / cycleSpeed[i];
}

//달리기 구간 길이가 r일 때, others(r) - cheaper(r)를 반환한다.
double diff(double r) {
	int n = runSpeed.size();
	double cheater = time(n - 1, r);
	double others = time(0, r);
	for (int i = 1; i < n - 1; i++)
		others = min(others, time(i, r));
	return others - cheater;
}

//diff() 함수의 최대치의 위치를 삼분 검색으로 계산한다.
double maxDifference() {
	double lo = 0, hi = t;
	for (int it = 0; it < 100; it++) {
		double aab = (2 * lo + hi) / 3;
		double abb = (lo + 2 * hi) / 2;
		if (diff(aab) > diff(abb))
			hi = abb;
		else
			lo = aab;
	}
	return (lo + hi) / 2;
}