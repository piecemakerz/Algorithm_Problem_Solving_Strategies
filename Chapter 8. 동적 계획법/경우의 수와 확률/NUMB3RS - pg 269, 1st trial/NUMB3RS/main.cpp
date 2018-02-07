#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N, D, P; // N = 지도에 포함된 마을의 수, D = 탈출 후 지금까지 지난 일수, P = 교도소가 있는 마을의 번호
int T; // T = 확률을 계산할 마을의 수
vector<vector<int>> villagePath; // 마을 길 정보
vector<vector<int>> connectedVillage; // 각 마을마다 연결되어 있는 마을들 정보
double cache[101][51]; // cache[일자][마을]

double villagePerCounter(int day, int curPos) { // day 후에 curPos에 있을 확률. 계산하고자 하는 마을에서부터 교도소가 있는 마을까지 가는 경로를 거꾸로 되짚는다.
	if (day == 0) { // 기저사례: 교도소가 있는 마을에서 시작하는 경우 1.0 아니면 0.0
		if (curPos == P)
			return 1.0;
		else
			return 0.0;
	}
	double& ret = cache[day][curPos];
	if (ret != -1.0) return ret;
	ret = 0.0;

	for (int i = 0; i < connectedVillage[curPos].size(); i++) {
		int nextPos = connectedVillage[curPos][i];
		ret += villagePerCounter(day - 1, nextPos) / connectedVillage[nextPos].size(); // 재귀호출한 결과값을 이전에 방문한 마을에 있는 길의 수만큼으로 나누기
	}
	return ret;
}

// 책의 답 1. 메모이제이션을 적용하지 않은 완전 탐색 알고리즘
int Q;
//connected[i][j] = 마을 i,j가 연결되어 있나 여부
//deg[i] = 마을 i와 연결된 마을의 개수
int connected[51][51], deg[51];
double search(vector<int>& path) {
	if (path.size() == D + 1) {
		if (path.back() != Q) return 0.0;
		double ret = 1.0;
		//path의 출현 확률 계산
		for (int i = 0; i + 1 < path.size(); i++)
			ret /= deg[path[i]];
		return ret;
	}
	double ret = 0;
	// 경로의 다음 위치 설정
	for (int there = 0; there < N; there++) {
		if (connected[path.back()][there]) {
			path.push_back(there);
			ret += search(path);
			path.pop_back();
		}
	}
	return ret;
}

// 책의 답 2. 메모에제이션을 적용한 동적 계획법 알고리즘
// double cache[51][101] - cache[현재 위치][일자]
double search2(int here, int days) {
	//기저사례: d일이 지난 경우
	if (days == D) return (here == Q ? 1.0 : 0.0);
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < N; there++) {
		if (connected[here][there])
			ret += search2(there, days + 1) / deg[here];
	}
	return ret;
}

// 책의 답 3. 계산의 순서를 반대 방향으로 바꾼 알고리즘. 내 알고리즘과 해결 방식이 같다.
double search3(int here, int days) {
	if (days == 0) return (here == P ? 1.0 : 0.0);
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < N; there++)
		if (connected[here][there])
			ret += search3(there, days - 1) / deg[there];
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		for(int i=0; i<101; i++)
			for (int j = 0; j < 51; j++)
				cache[i][j] = -1.0;

		int input;
		cin >> N >> D >> P;
		villagePath = vector<vector<int>>(N);
		connectedVillage = vector<vector<int>>(N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> input;
				villagePath[i].push_back(input);
				if (input == 1)
					connectedVillage[i].push_back(j);
			}
		}
		cin >> T;
		for (int i = 0; i < T; i++) {
			cin >> input;
			printf("%.8f ", villagePerCounter(D, input));
		}
		cout << endl;
	}
	return 0;
}