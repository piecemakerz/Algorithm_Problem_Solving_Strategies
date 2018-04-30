//레드 블랙 트리는 이진 검색 트리로서 각 노드당 한 비트의 추가 기억 공간을 가진다.
//이 비트는 노드의 색깔을 나타내는데, 레드이거나 블랙이 될 수 있다.
//레드 블랙 트리는 루트에서 리프까지의 경로에 나타나는 노드의 색깔을 제한함으로써
//루트 노드로부터 가장 먼 경로까지의 거리가, 가장 가까운 경로까지의 거리의 두 배 보다 항상 작다.
//이는 최단 경로가 모두 블랙 노드로만 구성되어 있을 때, 최장 경로는 블랙 노드와 레드 노드가 
//번갈아 나오는 것이 될 것이기 때문이다. 모든 경로에서 블랙 노드의 수가 같으므로 존재하는 모든
//경로에 대해 최장 경로의 거리는 최단 경로의 거리의 두배 이상이 될 수 없다. 
//즉, 레드-블랙 트리는 개략적으로 균형잡혀 있다.

//레드 블랙 트리의 특성
//1. 모든 노드는 레드 혹은 블랙이다.
//2. 루트 노드는 블랙이다.
//3. 모든 리프(nil)는 블랙이다.
//4. 레드 노드의 양쪽 자식노드는 언제나 블랙이다. (블랙노드는 연속으로 나올 수 있다.)
//5. 각 노드로부터 리프노드에 도달하는 모든 경로들은 리프 노드를 제외하면 모두 같은 수의 흑색 노드를 포함한다.

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
	Node * nil; // 경계 노드. 모든 리프 노드는 이 노드를 가리키게 된다(& 루트의 부모).
	Tree() {
		nil = new Node(-1);
		nil->color = BLACK;
		root = nil;
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

//node를 트리의 루트노드로 설정. 루트노드는 반드시 블랙노드이다.
void makeNewRoot(Node * node) {
	node->parent = T->nil;
	T->root = node;
	node->color = BLACK;
}

//node->right != T.nil임을 가정한다.
//node를 왼쪽으로 돌려 새로운 루트 노드가 된 rightChild를 반환한다.
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

//node->left != T.nil임을 가정한다.
//node를 오른쪽으로 돌려 새로운 루트 노드가 된 leftNode를 반환한다.
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

//노드의 검색
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

//uncle은 sibling의 부모 노드, 즉 parent의 형제이다.
Node * findUncle(Node * n)
{
	Node * g = findGrandparents(n);
	//조부모가 존재하지 않는다면 삼촌도 존재하지 않는다.
	if (g == T->nil)
		return T->nil;
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}

void insertFixup(Node * node) {
	//새로 삽입하는 노드의 색은 레드이다.
	//따라서 node의 부모 노드 색이 레드라면 레드 블랙 트리의 조건을 위반하므로
	//트리의 재조정을 while문에서 수행하며,
	//처음 while문에 진입한다면 node의 조부모는 무조건 존재하며 블랙이다.

	while (node->parent->color == RED) {
		Node * parent = node->parent;
		Node * grandParent = findGrandparents(node);// 조부모
		Node * uncle = findUncle(node); // 삼촌
		bool isRightChild = (node == parent->right);
		//parent와 uncle이 모두 레드라면 특성 5를 유지하기 위해
		//parent와 uncle의 색을 모두 블랙으로 바꾼 후 grandParent의 색을 레드로 바꾼다.
		//이로써 node는 블랙 부모 노드를 가지게 된다.
		//이후 레드 블랙 트리의 조건(특성 2나 특성 4)을 만족하지 않을 가능성을 가진 노드는
		//grandParent이므로 node가 grandParent를 가리키도록 한 후 트리 재조정을 재개한다.
		if (uncle != T->nil && uncle->color == RED) {
			parent->color = BLACK;
			uncle->color = BLACK;
			grandParent->color = RED;
			node = grandParent;
		}
		//uncle이 블랙이라면, 즉 parent가 레드이고 uncle과 grandParent가 모두 블랙일 경우
		//회전을 통해 레드 블랙 트리의 특성을 만족시키도록 재조정한다.
		//이 else문의 경우 한 번 수행 시 트리가 레드 블랙 트리의 특성을 모두 만족하게 되므로
		//다음 while문은 더 이상 수행되지 않는다.
		else {
			//node와 parent가 트리상에서 일렬이 아닐 경우 node를 기준으로 회전하여 node와 parent를 일렬로 배치한다.
			//이는 다음 과정에서 회전 이후에 parent의 양쪽 자식이 node와 grandParent가 되도록 하기 위함이다.
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
			//parent가 grandParent의 자리에 위치하도록 grandParent를 기준으로 회전한다.
			//grandParent가 이전에 블랙이었고, parent는 레드였기 때문에 두 노드의 색을 바꾸면 
			//grandParent의 자리에 위치한 parent가 블랙노드이고 parent의 양쪽 자식인 grandParent와
			//uncle이 레드 노드가 되기 때문에 레드 블랙 트리의 특성 4를 만족하게 된다.
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

//레드 블랙 트리의 삽입
//트리를 재조정해주는 insertFixup()의 호출을 제외하면
//이진 검색 트리에서의 삽입과 유사하다.
//삽입하는 노드의 기본 색은 레드이다.
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

	if (prevNode == T->nil) { // 트리가 비어있을 경우 newNode가 트리의 루트가 된다.
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
//노드 n1을 노드 n2로 대체한다. 
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

//재귀 시 node는 블랙노드임이 보장된다.
void deleteFixup(Node * node) {
	//node가 새로운 루트노드라면 모든 경로에서 하나의 블랙노드(delNode)를 삭제했고
	//새로운 루트노드가 블랙노드이므로 트리의 모든 특성이 보존된다. 

	while (node->parent != T->nil) {
		//cout << "checking node" << node->data << endl;
		Node * parent = node->parent;
		Node * sibling = (node == parent->left) ? parent->right : parent->left;
		bool isRightChild = (node == parent->right);
		bool isRightChild = (node == parent->right);

		//sibling sibling의 모든 자식들, 그리고 node, parent가 모두 블랙노드일 경우
		//간단히 sibling을 레드노드로 바꾸면 된다. 이로 인해 parent를 루트로 하는 트리의
		//블랙노드 갯수 불균형은 해결되었으나, parent를 지나지 않는 모든
		//경로는 parent를 지나는 모든 경로에 대해 검은 노드를 한 개 더 가지게 되므로
		//트리가 특성 5를 위반하게 된다. 따라서 parent에 대해 재조정을 다시 시작한다.
		if (parent->color == BLACK && sibling->color == BLACK &&
			sibling->left->color == BLACK && sibling->right->color == BLACK) {
			sibling->color = RED;
			node = parent;
			continue;
		}
		//sibling이 레드노드, 즉 node, parent가 블랙노드이고 sibling이 레드노드일 경우
		//(sibling이 레드일 경우 레드노드는 연속해서 나올 수 없기 때문에 parent는 무조건 블랙임이 보장된다.
		//또한 node의 위치에 있던 블랙노드를 삭제하여 불균형이 발생했으므로 sibling의 자식 노드들이 블랙 노드임은
		//물론이고 자식 노드들의 자식 노드들도 경로 중 블랙노드를 반드시 하나 이상 포함할 것이다.)
		//node가 블랙 형제노드와 레드 부모노드를 가지게 하기 위해 parent를 기준으로 회전하고 parent의 색을 레드로,
		//sibling의 색을 BLACK으로 바꾼다. 이는 트리 재조정의 다음 과정의 조건
		//(sibling->color == BLACK && parent->color == RED)을 만족시키기 위함이다.
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

		//sibling과 sibling의 자식들은 모두 블랙이지만, parent는 레드노드인 경우
		//단순히 sibling과 parent의 색을 바꿔주면 된다.
		//이는 node를 지나는 경로에 대해 블랙 노드의 갯수를 1개 증가시켜, 삭제된
		//블랙노드(직후노드)의 갯수를 보충해준다. 이후 레드블랙 트리가 모든 특성을 만족하므로
		//반복을 중단한다.
		if (sibling->color == BLACK && sibling->right->color == BLACK && 
			sibling->left->color == BLACK && parent->color == RED) {
			//cout << "checking node case 3 " << node->data << endl;
			sibling->color = RED;
			parent->color = BLACK;
			break;
		}
		
		//sibling은 이전에 조정했으므로 반드시 블랙노드이다.
		//sibling과 일렬로 있는 sibling의 자식노드가 블랙이며 다른 자식노드가 레드일 때
		//다음 과정의 조건을 만족시키기 위해 레드 노드를 parent의 오른쪽 자식의 오른쪽 자식이나,
		//parent의 왼쪽 자식의 왼쪽 자식으로 두기 위해 sibling을 기준으로 회전한다.
		//회전 후에도 node의 새로운 sibling은 무조건 블랙노드이다.
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

		//sibling이 블랙이고, parent의 왼쪽 노드의 왼쪽 노드나 오른쪽 노드의 오른쪽 노드가 레드노드일 경우
		//parent를 기준으로 회전하여 sibling이 parent와 레드 노드의 부모노드가 되도록 한다.
		//그 후 parent와 sibling의 색을	바꾸고 레드 노드를 블랙 노드로 바꾸면 된다.
		//이 과정이 끝나면 parent의 자리를 대신한 sibling을 루트로 하는 트리는 모든 경로에서
		//같은 블랙노드의 수를 가지게 된다.
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
	//삭제할 노드가 트리의 마지막 노드라면 삭제 후 루트노드를
	//NULL로 변경한다.
	else if (delNode == T->root && delNode->right == T->nil && delNode->left == T->nil) {
		free(delNode);
		T->root = T->nil;
		return T->nil;
	}

	cout << "delete Node" << delNode->data<<endl;
	//삭제할 노드를 대체할 직후노드를 찾는다.
	//직후노드가 존재하지 않는 경우 대체하지 않고 삭제할 노드를 그대로 삭제하면 된다.
	Node * successor = findSuccessor(delNode);
	cout << "successor found" << successor->data << endl;
	delNode->data = successor->data;
	delNode = successor;

	//직후노드가 존재하지 않는 경우의 자식은 반드시 왼쪽 자식노드일 것이며,
	//직후노드가 존재할 경우 직후노드의 자식은 반드시 오른쪽 자식노드일 것이다.
	Node * child = (delNode->right == T->nil) ? delNode->left : delNode->right;
	replaceNode(delNode, child);

	//삭제할 노드가 레드노드일 경우 자식노드는 반드시 블랙노드일 것이므로,
	//아무런 재조정 없이 노드를 대체하면 된다.

	cout << "rebalancing node" << child->data << endl;
	if (delNode->color == BLACK) {
		//삭제할 노드가 블랙노드이고 자식노드가 레드노드일 경우,
		//자식노드의 색을 블랙으로 바꾸면 레드블랙 트리의 특성을 위반하지 않게 된다.
		if (child->color == RED)
			child->color = BLACK;
		//삭제할 노드가 블랙노드이고 자식노드 또한 블랙노드일 경우
		//삭제할 노드를 자식노드로 대체했을 때 삭제할 노드를 지나는 경로가
		//다른 모든 경로에 대해 블랙노드가 1개 부족하게 되므로
		//트리의 재조정을 위해 deleteFixup()을 호출한다.
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