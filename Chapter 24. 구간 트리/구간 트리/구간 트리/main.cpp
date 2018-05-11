#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

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

//숫자의 최대 출현 횟수 문제의 두 개의 답을 합치기
struct RangeResult {
	//이 구간의 크기
	int size;
	//가장 자주 등장하는 숫자의 출현 횟수
	int mostFrequent;
	//왼쪽 끝 숫자와 왼쪽 끝 숫자의 출현 횟수
	int leftNumber, leftFreq;
	//오른쪽 끝 숫자와 오른쪽 끝 숫자의 출현 횟수
	int rightNumber, rightFreq;
};
//왼쪽 부분 구간의 계산 결과 a, 오른족 부분 구간의 계산 결과 b를 합친다.
RangeResult merge(const RangeResult& a, const RangeResult& b) {
	RangeResult ret;
	//구간의 크기는 쉽게 계산 가능
	ret.size = a.size + b.size;
	//왼쪽 숫자는 a,leftNumber로 정해져 있다.
	//왼쪽 부분 구간이 전부 a.leftNumber인 경우만 별도로 처리
	//예: [1,1,1,1]과 [1,2,2,2]를 합칠 때
	ret.leftNumber = a.leftNumber;
	ret.leftFreq = a.leftFreq;
	if (a.size == a.leftFreq && a.leftNumber == b.leftNumber)
		ret.leftFreq += b.leftFreq;
	//오른쪽 끝 숫자도 비슷하게 계산하자.
	ret.rightNumber = b.rightNumber;
	ret.rightFreq = b.rightFreq;
	if (b.size == b.rightFreq && a.rightNumber == b.rightNumber)
		ret.rightFreq += a.rightFreq;
	//기본적으로 가장 많이 출현하는 수의 빈도수는 둘 중 큰 쪽으로
	ret.mostFrequent = max(a.mostFrequent, b.mostFrequent);
	//왼쪽 구간의 오른쪽 끝 숫자와 오른쪽 구간의 왼쪽 끝 숫자가 합쳐지는 경우
	//이 두 수를 합쳤을 때 mostFrequent보다 커지는지 확인한다.
	if (a.rightNumber == b.leftNumber)
		ret.mostFrequent = max(ret.mostFrequent, a.rightFreq + b.leftFreq);
	return ret;
}