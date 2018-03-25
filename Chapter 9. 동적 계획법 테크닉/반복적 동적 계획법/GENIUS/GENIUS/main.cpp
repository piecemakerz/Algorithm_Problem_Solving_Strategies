#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
int n, k, m;
int Q;
int length[50];
double T[50][50];
double cache[1000001][50]; // [���� �ð�][���� ��]

//start(time, song) = ����� �������� time�� �Ŀ� song�� �뷡�� ����� ������ Ȯ��.
//å�� �ݺ��� ���� ��ȹ�� �˰����� �����Ͽ� ���� ���ȣ�� ���� ��ȹ�� �˰����̴�.
//����, �����̵� ���� ����� ������ �� ���� ������ �ſ� ū �޸𸮰� �ʿ��ϴ�.
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

//�ݺ��� ���� ��ȹ�� �˰���. �����̵� ���� ����� ����Ͽ� ĳ���� �޸𸮸� �ٿ���.
vector<double> getProb1() {
	//c[time][song] = time�� �Ŀ� song�� �뷡�� ������ Ȯ��
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
	//song�� �뷡�� ����ǰ� ���� Ȯ���� ����Ѵ�.
	for (int song = 0; song < n; song++)
		//song�� �뷡�� �������� �ð��� ��� ã�� ���Ѵ�.
		for (int start = k - length[song] + 1; start <= k; start++)
			ret[song] += c[start % 5][song];
	return ret;
}

//��� �ŵ������� �̿��� ���� ��ȹ���� ����.
//k�� 30�� �Ŀ� �� ���� ����ǰ� ���� Ȯ���� ��ȯ�Ѵ�.
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

// k�� 30�� �Ŀ� �� ���� ����ǰ� ���� Ȯ���� ��ȯ�Ѵ�.
vector<double> getProb2() {
	SquareMatrix W(4 * n);
	//ù 3*n���� ���Ҵ� �״�� �����ؿ´�.
	for (int i = 0; i < 3 * n; i++)
		W[i][i + n] = 1.0;
	//������ n���� ���Ҵ� ���� ���ҵ��� ���� �������� �̷������.
	for (int i = 0; i < n; i++)
		//C[time+1][i] = C[time+1-length[j]] * T[j][i]
		for (int j = 0; j < n; j++)
			W[3 * n + i][(4 - length[j])*n + j] = T[j][i];
	SquareMatrix Wk = pow(W, k);
	vector<double> ret(n);
	//song�� �뷡�� ����ǰ� ���� Ȯ���� ����Ѵ�.
	for (int song = 0; song < n; song++)
		//song�� �뷡�� �������� �ð��� ��� ã�� ���Ѵ�.
		for (int start = 0; start < length[song]; start++)
			ret[song] += Wk[(3 - start)*n + song][3 * n];
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n >> k >> m; // �� ��/�ð�/�����ϴ� �� ��
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