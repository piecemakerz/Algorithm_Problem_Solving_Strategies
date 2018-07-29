#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int C, N;
double mindis, maxdis;
const double MAX = 987654321.0;
vector<pair<double, double>> coord;
vector<vector<pair<double, int>>> dist;

void generateDistance() {
	mindis = MAX, maxdis = 0;
	for (int i = 0; i < N; i++) {
		double x1 = coord[i].second, y1 = coord[i].first;
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			double x2 = coord[j].second, y2 = coord[j].first;
			double dis = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			dist[i].push_back(make_pair(dis, j));
			if (mindis > dis) mindis = dis;
			if (maxdis < dis) maxdis = dis;
		}
		sort(dist[i].begin(), dist[i].end());
	}
}

bool solve(double gap) {
	int selected[100];
	memset(selected, 0, sizeof(selected));
	int curPos = 0;
	while (true) {
		for (int i = 0; i < dist[curPos].size(); i++) {
			double curdist = dist[curPos][i].first;
			int nextPos = dist[curPos][i].second;
			if (selected[nextPos]) continue;
			if (curdist > gap) return false;
			else
			{
				selected[curPos] = 1;
				curPos = nextPos;
				break;
			}
		}
	}
	return true;
}

//가능한 최소 통신 반경을 반환한다.
double optimize() {
	double lo = mindis, hi = maxdis;
	//반복적 불변식: !solve(lo) && solve(hi)
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2.0;
		//반경이 mid일 때 모든 기지가 통신할 수 있다면 답은 [lo, mid]에 있다.
		if (solve(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N;
		coord = vector<pair<double, double>>(N);
		dist = vector<vector<pair<double, int>>>(N, vector<pair<double, int>>(N-1));
		double x, y;
		for(int i=0; i<N; i++)
			for (int j = 0; j < N; j++) {
				cin >> x >> y;
				coord[i] = make_pair(y, x);
			}
		generateDistance();
		cout << optimize() << endl;
		coord.clear();
		dist.clear();
	}
}