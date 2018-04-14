#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C;

//�� ��. �ð��ʰ��� �߻��Ѵ�.
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

/*
bool kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	//pi[i] = N[..i]�� ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ��� �ִ� ����
	vector<int> pi = getPartialMatch(N);
	//begin = matched = 0�������� ��������.
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		//���� H�� �ش� ���ڰ� N�� �ش� ���ڿ� ���ٸ�
		if (matched < m && H[begin + matched] == N[matched]) {
			matched++;
			//��������� m���ڰ� ��� ��ġ�ߴٸ� �信 �߰��Ѵ�.
			if (matched == m) return true;
		}
		else {
			//����: matched�� 0�� ��쿡�� ���� ĭ�������� ���
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				//begin�� �Ű�ٰ� ó������ �ٽ� ���� �ʿ䰡 ����.
				//�ű� �Ŀ��� pi[matched-1]��ŭ�� �׻� ��ġ�ϱ� �����̴�.
				matched = pi[matched - 1];
			}
		}
	}
	return false;
}

int palindromize(const string& str) {
	int n = str.length();
	string revStr = str;
	reverse(revStr.begin(), revStr.end());
	int maxPand = 0;
	for (int i = 1; i <= n; i++) {
		string partialStr = revStr.substr(0, i);
		int m = partialStr.length();
		if (!kmpSearch(str, partialStr))
			break;

		maxPand = max(m, maxPand);
	}
	return 2 * n - maxPand;
}*/

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
