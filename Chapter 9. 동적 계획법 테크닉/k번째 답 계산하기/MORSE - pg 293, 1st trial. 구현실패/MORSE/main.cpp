#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

int n, m, k;
//내 풀이 1. 당연히 시간 초과가 난다.
void morse(int n, int m, vector<char>& morCode) {
	if (n == 0 && m == 0) {
		for (int i = 0; i < morCode.size(); i++)
			cout << morCode[i];
		cout << endl;
		return;
	}

	if (n > 0) {
		morCode.push_back('-');
		morse(n - 1, m, morCode);
		morCode.pop_back();
	}
	if (m > 0) {
		morCode.push_back('o');
		morse(n, m - 1, morCode);
		morCode.pop_back();
	}
}

//책의 무식한 알고리즘
void generate(int n, int m, string s) {
	if (n == 0 && m == 0) {
		cout << s << endl;
		return;
	}
	if (n > 0) generate(n - 1, m, s + "-");
	if (m > 0) generate(n, m - 1, s + "o");
}

//k-1개 건너 뛰는 알고리즘
int skip; // skip 개를 건너뛰고 출력한다.
void generate2(int n, int m, string s) {
	// 기저 사례: skip < 0
	if (skip < 0) return;
	// 기저 사례: n = m = 0
	if (n == 0 && m == 0) {
		//더 건너뛸 신호가 없는 경우
		if (skip == 0) cout << s << endl;
		--skip;
		return;
	}
	if (n > 0) generate2(n - 1, m, s + "-");
	if (m > 0) generate2(n, m - 1, s + "o");
}

//좀 더 똑똑하게 건너뛰는 알고리즘. 내가 생각했던 알고리즘과 굉장히 유사한 방법으로 구현되었다.
//나는 이 아이디어를 n+mCn을 구하는데 너무 시간이 많이 걸리고, 오버플로우가 발생할 것이라고 생각했기 때문에 폐기했다.
const int M = 1000000000 + 100; // K의 최대값+100, 오버플로를 막기 위해 이보다 큰 값은 구하지 않는다.
//상수 M으로 인해 내가 아이디어를 폐기했던 이유를 해결했다.
int bino[201][201];
//필요한 모든 이항계수를 미리 계산해둔다.
void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++)
			bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
	}
}

void generate3(int n, int m, string s) {
	if(skip < 0) return;
	if (n == 0 && m == 0) {
		if (skip == 0) cout << s << endl;
		--skip;
		return;
	}
	if (bino[n + m][n] <= skip) { // 남아있는 신호의 수 보다 skip이 더 클 때, 굳이 신호를 만들어가며 확인할 필요가 없다.
		skip -= bino[n + m][n];
		return;
	}
	if (n > 0) generate3(n - 1, m, s + "-");
	if (m > 0) generate3(n, m - 1, s + "o");
}

//좀 더 깔끔한 구현
//n개의 -, m개의 o로 구성된 신호 중 skip개를 건너뛰고 만들어지는 신호를 반환한다.
string kth(int n, int m, int skip) {
	//n == 0인 경우 나머지 부분은 전부 o일 수밖에 없다.
	if (n == 0) return string(m, 'o');
	if (skip < bino[n + m - 1][n - 1]) // 첫 글자가 장점으로 시작하는 신호의 수가 skip보다 크다면 이를 선택한다.
		return "-" + kth(n - 1, m, skip);
	return "o" + kth(n, m - 1, skip - bino[n+m-1][n-1]);
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		vector<char> morCode;
		cin >> n >> m >> k;	
		morse(n, m, morCode);
	}
	return 0;
}