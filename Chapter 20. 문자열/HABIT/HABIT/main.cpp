#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int C, K;

//ù t���ڷ� ���� �׷� ������ �̿��� ù 2t���ڸ� ���ϴ� ������ ����

//�� ���̻���� ù t���ڸ� �������� �� �׷� ��ȣ�� �־��� ��,
//�־��� �� ���̻縦 ù 2*t���ڸ� �������� ���Ѵ�.
//group[]�� ���̰� 0�� ���̻絵 �����Ѵ�.
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

//�� �κ� ���ڿ��� �ι� �̻� ������ ��� �̸� ���λ縦 ���� ���̻���� �׻� ������ �ִ�.
//���� ������ ���̻���� ���λ簡 �����ϴٸ� �̴� �ߺ� �����ϴ� �κ� ���ڿ��̴�.

int	longestPartialArray(const string& str) {
	int n = str.length();
	vector<int> suffix = getSuffixArray(str); // suffix = str�� ���������� ���ĵ� ���̻� �迭
	vector<int> length(n+1, 1); //���̰� i�� �κ����յ� �� ���� ���� �����ϴ� �κ������� ��. 
	//�⺻������ str�� ��� ���̻�� str�� �κ������̹Ƿ� length�迭�� ���ҵ��� 1�� �ʱ�ȭ�Ѵ�. (�ּ� ���̰� i�� �κ������� �ϳ��� �����Ѵ�)
	vector<int> lengthCount(n + 1, 1); // ������� ���ƿ� ���̰� i�� �κ� ���ڿ��� ��

	int maxSameCount = 0; // ������� ���ƿ� �κ� ���ڿ��� �ִ� ����
	for (int i = 1; i < suffix.size(); i++) { // str�� ��� ���̻翡 ���� ��ȸ
		int curSuffix = suffix[i], prevSuffix = suffix[i - 1];
		int sameCount = 0; // �κ� ���ڿ��� ����
		while (curSuffix < n && prevSuffix < n) {
			if (str[curSuffix] == str[prevSuffix]) {
				lengthCount[++sameCount]++;
				curSuffix++; prevSuffix++;
				maxSameCount = max(maxSameCount, sameCount);
				//���ϴ� �� ���� ���̻�� �� �ϳ��� ���̻簡 �ٸ� ���̻��� ���λ��� ��,(ex - ana, anana)
				//else���� ��ġ�� �ʰ� while���� ���������� ������ maxSameCount�� ������� ���ƿ� �κ� ���ڿ��� �ִ� ���̸�
				//�����س��� �ʴ´ٸ� ���� ��ȸ���� length�迭�� ������ �� �����ؾ� �� ���ҵ� �� �Ϻθ� ������ �� �ִ�.
			}
			else {
				for (int i = sameCount + 1; i <= maxSameCount; i++) //���� ��ȸ������ ���Ҵ� �κ����տ� ���ؼ��� length�迭�� �������� �ʴ´�.
					length[i] = max(length[i], lengthCount[i]); // ������ ���� �κ������� ���� �� Ŭ ���� �����Ƿ� max������ �Ѵ�.
				for (int i = sameCount + 1; i <= maxSameCount; i++)
					lengthCount[i] = 1;
				maxSameCount = sameCount;
				break;
			}
		}
	}
	
	//else���� ��ȸ���� �����Ƿν� ���ŵ��� ���� length�迭�� ������ ����
	for (int i = 1; i <= n; i++)
		length[i] = max(length[i], lengthCount[i]);

	//K�� �̻� �����ϴ� �κ� ���ڿ��� �ִ� ���� ��ȯ
	for (int i = n; i > 0; i--) {
		if (length[i] >= K)
			return i;
	}
	//K�� �̻� �����ϴ� �κ� ���ڿ��� ���� ��� 0 ��ȯ
	return 0;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> K;
		string inputStr;
		cin >> inputStr;
		cout << longestPartialArray(inputStr) << endl;
	}
}