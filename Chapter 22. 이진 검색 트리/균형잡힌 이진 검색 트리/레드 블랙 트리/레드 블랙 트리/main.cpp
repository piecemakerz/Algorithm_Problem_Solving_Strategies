//���� �� Ʈ���� ���� �˻� Ʈ���μ� �� ���� �� ��Ʈ�� �߰� ��� ������ ������.
//�� ��Ʈ�� ����� ������ ��Ÿ���µ�, �����̳� ����� �� �� �ִ�.
//���� �� Ʈ���� ��Ʈ���� ���������� ��ο� ��Ÿ���� ����� ������ ���������ν�
//��� �� ��� �͵� �ٸ� ��κ��� �� �� �̻� ���� ������ �����ϰ� �Ǵµ�,
//�̷ν� Ʈ���� �ٻ������� ������ �̷� Ʈ���� �ȴ�.

//���� �� Ʈ���� Ư��
//1. ��� ���� �����̰ų� ����̴�.
//2. ��Ʈ�� ����̴�.
//3. ��� ����(nil)�� ����̴�.
//4. ��尡 �����̸� �� ����� �ڽ��� ��� ����̴�. (������� �������� ���� �� �ִ�.)
//5. �� ���κ��� �� ����� �ڼ��� ������ ���� ��ε��� ��� ���� ���� ��� ��带 �����Ѵ�.

#include <iostream>
#include <vector>

using namespace std;

enum Color { RED, BLACK };

typedef struct Node
{
	int data;
	bool color;
	Node *left, *right, *parent;
	Node(int data) : data(data)	{
		left = right = parent = NULL;
	}
}Node;

typedef struct Tree {
	Node * root;
	Node * nil; // ��� ���. ��� ���� ���� �� ��带 ����Ű�� �ȴ�(& ��Ʈ�� �θ�).
	Tree(Node * root) : root(root) {
		nil = new Node(-1);
		nil->color = BLACK;
	}
}Tree;

Tree * T;

//�ּڰ� ��� ��ȯ
Node* findMinNode(Node * Tree) {
	while (Tree->left != T->nil)
		Tree = Tree->left;
	return Tree;
}

//�ִ� ��� ��ȯ
Node* findMaxNode(Node * Tree) {
	while (Tree->right != T->nil)
		Tree = Tree->right;
	return Tree;
}

//x->right != T.nil���� �����Ѵ�.
//x�� �������� ���� ���ο� ��Ʈ ��尡 �� y�� ��ȯ�Ѵ�.
Node * leftRotate(Node * x) {
	Node * y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		y->left->parent = x;
	if (x->parent == T->nil)
		T->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	return y;
}

//����� �˻�
Node* searchNode(Node * node, int data) {
	if (node == T->nil || node->data == data) return node;

	if (node->data > data)
		return searchNode(node->left, data);

	else return searchNode(node->right, data);
}

//x->left != T.nil���� �����Ѵ�.
//x�� ���������� ���� ���ο� ��Ʈ ��尡 �� y�� ��ȯ�Ѵ�.
Node * rightRotate(Node * x) {
	Node * y = x->left;
	x->left = y->right;
	if (y->right != T->nil)
		y->right->parent = x;
	if (x->parent == T->nil)
		T->root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	x->parent = y;
	return y;
}


void insertFixup(Node * node) {
	//���� �����ϴ� ����� ���� �����̴�.
	//���� node�� �θ� ��� ���� �����̶�� ���� �� Ʈ���� ������ �����ϹǷ�
	//Ʈ���� �������� while������ �����ϸ�,
	//while���� �����Ѵٸ� node�� ���θ�� ������ �����ϸ� ����̴�.

	while (node->parent->color == RED) {
		Node * sibling; // ģô
		Node * grandParent = node->parent->parent; // ���θ�

		//node�� �θ� ���θ��� ���� �ڽ��̶��
		if (node->parent == grandParent->left) {
			sibling = grandParent->right;
			//node�� �θ�� node�� ģô�� ��� �����̶�� node�� �θ�� ģô�� ���� ��� ������� �ٲ� ��
			//node�� node�� ���θ��� ��ġ�� �̵���Ų��.
			//���� ���� �� Ʈ���� ������ �������� ���� ���ɼ��� ���� ����
			//node�� ���θ��̹Ƿ� node�� ���θ� ����Ű���� �� �� Ʈ�� �������� �簳�Ѵ�.
			if (sibling->color == RED) {
				node->parent->color = BLACK;
				sibling->color = BLACK;
				grandParent->color = RED;
				node = grandParent;
			}
			//node�� ģô�� ����̶��, �� node�� ���θ�� ģô�� ��� ����̰� node�� �θ� ��� ������ ���
			//ȸ���� ���� ���� �� Ʈ���� Ư���� ������Ű���� �������Ѵ�.
			//�� else���� ��� �� �� ���� �� Ư���� ��� ������Ű�Ƿ�
			//���� while���� �� �̻� ������� �ʴ´�.
			else {
				//node�� ������ �ڽ��� ��� node�� ���� �ڽ����� �ٲٱ� ����
				//node�� �θ� �������� leftRotate�� ȣ���Ѵ�.
				if (node == node->parent->right) {
					node = node->parent;
					leftRotate(node);
				}
				//node�� ���� �ڽ��� ��� �θ�� ���θ��� ���� �ٲ� ��
				//���θ� �������� ������ ȸ���Ѵ�.
				node->parent->color = BLACK;
				grandParent->color = RED;
				rightRotate(grandParent);
			}
		}

		//node�� �θ� ���θ��� ������ �ڽ��̶��
		//node�� �θ� ���θ��� ���� �ڽ��� ���� �ڵ忡��
		//right�� left�� �ٲ� ���� ����.
		else {
			sibling = grandParent->left;
			if (sibling->color == RED) {
				node->parent->color = BLACK;
				sibling->color = BLACK;
				grandParent->color = RED;
				node = grandParent;
			}
			else {
				if (node == node->parent->left) {
					node = node->parent;
					rightRotate(node);
				}
				node->parent->color = BLACK;
				grandParent->color = RED;
				leftRotate(grandParent);
			}
		}
	}

	T->root->color = BLACK;
}

//���� �� Ʈ���� ����
//Ʈ���� ���������ִ� insertFixup()�� ȣ���� �����ϸ�
//���� �˻� Ʈ�������� ���԰� �����ϴ�.
void insert(int data) {
	Node * newNode = new Node(data);
	Node * prevNode = T->nil;
	Node * curNode = T->root;
	while (curNode != T->nil) {
		prevNode = curNode;
		if (data < curNode->data)
			curNode = curNode->left;
		else
			curNode = curNode->right;
	}
	newNode->parent = prevNode;

	if (prevNode == T->nil) // Ʈ���� ������� ���
		T->root = newNode;

	else if (data < prevNode->data)
		prevNode->left = newNode;

	else
		prevNode->right = newNode;

	newNode->left = T->nil;
	newNode->right = T->nil;
	newNode->color = RED;
	insertFixup(newNode);
}

//�� ���� Ʈ���� �ٸ� ���� Ʈ���� ��ü�ϴ� ���� ��ƾ. 
//��� u�� ��Ʈ�� ���� Ʈ���� ��� v�� ��Ʈ�� ���� Ʈ���� ��ü�Ѵ�.
//��� u�� �θ����� ����Ʈ�� �����Ϳ� ��� v�� �θ��常 �������ָ�,
//��� u�� ���� �޸� ��ε�, ��� v�� left, right ������ ������
//rbTransplant()�� ȣ������ ���̴�.
void rbTransplant(Node * u, Node * v) {
	if (u->parent == T->nil)
		T->root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

void deleteFixup(Node * node) {
	while (node != T->root && node->color == BLACK) {
		//sibling = node�� ģô
		Node * sibling;
		//node�� ���� �ڽ��� ���
		if (node == node->parent->left) {
			sibling = node->parent->right;
			//��� 1. sibling�� ������ ��� 
			//���� �� Ʈ���� Ư���� �������� �ʰ�sibling�� ��� ���� ����� ���� 
			//sibling�� node�� �θ� ��� ���� �ٲ� �� �θ� ��带 �������� Ʈ���� �������� ȸ����Ų��.
			//�θ� ����� ���ο� ������ �ڽ��� ���ο� sibling�� �Ǹ�, sibling�� ��� ��尡 �Ǿ����Ƿ�
			//��� 1�� �߻����� �ʴ´�.
			if (sibling->color == RED) {
				sibling->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				sibling = node->parent->right;
			}
			//��� 2. sibling�� ����̰� sibling�� �� �ڽ��� ��� ����� ���
			if (sibling->left->color = BLACK && sibling->right->color == BLACK) {
				sibling->color = RED;
				node = node->parent;
			}
			else {
				//��� 3. sibling�� ���, sibling�� ���� �ڽ��� ����, ������ �ڽ��� ����� ���
				//sibling�� ���� �ڽ��� ���� �ٲ� �� sibling�� �������� Ʈ���� ���������� ȸ����Ű��
				//���ο� sibling�� ������ ������ �ڽ��� ������ ��� ��尡 �ǹǷ� ��� 4�� �����ϰ� �ȴ�.
				if (sibling->right->color == BLACK) {
					sibling->left->color = BLACK;
					sibling->color = RED;
					rightRotate(sibling);
					sibling = node->parent->right;
				}
				//��� 4. sibling�� ����̰� sibling�� ������ �ڽ��� ������ ���
				//����� ������ �ٲٰ� node�� �θ� ��带 �������� Ʈ���� ��ȸ����Ű��
				//��ü Ʈ���� Ư���� ������ų �� �����Ƿ� while ������ �����Ű�� ����
				//node�� Ʈ���� ��Ʈ ���� �����Ѵ�.
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->right->color = BLACK;
				leftRotate(node->parent);
				node = T->root;
			}
		}

		//node�� ������ �ڽ��� ���
		else {

		}
	}
	node->color = BLACK;
}

Node * removeNode(int data) {
	Node * delNode = searchNode(T->root, data);
	if (delNode == T->nil)
		return T->nil;

	//replaceNode�� delNode�� �ϳ� ������ �ڽ��� ���� ������ delNode�� ����Ű��,
	//�� ���� �ڽ��� ���� ��� delNode�� ���Ŀ��Ҹ� ����Ų��.
	Node * replaceNode = delNode;
	int repnodeColor = replaceNode->color;
	//origReplaceNode = replaceNode�� Ʈ�� �󿡼��� ���� ��ġ�� ����Ű�� ���
	Node * origReplaceNode;

	//������ ��尡 ������ �ڽĸ� ������ �ִٸ�
	if (delNode->left == T->nil) {
		origReplaceNode = delNode->right;
		rbTransplant(delNode, delNode->right);
	}
	//������ ��尡 ���� �ڽĸ� ������ �ִٸ�
	else if (delNode->right == T->nil) {
		origReplaceNode = delNode->left;
		rbTransplant(delNode, delNode->left);
	}
	//������ ��尡 �� ���� �ڽ��� ��� ���� ��
	else {
		//replaceNode = delNode�� ���ĳ��
		replaceNode = findMinNode(delNode->right);
		repnodeColor = replaceNode->color;
		origReplaceNode = replaceNode->right;
		if (replaceNode->parent == delNode)
			origReplaceNode->parent = replaceNode;
		else {
			rbTransplant(replaceNode, replaceNode->right);
			replaceNode->right = delNode->right;
			replaceNode->right->parent = replaceNode;
		}
		rbTransplant(delNode, replaceNode);
		replaceNode->left = delNode->left;
		replaceNode->left->parent = replaceNode;
		replaceNode->color = delNode->color;
	}
	//replaceNode�� ����̸� �ϳ� �̻��� ���� �� Ʈ�� Ư���� ���ݵ� �� �ִµ�,
	//�̸� deleteFixup()���� �����Ѵ�.
	//replaceNode�� ����̶�� ���� �� ���� ������ �߻��� �� �ִ�.
	//1. replaceNode�� ��Ʈ ����̰� y�� ���� �ڽ� ��尡 ���ο� ��Ʈ�� �ȴٸ� Ư�� 2�� �����Ѵ�.
	//2. rbTransplant()�� ����� ������ �ٲ����� �����Ƿ�, origReplaceNode�� �����̰� origReplaceNode�� �θ�
	//���� ����� Ư�� 4�� �����Ѵ�.
	//3. replaceNode�� �̵������ν� replaceNode�� ���� �����ϰ� �ִ� ��ο����� ��� ��尡 �ϳ� �ٰ� �ȴ�.
	//���� replaceNode�� ���� ��ġ�� �������� ���� �� Ʈ���� ���������ش�.
	if (repnodeColor == BLACK)
		deleteFixup(origReplaceNode);

	return replaceNode;
}