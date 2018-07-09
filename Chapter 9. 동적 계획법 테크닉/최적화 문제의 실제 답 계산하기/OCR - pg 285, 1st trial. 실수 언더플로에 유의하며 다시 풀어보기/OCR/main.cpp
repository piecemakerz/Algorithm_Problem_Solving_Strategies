#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

//m = ������ ���� ������ �ܾ� ��, q = ó���ؾ� �� ������ ��
//n = �з���� �ν��� ������ ����
int m, q, n;
//B[i] = i�� �ܾ ������ ó���� ������ Ȯ��
double B[500];
//T[i][j] = i�� �ܾ��� ���� �ܾ j�� �ܾ��� Ȯ��
//M[i][j] = i�� �ܾ ���� ������ j�� �ܾ�� �з��� Ȯ��
double T[500][500], M[500][500];

//word[i] = ������ ���� ������ i��° �ܾ�
vector<string> word;
//classified = �з��⿡�� �ν��� ��� ������ ��ȣ
vector<int> classified;
//origin[count][prev+1] = count ������ �ܾ ���Ͽ�
//������ ������ �ܾ prev�� ��, ���Ǻ� ���� Ȯ���� ���� ���� ������
//���� �ܾ� ��ȣ
int origin[501][501];

//cache[count][prev+1] = count ������ �ܾ ���Ͽ� ������
//������ �ܾ prev�� ��, �ִ� ���Ǻ� ���� Ȯ��.
double cache[501][501];

//count = ������ count��° �ܾ�
//prev = ������ ������ count-1��° �ܾ�� ������ �ܾ� ��ȣ

//ORC(count, prev) = ������ ������ count-1��° �ܾ��
//prev��° �ܾ �������� ��, ���� ���� �� �ִ� �������
//�ִ� ���Ǻ� ���� Ȯ���� ��ȯ�Ѵ�.

double ORC(int count, int prev) {
	if (count == n)
		return 0;

	double& ret = cache[count][prev + 1];
	if (ret != 1.0)
		return ret;

	ret = -1e200;
	//curStr = �з��⿡�� �ν��� ������ count��° �ܾ�
	int curStr = classified[count];
	double result;

	for (int sel = 0; sel < m; sel++) {
		//������ ù ��° �ܾ� ����
		if (prev == -1) {
			//if (B[sel] == log(0.0))
				//continue;
			//���� ������ ù��° �ܾ sel�� �ܾ��� Ȯ�� ��ȯ
			result = ORC(count + 1, sel) + B[sel] + M[sel][curStr];
		}
		//������ ù ��° ���� �ܾ� ����
		else {
			//if (T[prev][sel] == log(0.0) || M[sel][curStr] == log(0.0))
				//continue;
			result = ORC(count + 1, sel) + T[prev][sel] + M[sel][curStr];
		}

		if (result > ret) {
			origin[count][prev + 1] = sel;
			ret = result;
		}
	}
	return ret;
}

int main(void) {
	cin >> m >> q;
	word = vector<string>(m);
	double dinput;

	for (int i = 0; i < m; i++)
		cin >> word[i];
	for (int i = 0; i < m; i++) {
		cin >> dinput;
		B[i] = log(dinput);
	}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			cin >> dinput;
			T[i][j] = log(dinput);
		}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			cin >> dinput;
			M[i][j] = log(dinput);
		}

	for (int test = 0; test < q; test++) {
		vector<string>::iterator it;
		for (int i = 0; i <= m; i++)
			for (int j = 0; j <= m; j++)
				cache[i][j] = 1.0;

		cin >> n;
		classified = vector<int>(n);
		memset(origin, -1, sizeof(origin));
		string input;
		for (int i = 0; i < n; i++) {
			cin >> input;
			it = find(word.begin(), word.end(), input);
			classified[i] = it - word.begin();
		}
		ORC(0, -1);

		int nextStr = origin[0][0];
		for (int i = 1; i <= n; i++) {
			cout << word[nextStr] << ' ';
			nextStr = origin[i][nextStr + 1];
		}
		cout << endl;
		classified.clear();

	}
}