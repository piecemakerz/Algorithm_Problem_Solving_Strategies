#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

//�ּ� ���� ���� ������ ���� �ּ� ���� ������ �ٲٱ�

const int MAX_N = 100000;
int n;
vector<int> child[MAX_N];
//Ʈ���� ��ȣ�� �Ϸ� ��ȣ ������ ���� ����
int no2serial[MAX_N], serial2no[MAX_N];
//�� ��尡 trip�� ó�� �����ϴ� ��ġ, �׸��� �� ����� ����
int locInTrip[MAX_N], depth[MAX_N];
//���� �Ϸù�ȣ
int nextSerial;

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

//���̰� d�� ��� here ���ϸ� ���� Ž���Ѵ�.
void traverse(int here, int d, vector<int>& trip) {
	//traverse()�� ó�� �湮���ڸ��� �Ϸ� ��ȣ�� �ο��Ѵ�.
	//�̷��� �ϸ� �׻� �θ�� �ڼպ��� ���� �Ϸ� ��ȣ�� ���� �ȴ�.
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	nextSerial++;
	//���� ���
	depth[here] = d;
	//trip�� ���� ����� �Ϸ� ��ȣ�� �߰��Ѵ�.
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);
	//��� �ڽ� ��带 �湮
	for (int i = 0; i < child[here].size(); i++) {
		traverse(child[here][i], d + 1, trip);
		//�ڽ� ��带 �湮�ϰ� ���� ���� ���ƿ� ������ �ٽ� �߰��ϱ�
		trip.push_back(no2serial[here]);
	}
}
//Ʈ���� ��ȸ�ϸ� ���� �ʿ��� ������ ����ϰ�,
//RMQ ���� Ʈ���� ����� ��ȯ�Ѵ�.
RMQ* prepareRMQ() {
	nextSerial = 0;
	//��ȸ �������� ������ ������ �Ϸ� ��ȣ�� ��´�.
	vector<int> trip;
	traverse(0, 0, trip);
	return new RMQ(trip);
}

//�ּ� ���� ���� ������ �̿��� Ʈ�� �������� ����� ���̸� ���ϱ�

//u�� v ������ �Ÿ��� ����Ѵ�.
int distance(RMQ* rmq, int u, int v) {
	//trip[] �迭���� u�� v�� ù ���� ��ġ�� ã�´�.
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv) swap(lu, lv);
	//rmq�� u�� v�� �ּ� ���� ������ �Ϸù�ȣ�� ��ȯ�Ѵ�.
	int lca = serial2no[rmq->query(lu, lv)];
	return depth[u] + depth[v] - 2 * depth[lca];
}