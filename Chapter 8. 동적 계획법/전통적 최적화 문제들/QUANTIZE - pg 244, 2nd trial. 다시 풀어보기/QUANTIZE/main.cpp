#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int C, n, s;
const int INF = 987654321;
vector<int> Seq;

int cache[11][101];
int SquaredCache[100][100];

//내가 작성한 조각의 최소 오차 제곱 합 산출 코드.
//O(N)의 시간이 걸린다.
//캐시를 도입하여 중복된 조각에 대한 오차 제곱 합을
//계산하지 않도록 설계하였다.
int calSquaredError(int start, int end) {
	int& ret = SquaredCache[start][end];
	if (ret != -1)
		return ret;

	int sum = 0;
	for (int i = start; i <= end; i++)
		sum += Seq[i];
	int mean = floor<int>(((double)sum / (end - start + 1)) + 0.5);
	sum = 0;

	for (int i = start; i <= end; i++) {
		sum += (Seq[i] - mean) * (Seq[i] - mean);
	}
	return ret = sum;
}

//책의 부분합을 계산하는 코드.
//pSum[]: Seq[]의 부분합을 저장한다. pSum[i]는 A[0]...A[i]의 합
//pSqSum[]: Seq[] 제곱의 부분합을 저장한다. pSqSum[i]는 A[0]^2...A[i]^2의 합
int pSum[101], pSqSum[101];
void precalc() {
	pSum[0] = Seq[0];
	pSqSum[0] = Seq[0] * Seq[0];
	for(int i = 1; i < n; i++) {
		pSum[i] = pSum[i - 1] + Seq[i];
		pSqSum[i] = pSqSum[i - 1] + Seq[i] * Seq[i];
	}
}

//책의 최소 오차 제곱 합 산출 코드. 부분합을 이용하여
//O(1)에 오차 제곱 합을 구할 수 있다.
//Seq[lo]...Seq[hi] 구간을 하나의 숫자로 표현할 때 최소 오차 합을 계산한다.
int minError(int lo, int hi) {
	//부분합을 이용해 Seq[lo] ~ Seq[hi]까지의 합을 구한다.
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);
	//평균을 반올림한 값으로 이 수들을 표현한다.
	int m = int(0.5 + (double)sum / (hi - lo + 1));
	//sum(A[i]-m)^2를 전개한 결과를 부분 합으로 표현
	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
	return ret;
}
//책의 답. '다음 조각의 시작점'을 기준으로 반복문을 작성한
//내 풀이와 달리 '현재 조각의 길이'를 기준으로 반복문을 작성하였다.
int quantize(int from, int parts) {
	if (from == n) return 0;
	if (parts == 0) return INF;

	int& ret = cache[parts][from];
	if (ret != INF) return ret;

	for (int partSize = 1; from + partSize <= n; partSize++)
		ret = min(ret, minError(from, from+partSize-1) + 
						quantize(from+partSize, parts-1));
	return ret;
}

//내 풀이 1. 책의 풀이와 논리구조가 완벽하게 같으나
//예외처리가 잘못되어 오답이 나왔었다. 현재는 예외처리를
//수정하여 정답이다.
int myQuantize(int start, int slice) {
	//start가 Seq의 범위를 벗어나는 경우를 예외처리 해주며,
	//나눌 수 있는 조각의 수가 현재 남아있는 수보다 작거나 같다면
	//남아있는 모든 수를 하나의 조각으로 취급할 시 오차가 0이 되므로
	//0을 리턴한다.
	if (start >= n - slice || start == n)
		return 0;
	//조각이 하나 남았다면 재귀호출을 하지 않고
	//남아있는 수들을 모두 마지막 조각으로 취급한다.
	else if (slice == 1)
		return calSquaredError(start, n - 1);

	int& ret = cache[slice - 1][start];
	if (ret != INF) return ret;

	//다음 조각의 시작점으로 가능한 모든 시작점에 대해 재귀호출을 시행한다.
	for (int i = start + 1; i < n; i++)
		ret = min(ret, myQuantize(i, slice - 1) + calSquaredError(start, i - 1));
	return ret;
}

//내 풀이 2. 책 풀이를 참고하여 수정한 내 풀이.
//예외처리가 좀 더 직관적이다.
int myQuantize2(int start, int slice) {
	if (start == n)	return 0;
	if (slice == 0) return INF;
	int& ret = cache[slice - 1][start];
	if (ret != INF) return ret;

	for (int next = start + 1; next <= n; next++)
		ret = min(ret, myQuantize2(next, slice - 1) + calSquaredError(start, next - 1));
	return ret;
}


int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		for (int i = 0; i < 11; i++)
			for (int j = 0; j < 101; j++)
				cache[i][j] = INF;

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				SquaredCache[i][j] = -1;

		cin >> n >> s;
		Seq = vector<int>(n);
		for (int i = 0; i < n; i++)
			cin >> Seq[i];
		sort(Seq.begin(), Seq.end());
		precalc();
		cout << quantize(0, s) << endl;
		Seq.clear();
	}
	return 0;
}