#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

//���� Ʈ���� ������ ����

//���� Ʈ���� ����. ������ �迭 A[]�� �κ� ����
//������ ������ �� �ֵ��� �Ѵ�. �ʱ�ȭ�ÿ��� A[]��
//���Ұ� ���� 0�̶�� �����Ѵ�.
struct FenwickTree {
	//tree[i] = ������ �� ��ġ�� A[i]�� ���� ��
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}
	//A[0...pos]�� �κ� ���� ���Ѵ�.
	int sum(int pos) {
		//�ε����� 1���� �����Ѵٰ� ��������
		pos++;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			//���� ������ ã�� ���� ���� ��Ʈ�� �����.
			pos &= (pos - 1);
		}
		return ret;
	}
	//A[pos]�� val�� ���Ѵ�.
	void add(int pos, int val) {
		pos++;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

//���� ���� �ð� ��� ������ ���� Ʈ���� �ذ��ϴ� å�� Ǯ��

//���� Ʈ���� �̿��� ������ �ذ��Ѵ�.
//���� Ʈ������ �� ������ ���� Ƚ���� �����Ѵ�.
long long countMoves(const vector<int> A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); i++) {
		ret += tree.sum(999999) - tree.sum(A[i]);
		tree.add(A[i], 1);
	}
	return ret;
}

//���� ���� �ð� ��� ������ ���� ������ �̿��� �ذ��� å�� Ǯ��

//A[left..right]�� ��������� ���� �����ϰ�,
//�ش� ���� ���� inversion(����)�� ���� ��ȯ�Ѵ�.
long long countMoves3(vector<int>& A, int left, int right) {
	//���� ���: ������ ���̰� 1�̶�� �̹� ���ĵǾ���, inversion�� ����.
	if (left == right) return 0;
	//������ ������ �κ� ����
	int mid = (left + right) / 2;
	long long ret = countMoves3(A, left, mid) +
		countMoves3(A, mid + 1, right);
	//�ӽ� �迭�� ���ĵ� �� �κ� �迭�� ��ģ��.
	//�κ� ���� ���Ŀ� A[left..mid]�� A[mid+1, right]��
	//���� ������������ ���ĵǾ� �ִ�.
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while (leftIndex <= mid || rightIndex <= right) {
		if (leftIndex <= mid &&
			(rightIndex > right || A[leftIndex] <= A[rightIndex]))
			tmp[tmpIndex++] = A[leftIndex++];
		else {
			//A[rightIndex]�� ���� �κ� �迭�� ���� �ִ� ��� ������ �۴�.
			//�� ���鸸ŭ inversion�� �����ش�.
			ret += mid - leftIndex + 1;
			tmp[tmpIndex++] = A[rightIndex++];
		}
	}
	//tmp�� ��ģ ����� A�� �ٽ� �����Ѵ�.
	for (int i = 0; i < tmp.size(); i++)
		A[left + i] = tmp[i];
	return ret;
}
