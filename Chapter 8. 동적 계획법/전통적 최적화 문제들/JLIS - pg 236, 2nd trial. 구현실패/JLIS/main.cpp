#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX = 100;
int c, n, m;
vector<int> A, B;
int cache[MAX+1][MAX+1];

//���������� ����: ���� ��� ������ ������ġ�� ���� ������ �˻縦 �ϸ�
//�Լ��� �ʹ� ���� �������� ���� ���� �ִٰ� �����ߴ�.
//����, ���� �Լ��� �� ������ �����ϴ� ����� �����س��� ���ߴ�.

//å�� ��
//�Է��� 32��Ʈ ��ȣ �ִ� ������ ��� ���� ���� �� �����Ƿ�
//�������� �ּ�ġ�� 64��Ʈ���� �Ѵ�.
const long long NEGINF = numeric_limits<long long>::min();
//min(A[indexA], B[indexB]), max(A[indexA], B[indexB])�� �����ϴ�
//��ģ ���� �κ� ������ �ִ� ���̸� ��ȯ�Ѵ�.
//�� indexA == indexB == -1 Ȥ�� A[indexA] != B[indexB]��� �����Ѵ�.

//jlis(indexA, indexB)�� ȣ��Ǿ��ٴ� ���� A[indexA]�� B[indexB]�� �̹�
//��ģ ���� �κм����� ���ԵǾ����� �ǹ��ϸ�, max(A[indexA], B[indexB])��
//��ģ ���� �κм����� ������ ������ �ǹ��ϱ⵵ �Ѵ�.
int jlis(int indexA, int indexB) {
	//�޸������̼�
	int& ret = cache[indexA + 1][indexB + 1];
	if (ret != -1) return ret;
	//A[indexA], B[indexB]�� �̹� �����ϹǷ� 2���� �׻� �ִ�.
	ret = 2;
	//���� A�� B������ ��� ������ ������ġ�� ���� ���� �κ� ������ Ȯ���ϱ� ����
	//indexA�� indexB�� -1�� ��� maxElement�� �������� �ּ�ġ�� �ʱ�ȭ�Ѵ�.
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	long long maxElement = max(a, b);
	//���� ���Ҹ� ã�´�.
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