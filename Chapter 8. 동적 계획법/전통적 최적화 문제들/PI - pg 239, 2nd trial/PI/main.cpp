#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

int C;
string PI;
int cache[10000];
const int INF = 987654321;

//�� Ǯ��. å�� ��� ���� ������� �����Ǿ�����,
//å�� Ǯ�̰� �� �����ϴ�.
int calDiff(const vector<char>& sel) {
	bool case1 = true, case2 = true, 
		case3 = true, case4 = true;
	int n = sel.size();
	int diff = sel[0] - sel[1];
	if (abs(diff) != 1)
		case2 = false;

	for (int i = 0; i < n - 1; i++) {
		if (case1 && sel[i] != sel[i + 1])
			case1 = false;
		if (case2 && sel[i] - sel[i + 1] != diff)
			case2 = false;
		if (case3 && i < n-2 && sel[i] != sel[i + 2])
			case3 = false;
		if (case4 && sel[i] - sel[i + 1] != diff)
			case4 = false;
	}
	if (case1)
		return 1;
	if (case2)
		return 2;
	if (case3)
		return 4;
	if (case4)
		return 5;

	return 10;
}

int piDiff(int start) {
	if (start >= PI.length())
		return 0;

	else if (start > PI.length() - 3)
		return 10;

	int& ret = cache[start];
	if (ret != INF) return ret;

	vector<char> sel;
	sel.push_back(PI[start]);
	sel.push_back(PI[start + 1]);

	for (int i = 2; i < 5; i++) {
		if (start + i >= PI.length())
			break;
		sel.push_back(PI[start + i]);
		ret = min(ret, calDiff(sel) + piDiff(start + 1 + i));
	}
	sel.clear();
	return ret;
}

//å�� Ǯ��. ������ �ܿ�� ������ �ذ��ϴ� ���� ��ȹ�� �˰���
//PI[a..b] ������ ���̵��� ��ȯ�Ѵ�.
int classify(int a, int b) {
	//���� ������ �����´�.
	string M = PI.substr(a, b - a + 1);
	//ù ���ڸ����� �̷���� ���ڿ��� ������ ���̵��� 1
	if (M == string(M.size(), M[0])) return 1;
	//������������ �˻��Ѵ�.
	bool progressive = true;
	for (int i = 0; i < M.size() - 1; i++)
		if (M[i + 1] - M[i] != M[1] - M[0])
			progressive = false;
	//���������̰� ������ 1 Ȥ�� -1�̸� ���̵��� 2
	if (progressive && abs(M[1] - M[0]) == 1)
		return 2;
	//�� ���� ������ �����ϴ��� Ȯ���Ѵ�.
	bool alternating = true;
	for (int i = 0; i < M.size(); i++)
		if (M[i] != M[i % 2])
			alternating = false;
	//�� ���� ������ �����ϸ� ���̵��� 4
	if (alternating) return 4;
	//������ 1 �ƴ� ���������� ���̵��� 5
	if (progressive) return 5;
	//�� �ܴ� ��� ���̵� 10
	return 10;
}
//���� PI[begin...]�� �ܿ�� ��� �� ���̵��� �ּ� ���� ����Ѵ�.
int memorize(int begin) {
	//���� ���: ������ ���� �������� ���
	if (begin == PI.size()) return 0;
	//�޸������̼�
	int& ret = cache[begin];
	if (ret != -1) return ret;
	ret = INF;
	for (int L = 3; L <= 5; L++)
		if (begin + L <= PI.size())
			ret = min(ret, memorize(begin + L) +
				classify(begin, begin + L - 1));
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		for (int i = 0; i < 10000; i++)
			cache[i] = INF;
		cin >> PI;
		cout << piDiff(0) << endl;
	}
	return 0;
}