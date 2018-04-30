//AVL 트리는 각각의 노드마다 왼쪽과 오른쪽 부분 트리의 높이 차이에 대한
//정보를 가지며, 부분 트리의 높이 차이가 1보다 크지 않은 성질(높이 균형 성질)을 가진다.
//AVL 트리에서는 노드가 삽입, 삭제될 때 회전을 통해 트리를 재구성하여
//높이 균형 성질을 유지시킨다. 즉, 삽입/삭제 연산시 BF(Balance Factor, 
//왼쪽 서브트리 높이에서 오른쪽 서브트리 높이를 뺀 것)가 일정 값 이상(보통 2)
//혹은 이하(-2)로 바뀐 노드를 기준으로 그 서브트리들의 위치를 회전하는 방식을 취한다.

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

//노드의 검색
Node* searchNode(Node * node, int data) {
	if (node == NULL || node->data == data) return node;

	if (node->data > data)
		return searchNode(node->left, data);

	else return searchNode(node->right, data);
}

//최솟값 노드 반환
Node* findMinNode(Node * Tree) {
	while (Tree->left != NULL)
		Tree = Tree->left;
	return Tree;
}

//최댓값 노드 반환
Node* findMaxNode(Node * Tree) {
	while (Tree->right != NULL)
		Tree = Tree->right;
	return Tree;
}

//node를 왼쪽으로 돌려 새로운 루트 노드가 된 rightChild를 반환한다.
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

//node를 오른쪽으로 돌려 새로운 루트 노드가 된 leftNode를 반환한다.
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

//Tree를 루트노드로 하는 서브트리의 높이를 해당 노드의 멤버변수로 저장한다.
//트리의 높이란 루트노드와 리프노드 사이의 경로의 최대 길이를 뜻한다.
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
	//왼쪽 노드와 오른쪽 노드 모두 존재하지 않으면 리프 노드라는 의미이므로
	//높이를 초기값 0으로 유지한다.
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
	//리프 노드라면 BF를 0으로 유지한다.
	else
		Tree->BF = 0;
}

void rebalance(Node * Tree) {
	//현재 노드의 BF 절댓값이 2 이상이면 불균형트리이므로
	//현재 노드를 기준으로 회전을 한다.
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

//노드의 삽입 후 각 노드의 높이와 BF를 갱신하기 위해 updateHeights()와
//updateBalances()를 호출하는 것과, 트리를 재조정해주는 rebalance()의
//호출을 제외하면 이진 검색 트리에서의 삽입과 유사하다.
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
		root = newNode; // Tree는 빈 트리이다.
	else if (data < prevNode->data)
		prevNode->left = newNode;
	else
		prevNode->right = newNode;

	updateHeights(root);
	updateBalances(root);
	rebalance(newNode);
}

//직후노드 리턴. 직후노드를 찾는 경우는 삭제할 노드가 두 개의
//자식을 가질 경우밖에 없으므로 직후노드는 반드시 삭제할 노드의
//아래 레벨에 존재한다. 따라서 삭제할 노드의 오른쪽 자식이 NULL인
//경우에 대한 예외처리를 하지 않아도 된다.
Node* findSuccessor(Node* node) {
	//if (node->right != NULL)
	return findMinNode(node->right);

	/*while (node->parent != NULL && node == node->parent->right) {
	node = node->parent;
	}
	return node->parent;
	*/
}

//코드가 매우 길다. 이진 검색 트리의 removeOtherNode()나 레드 블랙 트리 구현코드의 deleteNode()는
//삭제하는 노드를 다른 노드로 대체하는 작업을 별도의 함수로 분리하여
//코드의 길이를 훨씬 줄였다.
void removeNode(int data) {
	Node * delNode = searchNode(root, data);
	Node * replaceNode = NULL;
	if (delNode == NULL) {
		cout << ("해당하는 노드를 찾을 수 없습니다.");
		return;
	}

	//삭제할 노드가 잎 노드인 경우
	if (delNode->right == NULL && delNode->left == NULL) {
		//삭제할 노드가 트리의 마지막 노드인 경우
		if (delNode->parent == NULL)
			root = NULL;
		else if (delNode->parent->left == delNode)
			delNode->parent->left = NULL;
		else
			delNode->parent->right = NULL;
		replaceNode = delNode->parent;
	}

	//삭제할 노드가 하나의 자식을 가질 경우
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
	//삭제할 노드가 두 개의 자식을 가질 경우
	//오른쪽 서브 트리에서 가장 작은 값(delNode의 직후노드)으로 대체한다.
	//직후노드는 왼쪽 자식이 존재하지 않는다.
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

//중위순회 출력
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