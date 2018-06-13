#include <iostream>
#include <vector>
using namespace std;

int N;

void merge(vector<int>& arr, int left, int mid, int right) {
	int i, j, k;
	int i = left, j = mid + 1, k = left;
	
	vector<int> tempArr(N);

	//left부터 mid까지의 블록과 mid+1부터 right까지의 블록을 서로 비교
	while (i <= mid && j <= right) {
		if (arr[i] <= arr[j]) {
			tempArr[k] = arr[i];
			i++;
		}
		else {
			tempArr[k] = arr[j];
			j++;
		}
		k++;
	}
	//left 블록의 값이 다 처리되었지만, right 블록의 index가 남아 있는 경우
	//right 블록의 남은 부분을 순차적으로 tempArr에 복사
	if (i > mid) {
		for (int l = j; l <= right; l++)
			tempArr[k++] = arr[l];
	}
	//left블록의 남은 부분을 순차적으로 tempArr에 복사
	else {
		for (int l = i; l <= mid; l++)
			tempArr[k++] = arr[l];
	}

	//임시 배열인 tempArr의 값을 원본 배열에 복사한다.
	for (int l = left; l <= right; l++)
		arr[l] = tempArr[l];
}

void mergesort(vector<int>& arr, int left, int right) {
	int mid;

	if (left < right) {
		//절반으로 나누기 위해 중간 위치 찾기
		mid = (left + right) / 2;

		//분할
		mergesort(arr, left, mid);
		mergesort(arr, mid + 1, right);

		//합병
		merge(arr, left, mid, right);
	}
}