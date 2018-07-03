#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int C, n, s;
const int INF = 987654321;
vector<int> Seq;

int cache[10][100];
int SquaredCache[100][100];

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

int Quantize(int start, int slice) {
	if (start == n) return 0;
	if (slice == 0) return INF;

	int& ret = cache[slice - 1][start];
	if (ret != INF) return ret;

	for (int partSize = 1; start + partSize <= n; partSize++)
		ret = min(ret, Quantize(start + partSize, slice - 1) + calSquaredError(start, start + partSize - 1));
	return ret;
}

int myQuantize(int start, int slice) {
	if (start == n - slice)
		return 0;
	else if (slice == 1)
		return calSquaredError(start, n - 1);

	int& ret = cache[slice - 1][start];
	if (ret != INF) return ret;

	for (int i = start + 1; i < n - slice; i++)
		ret = min(ret, myQuantize(i, slice - 1) + calSquaredError(start, i - 1));
	return ret;
}

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
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 100; j++)
				cache[i][j] = INF;

		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++)
				SquaredCache[i][j] = -1;

		cin >> n >> s;
		Seq = vector<int>(n);
		for (int i = 0; i < n; i++)
			cin >> Seq[i];
		sort(Seq.begin(), Seq.end());
		cout << myQuantize2(0, s) << endl;
		Seq.clear();
	}
	return 0;
}