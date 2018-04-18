#include <iostream>
#include <vector>

using namespace std;

//���� �˻� Ʈ���� ������ ��� �˻�/����/������ ����
//��� ������ �� ���� ������� �����ߴµ�,
//removeNode()�� pg 700�� '��ġ��' ����� ����� ����������,
//removeNodeOther()�� https://blog.naver.com/wpdls6012/220282739841 �� ����� ����� ����������,
//������ ����� ������ �κ� Ʈ������ ���� ���� ���� ���� ��带 ������ ����� ��ġ�� �Ű��.
typedef struct Node {
	int Data;
	Node * Left;
	Node * Right;
	Node(int data) : Data(data) {
		Left = NULL, Right = NULL;
	}
} Node;

//����� �˻�
Node* searchNode(Node* Tree, int data) {
	if (Tree == NULL) return NULL;
	if (Tree->Data == data)
		return Tree;

	else if (Tree->Data > data)
		return searchNode(Tree->Left, data);

	else return searchNode(Tree->Right, data);
}

//����� ����
void insertNode(Node * Tree, Node* newNode) {
	if (newNode->Data > Tree->Data) {
		if (Tree->Right != NULL) insertNode(Tree->Right, newNode);
		else Tree->Right = newNode;
	}
	else {
		if (Tree->Left != NULL) insertNode(Tree->Left, newNode);
		else Tree->Left = newNode;
	}
}

//�ּڰ� ��� ��ȯ
Node* findMinNode(Node * Tree) {
	if (Tree == NULL) return NULL;
	if (Tree->Left != NULL) return findMinNode(Tree->Left);
	else return Tree;
}

//�ִ� ��� ��ȯ
Node* findMaxNode(Node * Tree) {
	if (Tree == NULL) return NULL;
	if (Tree->Right != NULL) return findMaxNode(Tree->Right);
	else return Tree;
}

//�� Ʈ�� ��ġ��
Node* combineTree(Node * LTree, Node * RTree) {
	Node * newRoot = LTree;
	if (newRoot == NULL)
		return RTree;

	newRoot->Right = combineTree(newRoot->Right, RTree);
	return newRoot;
}

//��� ����
Node* removeNode(Node * Tree, int data) {
	bool wasLeftTree;
	Node * delNode = Tree;
	Node * prevNode;
	while (!(delNode == NULL || delNode->Data == data)) {
		prevNode = delNode;
		if (delNode->Data < data)
			delNode = delNode->Right;
		else
			delNode = delNode->Left;
	}

	if (delNode == NULL) {
		cout << ("�ش��ϴ� ��带 ã�� �� �����ϴ�.");
		return NULL;
	}
	
	if (prevNode->Left == delNode)
		wasLeftTree = true;
	else
		wasLeftTree = false;

	Node * delNodeLeft = delNode->Left, * delNodeRight = delNode->Right;
	delete(delNode);
	delNode = combineTree(delNodeLeft, delNodeRight);
	if (wasLeftTree)
		prevNode->Left = delNode;
	else
		prevNode->Right = delNode;

	return delNode;
}

Node * removeNodeOther(Node * Tree, int data) {
	bool wasLeftTree;
	Node * delNode = Tree;
	Node * prevNode;
	while (!(delNode == NULL || delNode->Data == data)) {
		prevNode = delNode;
		if (delNode->Data < data)
			delNode = delNode->Right;
		else
			delNode = delNode->Left;
	}

	if (delNode == NULL) {
		cout << ("�ش��ϴ� ��带 ã�� �� �����ϴ�.");
		return NULL;
	}

	if (prevNode->Left == delNode)
		wasLeftTree = true;
	else
		wasLeftTree = false;

	//������ ��尡 �� ����� ���
	if (delNode->Right == NULL && delNode->Left == NULL) {
		delete(delNode);
		if (wasLeftTree)
			prevNode->Left = NULL;
		else
			prevNode->Right = NULL;
	}

	//������ ��尡 �ϳ��� �ڽ��� ���� ���
	if (delNode->Right == NULL) {
		delNode->Data = delNode->Left->Data;
		delete(delNode->Left);
		delNode->Left = NULL;
	}
	else if (delNode->Left == NULL) {
		delNode->Data = delNode->Right->Data;
		delete(delNode->Right);
		delNode->Right = NULL;
	}

	//������ ��尡 �� ���� �ڽ��� ���� ���
	//������ ���� Ʈ������ ���� ���� ������ ��ü�Ѵ�.
	else {
		Node * delNodeRight = delNode->Right;
		Node * minNode = delNodeRight;
		Node * minPrevNode = NULL;
		while (minNode->Left != NULL) {
			minPrevNode = minNode;
			minNode = minNode->Left;
		}
		delNode->Data = minNode->Data;

		if (minNode == delNodeRight)
			delNode->Right = NULL;

		if(minPrevNode != NULL)
			minPrevNode->Left = NULL;
	}
	return delNode;
}
//������ȸ ���
void printTree(Node* Tree)
{
	if (Tree == NULL) return;
	printTree(Tree->Left);
	cout << Tree->Data << ' ';
	printTree(Tree->Right);
}

int main(void) {
	int N;
	cin >> N;

	int data;
	cin >> data;
	Node * root = new Node(data);
	for (int i = 0; i < N-1; i++) {
		cin >> data;
		insertNode(root, new Node(data));
	}
	printTree(root);
	cout << endl;
	removeNodeOther(root, 72);
	printTree(root);
	cout << endl;
	return 0;
}