#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int C, N;

//�� Ǯ��. �ݽð� �������� ������ ���� �ܼ��� dial���� nextState��
//ã�� �������� ǥ���� �� ������, �ð� �������� ������ ���� dial�� 
//nextState�� ������ ����ϴ� ������ ǥ���Ͽ���.
int solve(int n) {
	int ret = 0;
	string curState, nextState, dial;
	cin >> curState;
	for (int i = 0; i < n; i++) {
		cin >> nextState;
		dial = curState + curState;
		curState = nextState;

		if (i % 2 == 0) {
			reverse(dial.begin(), dial.end());
			reverse(nextState.begin(), nextState.end());
		}
		ret += dial.find(nextState);
	}
	return ret;
}

//KMP �˰����� �̿��� �κ� ��ġ ���̺��� �����ϱ�
//N���� �ڱ� �ڽ��� ã���鼭 ��Ÿ���� �κ� ��ġ�� �̿��� pi[]�� ����Ѵ�.
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

//Ŀ����-�𸮽�-����(KMP) ���ڿ� �˻� �˰����� ����
//H�� �κ� ���ڿ��� N�� �����ϴ� ���� ��ġ���� ��� ��ȯ�Ѵ�.
vector<int> kmpSearch(const string& H, const string& N) {
	int n = H.size(), m = N.size();
	vector<int> ret;
	//pi[i] = N[..i]�� ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ��� �ִ� ����
	vector<int> pi = getPartialMatch(N);
	//begin = matched = 0�������� ��������.
	int begin = 0, matched = 0;
	while (begin <= n - m) {
		//���� H�� �ش� ���ڰ� N�� �ش� ���ڿ� ���ٸ�
		if (matched < m && H[begin + matched] == N[matched]) {
			matched++;
			//��������� m���ڰ� ��� ��ġ�ߴٸ� �信 �߰��Ѵ�.
			if (matched == m) ret.push_back(begin);
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
	return ret;
}

//������ �ݰ� ������ �ذ��ϴ� å�� �˰���.
//original�� �ݽð� �������� ���� target�� ����� ���� 
//�ݰ� ������ �ϴ� ���� ��ȯ�Ѵ�. KMP �˰����� ���������� ����Ͽ���.
int shift(const string& original, const string& target) {
	return kmpSearch(original + original, target)[0];
}

int bookSolve(int n) {
	int ret = 0;
	string curState, nextState;
	cin >> curState;
	for (int i = 0; i < n; i++) {
		cin >> nextState;
		//�ð� �������� ȸ���� ���
		if (i % 2)
			ret += shift(nextState, curState);
		//�ݽð� �������� ȸ���� ���
		else
			ret += shift(curState, nextState);

		curState = nextState;
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N;
		cout << solve(N) << endl;
	}
}