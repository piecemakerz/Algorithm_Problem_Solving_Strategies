#include <iostream>
#include <vector>

using namespace std;

//이진 검색 트리의 구현과 노드 검색/삽입/삭제의 구현
//노드 삭제는 세 가지 방법으로 구현했는데,
//removeNode()는 pg 700의 '합치기' 기법을 사용해 구현했으며,
//removeNodeOther()는 https://blog.naver.com/wpdls6012/220282739841 의 방법을 사용해 구현했으며,
//삭제할 노드의 오른쪽 부분 트리에서 가장 작은 값을 가진 노드를 삭제할 노드의 위치로 옮겼다.
//removeNodeBook()은 책 Introduction to Alglrithms에서 제시하는 노드 삭제 알고리즘이며,
//removeNodeOther()과 같은 방법을 이용해 노드 삭제를 구현한다.
typedef struct Node {
	int data;
	Node * left;
	Node * right;
	Node * parent;
	Node(int data) : data(data) {
		left = NULL, right = NULL, parent = NULL;
	}
} Node;

//노드의 검색. 검색에 실패할 경우 NULL를 반환한다.
Node* searchNode(Node* node, int data) {
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

//노드의 삽입
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
		Tree = newNode; // Tree는 빈 트리이다.
	else if (data < prevNode->data)
		prevNode->left = newNode;
	else
		prevNode->right = newNode;
}

//두 트리 합치기. LTree의 루트 노드를 합친 트리의 루트로 설정한 후.
//RTree와 LTree의 오른쪽 서브트리를 재귀적으로 합쳐 LTree의 새로운
//오른쪽 트리로 한다.
Node* combineTree(Node * LTree, Node * RTree) {
	Node * newRoot = LTree;
	if (newRoot == NULL)
		return RTree;
	else if (RTree == NULL)
		return newRoot;

	newRoot->right = combineTree(newRoot->right, RTree);
	//합친 트리를 오른쪽 자식으로 한다.
	if (newRoot->right != NULL)
		newRoot->right->parent = newRoot;
	return newRoot;
}

//노드 삭제
Node* removeNode(Node*& Tree, int data) {
	Node * delNode = searchNode(Tree, data);

	if (delNode == NULL) {
		cout << ("해당하는 노드를 찾을 수 없습니다.");
		return NULL;
	}
	
	//replaceNode = 삭제할 노드의 자리에 위치할 노드
	Node * replaceNode = combineTree(delNode->left, delNode->right);
	replaceNode->parent = delNode->parent;

	if(delNode->parent != NULL) // delNode가 루트 노드가 아니라면
		if (delNode->parent->right == delNode)
			delNode->parent->right = replaceNode;
		else
			delNode->parent->left = replaceNode;
	else { // delNode가 루트 노드라면
		Tree = replaceNode;
	}
	delete(delNode);
	return replaceNode;
}

//코드가 매우 길다. 아래의 removeOtherNode()나 레드 블랙 트리 구현코드의 deleteNode()는
//삭제하는 노드를 다른 노드로 대체하는 작업을 별도의 함수로 분리하여
//코드의 길이를 훨씬 줄였다.
Node * removeNodeOther(Node*& Tree, int data) {
	Node * delNode = searchNode(Tree, data);
	Node * replaceNode = NULL;
	if (delNode == NULL) {
		cout << ("해당하는 노드를 찾을 수 없습니다.");
		return NULL;
	}

	//삭제할 노드가 잎 노드인 경우
	if (delNode->right == NULL && delNode->left == NULL) {
		//삭제할 노드가 트리의 마지막 노드인 경우
		if (delNode->parent == NULL)
			Tree = NULL;
		else if (delNode->parent->left == delNode)
			delNode->parent->left = NULL;
		else
			delNode->parent->right = NULL;
	}

	//삭제할 노드가 하나의 자식을 가질 경우
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
	//삭제할 노드가 두 개의 자식을 가질 경우
	//1. 삭제할 노드를 대체할 노드(replaceNode)를 찾고
	//2. 대체할 노드에 저장할 값을 삭제할 노드에 대입하고
	//3. 대체할 노드의 부모 노드와 자식노드를 연결(주소값)한다.
	//대체할 노드는 서브트리에서 가장 작은 값이므로 왼쪽 자식이 존재하지 않는다.
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

//한 서브 트리를 다른 서브 트리로 교체하는 서브 루틴. 
//노드 u가 루트인 서브 트리를 노드 v가 루트인 서브 트리로 교체한다.
//u가 전체 트리의 루트노드일 때 루트노드를 v로 바꿔주며,
//노드 u의 부모노드의 서브트리 포인터와 노드 v의 부모노드를 갱신해준다.
//교체 후 노드 u에 대한 메모리 언로드, 노드 v의 left, right 포인터 갱신은
//transplant()의 호출자의 몫이다.
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
	//delNode가 오른쪽 자식 노드만 가질 때
	if (delNode->left == NULL) {
		transplant(Tree, delNode, delNode->right);
		replaceNode = delNode->right;
	}
	//delNode가 왼쪽 자식 노드만 가질 때
	else if (delNode->right == NULL) {
		transplant(Tree, delNode, delNode->left);
		replaceNode = delNode->left;
	}
	//delNode가 왼쪽과 오른쪽 자식 노드를 모두 가질 때
	//delNode를 delNode의 직후노드로 대체한다.
	//직후노드는 왼쪽 자식노드를 가지지 않는다.
	else {
		replaceNode = findMinNode(delNode->right);
		//직후노드가 delNode 바로 오른쪽 자식이라면 대체 시 직후노드의 오른쪽 자식이
		//바로 delNode 자리의 오른쪽 자식이 되기 때문에 직후노드에 delNode의 오른쪽 자식을
		//연결하는 과정을 생략해도 된다.
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
//중위순회 출력
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