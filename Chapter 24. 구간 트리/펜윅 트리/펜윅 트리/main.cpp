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
