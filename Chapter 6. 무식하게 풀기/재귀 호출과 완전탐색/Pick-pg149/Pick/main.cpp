#include <iostream>
#include <vector>
#include <ctime>
#define NUMBERS_TO_PICK 4

using namespace std;
// �� Ǯ��. �̹� ���Ϳ� �� �ִ� ������ ���Һ��� �ϳ� �� ū �������� �����ϸ� �ڵ尡 �ξ� ���������
// �ؼ��ϱ� ������. �� �ڵ��� ��� ��� üũ ���� ���Ҹ� �����ϰ� ��� ������ üũ�� ���Ҹ� ������ �� ���� ���.
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
	cout << "����ð� : " << ((double)(end - begin) / CLOCKS_PER_SEC) << endl;
	arr.clear();

	begin = clock();
	pick(N, arr, NUMBERS_TO_PICK);
	end = clock();
	cout << "����ð� : " << ((double)(end - begin) / CLOCKS_PER_SEC) << endl;
	return 0;
}