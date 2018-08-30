#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int C, N, Q;
struct RMQ {
	int n;
	vector<int> rangeMin, rangeMax;
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		rangeMax.resize(n * 4);
		initMin(array, 0, n - 1, 1);
		initMax(array, 0, n - 1, 1);
	}

	int initMin(const vector<int>& array, int left, int right, int node) {
		if (left == right) return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = initMin(array, left, mid, node * 2);
		int rightMin = initMin(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}

	int initMax(const vector<int>& array, int left, int right, int node) {
		if (left == right) return rangeMax[node] = array[left];
		int mid = (left + right) / 2;
		int leftMax = initMax(array, left, mid, node * 2);
		int rightMax = initMax(array, mid + 1, right, node * 2 + 1);
		return rangeMax[node] = max(leftMax, rightMax);
	}

	int queryMin(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || nodeRight < left) return INT_MAX;
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(queryMin(left, right, node * 2, nodeLeft, mid),
			queryMin(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	int queryMin(int left, int right) {
		return queryMin(left, right, 1, 0, n - 1);
	}
	
	int queryMax(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || nodeRight < left) return INT_MIN;
		if (left <= nodeLeft && nodeRight <= right) return rangeMax[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return max(queryMax(left, right, node * 2, nodeLeft, mid),
			queryMax(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	int queryMax(int left, int right) {
		return queryMax(left, right, 1, 0, n - 1);
	}
};

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		int a, b;
		cin >> N >> Q;
		vector<int> signs(N);
		for (int i = 0; i < N; i++)
			scanf("%d", &signs[i]);

		RMQ * trail = new RMQ(signs);
		for (int i = 0; i < Q; i++) {
			cin >> a >> b;
			cout << trail->queryMax(a, b) - trail->queryMin(a, b) << endl;
		}
		delete trail;
	}
}