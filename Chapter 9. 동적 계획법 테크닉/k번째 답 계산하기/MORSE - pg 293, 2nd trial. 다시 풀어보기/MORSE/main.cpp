#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int C, k;

int combCache[201][101];
const int MAX = 1000000001;
int total;

//내 풀이. k번째 신호를 찾기 위해 건너뛰어야 하는 신호의 수 skip
//변수만을 필요로 하는 책의 답과 달리 내 풀이는 k번째 신호를
//찾을 가능성이 있는 모든 경우의 수 remain과 전역 변수 k 두 개의 변수를
//필요로 한다.

//nCr의 값을 계산하는 함수. MAX를 넘어가는 값들은
//모두 MAX로 간주한다.
int combination(int n, int r) {
	if (n == r || r == 0) return 1;

	int& ret = combCache[n][r];
	if (ret != -1) return ret;

	ret = combination(n - 1, r - 1) + combination(n - 1, r);
	if (ret > MAX)
		ret = MAX;
	combCache[n][n - r] = ret;
	return ret;
}

//remain = k번째 신호를 찾을 수 있는 모든 남아있는 경우의 수
string morse(int n, int m, int remain) {
	//더 이상 고를 수 있는 긴 신호가 없을 경우 남은 모든 짧은 신호를 리턴한다.
	if (n == 0)
		return string(m, 'o');
	//더 이상 고를 수 있는 짧은 신호가 없을 경우 남은 모든 긴 신호를 리턴한다.
	else if (m == 0)
		return string(n, '-');
	
	//"-"를 선택했을 경우 이후 경우의 수
	int selLong = combination(n + m - 1, m);

	//"-"를 선택했을 때 이후 k번째 신호를 얻을 수 있다면 "-"를 선택한다.
	if (selLong >= k)
		return "-" + morse(n - 1, m, selLong);
	//"-"를 선택했을 때 k번째 신호를 얻을 수 없다면 "o"를 선택한다.
	else {
		k -= selLong;
		return "o" + morse(n, m - 1, remain - selLong);
	}
}

//책의 모든 모스 신호를 만드는 완전 탐색 알고리즘.
//s: 지금까지 만든 신호
//n: 더 필요한 -의 개수
//m: 더 필요한 o의 개수
void generate(int n, int m, string s) {
	//기저 사례: n=m=0
	if (n == 0 && m == 0) {
		cout << s << endl;
		return;
	}
	if (n > 0) generate(n - 1, m, s + "-");
	if (m > 0) generate(n, m - 1, s + "o");
}

//k-1개 건너뛰고 첫 번째 신호를 출력하는 알고리즘
//모든 신호는 사전순으로 생성되므로 함수 호출 전에
//skip을 k-1로 초기화하면 skip = 0일 때 k번째 신호가 생성된다.
int skip;
//skip개를 건너뛰고 출력한다.
void generate2(int n, int m, string s) {
	//기저 사례: skip < 0
	if (skip < 0) return;
	//기저 사례: n=m=0
	if (n == 0 && m == 0) {
		//더 건너뛸 신호가 없는 경우
		if (skip == 0) cout << s << endl;
		skip--;
		return;
	}
	if (n > 0) generate2(n - 1, m, s + "-");
	if (m > 0) generate2(n, m - 1, s + "o");
}

//k-1개 건너뛰고 첫 번째 신호를 출력하는 동적 계획법 알고리즘
//K의 최대값+100. 오버플로를 막기 위해 이보다 큰 값은 구하지 않는다.
const int M = 1000000000 + 100;
int bino[201][201];
//필요한 모든 이항계수를 미리 계산해 둔다.
void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++)
			bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
	}
}
//skip개를 건너뛰고 출력한다.
void generate3(int n, int m, string s) {
	//기저 사례: skip < 0
	if (skip < 0) return;
	//기저 사례: n=m=0
	if (n == 0 && m == 0) {
		if (skip == 0) cout << s << endl;
		skip--;
		return;
	}
	if (bino[n + m][n] <= skip) {
		skip -= bino[n + m][n];
		return;
	}
	if (n > 0) generate3(n - 1, m, s + "-");
	if (m > 0) generate3(n, m - 1, s + "o");
}
//책의 k번째 신호를 계산하는 알고리즘
//n개의 -, m개의 o로 구성된 신호 중 skip개를 건너뛰고
//만들어지는 신호를 반환한다.
string kth(int n, int m, int skip) {
	//n == 0인 경우 나머지 부분은 전부 o일 수밖에 없다.
	if (n == 0) return string(m, 'o');
	if (skip < bino[n + m - 1][n - 1])
		return "-" + kth(n - 1, m, skip);
	return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
}

int main(void) {
	cin >> C;
	memset(combCache, -1, sizeof(combCache));

	for (int test = 0; test < C; test++) {
		//n = 긴 신호의 수(-), m = 짧은 신호의 수(o)
		//k = 찾으려는 신호
		int n, m;
		cin >> n >> m >> k;
		total = combination(n + m, m);
		cout << morse(n, m, total) << endl;
	}
}