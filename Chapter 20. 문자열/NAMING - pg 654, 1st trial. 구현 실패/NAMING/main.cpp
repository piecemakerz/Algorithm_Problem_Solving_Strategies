#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

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

//�� Ǯ��
//�κ� ��ġ ���̺��� ���� ��� ���λ翡 ���� Ȯ���� �ϴ� ���� ���� �� �־�����,
//������ ��ġ�� '���ɼ�'�� �ִ� ��� ���λ翡 ���� S���� �񱳸� �ϹǷ�
//������ ���ѽð��� ������ ���� �ð� �ʰ��� �߻��Ѵ�.
vector<int> naming(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);

	int begin = 1, matched = 0;
	int n = s.length();
	ret.push_back(n);

	while (begin < n) {
		if (begin + matched < n && s[begin + matched] == s[matched]) {
			matched++;
			if (begin + matched == n)
				ret.push_back(matched);
		}
		else {
			if (matched == 0)
				begin++;
			else {
				begin += matched - pi[matched - 1];
				//matched = pi[matched - 1]; // �� �κ� ������ �� �˰����� �������� �ʾҴ�. 
				//KMP�˰��򿡼��� �κ� ���ڿ� �˻��� �����̰�, matched������ ���� �ʿ� ���� ������ ��ġ�ϹǷ�
				//matched�� pi[matched-1]�� ������ �ξ�����, �� �˰����� ������ ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ�����
				//���̸� ���� ����ϴ� ���̹Ƿ� matched�� 0���� �ξ�� �Ѵ�.
				matched = 0;
			}
		}
	}
	return ret;
}

//å�� ��

//s�� ���λ絵 �ǰ� ���̻絵 �Ǵ� ���ڿ����� ���̸� ��ȯ�Ѵ�.
vector<int> getPrefixSuffix(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);
	int k = s.size();
	while (k > 0) {
		//s[...k-1]�� ���̴�.
		ret.push_back(k);
		k = pi[k - 1];
	}
	return ret;
}

int main(void) {
	string father;
	string mother;
	cin >> father >> mother;
	vector<int> result = naming(father + mother);
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i] << ' ';
	cout << endl;
	return 0;
}