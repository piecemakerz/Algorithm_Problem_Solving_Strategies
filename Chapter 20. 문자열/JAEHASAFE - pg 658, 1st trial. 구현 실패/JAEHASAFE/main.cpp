#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C, N;

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
//�� Ǯ��. ���������� �� �����ϳ� ���� �� �����̴�.
//���� �� ���ڿ��� ���� �� �� ���ڿ�(H)�� ���� ���ڿ�(N)�� H�� ������ġ�� �����ذ��� ���Ͽ�
//���ڿ� N�� ���λ簡 �� ���ڿ� H�� ���̻翡 ���Ե� �� ������ �ϴ� Ƚ���� ã�Ҵٰ� �����ϴ� �˰����� �ۼ��Ͽ���.
//(ex. H = babab�̰� N = abbab�� ��, H[3...]�� N[...1]�� �����ϹǷ� �ð� �������� 3(5-2)���� ������ �ȴ�.)
//������ �̿� ���� �˰����� ����� ��� N�� ������ �� �κа� H�� ���� �� �κ��� ��ġ���� �ʴ� ��찡
//�߻��� �� �ִ�.
//(ex. H = aabaa�̰� N = aaaba�� ��, H[3...]�� N[...1]�� �����ϹǷ� �� �˰����� ����� ���
//�ð� �������� 3(5-2)���� ������ �ȴٴ� ����� ������, 3���� ���� ��� N = abaaa�� �ǹǷ� ��ġ���� �ʴ´�.
//��, H[3...]�� N[...1]�� �����ϴٰ� �ؼ� ���� �κ� H[...2]�� N[[2...]�� �����ϴٴ� ���� ����������
//�ʴ´ٴ� ���̴�.)
//���� H�� ������ ���� ���λ� �κ�(H[...2])�� N�� ������ ���� ���̻� �κ�(N[2...])�� ��������
//Ȯ���ϴ� �ڵ嵵 �߰��ؾ� ������ �߻����� �ʴ´�.

int kmpSearch(const string& H, const string& N, const vector<int>& pi) {
	int n = H.length();
	int begin = 1, matched = 0;
	while (begin + matched < n) {
		//���� H�� �ش� ���ڰ� N�� �ش� ���ڿ� ���ٸ�
		if (H[begin + matched] == N[matched]) {
			matched++;
			if (begin + matched == n) return matched;
		}
		else {
			//����: matched�� 0�� ��쿡�� ���� ĭ�������� ���
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return 1;
}

int unlockSafe(const vector<string>& strArr, const vector<vector<int>>& pi) {
	int shiftCount = 0;
	int strN = strArr[0].length();
	bool clockWise = true;

	for (int i = 0; i < N; i++) {
		if (clockWise)
			//�ð� �������� ȸ��
			shiftCount += strN - (kmpSearch(strArr[i + 1], strArr[i], pi[i]));
		else
			//�ݽð� �������� ȸ��
			shiftCount += strN - (kmpSearch(strArr[i], strArr[i+1], pi[i+1]));
		clockWise = !clockWise;
	}
	return shiftCount;
}
*/

//å�� ��
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

//shift(original, tarrget) = ���ڿ� original�� target���� ����� ���� ȯ�� ����Ʈ�� �� ���̳� �ؾ� �ϴ��� ��ȯ
int shifts(const string& original, const string& target) {
	return kmpSearch(original + original, target)[0];
}

int unlockSafe(const vector<string>& strArr) {
	int shiftCount = 0;
	int strN = strArr[0].length();
	bool clockWise = true;

	for (int i = 0; i < N; i++) {
		if (clockWise)
			//�ð� �������� ȸ��
			shiftCount += shifts(strArr[i+1], strArr[i]);
		else
			//�ݽð� �������� ȸ��
			shiftCount += shifts(strArr[i], strArr[i+1]);
		clockWise = !clockWise;
	}
	return shiftCount;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> N;
		vector<string> strArr(N+1);
		for (int i = 0; i < N + 1; i++)
			cin >> strArr[i];
		cout << unlockSafe(strArr) << endl;
	}
	return 0;
}