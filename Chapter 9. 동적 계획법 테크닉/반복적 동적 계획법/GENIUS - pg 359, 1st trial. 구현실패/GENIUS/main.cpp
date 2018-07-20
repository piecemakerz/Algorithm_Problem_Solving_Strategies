#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
int n, k, m;
int Q;
int length[50];
double T[50][50];
double cache[1000001][50]; // [현재 시간][현재 곡]

//start(time, song) = 재생을 시작한지 time분 후에 song번 노래가 재생을 시작할 확률.
//책의 반복적 동적 계획법 알고리즘을 참고하여 만든 재귀호출 동적 계획법 알고리즘이다.
//물론, 슬라이딩 윈도 기법을 적용할 수 없기 때문에 매우 큰 메모리가 필요하다.
double start(int time, int song) {
	if (time < 0)
		return 0;

	double& ret = cache[time][song];
	if (ret != -1.0)
		return ret;
	 
	ret = 0.0;
	for (int prev = 0; prev < n; prev++)
		ret += T[prev][song] * start(time - length[prev], prev);

	return ret;
}

//반복적 동적 계획법 알고리즘. 슬라이딩 윈도 기법을 사용하여 캐시의 메모리를 줄였다.
vector<double> getProb1() {
	//c[time][song] = time분 후에 song번 노래가 시작할 확률
	double c[5][50];
	memset(c, 0, sizeof(c));
	c[0][0] = 1.0;
	for(int time = 1; time < k; time++)
		for (int song = 0; song < n; song++) {
			double& prob = c[time%5][song];
			prob = 0;
			for (int last = 0; last < n; last++)
				prob += c[(time - length[last] + 5) % 5][last] * T[last][song];
		}

	vector<double> ret(n);
	//song번 노래가 재생되고 있을 확률을 계산한다.
	for (int song = 0; song < n; song++)
		//song번 노래가 시작했을 시간을 모두 찾아 더한다.
		for (int start = k - length[song] + 1; start <= k; start++)
			ret[song] += c[start % 5][song];
	return ret;
}

//행렬 거듭제곱을 이용한 동적 계획법의 구현.
//k분 30초 후에 각 곡이 재생되고 있을 확률을 반환한다.
typedef vector<vector<int>> Matrix;
const int M = 100000;
Matrix operator * (const Matrix& a, const Matrix& b)
{
	int n = a.size();
	Matrix ret(n, vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				(ret[i][j] += (a[i][k] * (long long)b[k][j]) % M) %= M;
	return ret;
}

struct SquareMatrix {
	Matrix mat;
	int size() const { return mat.size(); }
	SquareMatrix(int n) : mat(vector<vector<int> >(n, vector<int>(n, 0))) {}
	SquareMatrix(vector<vector<int> > m) : mat(m) {}
	vector<int>& operator [] (int idx) { return mat[idx]; }
};

SquareMatrix operator * (const SquareMatrix& a, const SquareMatrix& b) {
	return SquareMatrix(a.mat * b.mat);
}

SquareMatrix pow(SquareMatrix a, int p)
{
	if (p == 0) {
		int n = a.size();
		SquareMatrix ret(n);
		for (int i = 0; i < n; i++)
			ret[i][i] = 1;
		return ret;
	}
	if (p % 2) return pow(a, p - 1) * a;
	SquareMatrix half = pow(a, p / 2);
	return half * half;
}

// k분 30초 후에 각 곡이 재생되고 있을 확률을 반환한다.
vector<double> getProb2() {
	SquareMatrix W(4 * n);
	//첫 3*n개의 원소는 그대로 복사해온다.
	for (int i = 0; i < 3 * n; i++)
		W[i][i + n] = 1.0;
	//마지막 n개의 원소는 이전 원소들의 선형 결합으로 이루어진다.
	for (int i = 0; i < n; i++)
		//C[time+1][i] = C[time+1-length[j]] * T[j][i]
		for (int j = 0; j < n; j++)
			W[3 * n + i][(4 - length[j])*n + j] = T[j][i];
	SquareMatrix Wk = pow(W, k);
	vector<double> ret(n);
	//song번 노래가 재생되고 있을 확률을 계산한다.
	for (int song = 0; song < n; song++)
		//song번 노래가 시작했을 시간을 모두 찾아 더한다.
		for (int start = 0; start < length[song]; start++)
			ret[song] += Wk[(3 - start)*n + song][3 * n];
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n >> k >> m; // 곡 수/시간/좋아하는 곡 수
		for (int i = 0; i < n; i++)
			cin >> length[i];

		for (int time = 0; time < k+1; time++)
			for (int song = 0; song < n; song++)
				cache[time][song] = -1.0;

		cache[0][0] = 1.0;
		for (int song = 1; song < n; song++)
			cache[0][song] = 0.0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> T[i][j];
		for (int i = 0; i < m; i++) {
			cin >> Q;
			double ret = 0.0;
			for(int startTime = k + 1 - length[Q]; startTime <= k; startTime++)
				ret += start(startTime, Q);
			cout << ret << ' ';
		}
		cout << endl;
	}
}