#include <iostream>
#include <cstdio>
using namespace std;

int C, n, m;
double cache[1000][1000];

//climb(date, meter) = ������� date���� ������ meter���͸�
//�ö��� ��, m�� �ȿ� n���͸� �ö� �� �ִ� Ȯ��
double climb(int date, int meter) {
	if (meter >= n)
		return 1;
	if (date >= m)
		return 0;
	double& ret = cache[date][meter];
	if (ret != -1) return ret;

	return ret = (climb(date + 1, meter + 2)*0.75 + climb(date + 1, meter + 1)*0.25);
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		for (int i = 0; i < 1000; i++)
			for (int j = 0; j < 1000; j++)
				cache[i][j] = -1;
		cin >> n >> m;
		printf("%.10f\n", climb(0, 0));
	}
}