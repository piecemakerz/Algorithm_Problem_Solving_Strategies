#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_N = 100;
int C, n;
int triangle[MAX_N][MAX_N];

//�� ��. å�� ���� ���ٹ���� top-down ����� �ƴ� down-top����� ����Ͽ�
//���� ĳ�ù迭�� ������� �ʾƵ� �� ��ġ�� ���� ����� �ѹ����� �ϵ��� �Ͽ���.
//�ﰢ���� �� �Ʒ����� �ٷ� ���ٿ��� �����Ͽ�, �� �� ū ���� ��� ���� ���� �� ����
//���� ������ triangle���� �����Ѵ�.

int findLongestPath() {
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j <= i; j++) {
			triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
		}
	}
	return triangle[0][0];
}

//å�� ��. �ﰢ�� ���� �ִ� ��� ������ Ǫ�� ���� ��ȹ�� �˰���
//ĳ�ù迭�� ����ϹǷν� �� ��ġ�� ���� �Լ�ȣ���� �ѹ����� �߻��Ѵ�.
int cache[100][100];
//(y, x) ��ġ���� �� �Ʒ��ٱ��� �������鼭 ���� �� �ִ� �ִ� ����� ���� ��ȯ�Ѵ�.
int path(int y, int x) {
	//���� ���
	if (y == n - 1) return triangle[y][x];
	//�޸������̼�
	int& ret = cache[y][x];
	if (ret != -1) return ret;
	return ret = triangle[y][x] + max(path(y + 1, x), path(y + 1, x + 1));
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j <= i; j++)
				cin >> triangle[i][j];
		cout << findLongestPath() << endl;
	}
	return 0;
}