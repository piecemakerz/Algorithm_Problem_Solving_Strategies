#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

int n, m, k;
//�� Ǯ�� 1. �翬�� �ð� �ʰ��� ����.
void morse(int n, int m, vector<char>& morCode) {
	if (n == 0 && m == 0) {
		for (int i = 0; i < morCode.size(); i++)
			cout << morCode[i];
		cout << endl;
		return;
	}

	if (n > 0) {
		morCode.push_back('-');
		morse(n - 1, m, morCode);
		morCode.pop_back();
	}
	if (m > 0) {
		morCode.push_back('o');
		morse(n, m - 1, morCode);
		morCode.pop_back();
	}
}

//å�� ������ �˰���
void generate(int n, int m, string s) {
	if (n == 0 && m == 0) {
		cout << s << endl;
		return;
	}
	if (n > 0) generate(n - 1, m, s + "-");
	if (m > 0) generate(n, m - 1, s + "o");
}

//k-1�� �ǳ� �ٴ� �˰���
int skip; // skip ���� �ǳʶٰ� ����Ѵ�.
void generate2(int n, int m, string s) {
	// ���� ���: skip < 0
	if (skip < 0) return;
	// ���� ���: n = m = 0
	if (n == 0 && m == 0) {
		//�� �ǳʶ� ��ȣ�� ���� ���
		if (skip == 0) cout << s << endl;
		--skip;
		return;
	}
	if (n > 0) generate2(n - 1, m, s + "-");
	if (m > 0) generate2(n, m - 1, s + "o");
}

//�� �� �ȶ��ϰ� �ǳʶٴ� �˰���. ���� �����ߴ� �˰���� ������ ������ ������� �����Ǿ���.
//���� �� ���̵� n+mCn�� ���ϴµ� �ʹ� �ð��� ���� �ɸ���, �����÷ο찡 �߻��� ���̶�� �����߱� ������ ����ߴ�.
const int M = 1000000000 + 100; // K�� �ִ밪+100, �����÷θ� ���� ���� �̺��� ū ���� ������ �ʴ´�.
//��� M���� ���� ���� ���̵� ����ߴ� ������ �ذ��ߴ�.
int bino[201][201];
//�ʿ��� ��� ���װ���� �̸� ����صд�.
void calcBino() {
	memset(bino, 0, sizeof(bino));
	for (int i = 0; i <= 200; i++) {
		bino[i][0] = bino[i][i] = 1;
		for (int j = 1; j < i; j++)
			bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
	}
}

void generate3(int n, int m, string s) {
	if(skip < 0) return;
	if (n == 0 && m == 0) {
		if (skip == 0) cout << s << endl;
		--skip;
		return;
	}
	if (bino[n + m][n] <= skip) { // �����ִ� ��ȣ�� �� ���� skip�� �� Ŭ ��, ���� ��ȣ�� ������ Ȯ���� �ʿ䰡 ����.
		skip -= bino[n + m][n];
		return;
	}
	if (n > 0) generate3(n - 1, m, s + "-");
	if (m > 0) generate3(n, m - 1, s + "o");
}

//�� �� ����� ����
//n���� -, m���� o�� ������ ��ȣ �� skip���� �ǳʶٰ� ��������� ��ȣ�� ��ȯ�Ѵ�.
string kth(int n, int m, int skip) {
	//n == 0�� ��� ������ �κ��� ���� o�� ���ۿ� ����.
	if (n == 0) return string(m, 'o');
	if (skip < bino[n + m - 1][n - 1]) // ù ���ڰ� �������� �����ϴ� ��ȣ�� ���� skip���� ũ�ٸ� �̸� �����Ѵ�.
		return "-" + kth(n - 1, m, skip);
	return "o" + kth(n, m - 1, skip - bino[n+m-1][n-1]);
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		vector<char> morCode;
		cin >> n >> m >> k;	
		morse(n, m, morCode);
	}
	return 0;
}