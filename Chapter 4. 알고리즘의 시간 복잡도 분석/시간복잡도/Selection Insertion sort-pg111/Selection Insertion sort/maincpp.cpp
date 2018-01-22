#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void selectionSort(vector<int>& A) {
	int N = A.size();
	int minIdx;
	for (int i = 0; i < N - 1; i++) {
		minIdx = i;
		for (int j = i + 1; j < N; j++) {
			if (A[minIdx] > A[j])
				minIdx = j;
		}
		swap(A[i], A[minIdx]);
	}
}

void InsertionSort(vector<int>& A) {
	int N = A.size();
	for (int i = 1; i < N; i++) {
		int j = i;
		while (j>0 && A[j] < A[j - 1]) {
			swap(A[j], A[j - 1]);
			--j;
		}
	}
}

int main(void) {
	vector<int> arr(10);
	vector<int> arr2(10);
	srand(time(NULL));
	
	for (int i = 0; i < arr.size(); i++)
		arr[i] = rand() % 10 + 1;

	selectionSort(arr);
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << ' ';
	cout << endl;

	for (int i = 0; i < arr2.size(); i++)
		arr2[i] = rand() % 100 + 1;

	InsertionSort(arr2);
	for (int i = 0; i < arr2.size(); i++)
		cout << arr2[i] << ' ';
	cout << endl;
}