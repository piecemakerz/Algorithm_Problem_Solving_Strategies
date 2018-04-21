//레드 블랙 트리는 이진 검색 트리로서 각 노드당 한 비트의 추가 기억 공간을 가진다.
//이 비트는 노드의 색깔을 나타내는데, 적색이나 흑색이 될 수 있다.
//레드 블랙 트리는 루트에서 리프까지의 경로에 나타나는 노드의 색깔을 제한함으로써
//경로 중 어떠한 것도 다른 경로보다 두 배 이상 길지 않음을 보장하게 되는데,
//이로써 트리가 근사적으로 균형을 이룬 트리가 된다.

//레드 블랙 트리의 특성
//1. 모든 노드는 적색이거나 흑색이다.
//2. 루트는 흑색이다.
//3. 모든 리프(nil)는 흑색이다.
//4. 노드가 적색이면 그 노드의 자식은 모두 흑색이다. (흑색노드는 연속으로 나올 수 있다.)
//5. 각 노드로부터 그 노드의 자손인 리프로 가는 경로들은 모두 같은 수의 흑색 노드를 포함한다.

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
	Node * nil; // 경계 노드. 모든 리프 노드는 이 노드를 가리키게 된다(& 루트의 부모).
	Tree(Node * root) : root(root) {
		nil = new Node(-1);
		nil->color = BLACK;
	}
}Tree;

Tree * T;

//최솟값 노드 반환
Node* findMinNode(Node * Tree) {
	while (Tree->left != T->nil)
		Tree = Tree->left;
	return Tree;
}

//최댓값 노드 반환
Node* findMaxNode(Node * Tree) {
	while (Tree->right != T->nil)
		Tree = Tree->right;
	return Tree;
}

//x->right != T.nil임을 가정한다.
//x를 왼쪽으로 돌려 새로운 루트 노드가 된 y를 반환한다.
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

//노드의 검색
Node* searchNode(Node * node, int data) {
	if (node == T->nil || node->data == data) return node;

	if (node->data > data)
		return searchNode(node->left, data);

	else return searchNode(node->right, data);
}

//x->left != T.nil임을 가정한다.
//x를 오른쪽으로 돌려 새로운 루트 노드가 된 y를 반환한다.
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
	//새로 삽입하는 노드의 색은 적색이다.
	//따라서 node의 부모 노드 색이 적색이라면 레드 블랙 트리의 조건을 위반하므로
	//트리의 재조정을 while문에서 수행하며,
	//while문에 진입한다면 node의 조부모는 무조건 존재하며 흑색이다.

	while (node->parent->color == RED) {
		Node * sibling; // 친척
		Node * grandParent = node->parent->parent; // 조부모

		//node의 부모가 조부모의 왼쪽 자식이라면
		if (node->parent == grandParent->left) {
			sibling = grandParent->right;
			//node의 부모와 node의 친척도 모두 적색이라면 node의 부모와 친척의 색을 모두 흑색으로 바꾼 후
			//node를 node의 조부모의 위치로 이동시킨다.
			//이후 레드 블랙 트리의 조건을 만족하지 않을 가능성을 가진 노드는
			//node의 조부모이므로 node가 조부모를 가리키도록 한 후 트리 재조정을 재개한다.
			if (sibling->color == RED) {
				node->parent->color = BLACK;
				sibling->color = BLACK;
				grandParent->color = RED;
				node = grandParent;
			}
			//node의 친척이 흑색이라면, 즉 node의 조부모와 친척이 모두 흑색이고 node와 부모가 모두 적색인 경우
			//회전을 통해 레드 블랙 트리의 특성을 만족시키도록 재조정한다.
			//이 else문의 경우 한 번 수행 시 특성을 모두 만족시키므로
			//다음 while문은 더 이상 수행되지 않는다.
			else {
				//node가 오른쪽 자식인 경우 node를 왼쪽 자식으로 바꾸기 위해
				//node의 부모를 기준으로 leftRotate를 호출한다.
				if (node == node->parent->right) {
					node = node->parent;
					leftRotate(node);
				}
				//node가 왼쪽 자식인 경우 부모와 조부모의 색을 바꾼 후
				//조부모를 기준으로 오른쪽 회전한다.
				node->parent->color = BLACK;
				grandParent->color = RED;
				rightRotate(grandParent);
			}
		}

		//node의 부모가 조부모의 오른쪽 자식이라면
		//node의 부모가 조부모의 왼쪽 자식일 때의 코드에서
		//right와 left를 바꾼 경우와 같다.
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

//레드 블랙 트리의 삽입
//트리를 재조정해주는 insertFixup()의 호출을 제외하면
//이진 검색 트리에서의 삽입과 유사하다.
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

	if (prevNode == T->nil) // 트리가 비어있을 경우
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

//한 서브 트리를 다른 서브 트리로 교체하는 서브 루틴. 
//노드 u가 루트인 서브 트리를 노드 v가 루트인 서브 트리로 교체한다.
//노드 u의 부모노드의 서브트리 포인터와 노드 v의 부모노드만 갱신해주며,
//노드 u에 대한 메모리 언로드, 노드 v의 left, right 포인터 갱신은
//rbTransplant()의 호출자의 몫이다.
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
		//sibling = node의 친척
		Node * sibling;
		//node가 왼쪽 자식일 경우
		if (node == node->parent->left) {
			sibling = node->parent->right;
			//경우 1. sibling이 적색인 경우 
			//레드 블랙 트리의 특성을 위반하지 않고sibling을 흑색 노드로 만들기 위해 
			//sibling과 node의 부모 노드 색을 바꾼 후 부모 노드를 기준으로 트리를 왼쪽으로 회전시킨다.
			//부모 노드의 새로운 오른쪽 자식은 새로운 sibling이 되며, sibling이 흑색 노드가 되었으므로
			//경우 1은 발생하지 않는다.
			if (sibling->color == RED) {
				sibling->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				sibling = node->parent->right;
			}
			//경우 2. sibling이 흑색이고 sibling의 두 자식이 모두 흑색인 경우
			if (sibling->left->color = BLACK && sibling->right->color == BLACK) {
				sibling->color = RED;
				node = node->parent;
			}
			else {
				//경우 3. sibling은 흑색, sibling의 왼쪽 자식은 적색, 오른쪽 자식은 흑색인 경우
				//sibling과 왼쪽 자식의 색을 바꾼 후 sibling을 기준으로 트리를 오른쪽으로 회전시키면
				//새로운 sibling은 적색인 오른쪽 자식을 가지는 흑색 노드가 되므로 경우 4를 만족하게 된다.
				if (sibling->right->color == BLACK) {
					sibling->left->color = BLACK;
					sibling->color = RED;
					rightRotate(sibling);
					sibling = node->parent->right;
				}
				//경우 4. sibling은 흑색이고 sibling의 오른쪽 자식은 적색인 경우
				//노드의 색깔을 바꾸고 node의 부모 노드를 기준으로 트리를 좌회전시키면
				//전체 트리의 특성을 만족시킬 수 있으므로 while 루프를 종료시키기 위해
				//node를 트리의 루트 노드로 변경한다.
				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->right->color = BLACK;
				leftRotate(node->parent);
				node = T->root;
			}
		}

		//node가 오른쪽 자식일 경우
		else {

		}
	}
	node->color = BLACK;
}

Node * removeNode(int data) {
	Node * delNode = searchNode(T->root, data);
	if (delNode == T->nil)
		return T->nil;

	//replaceNode는 delNode가 하나 이하의 자식을 가질 때에는 delNode를 가리키며,
	//두 개의 자식을 가질 경우 delNode의 직후원소를 가리킨다.
	Node * replaceNode = delNode;
	int repnodeColor = replaceNode->color;
	//origReplaceNode = replaceNode의 트리 상에서의 이전 위치를 가리키는 노드
	Node * origReplaceNode;

	//삭제할 노드가 오른쪽 자식만 가지고 있다면
	if (delNode->left == T->nil) {
		origReplaceNode = delNode->right;
		rbTransplant(delNode, delNode->right);
	}
	//삭제할 노드가 왼쪽 자식만 가지고 있다면
	else if (delNode->right == T->nil) {
		origReplaceNode = delNode->left;
		rbTransplant(delNode, delNode->left);
	}
	//삭제할 노드가 두 개의 자식을 모두 가질 때
	else {
		//replaceNode = delNode의 직후노드
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
	//replaceNode가 흑색이면 하나 이상의 레드 블랙 트리 특성이 위반될 수 있는데,
	//이를 deleteFixup()에서 복구한다.
	//replaceNode가 흑색이라면 다음 세 가지 문제가 발생할 수 있다.
	//1. replaceNode가 루트 노드이고 y의 적색 자식 노드가 새로운 루트가 된다면 특성 2를 위반한다.
	//2. rbTransplant()가 노드의 색까지 바꿔주지 않으므로, origReplaceNode가 적색이고 origReplaceNode의 부모가
	//적색 노드라면 특성 4를 위반한다.
	//3. replaceNode를 이동함으로써 replaceNode를 원래 포함하고 있던 경로에서는 흑색 노드가 하나 줄게 된다.
	//따라서 replaceNode의 원래 위치를 기준으로 레드 블랙 트리를 재조정해준다.
	if (repnodeColor == BLACK)
		deleteFixup(origReplaceNode);

	return replaceNode;
}