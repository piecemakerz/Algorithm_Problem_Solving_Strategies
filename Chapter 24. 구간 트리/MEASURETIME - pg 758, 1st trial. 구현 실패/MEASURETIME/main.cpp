#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int C, N;
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

//삽입 정렬 시간 재기 문제를 펜윅 트리로 해결하기
//숫자를 옮기는 총 횟수 리턴
long long countMoves(const vector<int>& A) {
	//각 숫자의 출현 횟수를 저장하는 펜윅 트리
	//처음 생성한 펜윅 트리는 배열 값이 모두 0으로 초기화된다.
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); i++) {
		//현재 tree에는 A[0...i-1] 구간의 수에 대한 출현 횟수만 저장되어 있다.
		//따라서 tree.sum(999999)는 A[0...i-1] 구간의 모든 수의 출현 횟수를 뜻한다.
		//tree.sum(A[i])는 0~A[i] 사이의 값을 가지는 수의 출현 횟수를 뜻하므로,
		//tree.sum(999999)-tree.sum(A[i])는 A[0...i-1]구간에서 A[i]보다 큰 수의
		//출현 횟수를 나타낸다.
		ret += tree.sum(999999) - tree.sum(A[i]);
		//펜윅 트리에서 A[i]의 출현 횟수를 1 증가시킨다.
		tree.add(A[i], 1);
	}
	return ret;
}

//삽입 정렬 시간 재기 문제를 트립으로 해결하기

typedef int KeyType;
//트립의 한 노드를 저장한다.
struct Node {
	//노드에 저장된 원소
	KeyType key;
	//이 노드의 우선순위(priority)
	//이 노드를 루트로 하는 서브트리의 크기(size)
	int priority, size;
	//두 자식 노드의 포인터
	Node *left, *right;
	//생성자에서 난수 우선순위를 생성하고, size와 left/right를 초기화한다.
	Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
	void setLeft(Node *newLeft) { left = newLeft; calcSize(); }
	void setRight(Node *newRight) { right = newRight; calcSize(); }
	//size 멤버를 갱신한다.
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};
//트립에서 X보다 작은 원소의 수를 찾는 알고리즘의 구현
//key보다 작은 키값의 수를 반환한다.
int countLessThan(Node *root, KeyType key) {
	if (root == NULL) return 0;
	if (root->key >= key)
		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}
//트립에서의 노드 추가와 트립 쪼개기 연산의 구현
typedef pair<Node*, Node*> NodePair;
//root를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는
//두 개의 트립으로 분리한다.
NodePair split(Node *root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);
	//루트가 key 미만이면 오른쪽 서브트리를 쪼갠다.
	//왼쪽 서브트리는 반드시 key 미만의 값을 갖는다.
	//rs.first = key 미만의 값을 갖는 서브트리
	//rs.second = key 이상의 값을 갖는 서브트리
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	//루트가 key 이상이면 왼쪽 서브트리를 쪼갠다.
	//오른쪽 서브트리는 반드시 key 이상의 값을 갖는다.
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}
//root를 루트로 하는 트립에 새 노드 node를 삽인한 뒤 결과
//트립의 루트를 반환한다.
Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;
	//node의 우선순위가 root의 우선순위보다 높다면
	//node가 루트를 대체해야 한다. 해당 서브트리를 반으로 잘라
	//각각 자손으로 한다.
	if (root->priority < node->priority) {
		NodePair splitted = split(root, node->key);
		node->setLeft(splitted.first);
		node->setRight(splitted.second);
		return node;
	}
	else if (node->key < root->key)
		root->setLeft(insert(root->left, node));
	else
		root->setRight(insert(root->right, node));
	return root;
}
//만들었던 트리를 지운다.
void deleteTree(Node * node) {
	if (node == NULL) return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}
//트립을 이용해 문제를 해결한다.
long long countMoves2(const vector<int>& A) {
	Node * root = NULL;
	long long ret = 0;
	for (int i = 0; i < A.size(); i++) {
		ret += i - countLessThan(root, A[i] + 1);
		root = insert(root, new Node(A[i]));
	}
	deleteTree(root);
	return ret;
}

//삽입 정렬 시간 재기 문제를 병합 정렬을 이용해 풀기

//A[left...right]를 재귀적으로 병합 정렬하고,
//해당 범위 내의 inversion(반전)의 수를 반환한다.
long long countMoves3(vector<int>& A, int left, int right) {
	//기저 사례: 구간의 길이가 1이라면 이미 정렬되었고, inversion도 없다.
	if (left == right) return 0;
	//반으로 나눠서 부분 정복
	int mid = (left + right) / 2;
	long long ret = countMoves3(A, left, mid) + countMoves3(A, mid + 1, right);
	//임시 배열에 정렬된 두 부분 배열을 합친다.
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while (leftIndex <= mid || rightIndex <= right) {
		if (leftIndex <= mid && (rightIndex > right || A[leftIndex] <= A[rightIndex])) {
			tmp[tmpIndex++] = A[leftIndex++];
		}
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

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		int input;
		scanf("%d", &N);
		vector<int> inputnum(N);
		for (int i = 0; i < N; i++)
			scanf("%d", &inputnum[i]);
		printf("%lld\n", countMoves(inputnum));
	}
}