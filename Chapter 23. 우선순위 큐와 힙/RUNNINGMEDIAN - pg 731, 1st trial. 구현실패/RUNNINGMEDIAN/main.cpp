#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

int C, N, a, b;
vector<int> heap;
const int DIV = 20090711;

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

//트립에서 k번째 원소를 찾는 알고리즘의 구현
//root를 루트로 하는 트리 중에서 k번째 원소를 반환한다.
Node* kth(Node* root, int k) {
	//왼쪽 서브트리의 크기를 우선 계산한다.
	int leftSize = 0;
	if (root->left != NULL) leftSize = root->left->size;
	if (k <= leftSize) return kth(root->left, k);
	if (k == leftSize + 1) return root;
	return kth(root->right, k - leftSize - 1);
}

struct RNG {
	int seed;
	RNG() : seed(1983) {}
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % DIV;
		return ret;
	}
};

//변화하는 중간 값 문제를 트립을 사용해 풀기
//rng가 생성하는 첫 n개의 난수를 수열에 추가하며 중간 값을 구한다.
/*int runningMedian(int n, RNG rng) {
	Node *root = NULL;
	int ret = 0;
	for (int cnt = 1; cnt <= n; cnt++) {
		root = insert(root, new Node(rng.next()));
		int median = kth(root, (cnt + 1) / 2)->key;
		ret = (ret + median) % DIV;
	}
	return ret;
}
*/

//힙을 이용해 변화하는 중간 값 문제를 해결하는 함수의 구현
int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;
	//반복문 불변식:
	//1. maxHeap의 크기는 minHeap의 크기와 같거나 1 더 크다.
	//2. maxHeap.top() < minHeap.top()
	for (int cnt = 1; cnt <= n; cnt++) {
		//우선 1번 불변식부터 만족시킨다.
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		//2번 불변식이 깨졌을 경우 복구한다.
		if (!minHeap.empty() && !maxHeap.empty() &&
			minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop(); minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % DIV;
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> N >> a >> b;

	}
}