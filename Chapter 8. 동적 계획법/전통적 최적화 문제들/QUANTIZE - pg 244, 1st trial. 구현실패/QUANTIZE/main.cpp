#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> numArray;
int arrayMin, arrayMax;
//int cache[1001];
const int INF = 987654321;
int N, S;

//���� § �˰���. numArray�� ũ�� ������ �����ϴ� �� ������ �������� S���� �������� ���� ������ ���ߴ�. ��, 
//����, �� ���������� ���������� �ּ�ȭ�ϴ� ���� ã�� ������ �����س��� ���ߴ�.
//�� �˰����� ����� �ð� �ȿ� ���� �� �� ����. ���� ������ 1000���ϱ����̹Ƿ�, 
//S�� 10�̶�� �� �� ������ quantArray�� �������� 1000_C_10(����. 1000���� �ڿ��� �߿��� 10�� ����)���� �ȴ�.

int calculateDifferences(const vector<int>& quantArray) { // ���� § ���� ������ �� �����ϰ� Ǫ�� �˰���
	int diffSum = 0;
	for (int i = 0; i < N; i++)
		diffSum += pow<int>(numArray[i] - quantArray[i], 2);
	return diffSum;
}

vector<int> DecideQuantizationNumbers(const vector<int>& currentChoice) { // ���� § ǥ���� �� �����ϴ� ������ �˰���
	vector<int> quantArray;
	for (int i = 0; i < N; i++) {
		int mindiff = abs(numArray[i] - currentChoice[0]);
		int minChoice = 0;
		for (int j = 1; j < S; j++) {
			int diff = abs(numArray[i] - currentChoice[j]);
			if (mindiff > diff) {
				mindiff = diff;
				minChoice = j;
			}
		}
		quantArray.push_back(currentChoice[minChoice]);
	}
	return quantArray;
}

int Quantization(vector<int> currentChoice) {
	if (currentChoice.size() == S) {
		vector<int> quantArray = DecideQuantizationNumbers(currentChoice);
		return calculateDifferences(quantArray);
	}

	int start, ret = INF;
	if (currentChoice.empty())
		start = arrayMin;
	else {
		if (currentChoice.back() >= arrayMax)
			return ret;
		else
			start = currentChoice.back() + 1;
	}

	if (start > arrayMax)
		return ret;

	for (int i = start; i <= arrayMax; i++) {
		currentChoice.push_back(i);
		ret = min(ret, Quantization(currentChoice));
		currentChoice.pop_back();
	}
	return ret;
}

//å�� ��
int n;
int A[101], pSum[101], pSqSum[101]; 
// A[]: ����ȭ�ؾ� �� ����, ������ ����
// pSum[]: A[]�� �κ��� ����. pSum[i]�� A[0]..A[i]�� ��
// pSqSum[]: A[]������ �κ����� �����Ѵ�. pSqSum[i]�� A[0]^2...A[i]^2�� ��

void precalc() { // A�� �����ϰ� �� �κ����� ����Ѵ�.
	sort(A, A + n);
	pSum[0] = A[0];
	pSqSum[0] = pow<int>(A[0], 2);
	for (int i = 1; i < n; i++) {
		pSum[i] = pSum[i - 1] + A[i];
		pSqSum[i] = pSqSum[i - 1] + pow<int>(A[i], 2);
	}
}
//A[lo]...A[hi] ������ �ϳ��� ���ڷ� ǥ���� �� �ּ� ���� ���� ����Ѵ�.
int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]); // �κ����� ���� A[lo] ~ A[hi]������ ���� ���Ѵ�.
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]); //A[lo]^2 ~ A[hi]^2������ ���� ���Ѵ�.
	int m = int(0.5 + (double)sum / (hi - lo + 1)); // ����� �ݿø��� ������ ���� ������ ǥ���Ѵ�.
	int ret = sqSum - 2 * m*sum + m*m*(hi - lo + 1); // �ּ� ���� �� ��ȯ
	return ret;
}

int cache[101][11];
int quantize(int from, int parts) {
	//���� ���: ��� ���ڸ� �� ����ȭ���� ��
	if (from == n) return 0;
	//���� ���: ���ڴ� ���� ���Ҵµ� �� ���� �� ���� �� ���� ū ���� ��ȯ�Ѵ�.
	if (parts == 0) return INF;
	int& ret = cache[from][parts];
	if (ret != -1) return ret;
	ret = INF;
	// ������ ���̸� ��ȭ���� ���� �ּ�ġ�� ã�´�.
	for (int partSize = 1; from + partSize <= n; partSize++)
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		int input;
		cin >> N >> S;
		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < N; i++) {
			cin >> input;
			numArray.push_back(input);
		}
		sort(numArray.begin(), numArray.end());
		arrayMin = numArray.front();
		arrayMax = numArray.back();

		vector<int> temp;
		cout<<Quantization(temp)<<endl;
		numArray.clear();
	}
}