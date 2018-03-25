#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <cstdlib>
using namespace std;
int C, n;

//����Ž�� �˰���.
int brute(const vector<int>& russian, vector<int> korean) {
	sort(korean.begin(), korean.end());
	int ret = 0;
	do {
		int wins = 0;
		for (int i = 0; i < korean.size(); i++)
			if (korean[i] >= russian[i])
				wins++;
		ret = max(wins, ret);
	} while (next_permutation(korean.begin(), korean.end())); // ��� ���� ���� ����
	return ret;
}

//������ȹ�� �˰���
//�� �ѱ��� ������ �̹� ������ �߰��ߴ����� ���ΰ� taken�� �־��� ��,
//���� �������� ���� ��ġ�ؼ� ���� �� �ִ� �ִ� �¼�
int cache[(1 << 20)+1]; // n<=100�ε�, �̷� ������ ĳ�ø� ����ϸ� �޸𸮰� �ʹ� ���� �ʿ��ϴ�. �� ��� bool Ÿ���� ĳ�� �迭�� ����ϴ� ���� ����.
int order(const vector<int>& russian, const vector<int>& korean, int taken) {
	if (taken == (1 << n) - 1)
		return 0;

	int& ret = cache[taken];
	if (ret != -1)
		return ret;

	ret = 0;
	int curRus = 0;
	for (int i = 0; i < n; i++)
		if ((taken >> i) % 2 == 1)
			curRus++;

	for (int i = 0; i < n; i++)
		if ((taken >> i) % 2 == 0) {
			ret = max(ret, (russian[curRus] <= korean[i] ? 1 : 0) + order(russian, korean, taken + (1 << i)));
		}
	return ret;
}

//���� § �˰���. �ѱ����� ���þ����� ������ �迭�� ���� ������������ ������ ��,
//�ѱ����� �ְ� �������� ���þ��� �ְ� �����ú��� �� �۴ٸ� �� Ŀ���� ���� �ѱ����� �ּ� �����ð�
//���þ��� �ְ� �������� ��⸦ ġ���� �ϰ�, ���Ŀ��� �ѱ��� ���� ������ ��ΰ� �����
//�Ѵٶ�� �����߱� ������ �� �˰����� �ۼ��ߴ�.
//������ �� �˰����� russian = {3,3,4,7,8}, korean = {1,2,3,8,9}�� ������ó�� �������� ���� ��ȯ���� �ʴ´�.
int matchorder(vector<int>& russian, vector<int>& korean) {
	sort(russian.begin(), russian.end());
	sort(korean.begin(), korean.end());
	int cmpPos = 0;
	while (cmpPos <= n-1 && russian[n - 1 - cmpPos] > korean[n - 1])
		cmpPos++;
	return n - cmpPos;
}

//å�� ��.
int order(const vector<int>& russian, const vector<int>& korean) {
	int n = russian.size(), wins = 0;
	//���� ���� �ִ� �������� ������
	multiset<int> ratings(korean.begin(), korean.end());
	for (int rus = 0; rus < n; rus++) {
		//���� �������� ���� �ѱ� ������ �̱� �� ���� ���
		//���� �������� ���� ������ ����Ų��.
		if (*ratings.rbegin() < russian[rus])
			ratings.erase(ratings.begin());
		//�� ���� ��� �̱� �� �ִ� ���� �� ���� �������� ���� ������ ����Ų��.
		else {
			ratings.erase(ratings.lower_bound(russian[rus]));
			wins++;
		}
	}
	return wins;
}
int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		vector<int> russian, korean;
		cin >> n;
		int input;
		for (int i = 0; i < n; i++) {
			cin >> input;
			russian.push_back(input);
		}
		for (int i = 0; i < n; i++) {
			cin >> input;
			korean.push_back(input);
		}
		memset(cache, -1, sizeof(cache));
		cout << brute(russian, korean) << endl;
		cout << order(russian, korean,0) << endl;
		russian.clear();
		korean.clear();
	}
}