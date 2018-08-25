#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int C, K;
string script;

struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
	bool operator() (int a, int b) {
		//ù t���ڰ� �ٸ��� �̵��� �̿��� ���Ѵ�.
		if (group[a] != group[b]) return group[a] < group[b];
		//�ƴ϶�� S[a+t...]�� S[b+t...]�� ù t���ڸ� ���Ѵ�.
		return group[a + t] < group[b + t];
	}
};

//���̻� �迭�� ����ϴ� �ǹ��� ���̾�� �˰���

//s�� ���̻� �迭�� ����Ѵ�.
vector<int> getSuffixArray(const string& s) {
	int n = s.size();
	//group[i] = ���̻���� ù t���ڸ� �������� �������� ��,
	//			 S[i...]�� ���� �׷� ��ȣ.
	//t=1�� ���� ������ �� ���� S[i...]�� ù ���ڷ� �׷� ��ȣ��
	//���� �൵ ���� ȿ���� �ִ�.
	int t = 1;
	vector<int> group(n + 1);
	for (int i = 0; i < n; i++) group[i] = s[i];
	group[n] = -1;
	//��������� ���̻� �迭�� �� ��ȯ ��. �� �迭�� lg(n)�� �����Ѵ�.
	vector<int> perm(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	while (t < n) {
		//group[]�� ù t���ڸ� �������� ����� �״�.
		//ù 2t���ڸ� �������� ���̻� �迭 perm�� �ٽ� �����Ѵ�.
		//���̻���� 2t�������� ���� �� ������ ���̻���� ���� �迭 
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);
		//2t���ڰ� n�� �Ѵ´ٸ� ���� ���̻� �迭 �ϼ�
		t *= 2;
		if (t >= n) break;
		//2t���ڸ� �������� �� �׷� ������ �����.
		//newGroup[i] = ���̻���� ù 2t���ڸ� �������� �������� ��,
		//			 S[i...]�� ���� �׷� ��ȣ.
		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0; // ù 2t���� �������� ���������� �������� �� ���� �տ� ���� ���̻���
							   //�׷� ��ȣ�� 0���� �����Ѵ�. ���� ù 2t���ڰ� ���ٸ� ���� �׷��ȣ��, �ٸ��ٸ� �׷� ��ȣ��
							   //1��ŭ �� �ø���.

		for (int i = 1; i < n; i++)
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		group = newGroup;
	}
	return perm;
}

//s[i...]�� s[j...]�� ���� ���λ��� �ִ� ���̸� ����Ѵ�.
int commonPrefix(const string& s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]) {
		i++; j++; k++;
	}
	return k;
}

//���̻� �迭�� �̿��� ������ ������ �ذ��ϴ� �˰���.

//k�� �̻� �����ϴ� s�� �κ� ���ڿ� �� �ִ� ���̸� ã�´�.
int longestFrequent(int k, const string& s) {
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	for (int i = 0; i + k <= s.size(); i++)
		ret = max(ret, commonPrefix(s, a[i], a[i + k - 1]));
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> K >> script;
		cout << longestFrequent(K, script) << endl;
	}
}