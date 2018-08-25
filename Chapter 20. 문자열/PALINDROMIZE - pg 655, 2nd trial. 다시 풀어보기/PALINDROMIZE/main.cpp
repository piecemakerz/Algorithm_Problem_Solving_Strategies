#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int C;

//KMP �˰����� �̿��� �κ� ��ġ ���̺� ����
vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	//KMP�� �ڱ� �ڽ��� ã�´�.
	//N�� N���� ã�´�. begin=0�̸� �ڱ� �ڽ��� ã�ƹ����� �����Ѵ�.
	int begin = 1, matched = 0;
	//���� ���ڰ� N�� ���� ������ ������ ã���鼭 �κ� ��ġ�� ��� ����Ѵ�.
	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			matched++;
			pi[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

//�Ӹ���� ����� ������ �ذ��ϴ� �� �˰���.
//KMP ���ڿ� �˻� �˰����� �����Ͽ���.
int solve(const string& str) {
	string revStr = str;
	reverse(revStr.begin(), revStr.end());
	vector<int> pi = getPartialMatch(revStr);

	int begin = 0, matched = 0;
	int n = revStr.length();

	while ((begin + matched) < n) {
		if (matched < n && str[begin + matched] == revStr[matched]) {
			matched++;
			if (begin + matched == n)
				return matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}

//�Ӹ���� ����� ������ �ذ��ϴ� å�� KMP �˰����� ����
//a�� ���̻��̸鼭 b�� ���λ��� ���ڿ��� �ִ� ���̸� ���Ѵ�.
int maxOverlap(const string& a, const string& b) {
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);
	//begin = matched = 0�������� ��������.
	int begin = 0, matched = 0;
	while (begin < n) {
		//���� ¤������ �ش� ���ڰ� �ٴ��� �ش� ���ڿ� ���ٸ�
		if (matched < m && a[begin + matched] == b[matched]) {
			matched++;
			if (begin + matched == n)
				return matched;
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 0;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		string inputStr;
		cin >> inputStr;
		cout << 2 * inputStr.length() - solve(inputStr) << endl;
	}
}