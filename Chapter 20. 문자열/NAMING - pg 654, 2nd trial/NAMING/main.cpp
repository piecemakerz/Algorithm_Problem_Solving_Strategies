#include <iostream>
#include <string>
#include <vector>
using namespace std;

//KMP �˰����� �̿��� �κ� ��ġ ���̺� ����
vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector<int> pi(m, 0);
	//KMP�� �ڱ� �ڽ��� ã�´�.
	//N�� N���� ã�´�. begin = 0�̸� �ڱ� �ڽ��� ã�ƹ����Ƿ� �ȵ�.
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
			else{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

//�� Ǯ��. �κ� ��ġ ���̺��� ���ߴٸ� str�� ���λ絵 �ǰ� ���̻絵 �Ǵ�
//���ڿ����� ���� �� �ִ�.
vector<int> solve(const string& str) {
	int n = str.length();
	vector<int> names;
	vector<int> pi = getPartialMatch(str);
	names.push_back(n);

	int curSize = n;
	while (true) {
		curSize = pi[curSize - 1];
		if (curSize == 0)
			break;
		names.push_back(curSize);
	}
	return names;
}

//S�� ���λ絵 �ǰ� ���̻絵 �Ǵ� ��� ���ڿ��� ���̸� ����ϴ� å�� �˰���
vector<int> getPrefixSuffix(const string& s) {
	vector<int> ret, pi = getPartialMatch(s);
	int k = s.size();
	while (k > 0) {
		//s[...k-1]�� ���̴�.
		ret.push_back(k);
		//s[...k-1]�� ���̻絵 �ǰ� ���λ絵 �Ǵ� ���ڿ��� ���̴�.
		k = pi[k - 1];
	}
	return ret;
}

int main(void) {
	string father, mother;
	cin >> father >> mother;
	vector<int> result = solve(father + mother);
	for (int i = result.size() - 1; i >= 0; i--)
		cout << result[i] << ' ';
	cout << endl;
	return 0;
}