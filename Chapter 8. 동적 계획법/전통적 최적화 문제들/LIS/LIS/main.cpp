#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 500;
int T, N;
int sequence[MAX_N], cache[MAX_N+1];

//�� Ǯ��. ���������� �������� �ʴ´�. ������ å�� ��Ʈ ����.
/*
int maxSeqlen(int idx = 0) {
	if (idx >= N - 1)
		return 1;
	int& ret = cache[idx];
	if (ret != -1)
		return ret;

	int nextIdx = idx + 1;

	//idx��° ��ȣ�� �������� �ʴ� �κм����� �ִ� ����
	ret = maxSeqlen(nextIdx);

	//idx��° ��ȣ�� �����ϴ� �κм����� �ִ� ����
	while (nextIdx <= N - 1 && sequence[idx] >= sequence[nextIdx])
		nextIdx++;

	if (nextIdx != N)
		ret = max(ret, 1 + maxSeqlen(nextIdx));

	return ret;
}
*/

//å�� �� 1. �ִ� ���� �κ� ���� ������ �ذ��ϴ� ���� Ž�� �˰���.
//�� �˰����� �Է��� ������ �ƴ϶� ������ �迭�̹Ƿ� �޸������̼���
//�����ϱ� ��ٷӴ�.
int lis(const vector<int>& A) {
	//���� ���: A�� �� ��� ���� ��
	if (A.empty())	return 0;
	int ret = 0;
	//A[i]�� ������ ù ���ڷ� ����ٰ� �����Ѵ�.
	for (int i = 0; i < A.size(); i++) {
		vector<int> B; //A[i+1...]�� LIS
		for (int j = i + 1; j < A.size(); j++)
			if (A[i] < A[j])
				B.push_back(A[j]);
		ret = max(ret, 1 + lis(B));
	}
	return ret;
}

//å�� �� 2. �ִ� ���� �κ� ���� ������ �ذ��ϴ� ���� ��ȹ�� �˰���
//sequence[start]���� �����ϴ� ���� �κ� ���� �� �ִ� ���̸� ��ȯ�Ѵ�.
int lis2(int start) {
	int& ret = cache[start + 1];
	if (ret != -1) return ret;
	//�׻� sequence[start]�� �����ϹǷ� ���̴� ���� 1
	ret = 1;
	for (int next = start + 1; next < N; next++)
		if (start == -1 || sequence[start] < sequence[next])
			ret = max(ret, 1 + lis2(next));
	return ret;
}

//���ͳ��� ���� �������� O(n^2) ��. 
//å�� ���� ���ȣ��� ������ȹ���� ���������� ���ͳ��� ����
//��ø�ݺ������� �̸� ����������, å�� ���� i��° ���Ҹ� ���������� �ϴ�
//LIS�� ���̸� ���ϴ� �ݸ� ���ͳ��� ���� i��° ���Ҹ� ����������
//�ϴ� LIS�� ���̸� ���Ѵ�.

//dp[i] = i��° ���Ҹ� ���������� �ϴ� LIS�� ����
//�� �Լ������� dp�� ĳ���� ������ �Ѵ�.
int dp[MAX_N];

int lisInter() {
	int result = 0;
	for (int i = 0; i < N; i++) {
		//i��° ���Ҹ� �κ� ������ ������ ���ҷ� �ݵ�� �����ϴ�
		//�κ� �������� Ȯ���Ѵ�.
		int here = 0;
		for (int j = 0; j < i; j++)
			if (sequence[i] > sequence[j])
				here = max(here, dp[j]);

		dp[i] = here + 1;
		result = max(result, dp[i]);
	}
	return result;
}

//å�� �� 3. �� �� �������� ������ ���ڸ� �ϳ��� �߰��� ������ �� ���̸� ����
//���� ���� �� ���� ������ ���� ���� ���� �������� �����ϴ� �˰���.

//C[i] = ���ݱ��� ���� �κ� �迭�� ���� ���� i�� ���� �κ� ���� �� �ּ��� ������ ��
int C[MAX_N];

int lis3(int start) {
	
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		memset(cache, -1, sizeof(cache));
		memset(C, 0, sizeof(C));

		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> sequence[i];
		//cout << maxSeqlen() << endl;
	}
	return 0;
}