#include <iostream>
#include <vector>
#include <ctime>
#define NUMBERS_TO_PICK 4

using namespace std;
// 내 풀이. 이미 벡터에 들어가 있는 마지막 원소보다 하나 더 큰 정수부터 시작하면 코드가 훨씬 깔끔해지고
// 해석하기 쉬워짐. 내 코드의 경우 어떻게 체크 시작 원소를 결정하고 어떻게 마지막 체크할 원소를 결정할 지 많이 헤맴.
void mypick(vector<int>& arr, int n, int start=0) {
	int arrSize = arr.size();

	if (arrSize == 4) {
		cout << '(';
		for (int i = 0; i < 4; i++) {
			cout << arr[i] << ' ';
		}
		cout << ')'<<endl;
		return;
	}

	for (int i = start; i <= start+(n-arrSize); i++) {
		if (i >= n)
			break;
		arr.push_back(i);
		mypick(arr, n, i+1);
		arr.pop_back();
	}
}

void pick(int n, vector<int>& picked, int toPick){
	if (toPick == 0) {
		cout << "( ";
		for (int i = 0; i < NUMBERS_TO_PICK; i++)
			cout << picked[i] << ' ';
		cout << ')'<<endl;
		return;
	}

	int smallest = picked.empty() ? 0 : picked.back() + 1;

	for (int next = smallest; next < n; next++) {
		picked.push_back(next);
		pick(n, picked, toPick - 1);
		picked.pop_back();
	}
}

int main(void) {
	int N;
	cin >> N;
	vector<int> arr;
	clock_t begin, end;
	begin = clock();
	mypick(arr, N);
	end = clock();
	cout << "수행시간 : " << ((double)(end - begin) / CLOCKS_PER_SEC) << endl;
	arr.clear();

	begin = clock();
	pick(N, arr, NUMBERS_TO_PICK);
	end = clock();
	cout << "수행시간 : " << ((double)(end - begin) / CLOCKS_PER_SEC) << endl;
	return 0;
}