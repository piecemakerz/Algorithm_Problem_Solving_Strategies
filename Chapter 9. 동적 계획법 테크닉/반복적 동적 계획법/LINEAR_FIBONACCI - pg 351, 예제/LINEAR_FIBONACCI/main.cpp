#include <iostream>
#include <vector>
using namespace std;

int fib(int n) {
	if (n <= 1) return n;
	int seq[3];
	seq[0] = 0;
	seq[1] = 1;
	for (int i = 2; i <= n; i++)
		seq[i % 3] = (seq[(i - 1) % 3] + seq[(i - 2) % 3]) % 100000;
	return seq[n % 3];
}

typedef vector<vector<int>> Matrix;
const int M = 100000;
Matrix operator * (const Matrix& a, const Matrix& b) {
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
	SquareMatrix(int n) : mat(Matrix(n, vector<int>(n, 0))) {}
	SquareMatrix(Matrix m) : mat(m) {}
	vector<int>& operator[] (int idx) { return mat[idx]; }
};

SquareMatrix operator*(const SquareMatrix& a, const SquareMatrix& b) {
	return SquareMatrix(a.mat * b.mat);
}

SquareMatrix Mpow(SquareMatrix a, int p) {
	if (p == 0) {
		int n = a.size();
		SquareMatrix ret(n);
		for (int i = 0; i < n; i++)
			ret[i][i] = 1;
		return ret;
	}
	if (p % 2) return Mpow(a, p - 1) * a;
	SquareMatrix half = Mpow(a, p / 2);
	return half * half;
}

int fib3(int n) {
	if (n == 0) return 0;

	SquareMatrix W(2);
	W[0][0] = 0;
	W[0][1] = W[1][0] = W[1][1] = 1;
	return Mpow(W, n-1)[1][1];
}