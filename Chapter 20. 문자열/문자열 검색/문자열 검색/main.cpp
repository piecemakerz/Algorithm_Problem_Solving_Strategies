#include <iostream>
#include <vector>
#include <string>
using namespace std;

//�ܼ��� ���ڿ� �˻� �˰����� ����
//H�� �κ� ���ڿ��� N���ڿ��� �����ϴ� ���� ��ġ���� ��� ��ȯ�Ѵ�.
vector<int> naiveSearch(const string& H, const string& N) {
	vector<int> ret;
	//��� ���� ��ġ�� �� �õ��� ����.
	for (int begin = 0; begin + N.size() <= H.size(); begin++) {
		bool matched = true;
		for(int i=0; i<N.size(); i++)
			if (H[begin + i] != N[i]) {
				matched = false;
				break;
			}
		if (matched) ret.push_back(begin);
	}
	return ret;
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
		else{
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