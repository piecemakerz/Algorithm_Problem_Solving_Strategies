//AVL Ʈ���� ������ ��帶�� ���ʰ� ������ �κ� Ʈ���� ���� ���̿� ����
//������ ������, �κ� Ʈ���� ���� ���̰� 1���� ũ�� ���� ����(���� ���� ����)�� ������.
//AVL Ʈ�������� ��尡 ����, ������ �� ȸ���� ���� Ʈ���� �籸���Ͽ�
//���� ���� ������ ������Ų��. ��, ����/���� ����� BF(Balance Factor, 
//���� ����Ʈ�� ���̿��� ������ ����Ʈ�� ���̸� �� ��)�� ���� �� �̻�(���� 2)
//Ȥ�� ����(-2)�� �ٲ� ��带 �������� �� ����Ʈ������ ��ġ�� ȸ���ϴ� ����� ���Ѵ�.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Node {
	int data;
	Node * left;
	Node * right;
	Node * parent;
	int BF;
	int height;
	Node(int data) : data(data) {
		left = NULL, right = NULL, parent = NULL;
		BF = 0, height = 0;
	}
} Node;

Node * root;

//����� �˻�
Node* searchNode(Node * node, int data) {
	if (node == NULL || node->data == data) return node;

	if (node->data > data)
		return searchNode(node->left, data);

	else return searchNode(node->right, data);
}

//�ּڰ� ��� ��ȯ
Node* findMinNode(Node * Tree) {
	while (Tree->left != NULL)
		Tree = Tree->left;
	return Tree;
}

//�ִ� ��� ��ȯ
Node* findMaxNode(Node * Tree) {
	while (Tree->right != NULL)
		Tree = Tree->right;
	return Tree;
}

//node�� �������� ���� ���ο� ��Ʈ ��尡 �� rightChild�� ��ȯ�Ѵ�.
Node * leftRotate(Node * node) {
	Node * rightNode = node->right;
	node->right = rightNode->left;

	if (rightNode->left != NULL)
		rightNode->left->parent = node;

	if (node->parent == NULL)
		root = rightNode;
	else if (node == node->parent->right)
		node->parent->right = rightNode;
	else
		node->parent->left = rightNode;

	rightNode->left = node;
	rightNode->parent = node->parent;
	node->parent = rightNode;
	return rightNode;
}

//node�� ���������� ���� ���ο� ��Ʈ ��尡 �� leftNode�� ��ȯ�Ѵ�.
Node * rightRotate(Node * node) {
	Node * leftNode = node->left;
	node->left = leftNode->right;

	if (leftNode->right != NULL)
		leftNode->right->parent = node;

	if (node->parent == NULL)
		root = leftNode;
	else if (node == node->parent->left)
		node->parent->left = leftNode;
	else
		node->parent->right = leftNode;

	leftNode->right = node;
	leftNode->parent = node->parent;
	node->parent = leftNode;
	return leftNode;
}

//Tree�� ��Ʈ���� �ϴ� ����Ʈ���� ���̸� �ش� ����� ��������� �����Ѵ�.
//Ʈ���� ���̶� ��Ʈ���� ������� ������ ����� �ִ� ���̸� ���Ѵ�.
void updateHeights(Node * Tree) {
	if (Tree == NULL)
		return;

	if (Tree->left != NULL)
		updateHeights(Tree->left);
	if (Tree->right != NULL)
		updateHeights(Tree->right);

	if (Tree->left != NULL && Tree->right != NULL)
		Tree->height = max(Tree->left->height, Tree->right->height) + 1;
	else if (Tree->left != NULL)
		Tree->height = Tree->left->height + 1;
	else if (Tree->right != NULL)
		Tree->height = Tree->right->height + 1;
	//���� ���� ������ ��� ��� �������� ������ ���� ����� �ǹ��̹Ƿ�
	//���̸� �ʱⰪ 0���� �����Ѵ�.
	else
		Tree->height = 0;
}

void updateBalances(Node * Tree) {
	if (Tree == NULL)
		return;

	if (Tree->left != NULL)
		updateBalances(Tree->left);
	if (Tree->right != NULL)
		updateBalances(Tree->right);

	if (Tree->left != NULL && Tree->right != NULL)
		Tree->BF = Tree->left->height - Tree->right->height;
	else if (Tree->left != NULL)
		Tree->BF = Tree->left->height + 1;
	else if (Tree->right != NULL)
		Tree->BF = -(Tree->right->height + 1);
	//���� ����� BF�� 0���� �����Ѵ�.
	else
		Tree->BF = 0;
}

void rebalance(Node * Tree) {
	//���� ����� BF ������ 2 �̻��̸� �ұ���Ʈ���̹Ƿ�
	//���� ��带 �������� ȸ���� �Ѵ�.
	while (Tree != NULL) {
		if (Tree->BF < -1 || Tree->BF > 1) {
			//cout << "needs rebalancing in node " << Tree->data << endl;
			if (Tree->BF > 1) {
				if (Tree->left != NULL && Tree->left->BF < 0) {
					Tree = leftRotate(Tree->left);
					updateHeights(root);
					updateBalances(root);
				}
				Tree = rightRotate(Tree);
				updateHeights(root);
				updateBalances(root);
			}

			else {
				if (Tree->right != NULL && Tree->right->BF > 0) {
					Tree = rightRotate(Tree->right);
					updateHeights(root);
					updateBalances(root);
				}
				Tree = leftRotate(Tree);
				updateHeights(root);
				updateBalances(root);
			}
		}
		Tree = Tree->parent;
	}
}

//����� ���� �� �� ����� ���̿� BF�� �����ϱ� ���� updateHeights()��
//updateBalances()�� ȣ���ϴ� �Ͱ�, Ʈ���� ���������ִ� rebalance()��
//ȣ���� �����ϸ� ���� �˻� Ʈ�������� ���԰� �����ϴ�.
void insertNode(int data) {
	Node * curNode = root;
	Node * prevNode = NULL;
	Node * newNode = new Node(data);

	while (curNode != NULL) {
		prevNode = curNode;
		if (data < curNode->data)
			curNode = curNode->left;
		else
			curNode = curNode->right;
	}
	newNode->parent = prevNode;

	if (prevNode == NULL)
		root = newNode; // Tree�� �� Ʈ���̴�.
	else if (data < prevNode->data)
		prevNode->left = newNode;
	else
		prevNode->right = newNode;

	updateHeights(root);
	updateBalances(root);
	rebalance(newNode);
}

//���ĳ�� ����. ���ĳ�带 ã�� ���� ������ ��尡 �� ����
//�ڽ��� ���� ���ۿ� �����Ƿ� ���ĳ��� �ݵ�� ������ �����
//�Ʒ� ������ �����Ѵ�. ���� ������ ����� ������ �ڽ��� NULL��
//��쿡 ���� ����ó���� ���� �ʾƵ� �ȴ�.
Node* findSuccessor(Node* node) {
	//if (node->right != NULL)
	return findMinNode(node->right);

	/*while (node->parent != NULL && node == node->parent->right) {
	node = node->parent;
	}
	return node->parent;
	*/
}

//�ڵ尡 �ſ� ���. ���� �˻� Ʈ���� removeOtherNode()�� ���� �� Ʈ�� �����ڵ��� deleteNode()��
//�����ϴ� ��带 �ٸ� ���� ��ü�ϴ� �۾��� ������ �Լ��� �и��Ͽ�
//�ڵ��� ���̸� �ξ� �ٿ���.
void removeNode(int data) {
	Node * delNode = searchNode(root, data);
	Node * replaceNode = NULL;
	if (delNode == NULL) {
		cout << ("�ش��ϴ� ��带 ã�� �� �����ϴ�.");
		return;
	}

	//������ ��尡 �� ����� ���
	if (delNode->right == NULL && delNode->left == NULL) {
		//������ ��尡 Ʈ���� ������ ����� ���
		if (delNode->parent == NULL)
			root = NULL;
		else if (delNode->parent->left == delNode)
			delNode->parent->left = NULL;
		else
			delNode->parent->right = NULL;
		replaceNode = delNode->parent;
	}

	//������ ��尡 �ϳ��� �ڽ��� ���� ���
	else if (delNode->right == NULL) {
		replaceNode = delNode->left;
		replaceNode->parent = delNode->parent;
		if (replaceNode->parent == NULL)
			root = replaceNode;
		else if (delNode->parent->right == delNode)
			delNode->parent->right = replaceNode;
		else
			delNode->parent->left = replaceNode;
	}
	else if (delNode->left == NULL) {
		replaceNode = delNode->right;
		replaceNode->parent = delNode->parent;
		if (replaceNode->parent == NULL)
			root = replaceNode;
		else if (delNode->parent->right == delNode)
			delNode->parent->right = replaceNode;
		else
			delNode->parent->left = replaceNode;
	}
	//������ ��尡 �� ���� �ڽ��� ���� ���
	//������ ���� Ʈ������ ���� ���� ��(delNode�� ���ĳ��)���� ��ü�Ѵ�.
	//���ĳ��� ���� �ڽ��� �������� �ʴ´�.
	else {
		replaceNode = findSuccessor(delNode);

		if (replaceNode->parent->left == replaceNode)
			replaceNode->parent->left = replaceNode->right;
		else
			replaceNode->parent->right = replaceNode->right;

		if (replaceNode->right != NULL)
			replaceNode->right->parent = replaceNode->parent;

		replaceNode->parent = delNode->parent;
		if (delNode->parent == NULL) {
			root = replaceNode;
			replaceNode->left = delNode->left;
			replaceNode->right = delNode->right;
			if(replaceNode->left != NULL)
				replaceNode->left->parent = replaceNode;
			if(replaceNode->right != NULL)
				replaceNode->right->parent = replaceNode;
		}
		else if (delNode->parent->right == delNode)
			delNode->parent->right = replaceNode;
		else
			delNode->parent->left = replaceNode;
	}

	delete(delNode);
	if (root != NULL) {
		updateHeights(root);
		updateBalances(root);
		rebalance(replaceNode);
	}
}

//������ȸ ���
void printTree(Node* Tree)
{
	if (Tree == NULL) return;
	//if(Tree->left != NULL)
		//cout << "left child ";
	printTree(Tree->left);
	cout << Tree->data << ' ';
	//if(Tree->right != NULL)
		//cout << "right child ";
	printTree(Tree->right);
}

int main(void) {
	root = NULL;
	cout << "insert data" << endl;
	int data;
	while (true) {
		cin >> data;
		if (data == -1)
			break;
		insertNode(data);
		printTree(root);
		cout << endl;
		cout << "root: " << root->data << endl;
	}
	cout << "delete data" << endl;
	while (true) {
		cin >> data;
		if (data == -1)
			break;
		removeNode(data);
		printTree(root);
		cout << endl;
		if (root == NULL)
			break;
		cout << "root: " << root->data << endl;
	}
	return 0;
}