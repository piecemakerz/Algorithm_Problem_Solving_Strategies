#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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
	for (int it; it < 100; it++) {
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
