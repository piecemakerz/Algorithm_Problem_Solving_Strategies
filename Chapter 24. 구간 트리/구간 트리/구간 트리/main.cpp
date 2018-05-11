#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

//�迭�� ���� �ּ� ����(RMQ) ������ �ذ��ϴ� ���� Ʈ���� �ʱ�ȭ
//�迭�� ���� �ּ� ������ �ذ��ϱ� ���� ���� Ʈ���� ����
struct RMQ {
	//�迭�� ����
	int n;
	//�� ������ �ּ�ġ
	vector<int> rangeMin;
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	//node ��尡 array[left..right] �迭�� ǥ���� ��
	//node�� ��Ʈ�� �ϴ� ����Ʈ���� �ʱ�ȭ�ϰ�, �� ������ �ּ�ġ�� ��ȯ�Ѵ�.
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}

	//RMQ ������ Ǫ�� ���� Ʈ������ ���� ������ ����
	//node�� ǥ���ϴ� ���� array[nodeLeft...nodeRight]�� �־��� ��
	//�� ������ array[left...right]�� �������� �ּ�ġ�� ���Ѵ�.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//�� ������ ��ġ�� ������ ���� ū ���� ��ȯ�Ѵ�. (�����ϱ� ����)
		if (right < nodeLeft || nodeRight < left) return INT_MAX;
		//node�� ǥ���ϴ� ������ array[left...right]�� ������ ���ԵǴ� ���
		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];
		//���� ������ ������ Ǭ �� ����� ��ģ��.
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),
			query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	//query()�� �ܺο��� ȣ���ϱ� ���� �������̽�
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	//RMQ ������ Ǫ�� ���� Ʈ������ ���� ������ ����
	//array[index] = newValue�� �ٲ���� �� node�� ��Ʈ�� �ϴ�
	//���� Ʈ���� �����ϰ� ��尡 ǥ���ϴ� ������ �ּ�ġ�� ��ȯ�Ѵ�.
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		//index�� ��尡 ǥ���ϴ� ������ ������� ��쿣 �����Ѵ�.
		if (index < nodeLeft || nodeRight < index)
			return rangeMin[node];
		//Ʈ���� �������� ������ ���
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(
			update(index, newValue, node * 2, nodeLeft, mid),
			update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()�� �ܺο��� ȣ���ϱ� ���� �������̽�
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};

//������ �ִ� ���� Ƚ�� ������ �� ���� ���� ��ġ��
struct RangeResult {
	//�� ������ ũ��
	int size;
	//���� ���� �����ϴ� ������ ���� Ƚ��
	int mostFrequent;
	//���� �� ���ڿ� ���� �� ������ ���� Ƚ��
	int leftNumber, leftFreq;
	//������ �� ���ڿ� ������ �� ������ ���� Ƚ��
	int rightNumber, rightFreq;
};
//���� �κ� ������ ��� ��� a, ������ �κ� ������ ��� ��� b�� ��ģ��.
RangeResult merge(const RangeResult& a, const RangeResult& b) {
	RangeResult ret;
	//������ ũ��� ���� ��� ����
	ret.size = a.size + b.size;
	//���� ���ڴ� a,leftNumber�� ������ �ִ�.
	//���� �κ� ������ ���� a.leftNumber�� ��츸 ������ ó��
	//��: [1,1,1,1]�� [1,2,2,2]�� ��ĥ ��
	ret.leftNumber = a.leftNumber;
	ret.leftFreq = a.leftFreq;
	if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
		ret.leftFreq += b.leftFreq;
	//������ �� ���ڵ� ����ϰ� �������.
	ret.rightNumber = b.rightNumber;
	ret.rightFreq = b.rightFreq;
	if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
		ret.rightFreq += a.rightFreq;
	//�⺻������ ���� ���� �����ϴ� ���� �󵵼��� �� �� ū ������
	ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);
	//���� ������ ������ �� ���ڿ� ������ ������ ���� �� ���ڰ� �������� ���
	//�� �� ���� ������ �� mostFrequent���� Ŀ������ Ȯ���Ѵ�.
	if (a.rightNumber == b.leftNumber)
		ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);
	return ret;
}