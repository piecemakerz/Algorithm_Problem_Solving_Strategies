#include <iostream>
#include <vector>
using namespace std;

int N;

void merge(vector<int>& arr, int left, int mid, int right) {
	int i, j, k;
	int i = left, j = mid + 1, k = left;
	
	vector<int> tempArr(N);

	//left���� mid������ ��ϰ� mid+1���� right������ ����� ���� ��
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
	//left ����� ���� �� ó���Ǿ�����, right ����� index�� ���� �ִ� ���
	//right ����� ���� �κ��� ���������� tempArr�� ����
	if (i > mid) {
		for (int l = j; l <= right; l++)
			tempArr[k++] = arr[l];
	}
	//left����� ���� �κ��� ���������� tempArr�� ����
	else {
		for (int l = i; l <= mid; l++)
			tempArr[k++] = arr[l];
	}

	//�ӽ� �迭�� tempArr�� ���� ���� �迭�� �����Ѵ�.
	for (int l = left; l <= right; l++)
		arr[l] = tempArr[l];
}

void mergesort(vector<int>& arr, int left, int right) {
	int mid;

	if (left < right) {
		//�������� ������ ���� �߰� ��ġ ã��
		mid = (left + right) / 2;

		//����
		mergesort(arr, left, mid);
		mergesort(arr, mid + 1, right);

		//�պ�
		merge(arr, left, mid, right);
	}
}