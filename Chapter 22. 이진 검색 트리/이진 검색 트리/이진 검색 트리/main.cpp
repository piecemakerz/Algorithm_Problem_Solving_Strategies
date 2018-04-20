#include <iostream>
#include <vector>

using namespace std;

//���� �˻� Ʈ���� ������ ��� �˻�/����/������ ����
//��� ������ �� ���� ������� �����ߴµ�,
//removeNode()�� pg 700�� '��ġ��' ����� ����� ����������,
//removeNodeOther()�� https://blog.naver.com/wpdls6012/220282739841 �� ����� ����� ����������,
//������ ����� ������ �κ� Ʈ������ ���� ���� ���� ���� ��带 ������ ����� ��ġ�� �Ű��.
//removeNodeBook()�� å Introduction to Alglrithms���� �����ϴ� ��� ���� �˰����̸�,
//removeNodeOther()�� ���� ����� �̿��� ��� ������ �����Ѵ�.
typedef struct Node {
	int Data;
	Node * Left;
	Node * Right;
	Node * parent;
	Node(int data) : Data(data) {
		Left = NULL, Right = NULL, parent = NULL;
	}
} Node;

//����� �˻�
Node* searchNode(Node* Tree, int data) {
	if (Tree == NULL || Tree->Data == data) return Tree;

	if (Tree->Data > data)
		return searchNode(Tree->Left, data);

	else return searchNode(Tree->Right, data);
}

//�ּڰ� ��� ��ȯ
Node* findMinNode(Node * Tree) {
	while (Tree->Left != NULL)
		Tree = Tree->Left;
	return Tree;
}

//�ִ� ��� ��ȯ
Node* findMaxNode(Node * Tree) {
	while (Tree->Right != NULL)
		Tree = Tree->Right;
	return Tree;
}

//���ĳ�� ����
Node* findSuccessor(Node* node) {
	if (node->Right != NULL)
		return findMinNode(node->Right);

	Node * prevNode = node->parent;
	while (prevNode != NULL && node == prevNode->Right) {
		node = prevNode;
		prevNode = prevNode->parent;
	}
	return prevNode;
}

//����� ����
void insertNode(Node*& Tree, int data) {
	Node * curNode = Tree;
	Node * prevNode = NULL;
	Node * newNode = new Node(data);

	while (curNode != NULL) {
		prevNode = curNode;
		if (data < curNode->Data)
			curNode = curNode->Left;
		else curNode = curNode->Right;
	}
	newNode->parent = prevNode;

	if (prevNode == NULL)
		Tree = newNode; // Tree�� �� Ʈ���̴�.
	else if (data < prevNode->Data)
		prevNode->Left = newNode;
	else
		prevNode->Right = newNode;
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
	delNode = searchNode(Tree, data);

	if (delNode == NULL) {
		cout << ("�ش��ϴ� ��带 ã�� �� �����ϴ�.");
		return NULL;
	}

	if (delNode->parent->Left == delNode)
		wasLeftTree = true;
	else
		wasLeftTree = false;

	//������ ��尡 �� ����� ���
	if (delNode->Right == NULL && delNode->Left == NULL) {
		delete(delNode);
		if (wasLeftTree)
			delNode->parent->Left = NULL;
		else
			delNode->parent->Right = NULL;
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

//�� ���� Ʈ���� �ٸ� ���� Ʈ���� ��ü�ϴ� ���� ��ƾ. 
//��� u�� ��Ʈ�� ���� Ʈ���� ��� v�� ��Ʈ�� ���� Ʈ���� ��ü�Ѵ�.
//��� u�� �θ����� ����Ʈ�� �����Ϳ� ��� v�� �θ��常 �������ָ�,
//��� u�� ���� �޸� ��ε�, ��� v�� left, right ������ ������
//transplant()�� ȣ������ ���̴�.
void transplant(Node*& Tree, Node * u, Node * v) {
	if (u->parent == NULL)
		Tree = v;
	else if (u == u->parent->Left)
		u->parent->Left = v;
	else
		u->parent->Right = v;
	if (v != NULL)
		v->parent = u->parent;
}

Node * removeNodeBook(Node * Tree, int data) {
	Node * delNode = searchNode(Tree, data);
	Node * replaceNode = NULL;
	//delNode�� ������ �ڽ� ��常 ���� ��
	if (delNode->Left == NULL) {
		transplant(Tree, delNode, delNode->Right);
		replaceNode = delNode->Right;
	}
	//delNode�� ���� �ڽ� ��常 ���� ��
	else if (delNode->Right == NULL) {
		transplant(Tree, delNode, delNode->Left);
		replaceNode = delNode->Left;
	}
	//delNode�� ���ʰ� ������ �ڽ� ��带 ��� ���� ��
	else {
		replaceNode = findMinNode(delNode->Right);
		if (replaceNode->parent != delNode) {
			transplant(Tree, replaceNode, replaceNode->Right);
			replaceNode->Right = delNode->Right;
			replaceNode->Right->parent = replaceNode;
		}
		transplant(Tree, delNode, replaceNode);
		replaceNode->Left = delNode->Left;
		replaceNode->Left->parent = replaceNode;
	}
	delete(delNode);
	return replaceNode;
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
		insertNode(root, data);
	}
	printTree(root);
	cout << endl;
	removeNodeOther(root, 72);
	printTree(root);
	cout << endl;
	return 0;
}