#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

vector<double> movingAverage(const vector<double>& A, int M) {
	int N = A.size();
	vector<double> movingAverage;
	double totalSum = 0;

	for (int i = 0; i < M - 1; i++) {
		totalSum += A[i];
	}

	for (int i = M - 1; i < N; i++) {
		totalSum += A[i];
		movingAverage.push_back(totalSum / M);
		totalSum -= A[i - (M - 1)];
	}

	return movingAverage;
}

int main(void) {
	int N, M;
	cin >>N>>M;

	vector<double> inputs(N, 0);
	double input;
	for (int i = 0; i < N; i++) {
		input = 1 + (0.1*i);
		inputs[i] = input;
	}

	vector<double>& averageResult = movingAverage(inputs, M);
	for (int i = 0; i < averageResult.size(); i++) {
		cout << averageResult[i] << ' ';
	}
	return 0;
}