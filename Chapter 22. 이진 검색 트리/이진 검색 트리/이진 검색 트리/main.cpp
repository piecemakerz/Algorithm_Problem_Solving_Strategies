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
	int Data;
	Node * Left;
	Node * Right;
	Node * parent;
	Node(int data) : Data(data) {
		Left = NULL, Right = NULL, parent = NULL;
	}
} Node;

//노드의 검색
Node* searchNode(Node* Tree, int data) {
	if (Tree == NULL || Tree->Data == data) return Tree;

	if (Tree->Data > data)
		return searchNode(Tree->Left, data);

	else return searchNode(Tree->Right, data);
}

//최솟값 노드 반환
Node* findMinNode(Node * Tree) {
	while (Tree->Left != NULL)
		Tree = Tree->Left;
	return Tree;
}

//최댓값 노드 반환
Node* findMaxNode(Node * Tree) {
	while (Tree->Right != NULL)
		Tree = Tree->Right;
	return Tree;
}

//직후노드 리턴
Node* findSuccessor(Node* node) {
	if (node->Right != NULL)
		return findMinNode(node->Right);

	while (node->parent != NULL && node == node->parent->Right) {
		node = node->parent;
	}
	return node->parent;
}

//노드의 삽입
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
		Tree = newNode; // Tree는 빈 트리이다.
	else if (data < prevNode->Data)
		prevNode->Left = newNode;
	else
		prevNode->Right = newNode;
}

//두 트리 합치기
Node* combineTree(Node * LTree, Node * RTree) {
	Node * newRoot = LTree;
	if (newRoot == NULL)
		return RTree;

	newRoot->Right = combineTree(newRoot->Right, RTree);
	if (newRoot->Right != NULL)
		newRoot->Right->parent = newRoot;
	return newRoot;
}

//노드 삭제
Node* removeNode(Node * Tree, int data) {
	Node * delNode = searchNode(Tree, data);

	if (delNode == NULL) {
		cout << ("해당하는 노드를 찾을 수 없습니다.");
		return NULL;
	}
	
	Node * replaceNode = combineTree(delNode->Left, delNode->Right);
	replaceNode->parent = delNode->parent;

	if(delNode->parent != NULL) // delNode가 루트 노드가 아니라면
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
		cout << ("해당하는 노드를 찾을 수 없습니다.");
		return NULL;
	}

	//삭제할 노드가 잎 노드인 경우
	if (delNode->Right == NULL && delNode->Left == NULL) {
		if (delNode->parent->Left == delNode)
			delNode->parent->Left = NULL;
		else
			delNode->parent->Right = NULL;
	}

	//삭제할 노드가 하나의 자식을 가질 경우
	if (delNode->Right == NULL) {
		replaceNode = delNode->Left;
		replaceNode->parent = delNode->parent;
	}
	else if (delNode->Left == NULL) {
		replaceNode = delNode->Right;
		replaceNode->parent = delNode->parent;
	}
	//삭제할 노드가 두 개의 자식을 가질 경우
	//오른쪽 서브 트리에서 가장 작은 값(delNode의 직후노드)으로 대체한다.
	//직후노드는 왼쪽 자식이 존재하지 않는다.
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

//한 서브 트리를 다른 서브 트리로 교체하는 서브 루틴. 
//노드 u가 루트인 서브 트리를 노드 v가 루트인 서브 트리로 교체한다.
//노드 u의 부모노드의 서브트리 포인터와 노드 v의 부모노드만 갱신해주며,
//노드 u에 대한 메모리 언로드, 노드 v의 left, right 포인터 갱신은
//transplant()의 호출자의 몫이다.
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
	//delNode가 오른쪽 자식 노드만 가질 때
	if (delNode->Left == NULL) {
		transplant(Tree, delNode, delNode->Right);
		replaceNode = delNode->Right;
	}
	//delNode가 왼쪽 자식 노드만 가질 때
	else if (delNode->Right == NULL) {
		transplant(Tree, delNode, delNode->Left);
		replaceNode = delNode->Left;
	}
	//delNode가 왼쪽과 오른쪽 자식 노드를 모두 가질 때
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
//중위순회 출력
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