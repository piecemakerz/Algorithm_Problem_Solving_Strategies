#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits>
using namespace std;

const int MAX = numeric_limits<int>::max();
int C, n, k;

int cacheLen[501], cacheCnt[501], S[500];
//sortedS = ������ ���ҵ��� ���� ���� �������� �������� �����Ͽ� ������ �迭.
vector<pair<int, int>> sortedS;

//S[start]���� �����ϴ� ���� �κ� ���� �� �ִ� ���̸� ��ȯ�Ѵ�.
int lis3(int start) {
	//�޸������̼�
	int& ret = cacheLen[start + 1];
	if (ret != -1) return ret;
	//�׻� S[start]�� �ֱ� ������ ���̴� ���� 1
	ret = 1;
	for (int next = start + 1; next < n; next++)
		if (start == -1 || S[start] < S[next])
			ret = max(ret, lis3(next) + 1);
	return ret;
}

//S[start]���� �����ϴ� �ִ� ���� �κ� ������ ���� ��ȯ�Ѵ�.
int count(int start) {
	//���� ���: LIS�� ���̰� 1�� ��� �ִ� ���� �κ� ������ �ϳ� ã��.
	if (lis3(start) == 1) return 1;
	//�޸������̼�
	int& ret = cacheCnt[start + 1];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = start + 1; next < n; next++) {
		if ((start == -1 || S[start] < S[next]) &&
			lis3(start) == lis3(next) + 1)
			//lis3(start) == lis3(next) + 1�� ��츸 Ȯ���ϹǷ� �ݵ��
			//LIS�� ������ ����.
			ret = min<long long>(MAX, (long long)ret + count(next));
	}
	return ret;
}

//S[start]���� �����ϴ� LIS �� ���������� skip�� �ǳʶ� ������
//lis�� �����Ѵ�.
void reconstruct(int start, int skip, vector<int>& lis) {
	//1. S[start]�� �׻� LIS�� ���Եȴ�.
	if (start != -1) lis.push_back(S[start]);
	//2. S[start] �ڿ� �� �� �ִ� ���ڵ��� ����� �����.
	//���������� ���� ���� ���ڵ��� ���� ���Ϳ� �ִ´�.
	vector<int> nextList;
	for (int i = 0; i < n; i++) {
		int next = sortedS[i].second;
		if (next > start && (start == -1 || S[start] < S[next]) &&
			lis3(start) == lis3(next) + 1)
			nextList.push_back(next);
	}
	//3. ��� �� k��° LIS�� ���ԵǴ� ���� ���ڸ� ã�´�.
	for (int i = 0; i < nextList.size(); i++) {
		//�� ���ڸ� �ڿ� �̾ ���� �� �ִ� LIS�� ������ ����.
		int idx = nextList[i];
		int cnt = count(idx);
		if (cnt <= skip)
			skip -= cnt;
		else {
			//���� ���ڴ� S[idx]���� �˾Ҵ�.
			//4. ��� ȣ���� ���� LIS�� ������ �κ��� ����Ѵ�.
			reconstruct(idx, skip, lis);
			break;
		}
	}
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cacheLen, -1, sizeof(cacheLen));
		memset(cacheCnt, -1, sizeof(cacheCnt));
		cin >> n >> k;
		for (int i = 0; i < n; i++) {
			cin >> S[i];
			sortedS.push_back(make_pair(S[i], i));
		}
		sort(sortedS.begin(), sortedS.end());
		cout << lis3(-1) - 1 << endl;
		
		vector<int> lis;
		reconstruct(-1, k - 1, lis);
		for (int i = 0; i < lis.size(); i++)
			cout << lis[i] << ' ';
		cout << endl;
		sortedS.clear();
	}
	return 0;
}