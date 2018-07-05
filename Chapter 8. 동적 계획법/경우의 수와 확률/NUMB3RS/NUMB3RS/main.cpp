#include <iostream>
#include <vector>
using namespace std;

//n = 마을의 수, d = 탈출 후 지금까지 지난 일수
//p = 교도소가 있는 마을, t = 확률을 계산한 마을 수
//q = 확률을 계산할 마을의 번호
int c, n, d, p, t, q;
//cache[i][j] = i번 마을에서 j일 이후에 p마을에 도착할 확률
int A[50][50];
double cache[50][101];

//내 풀이. 책의 답 2와 같이 계산 순서를 반대 방향으로 바꿔
//캐시를 모든 테스트 케이스에 대해 활용할 수 있게 만들었다.
vector<vector<int>> canVisit;
//village번 마을에서 days일 이후에 p마을에 도착할 수 있는 확률을 리턴한다.
double possibility(int village, int days) {
	if (days == 0)	return (village == p ? 1 : 0);

	double& ret = cache[village][days];
	if (ret != -1) return ret;
	
	ret = 0;
	int ways = canVisit[village].size();

	for (int i = 0; i < ways; i++) {
		int nextVillage = canVisit[village][i];
		ret += possibility(nextVillage, days - 1) / canVisit[nextVillage].size();
	}
	return ret;
}

//책의 답 1. 두니발 박사의 탈옥 문제를 해결하는 동적 계획법 알고리즘.
//connected[i][j] = 마을 i, j가 연결되어 있나 여부
//deg[i] = 마을 i와 연결된 마을의 개수
int connected[51][51], deg[51];
//search2(here, days) = 두니발 박사가 days일째에 here번 마을에 숨어 있을 때,
//마지막 날에 q번 마을에 있을 조건부 확률을 반환한다.
//days일째에 here번 마을에 숨어 있다고 가정하고,
//마지막 날에 q번 마을에 숨어 있을 조건부 확률을 반환한다.
double search2(int here, int days) {
	//기저 사례: d일이 지난 경우
	if (days == d) return (here == q ? 1.0 : 0.0);
	//메모이제이션
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < n; there++)
		if (connected[here][there])
			ret += search2(there, days + 1) / deg[here];
	return ret;
}

//책의 답 2. 계산의 순서를 반대 방향으로 바꿔 더 빠르게 구현한 알고리즘.
//search3(here, days) = 탈옥 후 days일째에 두니발 박사가 here번 마을에
//숨어 있을 확룰
double search3(int here, int days) {
	//기저 사례: 0일째
	if (days == 0) return (here == p ? 1.0 : 0.0);
	//메모이제이션
	double& ret = cache[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < n; there++)
		if (connected[here][there])
			ret += search3(there, days - 1) / deg[there];
	return ret;
}
int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 101; j++)
				cache[i][j] = -1;

		cin >> n >> d >> p;
		canVisit = vector<vector<int>>(n);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> A[i][j];
				if (A[i][j] == 1)
					canVisit[i].push_back(j);
			}

		cin >> t;
		for (int i = 0; i < t; i++) {
			cin >> q;
			printf("%.8f ", possibility(q, d));
		}
		cout << endl;
		canVisit.clear();
	}
}