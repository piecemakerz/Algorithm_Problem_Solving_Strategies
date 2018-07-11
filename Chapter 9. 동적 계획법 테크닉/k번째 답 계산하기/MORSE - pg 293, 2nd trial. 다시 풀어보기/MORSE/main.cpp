#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int C, k;

int combCache[201][101];
const int MAX = 1000000001;
int total;

//�� Ǯ��. k��° ��ȣ�� ã�� ���� �ǳʶپ�� �ϴ� ��ȣ�� �� skip
//�������� �ʿ�� �ϴ� å�� ��� �޸� �� Ǯ�̴� k��° ��ȣ��
//ã�� ���ɼ��� �ִ� ��� ����� �� remain�� ���� ���� k �� ���� ������
//�ʿ�� �Ѵ�.

//nCr�� ���� ����ϴ� �Լ�. MAX�� �Ѿ�� ������
//��� MAX�� �����Ѵ�.
int combination(int n, int r) {
	if (n == r || r == 0) return 1;

	int& ret = combCache[n][r];
	if (ret != -1) return ret;

	ret = combination(n - 1, r - 1) + combination(n - 1, r);
	if (ret > MAX)
		ret = MAX;
	combCache[n][n - r] = ret;
	return ret;
}

//remain = k��° ��ȣ�� ã�� �� �ִ� ��� �����ִ� ����� ��
string morse(int n, int m, int remain) {
	//�� �̻� �� �� �ִ� �� ��ȣ�� ���� ��� ���� ��� ª�� ��ȣ�� �����Ѵ�.
	if (n == 0)
		return string(m, 'o');
	//�� �̻� �� �� �ִ� ª�� ��ȣ�� ���� ��� ���� ��� �� ��ȣ�� �����Ѵ�.
	else if (m == 0)
		return string(n, '-');
	
	//"-"�� �������� ��� ���� ����� ��
	int selLong = combination(n + m - 1, m);

	//"-"�� �������� �� ���� k��° ��ȣ�� ���� �� �ִٸ� "-"�� �����Ѵ�.
	if (selLong >= k)
		return "-" + morse(n - 1, m, selLong);
	//"-"�� �������� �� k��° ��ȣ�� ���� �� ���ٸ� "o"�� �����Ѵ�.
	else {
		k -= selLong;
		return "o" + morse(n, m - 1, remain - selLong);
	}
}

//å�� ��� �� ��ȣ�� ����� ���� Ž�� �˰���.
//s: ���ݱ��� ���� ��ȣ
//n: �� �ʿ��� -�� ����
//m: �� �ʿ��� o�� ����
void generate(int n, int m, string s) {
	//���� ���: n=m=0
	if (n == 0 && m == 0) {
		cout << s << endl;
		return;
	}
	if (n > 0) generate(n - 1, m, s + "-");
	if (m > 0) generate(n, m - 1, s + "o");
}

//k-1�� �ǳʶٰ� ù ��° ��ȣ�� ����ϴ� �˰���
//��� ��ȣ�� ���������� �����ǹǷ� �Լ� ȣ�� ����
//skip�� k-1�� �ʱ�ȭ�ϸ� skip = 0�� �� k��° ��ȣ�� �����ȴ�.
int skip;
//skip���� �ǳʶٰ� ����Ѵ�.
void generate2(int n, int m, string s) {
	//���� ���: skip < 0
	if (skip < 0) return;
	//���� ���: n=m=0
	if (n == 0 && m == 0) {
		//�� �ǳʶ� ��ȣ�� ���� ���
		if (skip == 0) cout << s << endl;
		skip--;
		return;
	}
	if (n > 0) generate2(n - 1, m, s + "-");
	if (m > 0) generate2(n, m - 1, s + "o");
}

//k-1�� �ǳʶٰ� ù ��° ��ȣ�� ����ϴ� ���� ��ȹ�� �˰���
//K�� �ִ밪+100. �����÷θ� ���� ���� �̺��� ū ���� ������ �ʴ´�.
const int M = 1000000000 + 100;
int bino[201][201];
//�ʿ��� ��� ���װ���� �̸� ����� �д�.
void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++)
			bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
	}
}
//skip���� �ǳʶٰ� ����Ѵ�.
void generate3(int n, int m, string s) {
	//���� ���: skip < 0
	if (skip < 0) return;
	//���� ���: n=m=0
	if (n == 0 && m == 0) {
		if (skip == 0) cout << s << endl;
		skip--;
		return;
	}
	if (bino[n + m][n] <= skip) {
		skip -= bino[n + m][n];
		return;
	}
	if (n > 0) generate3(n - 1, m, s + "-");
	if (m > 0) generate3(n, m - 1, s + "o");
}
//å�� k��° ��ȣ�� ����ϴ� �˰���
//n���� -, m���� o�� ������ ��ȣ �� skip���� �ǳʶٰ�
//��������� ��ȣ�� ��ȯ�Ѵ�.
string kth(int n, int m, int skip) {
	//n == 0�� ��� ������ �κ��� ���� o�� ���ۿ� ����.
	if (n == 0) return string(m, 'o');
	if (skip < bino[n + m - 1][n - 1])
		return "-" + kth(n - 1, m, skip);
	return "o" + kth(n, m - 1, skip - bino[n + m - 1][n - 1]);
}

int main(void) {
	cin >> C;
	memset(combCache, -1, sizeof(combCache));

	for (int test = 0; test < C; test++) {
		//n = �� ��ȣ�� ��(-), m = ª�� ��ȣ�� ��(o)
		//k = ã������ ��ȣ
		int n, m;
		cin >> n >> m >> k;
		total = combination(n + m, m);
		cout << morse(n, m, total) << endl;
	}
}