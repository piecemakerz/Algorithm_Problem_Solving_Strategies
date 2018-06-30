#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int C, N;

//�� Ǯ��. å�� Ǯ�� 1�� �����ϳ� å�� Ǯ�̺��� �� �����ϴ�.
vector<string> matched;
string wildcard;
string str;

//isMatchable[i][j] = str[j...]�� wildcard[i...]�� ǥ���� �� �ִ°�
int isMatchable[100][100];

int checkWildcard(int wildIdx, int strIdx) {
	if (wildIdx >= wildcard.length() || strIdx >= str.length())
		return 0;

	int& ret = isMatchable[wildIdx][strIdx];
	if (ret != -1)
		return ret;

	while (wildIdx < wildcard.length() && strIdx < str.length()) {
		char curWild = wildcard[wildIdx], curStr = str[strIdx];
		//���ڰ� ���ų� ?�� ó���� �� ���� ��
		if (curWild == curStr || curWild == '?') {
			wildIdx++;
			strIdx++;
		}
		//���� * ó���ϱ�
		//*�� 0���� ���ں��� str�� ������ ó���ϴ� ��� ��츦 ���ȣ��� ó���Ѵ�.
		//�ٸ� 0���� ���ڸ� ó���ϴ� ���� ���� ȣ�⹮���� ó���� �� �����Ƿ� 
		//���� ���ȣ��� ó������ �ʴ´�.
		else if (curWild == '*') {
			if (wildIdx == wildcard.length() - 1) {
				return ret = 1;
			}
			int passed = 1;
			while (strIdx + passed < str.length()) {
				if (checkWildcard(wildIdx + 1, strIdx + passed))
					return ret = 1;
				passed++;
			}
			wildIdx++;
		}
		//�� ���� ��쿡�� ��� �������� �ʴ´�.
		else
			break;
	}

	if (wildIdx == wildcard.length() && strIdx == str.length())
		return ret = 1;
	else
		return ret = 0;
}

//å�� �� 1. ���ϵ�ī�� ������ �ذ��ϴ� ���� ��ȹ�� �˰���

//-1�� ���� ���� ������ �ʾ����� �ǹ��Ѵ�.
//1�� �ش� �Էµ��� ���� �������� �ǹ��Ѵ�.
//0�� �ش� �Էµ��� ���� �������� ������ �ǹ��Ѵ�.
int cache[101][101];
//���ϰ� ���ڿ�
string W, S;
//���ϵ�ī�� ���� W[w...]�� ���ڿ� S[s...]�� �����Ǵ��� ���θ� ��ȯ�Ѵ�.
bool matchMemoized(int w, int s) {
	//�޸������̼�
	int& ret = cache[w][s];
	if (ret != -1) return ret;
	//W[w]�� S[s]�� ���糪����.
	while (s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s])) {
		w++;
		s++;
	}
	//���̻� ������ �� ������ �� while���� �������� Ȯ���Ѵ�.
	//���� ���� �����ؼ� ���� ��� : ���ڿ��� ������� ���̴�.
	if (w == W.size()) return ret = (s = S.size());
	//*�� ������ ���� ���: *�� �� ���ڸ� �����ؾ� ���� ��� ȣ���ϸ鼭 Ȯ���Ѵ�.
	if (W[w] == '*')
		for (int skip = 0; skip + s <= S.size(); skip++)
			if (matchMemoized(w + 1, s + skip))
				return ret = 1;
	//�� ���� ��쿡�� ��� �������� �ʴ´�.
	return ret = 0;
}

//å�� �� 2. ���� ����� �����Ͽ� ������ O(n^3)�� �ƴ� O(n^2) �ð��� Ǫ�� ���.
bool matchMemoized2(int w, int s) {
	//�޸������̼�
	int& ret = cache[w][s];
	if (ret != -1) return ret;
	//ù �� ���ھ��� ���� �̵��� ���� �����Ǵ��� ���ȣ��� Ȯ���Ѵ�.
	if (s < S.size() && w < W.size() &&
		(W[w] == '?' || W[w] == S[s])) {
		return ret = matchMemoized2(w + 1, s + 1);	
	}
	//���̻� ������ �� ������ �� while���� �������� Ȯ���Ѵ�.
	//���� ���� �����ؼ� ���� ��� : ���ڿ��� ������� ���̴�.
	if (w == W.size()) return ret = (s = S.size());
	//*�� ������ ���� ���: *�� �� ���ڸ� �����ؾ� ���� ��� ȣ���ϸ鼭 Ȯ���Ѵ�.
	if (W[w] == '*')
		//�� �ܰ迡�� *�� �ƹ� ���ڵ� ������Ű�� ���� ������, �ƴϸ� �� ���ڸ� �� ������ų ���ΰ��� ����.
		if (matchMemoized2(w + 1, s) || matchMemoized2(w, s+1))
			return ret = 1;
	//�� ���� ��쿡�� ��� �������� �ʴ´�.
	return ret = 0;
}
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> wildcard >> N;
		for (int i = 0; i < N; i++) {
			memset(isMatchable, -1, sizeof(isMatchable));
			cin >> str;
			if (checkWildcard(0, 0))
				matched.push_back(str);
		}
		sort(matched.begin(), matched.end());
		for (int i = 0; i < matched.size(); i++)
			cout << matched[i] << endl;

		matched.clear();
	}
}