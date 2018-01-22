#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
int n, m;
bool areFriends[10][10];

//내 풀이
int MycountPairings(const vector<pair<int, int>>& arr, vector<bool>& picked, int curIdx=0, int pickedNum=0) {
	int ret = 0;

	//기저사례1: 모든 학생들을 골랐을 때
	if (pickedNum == n)
		return 1;
	//기저사례2: 모든 친구 쌍 수를 검사했을 때(모든 학생들을 고르지 못함)
	if (curIdx > m-1)
		return 0;
	
	if (!picked[arr[curIdx].first] && !picked[arr[curIdx].second]) {
		picked[arr[curIdx].first] = true;
		picked[arr[curIdx].second] = true;
		ret += MycountPairings(arr, picked, curIdx + 1, pickedNum + 2);

		picked[arr[curIdx].first] = false;
		picked[arr[curIdx].second] = false;
	}

	ret += MycountPairings(arr, picked, curIdx + 1, pickedNum);
	return ret;
}

//책의 답
int countPairings(bool taken[10]) {
	int toCheck = -1;
	for (int i = 0; i<n; i++) {
		if (!taken[i]) {
			toCheck = i;
			break;
		}
	}

	if (toCheck == -1)
		return 1;

	int ret = 0;
	for (int i = toCheck + 1; i<n; i++) {
		if (!taken[i] && areFriends[toCheck][i]) {
			taken[toCheck] = taken[i] = true;
			ret += countPairings(taken);
			taken[toCheck] = taken[i] = false;
		}
	}
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> n >> m;
		vector<bool> picked(n);
		vector<pair<int, int>> arr;
		int input1, input2;

		for (int j = 0; j < m; j++) {
			cin >> input1 >> input2;
			arr.push_back(make_pair(input1, input2));
		}

		cout << MycountPairings(arr, picked)<<endl;
	}
	return 0;
}
