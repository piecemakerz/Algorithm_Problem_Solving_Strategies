#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

//m = ������ ���� ������ �ܾ� ��, q = ó���ؾ� �� ������ ��
//n = �з���� �ν��� ������ ����
int m, q, n;

/*���� �־����� Ȯ�� ������ �ſ� �۱� ������ �̵��� ���� ���� ���ϸ�
Ȯ�� ���� �ʹ� �۾�����, ��������� ����÷ΰ� �Ͼ�� ����Ƿ� Ȯ�� ����
�״�� �� �� ����. ���� Ȯ���� �α� ���� ���ϸ� �� ���� Ȯ������
�α� ���� ���ϱ⸸ �ϸ� �Ǳ� ������ ����÷θ� ������ �� �ִ�.
�� ���� ���� �̸� �����Ͽ� ����ó���Ǿ���.
*/

//B[i] = i�� �ܾ ������ ó���� ������ Ȯ��(�� �αװ�)
double B[500];
//T[i][j] = i�� �ܾ��� ���� �ܾ j�� �ܾ��� Ȯ��(�� �αװ�)
//M[i][j] = �з��⿡�� i�� �ܾ j�� �ܾ�� �з��� Ȯ��(�� �αװ�)
double T[500][500], M[500][500];

//word = ������ ���� ������ �ܾ� ���
vector<string> word;
//classified = �з��⿡�� �ν��� ��� ������ �̷�� �ܾ���� ��ȣ
vector<int> classified;

//origin[count][prev+1] = ���� ���� Q�� �̷�� �ܾ� �� Q[count-1]�� word[prev]��
//������ ��, Q[count] ���ĸ� ä���� ���� �� �ִ� ��� ���� �� ���Ǻ� ���� Ȯ���� ���� ���� 
//������ count��° �ܾ� ��ȣ.
//���� ������ �籸���� �� �ʿ��ϴ�.
int origin[501][501];

//cache[count][prev+1] =  ���� ���� Q�� �̷�� �ܾ� �� Q[count-1]�� word[prev]�� ������ ��,
//Q[count] ���ĸ� ä���� ���� �� �ִ� �ִ� ���Ǻ� ���� Ȯ���� �αװ�.
double cache[501][501];

const double MIN = log(0.0);
//ORC(count, prev) = ���� ���� Q[count-1]�� word[prev]�� ������ ��,
//Q[count] ���ĸ� ä���� ���� �� �ִ� �ִ� ���Ǻ� Ȯ���� �α� ���� ��ȯ�Ѵ�.
double ORC(int count, int prev) {
	//���� ���: Q�� n-1��° �ܾ���� ��� ������ ���
	if (count == n)
		return 0;

	double& ret = cache[count][prev + 1];
	if (ret != 1.0)
		return ret;

	//log(0) = ���� ���Ѵ뿡 �ش��ϴ� ��
	ret = MIN;

	//curStr = �з��⿡�� �ν��� ������ count��° �ܾ� ��ȣ
	int curStr = classified[count];
	double result;

	for (int sel = 0; sel < m; sel++) {
		//Q[0] ����
		if (prev == -1) {
			//word[sel]�� Q[0]�� ��ġ�� Ȯ���� 0�̶�� ���ĸ� Ȯ������ �ʴ´�.
			if (B[sel] == MIN)
				continue;
			//OCR(count+1, sel) * 'word[sel]�� Q[0]�� Ȯ��' * 'word[sel]�� �з��Ⱑ 'word[curStr]�� �з����� Ȯ��
			//�α� ���� �������Ƿ� ���ϴ� ��� ���Ѵ�.
			result = ORC(count + 1, sel) + B[sel] + M[sel][curStr];
		}
		//Q[0] ���� �ܾ� ����
		else {
			//word[prev]���Ŀ� word[sel]�� ���� Ȯ���� 0�̰ų� word[sel]�� word[curStr]��
			//�з��� Ȯ���� 0�̶�� Ȯ������ �ʴ´�.
			if (T[prev][sel] == MIN || M[sel][curStr] == MIN)
				continue;
			//OCR(count+1, sel) * 'word[prev]�� ���� �ܾ word[sel]�� Ȯ��' * 'word[sel]�� �з��Ⱑ 'word[curStr]��
			//�з����� Ȯ��. �α� ���� �������Ƿ� ���ϴ� ��� ���Ѵ�.
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
		scanf("%lf", &dinput);
		B[i] = log(dinput);
	}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			scanf("%lf", &dinput);
			T[i][j] = log(dinput);
		}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			scanf("%lf", &dinput);
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

		//���� ���� �籸��. ���� ������ ù��° �ܾ� ��ȣ�� origin[0][0]�� ����Ǿ� �ִ�.
		int nextStr = origin[0][0];
		for (int i = 1; i <= n; i++) {
			cout<<word[nextStr]<<' ';
			nextStr = origin[i][nextStr + 1];
		}
		cout << endl;
		classified.clear();
	}
}