#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

//N = 표지판의 수, Q = 등산로의 수
int C, N, Q;

struct RMQ {
	//배열의 길이
	int n;
	//각 구간의 최소치
	vector<int> rangeMin;
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || nodeRight < left) return INT_MAX;
		if (left <= nodeLeft && nodeRight <= right) return rangeMin[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),
			query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
};

//책의 풀이에 의하면 이 구조체는 필요하지 않다.
struct RMaxQ {
	int n;
	vector<int> rangeMax;
	RMaxQ(const vector<int>& array) {
		n = array.size();
		rangeMax.resize(n * 4);
		init(array, 0, n - 1, 1);
	}

	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMax[node] = array[left];
		int mid = (left + right) / 2;
		int leftMax = init(array, left, mid, node * 2);
		int rightMax = init(array, mid + 1, right, node * 2 + 1);
		return rangeMax[node] = max(leftMax, rightMax);
	}

	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		if (right < nodeLeft || nodeRight < left) return INT_MIN;
		if (left <= nodeLeft && nodeRight <= right)
			return rangeMax[node];
		int mid = (nodeLeft + nodeRight) / 2;
		return max(query(left, right, node * 2, nodeLeft, mid),
			query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}
};

int main(void) {
	scanf("%d", &C);
	for (int testCase = 0; testCase < C; testCase++) {
		scanf("%d %d", &N, &Q);
		vector<int> signHeights(N);
		for (int i = 0; i < N; i++)
			scanf("%d", &signHeights[i]);
		RMQ rmq(signHeights);
		for (int i = 0; i < N; i++)
			signHeights[i] = -signHeights[i];
		//RMaxQ rmaxq(signHeights);
		RMQ rmaxq(signHeights);
		int a, b;
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &a, &b);
			printf("%d\n", (-rmaxq.query(a, b)) - rmq.query(a, b));
		}
	}
}
