#include <vector>
#include <algorithm>
using namespace std;

void quickSort(vector<int>& arr, int left, int right) {
	int i = left, j = right;
	//개선된 피벗 선택을 위해 세 값(좌측 끝, 중앙, 우측 끝)의 중위값을 피벗으로 사용한다.
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

	//피벗을 제외한 왼쪽 부분과 오른쪽 부분에 대해
	//새로운 퀵정렬을 수행한다.
	if (left < j)
		quickSort(arr, left, j);

	if (i < right)
		quickSort(arr, i, right);
}