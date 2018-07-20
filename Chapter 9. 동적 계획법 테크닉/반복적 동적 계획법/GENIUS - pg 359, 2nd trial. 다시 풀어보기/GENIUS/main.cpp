#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int C, n, k, m;
int L[50];
double T[50][50];
int Q;

//지니어스 문제를 해결하는 재귀호출 동적계획법 알고리즘.
//너무 큰 크기의 캐시배열을 필요로 하므로 스택 오버플로가 발생한다.

//cache[i][j] = 여태까지 음악을 들은지 i의 시간이 지났고,
//현재 듣는 음악이 j번 음악일 때, k분 30초에 Q번 음악을
//듣고 있을 확률
//double cache[1000005][50];
/*
double play(int timepassed, int cur) {
	if (timepassed > k)
		if (cur == Q)
			return 1.0;
		else
			return 0.0;

	double& ret = cache[timepassed][cur];
	if (ret != -1.0) return ret;

	ret = 0.0;
	for(int next = 0; next < n; next++)
		ret += play(timepassed + L[next], next) * T[cur][next];

	return ret;
}
*/

//지니어스 문제를 해결하는 반복적 동적계획법 알고리즘 1.
//알고리즘만 반복적으로 바꼈을 뿐 큰 크기의 캐시배열을 필요로 하는것은 동일하므로
//스택 오버플로가 발생한다.

//c[i][j] = 현재까지 i의 시간이 흘렀을 때, j번 음악이 실행 시작할 확률
//play2()를 한번 실행한 후 확률을 구해야 하는 모든 Q에 대하여 
//c[k-L[Q]+1...k][Q]를 계산하면 정답을 찾을 수 있다.
/*
double c[1000005][50];
void play2() {
	for (int timepassed = L[0]; timepassed <= k; timepassed++) {
		for (int prev = 0; prev < n; prev++)
			if (timepassed >= L[prev] && c[timepassed - L[prev]][prev] != 0.0)
				for (int next = 0; next < n; next++)
					c[timepassed][next] += c[timepassed - L[prev]][prev] * T[prev][next];
	}
}
*/

//지니어스 문제를 해결하는 반복적 동적계획법 알고리즘 2.
//캐시배열에 슬라이딩 윈도 테크닉을 적용하여 크기를 대폭 줄였으므로
//스택 오버플로가 발생하지 않는다.
double c[5][50];
void play3() {
	for (int timepassed = L[0]; timepassed <= k; timepassed++) {
		for (int i = 0; i < n; i++)
			//c[timepassed]의 값을 구하기 위해서는 c[timepassed-1...timepassed-4]의 값만을 필요로
			//하므로, 현재 for문에서 계산한 결과값을 저장할 c[timepassed % 5]의 값을 모두 0으로 바꾼다.
			c[timepassed % 5][i] = 0.0;

		for (int prev = 0; prev < n; prev++) {
			if (timepassed >= L[prev] && c[(timepassed - L[prev])%5][prev] != 0.0) {
				for (int next = 0; next < n; next++) {
					c[timepassed % 5][next] += c[(timepassed - L[prev])%5][prev] * T[prev][next];
				}
			}
		}
	}
}

//책의 지니어스 문제를 해결하는 반복적 동적 계획법 알고리즘
vector<double> getProb1() {
	//c[time][song] = time분 후에 song번 노래가 시작할 확률
	double c[5][50];
	memset(c, 0, sizeof(c));
	c[0][0] = 1.0;
	for(int time = 1; time <= k; time++)
		for (int song = 0; song < n; song++) {
			double& prob = c[time % 5][song];
			prob = 0;
			for (int last = 0; last < n; last++)
				prob += c[(time - L[last] + 5) % 5][last] * T[last][song];
		}
	vector<double> ret(n);
	//song번 노래가 재생되고 있을 확률을 계산한다.
	for (int song = 0; song < n; song++)
		//song번 노래가 시작했을 시간을 모두 찾아 더한다.
		for (int start = k - L[song] + 1; start <= k; start++)
			ret[song] += c[start % 5][song];
	return ret;
}

//책의 지니어스 문제를 해결하는 행렬의 거듭제곱 동적 계획법
//k분 30초 후에 각 곡이 재생되고 있을 확률을 반환한다.
vector<double> getProb2() {
	SquareMatricx W(4 * n);
	//첫 3*n개의 원소는 그대로 복사해온다.
	for (int i = 0; i < 3 * n; i++)
		W[i][i + n] = 1.0;
	//마지막 n개의 원소는 이전 원소들의 선형 결합으로 이루어진다.
	for (int i = 0; i < n; i++)
		//C[time+1][i] = C[time+1-L[j][j]] * T[j][i]
		for (int j = 0; j < n; j++)
			W[3 * n + i][(4 - L[j])*n + j] = T[j][i];
	SquareMatrix Wk = W.pow(k);
	vector<double> ret(n);
	//song번 노래가 재생되고 있을 확률을 계산한다.
	for (int song = 0; song < n; song++)
		//song번 노래가 시작했을 시간을 모두 찾아 더한다.
		for (int start = 0; start < L[song]; start++)
			ret[song] += Wk[(3 - start)*n + song][3 * n];
	return ret;
}
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n >> k >> m;
		for (int i = 0; i < n; i++)
			cin >> L[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> T[i][j];

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 50; j++)
				c[i][j] = 0.0;

		c[0][0] = 1.0;
		play3();

		for (int i = 0; i < m; i++) {
			double ret = 0.0;
			cin >> Q;
			int length = L[Q];
			for (int i = 0; i < length; i++)
				ret += c[(k-i)%5][Q];
			printf("%.8lf ", ret);
		}
		cout << endl;
	}
	return 0;
}