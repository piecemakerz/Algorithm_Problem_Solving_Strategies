#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C;

//pi[i] = N[...i]�� ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ��� �ִ� ����
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


//�� ��.
int kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> pi = getPartialMatch(N);
	int begin = 0, matched = 0;
	while (begin < n) {
		if ((begin + matched) < n && H[begin + matched] == N[matched]) {
			matched++;
			if (begin + matched == n) return matched;
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

int palindromize(const string& str) {
	int n = str.length();
	string revStr = str;
	reverse(revStr.begin(), revStr.end());
	return 2 * n - kmpSearch(str, revStr);
}

//å�� ��
//a�� ���̻��̸鼭 b�� ���λ��� ���ڿ��� �ִ� ���̸� ���Ѵ�.
int maxOverlap(const string& a, const string& b) {
	int n = a.size(), m = b.size();
	vector<int> pi = getPartialMatch(b);
	//begin = matched = 0�������� ��������.
	int begin = 0, matched = 0;
	while (begin < n) {
		//���� a�� �ش� ���ڰ� b�� �ش� ���ڿ� ���ٸ�
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
	for (int testCase = 0; testCase < C; testCase++) {
		string inputStr;
		cin >> inputStr;
		cout << palindromize(inputStr) << endl;
	}
	return 0;
}