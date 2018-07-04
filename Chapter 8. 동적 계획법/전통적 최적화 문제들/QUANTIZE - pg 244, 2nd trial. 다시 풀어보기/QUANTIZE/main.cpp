#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int C, n, s;
const int INF = 987654321;
vector<int> Seq;

int cache[11][101];
int SquaredCache[100][100];

//���� �ۼ��� ������ �ּ� ���� ���� �� ���� �ڵ�.
//O(N)�� �ð��� �ɸ���.
//ĳ�ø� �����Ͽ� �ߺ��� ������ ���� ���� ���� ����
//������� �ʵ��� �����Ͽ���.
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

//å�� �κ����� ����ϴ� �ڵ�.
//pSum[]: Seq[]�� �κ����� �����Ѵ�. pSum[i]�� A[0]...A[i]�� ��
//pSqSum[]: Seq[] ������ �κ����� �����Ѵ�. pSqSum[i]�� A[0]^2...A[i]^2�� ��
int pSum[101], pSqSum[101];
void precalc() {
	pSum[0] = Seq[0];
	pSqSum[0] = Seq[0] * Seq[0];
	for(int i = 1; i < n; i++) {
		pSum[i] = pSum[i - 1] + Seq[i];
		pSqSum[i] = pSqSum[i - 1] + Seq[i] * Seq[i];
	}
}

//å�� �ּ� ���� ���� �� ���� �ڵ�. �κ����� �̿��Ͽ�
//O(1)�� ���� ���� ���� ���� �� �ִ�.
//Seq[lo]...Seq[hi] ������ �ϳ��� ���ڷ� ǥ���� �� �ּ� ���� ���� ����Ѵ�.
int minError(int lo, int hi) {
	//�κ����� �̿��� Seq[lo] ~ Seq[hi]������ ���� ���Ѵ�.
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]);
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]);
	//����� �ݿø��� ������ �� ������ ǥ���Ѵ�.
	int m = int(0.5 + (double)sum / (hi - lo + 1));
	//sum(A[i]-m)^2�� ������ ����� �κ� ������ ǥ��
	int ret = sqSum - 2 * m * sum + m * m * (hi - lo + 1);
	return ret;
}
//å�� ��. '���� ������ ������'�� �������� �ݺ����� �ۼ���
//�� Ǯ�̿� �޸� '���� ������ ����'�� �������� �ݺ����� �ۼ��Ͽ���.
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

//�� Ǯ�� 1. å�� Ǯ�̿� �������� �Ϻ��ϰ� ������
//����ó���� �߸��Ǿ� ������ ���Ծ���. ����� ����ó����
//�����Ͽ� �����̴�.
int myQuantize(int start, int slice) {
	//start�� Seq�� ������ ����� ��츦 ����ó�� ���ָ�,
	//���� �� �ִ� ������ ���� ���� �����ִ� ������ �۰ų� ���ٸ�
	//�����ִ� ��� ���� �ϳ��� �������� ����� �� ������ 0�� �ǹǷ�
	//0�� �����Ѵ�.
	if (start >= n - slice || start == n)
		return 0;
	//������ �ϳ� ���Ҵٸ� ���ȣ���� ���� �ʰ�
	//�����ִ� ������ ��� ������ �������� ����Ѵ�.
	else if (slice == 1)
		return calSquaredError(start, n - 1);

	int& ret = cache[slice - 1][start];
	if (ret != INF) return ret;

	//���� ������ ���������� ������ ��� �������� ���� ���ȣ���� �����Ѵ�.
	for (int i = start + 1; i < n; i++)
		ret = min(ret, myQuantize(i, slice - 1) + calSquaredError(start, i - 1));
	return ret;
}

//�� Ǯ�� 2. å Ǯ�̸� �����Ͽ� ������ �� Ǯ��.
//����ó���� �� �� �������̴�.
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