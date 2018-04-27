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

	while (node->parent != NULL && node == node->parent->Right) {
		node = node->parent;
	}
	return node->parent;
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
	if (newRoot->Right != NULL)
		newRoot->Right->parent = newRoot;
	return newRoot;
}

//��� ����
Node* removeNode(Node * Tree, int data) {
	Node * delNode = searchNode(Tree, data);

	if (delNode == NULL) {
		cout << ("�ش��ϴ� ��带 ã�� �� �����ϴ�.");
		return NULL;
	}
	
	Node * replaceNode = combineTree(delNode->Left, delNode->Right);
	replaceNode->parent = delNode->parent;

	if(delNode->parent != NULL) // delNode�� ��Ʈ ��尡 �ƴ϶��
		if (delNode->parent->Right == delNode)
			delNode->parent->Right = replaceNode;
		else
			delNode->parent->Left = replaceNode;

	delete(delNode);
	return replaceNode;
}

Node * removeNodeOther(Node * Tree, int data) {
	Node * delNode = searchNode(Tree, data);
	Node * replaceNode = NULL;
	if (delNode == NULL) {
		cout << ("�ش��ϴ� ��带 ã�� �� �����ϴ�.");
		return NULL;
	}

	//������ ��尡 �� ����� ���
	if (delNode->Right == NULL && delNode->Left == NULL) {
		if (delNode->parent->Left == delNode)
			delNode->parent->Left = NULL;
		else
			delNode->parent->Right = NULL;
	}

	//������ ��尡 �ϳ��� �ڽ��� ���� ���
	if (delNode->Right == NULL) {
		replaceNode = delNode->Left;
		replaceNode->parent = delNode->parent;
	}
	else if (delNode->Left == NULL) {
		replaceNode = delNode->Right;
		replaceNode->parent = delNode->parent;
	}
	//������ ��尡 �� ���� �ڽ��� ���� ���
	//������ ���� Ʈ������ ���� ���� ��(delNode�� ���ĳ��)���� ��ü�Ѵ�.
	//���ĳ��� ���� �ڽ��� �������� �ʴ´�.
	else {
		Node * replaceNode = findSuccessor(delNode);
		if (replaceNode->parent->Left = replaceNode)
			replaceNode->parent->Left = replaceNode->Right;
		else
			replaceNode->parent->Right = replaceNode->Right;

		if (replaceNode->Right != NULL)
			replaceNode->Right->parent = replaceNode->parent;

		replaceNode->parent = delNode->parent;
	}

	if (replaceNode != NULL)
		if (delNode == delNode->parent->Left)
			delNode->parent->Left = replaceNode;
		else
			delNode->parent->Right = replaceNode;
	delete(delNode);
	return replaceNode;
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