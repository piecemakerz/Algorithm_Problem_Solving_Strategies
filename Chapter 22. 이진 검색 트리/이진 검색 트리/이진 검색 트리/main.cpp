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
	int data;
	Node * left;
	Node * right;
	Node * parent;
	Node(int data) : data(data) {
		left = NULL, right = NULL, parent = NULL;
	}
} Node;

//����� �˻�. �˻��� ������ ��� NULL�� ��ȯ�Ѵ�.
Node* searchNode(Node* node, int data) {
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

//����� ����
void insertNode(Node*& Tree, int data) {
	Node * curNode = Tree;
	Node * prevNode = NULL;
	Node * newNode = new Node(data);

	while (curNode != NULL) {
		prevNode = curNode;
		if (data < curNode->data)
			curNode = curNode->left;
		else curNode = curNode->right;
	}
	newNode->parent = prevNode;

	if (prevNode == NULL)
		Tree = newNode; // Tree�� �� Ʈ���̴�.
	else if (data < prevNode->data)
		prevNode->left = newNode;
	else
		prevNode->right = newNode;
}

//�� Ʈ�� ��ġ��. LTree�� ��Ʈ ��带 ��ģ Ʈ���� ��Ʈ�� ������ ��.
//RTree�� LTree�� ������ ����Ʈ���� ��������� ���� LTree�� ���ο�
//������ Ʈ���� �Ѵ�.
Node* combineTree(Node * LTree, Node * RTree) {
	Node * newRoot = LTree;
	if (newRoot == NULL)
		return RTree;
	else if (RTree == NULL)
		return newRoot;

	newRoot->right = combineTree(newRoot->right, RTree);
	//��ģ Ʈ���� ������ �ڽ����� �Ѵ�.
	if (newRoot->right != NULL)
		newRoot->right->parent = newRoot;
	return newRoot;
}

//��� ����
Node* removeNode(Node*& Tree, int data) {
	Node * delNode = searchNode(Tree, data);

	if (delNode == NULL) {
		cout << ("�ش��ϴ� ��带 ã�� �� �����ϴ�.");
		return NULL;
	}
	
	//replaceNode = ������ ����� �ڸ��� ��ġ�� ���
	Node * replaceNode = combineTree(delNode->left, delNode->right);
	replaceNode->parent = delNode->parent;

	if(delNode->parent != NULL) // delNode�� ��Ʈ ��尡 �ƴ϶��
		if (delNode->parent->right == delNode)
			delNode->parent->right = replaceNode;
		else
			delNode->parent->left = replaceNode;
	else { // delNode�� ��Ʈ �����
		Tree = replaceNode;
	}
	delete(delNode);
	return replaceNode;
}

//�ڵ尡 �ſ� ���. �Ʒ��� removeOtherNode()�� ���� �� Ʈ�� �����ڵ��� deleteNode()��
//�����ϴ� ��带 �ٸ� ���� ��ü�ϴ� �۾��� ������ �Լ��� �и��Ͽ�
//�ڵ��� ���̸� �ξ� �ٿ���.
Node * removeNodeOther(Node*& Tree, int data) {
	Node * delNode = searchNode(Tree, data);
	Node * replaceNode = NULL;
	if (delNode == NULL) {
		cout << ("�ش��ϴ� ��带 ã�� �� �����ϴ�.");
		return NULL;
	}

	//������ ��尡 �� ����� ���
	if (delNode->right == NULL && delNode->left == NULL) {
		//������ ��尡 Ʈ���� ������ ����� ���
		if (delNode->parent == NULL)
			Tree = NULL;
		else if (delNode->parent->left == delNode)
			delNode->parent->left = NULL;
		else
			delNode->parent->right = NULL;
	}

	//������ ��尡 �ϳ��� �ڽ��� ���� ���
	else if (delNode->right == NULL) {
		replaceNode = delNode->left;
		replaceNode->parent = delNode->parent;
		if (replaceNode->parent == NULL)
			Tree = replaceNode;
		else if (delNode->parent->right == delNode)
			delNode->parent->right = replaceNode;
		else
			delNode->parent->left = replaceNode;
	}
	else if (delNode->left == NULL) {
		replaceNode = delNode->right;
		replaceNode->parent = delNode->parent;
		if (replaceNode->parent == NULL)
			Tree = replaceNode;
		if (delNode->parent->right == delNode)
			delNode->parent->right = replaceNode;
		else
			delNode->parent->left = replaceNode;
	}
	//������ ��尡 �� ���� �ڽ��� ���� ���
	//1. ������ ��带 ��ü�� ���(replaceNode)�� ã��
	//2. ��ü�� ��忡 ������ ���� ������ ��忡 �����ϰ�
	//3. ��ü�� ����� �θ� ���� �ڽĳ�带 ����(�ּҰ�)�Ѵ�.
	//��ü�� ���� ����Ʈ������ ���� ���� ���̹Ƿ� ���� �ڽ��� �������� �ʴ´�.
	else {
		replaceNode = findSuccessor(delNode);
		delNode->data = replaceNode->data;

		if (replaceNode->parent->left == replaceNode)
			replaceNode->parent->left = replaceNode->right;
		else
			replaceNode->parent->right = replaceNode->right;

		if (replaceNode->right != NULL)
			replaceNode->right->parent = replaceNode->parent;

		delNode = replaceNode;
	}
	delete(delNode);
	return replaceNode;
}

//�� ���� Ʈ���� �ٸ� ���� Ʈ���� ��ü�ϴ� ���� ��ƾ. 
//��� u�� ��Ʈ�� ���� Ʈ���� ��� v�� ��Ʈ�� ���� Ʈ���� ��ü�Ѵ�.
//u�� ��ü Ʈ���� ��Ʈ����� �� ��Ʈ��带 v�� �ٲ��ָ�,
//��� u�� �θ����� ����Ʈ�� �����Ϳ� ��� v�� �θ��带 �������ش�.
//��ü �� ��� u�� ���� �޸� ��ε�, ��� v�� left, right ������ ������
//transplant()�� ȣ������ ���̴�.
void transplant(Node*& Tree, Node * u, Node * v) {
	if (u->parent == NULL)
		Tree = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
}

Node * removeNodeBook(Node * Tree, int data) {
	Node * delNode = searchNode(Tree, data);
	Node * replaceNode = NULL;
	//delNode�� ������ �ڽ� ��常 ���� ��
	if (delNode->left == NULL) {
		transplant(Tree, delNode, delNode->right);
		replaceNode = delNode->right;
	}
	//delNode�� ���� �ڽ� ��常 ���� ��
	else if (delNode->right == NULL) {
		transplant(Tree, delNode, delNode->left);
		replaceNode = delNode->left;
	}
	//delNode�� ���ʰ� ������ �ڽ� ��带 ��� ���� ��
	//delNode�� delNode�� ���ĳ��� ��ü�Ѵ�.
	//���ĳ��� ���� �ڽĳ�带 ������ �ʴ´�.
	else {
		replaceNode = findMinNode(delNode->right);
		//���ĳ�尡 delNode �ٷ� ������ �ڽ��̶�� ��ü �� ���ĳ���� ������ �ڽ���
		//�ٷ� delNode �ڸ��� ������ �ڽ��� �Ǳ� ������ ���ĳ�忡 delNode�� ������ �ڽ���
		//�����ϴ� ������ �����ص� �ȴ�.
		if (replaceNode->parent != delNode) {
			transplant(Tree, replaceNode, replaceNode->right);
			replaceNode->right = delNode->right;
			replaceNode->right->parent = replaceNode;
		}
		transplant(Tree, delNode, replaceNode);
		replaceNode->left = delNode->left;
		replaceNode->left->parent = replaceNode;
	}
	delete(delNode);
	return replaceNode;
}
//������ȸ ���
void printTree(Node* Tree)
{
	if (Tree == NULL) return;
	printTree(Tree->left);
	cout << Tree->data << ' ';
	printTree(Tree->right);
}

int main(void) {
	int data;
	Node * root = NULL;

	while (true) {
		cin >> data;
		if (data == -1)
			break;
		insertNode(root, data);
		printTree(root);
		cout << endl;
	}
	while (true) {
		cin >> data;
		if (data == -1)
			break;
		removeNodeOther(root, data);
		if (root == NULL)
			break;
		printTree(root);
		cout << endl;
	}
	return 0;
}