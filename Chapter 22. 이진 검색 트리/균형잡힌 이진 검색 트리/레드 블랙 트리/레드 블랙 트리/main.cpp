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
	Node * nil;
	Tree(Node * root) : root(root) {
		nil = new Node(-1);
		nil->color = BLACK;
	}
}Tree;

Tree * T;

//x->right != T.nil임을 가정한다.
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

//x->left != T.nil임을 가정한다.
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

Node * insert(int data) {
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
	if (prevNode == T->nil)
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