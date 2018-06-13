#include <vector>
#include <algorithm>
using namespace std;

void quickSort(vector<int>& arr, int left, int right) {
	int i = left, j = right;
	//������ �ǹ� ������ ���� �� ��(���� ��, �߾�, ���� ��)�� �������� �ǹ����� ����Ѵ�.
	int mid = (left + right) / 2;
	if (arr[mid] < arr[left])
		swap(arr[left], arr[mid]);
	if(arr[right] < arr[left])
		swap(arr[left], arr[right]);
	if (arr[mid] < arr[right])
		swap(arr[mid], arr[right]);

	int pivot = arr[right];
	do {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			swap(arr[i], arr[j]);
			i++;
			j--;
		}
	} while (i <= j);

	//�ǹ��� ������ ���� �κа� ������ �κп� ����
	//���ο� �������� �����Ѵ�.
	if (left < j)
		quickSort(arr, left, j);

	if (i < right)
		quickSort(arr, i, right);
}