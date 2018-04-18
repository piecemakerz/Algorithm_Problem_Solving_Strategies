#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N;
typedef struct TreeNode {
public:
	int label;
	bool visited;
	TreeNode* parent, *left, *right;
	TreeNode(int inputLabel) : label(inputLabel) {
		parent = NULL; left = NULL; right = NULL; visited = false;
	};

}Node;

Node* treeRoot; // Ʈ���� ��Ʈ ���

//�� Ǯ��1: ���� ��ȸ�� �Է� ������� ���� Ʈ���� �����, 
//�ϼ��� Ʈ���� �������� ���� ��ȸ�� ����� ��ȯ�Ѵ�.
//�� ������� ������ ���� Ʈ���� ���� ��ȸ�� ���� ���� ��ȸ�� ������ 
//�Է¹��� ������ ��ġ���� �ʴ´�.
/*
void MakeRealTree(vector<int>& labels) {
	treeRoot = new Node(labels[0]); //������ȸ���� ���� ���� �湮�ϴ� ���� Ʈ���� ��Ʈ����̴�.
	for (int i = 1; i < N; i++) {
		Node* curNode = treeRoot; // ��Ʈ��忡������ Ž�� ����

		while (true) {
			if (labels[i] < curNode->label)
				if (curNode->left == NULL) {
					curNode->left = new Node(labels[i]);
					curNode->left->parent = curNode;
					break;
				}
				else {
					curNode = curNode->left;
				}

			else
				if (curNode->right == NULL) {
					curNode->right = new Node(labels[i]);
					curNode->right->parent = curNode;
					break;
				}
				else {
					curNode = curNode->right;
				}
		}
	}
}

vector<int> postorderTraverse() {
	vector<int> visitedOrder; // ���� ��ȸ ����
	Node* curNode = treeRoot; // ��ȸ�� ��Ʈ ��忡������ ����
	while (!treeRoot->visited) {
		//���� ��带 ���� �湮���� �ʾҴٸ�
		if (!curNode->visited) {
			//���� �ڽ� ��尡 �����ϸ� ���� �湮���� �ʾҴٸ�
			if (curNode->left != NULL && !curNode->left->visited)
				curNode = curNode->left;
			//������ �ڽ� ��尡 �����ϸ� ���� �湮���� �ʾҴٸ�
			else if (curNode->right != NULL && !curNode->right->visited)
				curNode = curNode->right;
			//����&������ �ڽ� ������ ��� Ȯ���ߴٸ�
			else {
				curNode->visited = true;
				visitedOrder.push_back(curNode->label);
				curNode = curNode->parent;
			}
		}
	}
	return visitedOrder;
}
*/

//�� Ǯ��2: �Է¹��� ���� ��ȸ�� �������� ���� ���� Ʈ���� ������ ��
//���� ��ȸ�� ������ų �� �ֵ��� Ʈ���� �����Ѵ�.
//���� 1. ���� ������ȸ���� ����� ���� �ڽĳ�尡 �����ϰ� ���� �湮���� �ʾҴٸ�
//�̸� ������ �ڽĳ��� �ű��.
//���� 2. ���� ������ȸ���� ����� ���� �ڽĳ�尡 �����ϰ� �̵��� �湮�Ǿ��ٸ� 
//������ �湮�� ����� ������ �ڽĳ�带 �� ����� ������ �ڽĳ��� �ű��.
//���� 3. ���� 1�� 2�� ��� �������� �ʴ´ٸ� ��ġ�� �������� �ʴ´�.

Node* nodePos[1001]; // i�� ���� ������ �ִ� ����� ��ġ

//���� ��ȸ�� �������� ���� ���� ����Ʈ�� ����
void MakePreorderTree(const vector<int>& labels) {
	treeRoot = new Node(labels[0]);
	treeRoot->parent = treeRoot;
	nodePos[labels[0]] = treeRoot;
	Node* curPos = treeRoot;

	for (int i = 1; i < N; i++) {
		Node * child = new Node(labels[i]);
		nodePos[labels[i]] = child;
		curPos->left = child;
		child->parent = curPos;
		curPos = child;
	}
}

//���� ��ȸ�� ������ų �� �ִ� ����Ʈ�� ����
void MakeInorderTree(const vector<int>& labels) {
	Node * curNode;
	for (int i = 0; i < N; i++) {
		curNode = nodePos[labels[i]];
		if (curNode->left != NULL) {
			if (!curNode->left->visited) {
				curNode->right = curNode->left;
				curNode->left = NULL;
			}
			else {
				curNode->right = nodePos[labels[i - 1]]->right;
				if(curNode->right != NULL)
					curNode->right->parent = curNode;
				nodePos[labels[i - 1]]->right = NULL;
			}
		}
		curNode->visited = true;
	}
	//�� ����� visited���� false�� �ʱ�ȭ
	for (int i = 0; i < N; i++) {
		nodePos[labels[i]]->visited = false;
	}
}

//�ϼ��� ����Ʈ���� �������� ���� ��ȸ
vector<int> postorderTraverse() {
	Node* curNode = treeRoot;
	vector<int> labels;
	while (!treeRoot->visited) {
		if (curNode->left != NULL && !curNode->left->visited)
			curNode = curNode->left;
		else if (curNode->right != NULL && !curNode->right->visited)
			curNode = curNode->right;
		else {
			curNode->visited = true;
			labels.push_back(curNode->label);
			curNode = curNode->parent;
		}
	}
	return labels;
}

//å�� ��
//Ʈ�� ��ȸ ���� ���� ������ �ذ��ϴ� ��� ȣ�� �ڵ�
vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}
//Ʈ���� ����Ž�� ����� ����Ž�� ����� �־��� �� ����Ž�� ����� ����Ѵ�.
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
	//Ʈ���� ���Ե� ��� ��
	const int N = preorder.size();
	//���� ���: �� �� Ʈ���� ���� ����
	if (preorder.empty()) return;
	//�� Ʈ���� ��Ʈ�� ���� Ž�� ����κ��� ���� �� �� �ִ�.
	const int root = preorder[0];
	//�� Ʈ���� ���� ����Ʈ���� ũ��� ���� Ž�� ������� ��Ʈ�� ��ġ�� ã�Ƽ� �� �� �ִ�.
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
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
	for (int testCase = 0; testCase < C; testCase++) {
		memset(nodePos, NULL, sizeof(nodePos));
		cin >> N;
		int inputLabel;

		vector<int> preorderTraverse; // ���� ��ȸ ����
		for (int i = 0; i < N; i++) {
			cin >> inputLabel;
			preorderTraverse.push_back(inputLabel);
		}
		MakePreorderTree(preorderTraverse); // ���� ��ȸ�� �����ϴ� ���� ���� Ʈ�� ����

		vector<int> inorderTraverse; // ���� ��ȸ ����
		for (int i = 0; i < N; i++) {
			cin >> inputLabel;
			inorderTraverse.push_back(inputLabel);
		}
		MakeInorderTree(inorderTraverse); // ���� ��ȸ�� �����ϴ� Ʈ�� ����
		
		vector<int> postorderLabel;
		postorderLabel = postorderTraverse(); // ���� ��ȸ ���� ����
		for (int i = 0; i < N; i++) {
			cout << postorderLabel[i] << ' ';
		}
		cout << endl;

		for (int i = 0; i < N; i++) {
			delete nodePos[preorderTraverse[i]];
		}
	}
	return 0;
}