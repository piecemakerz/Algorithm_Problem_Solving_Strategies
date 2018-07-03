#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 100;
int c, n, m;
vector<int> A, B;
int cache[MAX+1][MAX+1];

//구현실패의 이유: 나는 모든 가능한 시작위치에 대해 일일히 검사를 하면
//함수가 너무 느려 동작하지 않을 수도 있다고 생각했다.
//물론, 이전 함수를 이 문제에 적용하는 방법도 생각해내지 못했다.

//책의 답
//입력이 32비트 부호 있는 정수의 모든 값을 가질 수 있으므로
//인위적인 최소치는 64비트여야 한다.
const long long NEGINF = numeric_limits<long long>::min();
//min(A[indexA], B[indexB]), max(A[indexA], B[indexB])로 시작하는
//합친 증가 부분 수열의 최대 길이를 반환한다.
//단 indexA == indexB == -1 혹은 A[indexA] != B[indexB]라고 가정한다.

//jlis(indexA, indexB)가 호출되었다는 것은 A[indexA]와 B[indexB]가 이미
//합친 증가 부분수열에 포함되었음을 의미하며, max(A[indexA], B[indexB])가
//합친 증가 부분수열의 마지막 값임을 의미하기도 한다.
int jlis(int indexA, int indexB) {
	//메모이제이션
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1) return ret;
	//A[indexA], B[indexB]가 이미 존재하므로 2개는 항상 있다.
	ret = 2;
	//수열 A와 B에서의 모든 가능한 시작위치에 대한 증가 부분 수열을 확인하기 위해
	//indexA와 indexB가 -1인 경우 maxElement를 인위적인 최소치로 초기화한다.
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	long long maxElement = max(a, b);
	//다음 원소를 찾는다.
	for (int nextA = indexA + 1; nextA < n; nextA++)
		if (maxElement < A[nextA])
			ret = max(ret, jlis(nextA, indexB) + 1);
	for (int nextB = indexB + 1; nextB < m; nextB++)
		if (maxElement < B[nextB])
			ret = max(ret, jlis(indexA, nextB) + 1);
	return ret;
}

int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		memset(cache, -1, sizeof(cache));
		cin >> n >> m;
		A = vector<int>(n);
		B = vector<int>(m);
		for (int i = 0; i < n; i++)
			cin >> A[i];
		for (int i = 0; i < m; i++)
			cin >> B[i];
		cout << jlis(-1, -1) - 2 << endl;
		A.clear();
		B.clear();
	}
	return 0;
}