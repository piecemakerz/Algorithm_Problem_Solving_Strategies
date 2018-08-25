#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int C, N;

struct Node {
	Node(int val) : val(val) {
		parent = NULL, left = NULL, right = NULL;
	}
	int val;
	Node* parent, *left, *right;
};

//�� Ǯ��. �� Ǯ�̴� �ܼ��� ���� ��ȸ ������ ����� å�� ��� �޸�
//�ϼ��� Ʈ���� ��Ʈ�� ��ȯ�ϱ⵵ �Ѵ�.
Node* solve(queue<int>& preorderLeft, vector<int>& inorderLeft) {
	Node* root = new Node(preorderLeft.front());
	preorderLeft.pop();
	vector<int>::iterator it = find(inorderLeft.begin(), inorderLeft.end(), root->val);
	vector<int> left(inorderLeft.begin(), it), right(it + 1, inorderLeft.end());
	
	if (!left.empty()) {
		root->left = solve(preorderLeft, left);
		root->left->parent = root;
	}
	if (!right.empty()) {
		root->right = solve(preorderLeft, right);
		root->right->parent = root;
	}
	
	cout << root->val << ' ';
	return root;
}

//Ʈ�� ��ȸ ���� ���� ������ �ذ��ϴ� å�� ��� ȣ�� �ڵ�
vector<int>  slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}
//Ʈ���� ����Ž�� ����� ����Ž�� ����� �־��� �� ����Ž�� ����� ����Ѵ�.
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
	//Ʈ���� ���Ե� ����� ��
	const int N = preorder.size();
	//���� ���: �� �� Ʈ���� ���� ����
	if (preorder.empty()) return;
	//�� Ʈ���� ��Ʈ�� ���� Ž�� ����κ��� ���� �� �� �ִ�.
	const int root = preorder[0];
	//�� Ʈ���� ���� ����Ʈ���� ũ��� ���� Ž�� ������� ��Ʈ�� ��ġ�� ã�Ƽ� �� �� �ִ�.
	const int L = find(inorder.begin(), inorder.end(), root)
		- inorder.begin();
	//������ ����Ʈ���� ũ��� N���� ���� ����Ʈ���� ��Ʈ�� ���� �� �� �ִ�.
	const int R = N - 1 - L;
	//���ʰ� ������ ����Ʈ���� ��ȸ ����� ���
	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	//���� ��ȸ�̹Ƿ� ��Ʈ�� ���� �������� ����Ѵ�.
	cout << root << ' ';
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N;
		int input;
		queue<int> preorder;
		vector<int> inorder(N);

		for (int i = 0; i < N; i++) {
			cin >> input;
			preorder.push(input);
		}
		for (int i = 0; i < N; i++)
			cin >> inorder[i];

		Node* root = solve(preorder, inorder);
		cout << endl;
	}
}