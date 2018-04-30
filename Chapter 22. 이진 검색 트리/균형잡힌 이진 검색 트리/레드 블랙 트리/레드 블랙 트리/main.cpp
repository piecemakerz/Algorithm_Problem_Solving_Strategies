//���� �� Ʈ���� ���� �˻� Ʈ���μ� �� ���� �� ��Ʈ�� �߰� ��� ������ ������.
//�� ��Ʈ�� ����� ������ ��Ÿ���µ�, �����̰ų� ���� �� �� �ִ�.
//���� �� Ʈ���� ��Ʈ���� ���������� ��ο� ��Ÿ���� ����� ������ ���������ν�
//��Ʈ ���κ��� ���� �� ��α����� �Ÿ���, ���� ����� ��α����� �Ÿ��� �� �� ���� �׻� �۴�.
//�̴� �ִ� ��ΰ� ��� �� ���θ� �����Ǿ� ���� ��, ���� ��δ� �� ���� ���� ��尡 
//������ ������ ���� �� ���̱� �����̴�. ��� ��ο��� �� ����� ���� �����Ƿ� �����ϴ� ���
//��ο� ���� ���� ����� �Ÿ��� �ִ� ����� �Ÿ��� �ι� �̻��� �� �� ����. 
//��, ����-�� Ʈ���� ���������� �������� �ִ�.

//���� �� Ʈ���� Ư��
//1. ��� ���� ���� Ȥ�� ���̴�.
//2. ��Ʈ ���� ���̴�.
//3. ��� ����(nil)�� ���̴�.
//4. ���� ����� ���� �ڽĳ��� ������ ���̴�. (������ �������� ���� �� �ִ�.)
//5. �� ���κ��� ������忡 �����ϴ� ��� ��ε��� ���� ��带 �����ϸ� ��� ���� ���� ��� ��带 �����Ѵ�.

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
	};
}Node;

typedef struct Tree {
	Node * root;
	Node * nil; // ��� ���. ��� ���� ���� �� ��带 ����Ű�� �ȴ�(& ��Ʈ�� �θ�).
	Tree() {
		nil = new Node(-1);
		nil->color = BLACK;
		root = nil;
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

//node�� Ʈ���� ��Ʈ���� ����. ��Ʈ���� �ݵ�� ������̴�.
void makeNewRoot(Node * node) {
	node->parent = T->nil;
	T->root = node;
	node->color = BLACK;
}

//node->right != T.nil���� �����Ѵ�.
//node�� �������� ���� ���ο� ��Ʈ ��尡 �� rightChild�� ��ȯ�Ѵ�.
Node * leftRotate(Node * node) {
	Node * rightNode = node->right;
	node->right = rightNode->left;

	if (rightNode->left != T->nil)
		rightNode->left->parent = node;

	if (node->parent == T->nil)
		makeNewRoot(rightNode);
	else if (node == node->parent->right)
		node->parent->right = rightNode;
	else
		node->parent->left = rightNode;

	rightNode->left = node;
	rightNode->parent = node->parent;
	node->parent = rightNode;
	return rightNode;
}

//node->left != T.nil���� �����Ѵ�.
//node�� ���������� ���� ���ο� ��Ʈ ��尡 �� leftNode�� ��ȯ�Ѵ�.
Node * rightRotate(Node * node) {
	Node * leftNode = node->left;
	node->left = leftNode->right;

	if(leftNode->right != T->nil)
		leftNode->right->parent = node;

	if (node->parent == T->nil)
		makeNewRoot(leftNode);
	else if (node == node->parent->left)
		node->parent->left = leftNode;
	else
		node->parent->right = leftNode;

	leftNode->right = node;
	leftNode->parent = node->parent;
	node->parent = leftNode;
	return leftNode;
}

//����� �˻�
Node* searchNode(Node * node, int data) {
	if (node == T->nil || node->data == data) return node;

	if (node->data > data)
		return searchNode(node->left, data);

	else return searchNode(node->right, data);
}

Node * findGrandparents(Node * n)
{
	if ((n != T->nil) && (n->parent != T->nil))
		return n->parent->parent;
	else
		return T->nil;
}

//uncle�� sibling�� �θ� ���, �� parent�� �����̴�.
Node * findUncle(Node * n)
{
	Node * g = findGrandparents(n);
	//���θ� �������� �ʴ´ٸ� ���̵� �������� �ʴ´�.
	if (g == T->nil)
		return T->nil;
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void insertFixup(Node * node) {
	//���� �����ϴ� ����� ���� �����̴�.
	//���� node�� �θ� ��� ���� ������ ���� �� Ʈ���� ������ �����ϹǷ�
	//Ʈ���� �������� while������ �����ϸ�,
	//ó�� while���� �����Ѵٸ� node�� ���θ�� ������ �����ϸ� ���̴�.

	while (node->parent->color == RED) {
		Node * parent = node->parent;
		Node * grandParent = findGrandparents(node);// ���θ�
		Node * uncle = findUncle(node); // ����
		bool isRightChild = (node == parent->right);
		//parent�� uncle�� ��� ������ Ư�� 5�� �����ϱ� ����
		//parent�� uncle�� ���� ��� ������ �ٲ� �� grandParent�� ���� ����� �ٲ۴�.
		//�̷ν� node�� �� �θ� ��带 ������ �ȴ�.
		//���� ���� �� Ʈ���� ����(Ư�� 2�� Ư�� 4)�� �������� ���� ���ɼ��� ���� ����
		//grandParent�̹Ƿ� node�� grandParent�� ����Ű���� �� �� Ʈ�� �������� �簳�Ѵ�.
		if (uncle != T->nil && uncle->color == RED) {
			parent->color = BLACK;
			uncle->color = BLACK;
			grandParent->color = RED;
			node = grandParent;
		}
		//uncle�� ���̶��, �� parent�� �����̰� uncle�� grandParent�� ��� ���� ���
		//ȸ���� ���� ���� �� Ʈ���� Ư���� ������Ű���� �������Ѵ�.
		//�� else���� ��� �� �� ���� �� Ʈ���� ���� �� Ʈ���� Ư���� ��� �����ϰ� �ǹǷ�
		//���� while���� �� �̻� ������� �ʴ´�.
		else {
			//node�� parent�� Ʈ���󿡼� �Ϸ��� �ƴ� ��� node�� �������� ȸ���Ͽ� node�� parent�� �Ϸķ� ��ġ�Ѵ�.
			//�̴� ���� �������� ȸ�� ���Ŀ� parent�� ���� �ڽ��� node�� grandParent�� �ǵ��� �ϱ� �����̴�.
			if (node->parent == grandParent->right && !isRightChild) {
				parent = rightRotate(node);
				node = node->right;
				grandParent = findGrandparents(node);
				isRightChild = (node == parent->right);
			}
			else if (node->parent == grandParent->left && isRightChild) {
				parent = leftRotate(node);
				node = node->left;
				grandParent = findGrandparents(node);
				isRightChild = (node == parent->right);
			}
			//parent�� grandParent�� �ڸ��� ��ġ�ϵ��� grandParent�� �������� ȸ���Ѵ�.
			//grandParent�� ������ ���̾���, parent�� ���忴�� ������ �� ����� ���� �ٲٸ� 
			//grandParent�� �ڸ��� ��ġ�� parent�� ������̰� parent�� ���� �ڽ��� grandParent��
			//uncle�� ���� ��尡 �Ǳ� ������ ���� �� Ʈ���� Ư�� 4�� �����ϰ� �ȴ�.
			parent->color = BLACK;
			grandParent->color = RED;
			if (isRightChild)
				leftRotate(grandParent);
			else
				rightRotate(grandParent);
		}
	}
	T->root->color = BLACK;
}

//���� �� Ʈ���� ����
//Ʈ���� ���������ִ� insertFixup()�� ȣ���� �����ϸ�
//���� �˻� Ʈ�������� ���԰� �����ϴ�.
//�����ϴ� ����� �⺻ ���� �����̴�.
void insert(int data) {
	Node * newNode = new Node(data);
	newNode->left = T->nil;
	newNode->right = T->nil;
	newNode->parent = T->nil;
	newNode->color = RED;

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

	if (prevNode == T->nil) { // Ʈ���� ������� ��� newNode�� Ʈ���� ��Ʈ�� �ȴ�.
		makeNewRoot(newNode);
		return;
	}
	else if (data < prevNode->data)
		prevNode->left = newNode;
	else
		prevNode->right = newNode;

	insertFixup(newNode);
}

Node * findSuccessor(Node * node) {
	if (node->right == T->nil)
		return node;
	Node * successor = node->right;
	while (successor->left != T->nil)
		successor = successor->left;
	return successor;
}

Node * findPredecessor(Node * node) {
	if (node->left == T->nil)
		return node;
	Node * predecessor = node->left;
	while (predecessor->right != T->nil)
		predecessor = predecessor->right;
	return predecessor;
}
//��� n1�� ��� n2�� ��ü�Ѵ�. 
void replaceNode(Node * n1, Node * n2) {
	//cout << "replacing Node with" << n1->data<<" and "<<n2->data<<endl;
	if (n2 == T->nil) {
		if (n1 == n1->parent->left)
			n1->parent->left = T->nil;
		else
			n1->parent->right = T->nil;
	}
	else {
		if (n1->parent == T->nil)
			makeNewRoot(n2);
		else if (n1 == n1->parent->left)
			n1->parent->left = n2;
		else n1->parent->right = n2;
	}
	n2->parent = n1->parent;
}

//��� �� node�� ��������� ����ȴ�.
void deleteFixup(Node * node) {
	//node�� ���ο� ��Ʈ����� ��� ��ο��� �ϳ��� �����(delNode)�� �����߰�
	//���ο� ��Ʈ��尡 ������̹Ƿ� Ʈ���� ��� Ư���� �����ȴ�. 

	while (node->parent != T->nil) {
		//cout << "checking node" << node->data << endl;
		Node * parent = node->parent;
		Node * sibling = (node == parent->left) ? parent->right : parent->left;
		bool isRightChild = (node == parent->right);
		bool isRightChild = (node == parent->right);

		//sibling sibling�� ��� �ڽĵ�, �׸��� node, parent�� ��� ������� ���
		//������ sibling�� ������� �ٲٸ� �ȴ�. �̷� ���� parent�� ��Ʈ�� �ϴ� Ʈ����
		//����� ���� �ұ����� �ذ�Ǿ�����, parent�� ������ �ʴ� ���
		//��δ� parent�� ������ ��� ��ο� ���� ���� ��带 �� �� �� ������ �ǹǷ�
		//Ʈ���� Ư�� 5�� �����ϰ� �ȴ�. ���� parent�� ���� �������� �ٽ� �����Ѵ�.
		if (parent->color == BLACK && sibling->color == BLACK &&
			sibling->left->color == BLACK && sibling->right->color == BLACK) {
			sibling->color = RED;
			node = parent;
			continue;
		}
		//sibling�� ������, �� node, parent�� ������̰� sibling�� �������� ���
		//(sibling�� ������ ��� ������� �����ؼ� ���� �� ���� ������ parent�� ������ ������ ����ȴ�.
		//���� node�� ��ġ�� �ִ� ����带 �����Ͽ� �ұ����� �߻������Ƿ� sibling�� �ڽ� ������ �� �������
		//�����̰� �ڽ� ������ �ڽ� ���鵵 ��� �� ����带 �ݵ�� �ϳ� �̻� ������ ���̴�.)
		//node�� �� �������� ���� �θ��带 ������ �ϱ� ���� parent�� �������� ȸ���ϰ� parent�� ���� �����,
		//sibling�� ���� BLACK���� �ٲ۴�. �̴� Ʈ�� �������� ���� ������ ����
		//(sibling->color == BLACK && parent->color == RED)�� ������Ű�� �����̴�.
		else if(sibling->color == RED){
			//cout << "checking node case 2 " << node->data << endl;
			parent->color = RED;
			sibling->color = BLACK;
			if (isRightChild) {
				rightRotate(parent);
				sibling = parent->left;
			}
			else {
				leftRotate(parent);
				sibling = parent->right;
			}
		}

		//sibling�� sibling�� �ڽĵ��� ��� ��������, parent�� �������� ���
		//�ܼ��� sibling�� parent�� ���� �ٲ��ָ� �ȴ�.
		//�̴� node�� ������ ��ο� ���� �� ����� ������ 1�� ��������, ������
		//�����(���ĳ��)�� ������ �������ش�. ���� ����� Ʈ���� ��� Ư���� �����ϹǷ�
		//�ݺ��� �ߴ��Ѵ�.
		if (sibling->color == BLACK && sibling->right->color == BLACK && 
			sibling->left->color == BLACK && parent->color == RED) {
			//cout << "checking node case 3 " << node->data << endl;
			sibling->color = RED;
			parent->color = BLACK;
			break;
		}
		
		//sibling�� ������ ���������Ƿ� �ݵ�� ������̴�.
		//sibling�� �Ϸķ� �ִ� sibling�� �ڽĳ�尡 ���̸� �ٸ� �ڽĳ�尡 ������ ��
		//���� ������ ������ ������Ű�� ���� ���� ��带 parent�� ������ �ڽ��� ������ �ڽ��̳�,
		//parent�� ���� �ڽ��� ���� �ڽ����� �α� ���� sibling�� �������� ȸ���Ѵ�.
		//ȸ�� �Ŀ��� node�� ���ο� sibling�� ������ ������̴�.
		if (!isRightChild && sibling->right->color == BLACK && sibling->left->color == RED) {
			sibling->left->color = BLACK;
			sibling->color = RED;
			sibling = rightRotate(sibling);
		}
		else if (isRightChild && sibling->left->color == BLACK && sibling->right->color == RED) {
			sibling->right->color = BLACK;
			sibling->color = RED;
			sibling = leftRotate(sibling);
		}

		//sibling�� ���̰�, parent�� ���� ����� ���� ��峪 ������ ����� ������ ��尡 �������� ���
		//parent�� �������� ȸ���Ͽ� sibling�� parent�� ���� ����� �θ��尡 �ǵ��� �Ѵ�.
		//�� �� parent�� sibling�� ����	�ٲٰ� ���� ��带 �� ���� �ٲٸ� �ȴ�.
		//�� ������ ������ parent�� �ڸ��� ����� sibling�� ��Ʈ�� �ϴ� Ʈ���� ��� ��ο���
		//���� ������� ���� ������ �ȴ�.
		if (!isRightChild) {
			//cout << "checking node case 5 " << node->data << endl;
			sibling->right->color = BLACK;
			sibling->color = parent->color;
			parent->color = BLACK;
			leftRotate(parent);
		}
		else {
			//cout << "checking node case 6 " << node->data << endl;
			sibling->left->color = BLACK;
			sibling->color = parent->color;
			parent->color = BLACK;
			rightRotate(parent);
		}
		break;
	}
	node->color = BLACK;
}

Node * deleteNode(int data) {
	Node * delNode = searchNode(T->root, data);
	if (delNode == T->nil)
		return T->nil;
	//������ ��尡 Ʈ���� ������ ����� ���� �� ��Ʈ��带
	//NULL�� �����Ѵ�.
	else if (delNode == T->root && delNode->right == T->nil && delNode->left == T->nil) {
		free(delNode);
		T->root = T->nil;
		return T->nil;
	}

	cout << "delete Node" << delNode->data<<endl;
	//������ ��带 ��ü�� ���ĳ�带 ã�´�.
	//���ĳ�尡 �������� �ʴ� ��� ��ü���� �ʰ� ������ ��带 �״�� �����ϸ� �ȴ�.
	Node * successor = findSuccessor(delNode);
	cout << "successor found" << successor->data << endl;
	delNode->data = successor->data;
	delNode = successor;

	//���ĳ�尡 �������� �ʴ� ����� �ڽ��� �ݵ�� ���� �ڽĳ���� ���̸�,
	//���ĳ�尡 ������ ��� ���ĳ���� �ڽ��� �ݵ�� ������ �ڽĳ���� ���̴�.
	Node * child = (delNode->right == T->nil) ? delNode->left : delNode->right;
	replaceNode(delNode, child);

	//������ ��尡 �������� ��� �ڽĳ��� �ݵ�� ������� ���̹Ƿ�,
	//�ƹ��� ������ ���� ��带 ��ü�ϸ� �ȴ�.

	cout << "rebalancing node" << child->data << endl;
	if (delNode->color == BLACK) {
		//������ ��尡 ������̰� �ڽĳ�尡 �������� ���,
		//�ڽĳ���� ���� ������ �ٲٸ� ����� Ʈ���� Ư���� �������� �ʰ� �ȴ�.
		if (child->color == RED)
			child->color = BLACK;
		//������ ��尡 ������̰� �ڽĳ�� ���� ������� ���
		//������ ��带 �ڽĳ��� ��ü���� �� ������ ��带 ������ ��ΰ�
		//�ٸ� ��� ��ο� ���� ����尡 1�� �����ϰ� �ǹǷ�
		//Ʈ���� �������� ���� deleteFixup()�� ȣ���Ѵ�.
		else
			deleteFixup(child);
	}
	free(delNode);
	return child;
}

void printTree(Node * node) {
	if (node == T->nil) return;
	//if(node->left != T->nil)
		//cout << "left Child ";
	printTree(node->left);
	cout << node->data << ' ';
	//if(node->right != T->nil)
		//cout << "right Child ";
	printTree(node->right);
}

int main(void) {
	T = new Tree();
	cout << "insert Data" << endl;
	int data;
	while (true) {
		cin >> data;
		if (data == -1)
			break;
		insert(data);
		printTree(T->root);
		cout << "root: " << T->root->data;
		cout << endl;
	}
	cout << "delete Data" << endl;
	while (true) {
		if (T->root == T->nil)
			break;
		cin >> data;
		if (data == -1)
			break;
		deleteNode(data);
		printTree(T->root);
		cout << "root: " << T->root->data;
		cout << endl;
	}
	return 0;
}