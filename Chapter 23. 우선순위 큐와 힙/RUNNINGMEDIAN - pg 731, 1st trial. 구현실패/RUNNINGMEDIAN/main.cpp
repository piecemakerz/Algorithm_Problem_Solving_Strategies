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
//Ʈ���� �� ��带 �����Ѵ�.
struct Node {
	//��忡 ����� ����
	KeyType key;
	//�� ����� �켱����(priority)
	//�� ��带 ��Ʈ�� �ϴ� ����Ʈ���� ũ��(size)
	int priority, size;
	//�� �ڽ� ����� ������
	Node *left, *right;
	//�����ڿ��� ���� �켱������ �����ϰ�, size�� left/right�� �ʱ�ȭ�Ѵ�.
	Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
	void setLeft(Node *newLeft) { left = newLeft; calcSize(); }
	void setRight(Node *newRight) { right = newRight; calcSize(); }
	//size ����� �����Ѵ�.
	void calcSize() {
		size = 1;
		if (left) size += left->size;
		if (right) size += right->size;
	}
};

//Ʈ�������� ��� �߰��� Ʈ�� �ɰ��� ������ ����
typedef pair<Node*, Node*> NodePair;
//root�� ��Ʈ�� �ϴ� Ʈ���� key �̸��� ���� �̻��� ���� ����
//�� ���� Ʈ������ �и��Ѵ�.
NodePair split(Node *root, KeyType key) {
	if (root == NULL) return NodePair(NULL, NULL);
	//��Ʈ�� key �̸��̸� ������ ����Ʈ���� �ɰ���.
	//���� ����Ʈ���� �ݵ�� key �̸��� ���� ���´�.
	//rs.first = key �̸��� ���� ���� ����Ʈ��
	//rs.second = key �̻��� ���� ���� ����Ʈ��
	if (root->key < key) {
		NodePair rs = split(root->right, key);
		root->setRight(rs.first);
		return NodePair(root, rs.second);
	}
	//��Ʈ�� key �̻��̸� ���� ����Ʈ���� �ɰ���.
	//������ ����Ʈ���� �ݵ�� key �̻��� ���� ���´�.
	NodePair ls = split(root->left, key);
	root->setLeft(ls.second);
	return NodePair(ls.first, root);
}
//root�� ��Ʈ�� �ϴ� Ʈ���� �� ��� node�� ������ �� ���
//Ʈ���� ��Ʈ�� ��ȯ�Ѵ�.
Node* insert(Node* root, Node* node) {
	if (root == NULL) return node;
	//node�� �켱������ root�� �켱�������� ���ٸ�
	//node�� ��Ʈ�� ��ü�ؾ� �Ѵ�. �ش� ����Ʈ���� ������ �߶�
	//���� �ڼ����� �Ѵ�.
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

//Ʈ������ k��° ���Ҹ� ã�� �˰����� ����
//root�� ��Ʈ�� �ϴ� Ʈ�� �߿��� k��° ���Ҹ� ��ȯ�Ѵ�.
Node* kth(Node* root, int k) {
	//���� ����Ʈ���� ũ�⸦ �켱 ����Ѵ�.
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

//��ȭ�ϴ� �߰� �� ������ Ʈ���� ����� Ǯ��
//rng�� �����ϴ� ù n���� ������ ������ �߰��ϸ� �߰� ���� ���Ѵ�.
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

//���� �̿��� ��ȭ�ϴ� �߰� �� ������ �ذ��ϴ� �Լ��� ����
int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;
	//�ݺ��� �Һ���:
	//1. maxHeap�� ũ��� minHeap�� ũ��� ���ų� 1 �� ũ��.
	//2. maxHeap.top() < minHeap.top()
	for (int cnt = 1; cnt <= n; cnt++) {
		//�켱 1�� �Һ��ĺ��� ������Ų��.
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		//2�� �Һ����� ������ ��� �����Ѵ�.
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