#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int C, N;
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

//���� ���� �ð� ��� ������ ���� Ʈ���� �ذ��ϱ�
//���ڸ� �ű�� �� Ƚ�� ����
long long countMoves(const vector<int>& A) {
	//�� ������ ���� Ƚ���� �����ϴ� ���� Ʈ��
	//ó�� ������ ���� Ʈ���� �迭 ���� ��� 0���� �ʱ�ȭ�ȴ�.
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); i++) {
		//���� tree���� A[0...i-1] ������ ���� ���� ���� Ƚ���� ����Ǿ� �ִ�.
		//���� tree.sum(999999)�� A[0...i-1] ������ ��� ���� ���� Ƚ���� ���Ѵ�.
		//tree.sum(A[i])�� 0~A[i] ������ ���� ������ ���� ���� Ƚ���� ���ϹǷ�,
		//tree.sum(999999)-tree.sum(A[i])�� A[0...i-1]�������� A[i]���� ū ����
		//���� Ƚ���� ��Ÿ����.
		ret += tree.sum(999999) - tree.sum(A[i]);
		//���� Ʈ������ A[i]�� ���� Ƚ���� 1 ������Ų��.
		tree.add(A[i], 1);
	}
	return ret;
}

//���� ���� �ð� ��� ������ Ʈ������ �ذ��ϱ�

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
//Ʈ������ X���� ���� ������ ���� ã�� �˰����� ����
//key���� ���� Ű���� ���� ��ȯ�Ѵ�.
int countLessThan(Node *root, KeyType key) {
	if (root == NULL) return 0;
	if (root->key >= key)
		return countLessThan(root->left, key);
	int ls = (root->left ? root->left->size : 0);
	return ls + 1 + countLessThan(root->right, key);
}
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
//������� Ʈ���� �����.
void deleteTree(Node * node) {
	if (node == NULL) return;
	deleteTree(node->left);
	deleteTree(node->right);
	delete node;
}
//Ʈ���� �̿��� ������ �ذ��Ѵ�.
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

//���� ���� �ð� ��� ������ ���� ������ �̿��� Ǯ��

//A[left...right]�� ��������� ���� �����ϰ�,
//�ش� ���� ���� inversion(����)�� ���� ��ȯ�Ѵ�.
long long countMoves3(vector<int>& A, int left, int right) {
	//���� ���: ������ ���̰� 1�̶�� �̹� ���ĵǾ���, inversion�� ����.
	if (left == right) return 0;
	//������ ������ �κ� ����
	int mid = (left + right) / 2;
	long long ret = countMoves3(A, left, mid) + countMoves3(A, mid + 1, right);
	//�ӽ� �迭�� ���ĵ� �� �κ� �迭�� ��ģ��.
	vector<int> tmp(right - left + 1);
	int tmpIndex = 0, leftIndex = left, rightIndex = mid + 1;
	while (leftIndex <= mid || rightIndex <= right) {
		if (leftIndex <= mid && (rightIndex > right || A[leftIndex] <= A[rightIndex])) {
			tmp[tmpIndex++] = A[leftIndex++];
		}
		else {
			//A[rightIndex]�� ���� �κ� �迭�� ���� �ִ� ��� ������ �۴�.
			//�� ���鸸ŭ inversion�� �����ش�.
			ret += mid - leftIndex + 1;
			tmp[tmpIndex++] = A[rightIndex++];
		}
	}
	//tmp�� ��ģ ����� A�� �ٽ� �����Ѵ�.
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