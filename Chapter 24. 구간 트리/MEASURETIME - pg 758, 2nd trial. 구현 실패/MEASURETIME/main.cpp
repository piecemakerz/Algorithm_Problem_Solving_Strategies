#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

//펜윅 트리의 완전한 구현

//펜윅 트리의 구현. 가상의 배열 A[]의 부분 합을
//빠르게 구현할 수 있도록 한다. 초기화시에는 A[]의
//원소가 전부 0이라고 생각한다.
struct FenwickTree {
	//tree[i] = 오른쪽 끝 위치가 A[i]인 구간 합
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	//A[0...pos]의 부분 합을 구한다.
	int sum(int pos) {
		//인덱스가 1부터 시작한다고 생각하자
		pos++;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//다음 구간을 찾기 위해 최종 비트를 지운다.
			pos &= (pos - 1);
		}
		return ret;
	}
	//A[pos]에 val을 더한다.
	void add(int pos, int val) {
		pos++;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

//삽입 정렬 시간 재기 문제를 펜윅 트리로 해결하는 책의 풀이

//펜윅 트리를 이용해 문제를 해결한다.
//펜윅 트리에는 각 숫자의 출현 횟수를 저장한다.
long long countMoves(const vector<int> A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); i++) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}

//삽입 정렬 시간 재기 문제를 병합 정렬을 이용해 해결한 책의 풀이

//A[left..right]를 재귀적으로 병합 정렬하고,
//해당 범위 내의 inversion(반전)의 수를 반환한다.
long long countMoves3(vector<int>& A, int left, int right) {
	//기저 사례: 구간의 길이가 1이라면 이미 정렬되었고, inversion도 없다.
	if (left == right) return 0;
	//반으로 나눠서 부분 정복
	int mid = (left + right) / 2;
	long long ret = countMoves3(A, left, mid) +
		countMoves3(A, mid + 1, right);
	//임시 배열에 정렬된 두 부분 배열을 합친다.
	//부분 정복 이후에 A[left..mid]와 A[mid+1, right]는
	//각각 오름차순으로 정렬되어 있다.
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while (leftIndex <= mid || rightIndex <= right) {
		if (leftIndex <= mid &&
			(rightIndex > right || A[leftIndex] <= A[rightIndex]))
			tmp[tmpIndex++] = A[leftIndex++];
		else {
			//A[rightIndex]는 왼쪽 부분 배열에 남아 있는 모든 수보다 작다.
			//이 수들만큼 inversion을 더해준다.
			ret += mid - leftIndex + 1;
			tmp[tmpIndex++] = A[rightIndex++];
		}
	}
	//tmp에 합친 결과를 A로 다시 복사한다.
	for (int i = 0; i < tmp.size(); i++)
		A[left + i] = tmp[i];
	return ret;
}
