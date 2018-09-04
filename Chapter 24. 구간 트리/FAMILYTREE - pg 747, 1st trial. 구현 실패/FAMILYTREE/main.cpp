#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

//최소 공통 조상 문제를 구간 최소 질의 문제로 바꾸기

const int MAX_N = 100000;
int n;
vector<int> child[MAX_N];
//트리의 번호와 일련 번호 사이의 대응 관계
int no2serial[MAX_N], serial2no[MAX_N];
//각 노드가 trip에 처음 등장하는 위치, 그리고 각 노드의 깊이
int locInTrip[MAX_N], depth[MAX_N];
//다음 일련번호
int nextSerial;

//배열의 구간 최소 쿼리(RMQ) 문제를 해결하는 구간 트리의 초기화
//배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
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

	//node 노드가 array[left..right] 배열을 표현할 떄
	//node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다.
	int init(const vector<int>& array, int left, int right, int node) {
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}

	//RMQ 문제를 푸는 구간 트리에서 질의 연산의 구현
	//node가 표현하는 범위 array[nodeLeft...nodeRight]가 주어질 때
	//이 범위와 array[left...right]의 교집합의 최소치를 구한다.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		//두 구간이 겹치지 않으면 아주 큰 값을 반환한다. (무시하기 위함)
		if (right < nodeLeft || nodeRight < left) return INT_MAX;
		//node가 표현하는 범위가 array[left...right]에 완전히 포함되는 경우
		if (left <= nodeLeft && nodeRight <= right)
			return rangeMin[node];
		//양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),
			query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}
	//query()를 외부에서 호출하기 위한 인터페이스
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	//RMQ 문제를 푸는 구간 트리에서 갱신 연산의 구현
	//array[index] = newValue로 바뀌었을 때 node를 루트로 하는
	//구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		//index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
		if (index < nodeLeft || nodeRight < index)
			return rangeMin[node];
		//트리의 리프까지 내려온 경우
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(
			update(index, newValue, node * 2, nodeLeft, mid),
			update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}
	//update()를 외부에서 호출하기 위한 인터페이스
	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};

//깊이가 d인 노드 here 이하를 전위 탐색한다.
void traverse(int here, int d, vector<int>& trip) {
	//traverse()가 처음 방문하자마자 일련 번호를 부여한다.
	//이렇게 하면 항상 부모는 자손보다 작은 일련 번호를 갖게 된다.
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	nextSerial++;
	//깊이 계산
	depth[here] = d;
	//trip에 현재 노드의 일련 번호를 추가한다.
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);
	//모든 자식 노드를 방문
	for (int i = 0; i < child[here].size(); i++) {
		traverse(child[here][i], d + 1, trip);
		//자식 노드를 방문하고 현재 노드로 돌아올 때마다 다시 추가하기
		trip.push_back(no2serial[here]);
	}
}
//트리를 순회하며 각종 필요한 정보를 계산하고,
//RMQ 구간 트리를 만들어 반환한다.
RMQ* prepareRMQ() {
	nextSerial = 0;
	//순회 과정에서 만나는 노드들의 일련 번호를 담는다.
	vector<int> trip;
	traverse(0, 0, trip);
	return new RMQ(trip);
}

//최소 공통 조상 문제를 이용해 트리 위에서의 경로의 길이를 구하기

//u와 v 사이의 거리를 계산한다.
int distance(RMQ* rmq, int u, int v) {
	//trip[] 배열에서 u와 v의 첫 출현 위치를 찾는다.
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv) swap(lu, lv);
	//rmq는 u와 v의 최소 공통 조상의 일련번호를 반환한다.
	int lca = serial2no[rmq->query(lu, lv)];
	return depth[u] + depth[v] - 2 * depth[lca];
}