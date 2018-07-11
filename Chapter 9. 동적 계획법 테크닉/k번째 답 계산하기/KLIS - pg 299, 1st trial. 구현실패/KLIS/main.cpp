#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits>
using namespace std;

const int MAX = numeric_limits<int>::max();
int C, n, k;

int cacheLen[501], cacheCnt[501], S[500];
//sortedS = 수열의 원소들을 원소 값을 기준으로 오름차순 정렬하여 저장한 배열.
vector<pair<int, int>> sortedS;

//S[start]에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
int lis3(int start) {
	//메모이제이션
	int& ret = cacheLen[start + 1];
	if (ret != -1) return ret;
	//항상 S[start]는 있기 때문에 길이는 최하 1
	ret = 1;
	for (int next = start + 1; next < n; next++)
		if (start == -1 || S[start] < S[next])
			ret = max(ret, lis3(next) + 1);
	return ret;
}

//S[start]에서 시작하는 최대 증가 부분 수열의 수를 반환한다.
int count(int start) {
	//기저 사례: LIS의 길이가 1인 경우 최대 증가 부분 수열을 하나 찾음.
	if (lis3(start) == 1) return 1;
	//메모이제이션
	int& ret = cacheCnt[start + 1];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = start + 1; next < n; next++) {
		if ((start == -1 || S[start] < S[next]) &&
			lis3(start) == lis3(next) + 1)
			//lis3(start) == lis3(next) + 1인 경우만 확인하므로 반드시
			//LIS의 수만을 센다.
			ret = min<long long>(MAX, (long long)ret + count(next));
	}
	return ret;
}

//S[start]에서 시작하는 LIS 중 사전순으로 skip개 건너뛴 수열을
//lis에 저장한다.
void reconstruct(int start, int skip, vector<int>& lis) {
	//1. S[start]는 항상 LIS에 포함된다.
	if (start != -1) lis.push_back(S[start]);
	//2. S[start] 뒤에 올 수 있는 숫자들의 목록을 만든다.
	//사전순으로 먼저 오는 숫자들을 먼저 벡터에 넣는다.
	vector<int> nextList;
	for (int i = 0; i < n; i++) {
		int next = sortedS[i].second;
		if (next > start && (start == -1 || S[start] < S[next]) &&
			lis3(start) == lis3(next) + 1)
			nextList.push_back(next);
	}
	//3. 목록 중 k번째 LIS에 포함되는 다음 숫자를 찾는다.
	for (int i = 0; i < nextList.size(); i++) {
		//이 숫자를 뒤에 이어서 만들 수 있는 LIS의 개수를 본다.
		int idx = nextList[i];
		int cnt = count(idx);
		if (cnt <= skip)
			skip -= cnt;
		else {
			//다음 숫자는 S[idx]임을 알았다.
			//4. 재귀 호출을 통해 LIS의 나머지 부분을 계산한다.
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