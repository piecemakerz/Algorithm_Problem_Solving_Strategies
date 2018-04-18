#include <iostream>
#include <vector>

using namespace std;

//이진 검색 트리의 구현과 노드 검색/삽입/삭제의 구현
//노드 삭제는 두 가지 방법으로 구현했는데,
//removeNode()는 pg 700의 '합치기' 기법을 사용해 구현했으며,
//removeNodeOther()는 https://blog.naver.com/wpdls6012/220282739841 의 방법을 사용해 구현했으며,
//삭제할 노드의 오른쪽 부분 트리에서 가장 작은 값을 가진 노드를 삭제할 노드의 위치로 옮겼다.
typedef struct Node {
	int Data;
	Node * Left;
	Node * Right;
	Node(int data) : Data(data) {
		Left = NULL, Right = NULL;
	}
} Node;

//노드의 검색
Node* searchNode(Node* Tree, int data) {
	if (Tree == NULL) return NULL;
	if (Tree->Data == data)
		return Tree;

	else if (Tree->Data > data)
		return searchNode(Tree->Left, data);

	else return searchNode(Tree->Right, data);
}

//노드의 삽입
void insertNode(Node * Tree, Node* newNode) {
	if (newNode->Data > Tree->Data) {
		if (Tree->Right != NULL) insertNode(Tree->Right, newNode);
		else Tree->Right = newNode;
	}
	else {
		if (Tree->Left != NULL) insertNode(Tree->Left, newNode);
		else Tree->Left = newNode;
	}
}

//최솟값 노드 반환
Node* findMinNode(Node * Tree) {
	if (Tree == NULL) return NULL;
	if (Tree->Left != NULL) return findMinNode(Tree->Left);
	else return Tree;
}

//최댓값 노드 반환
Node* findMaxNode(Node * Tree) {
	if (Tree == NULL) return NULL;
	if (Tree->Right != NULL) return findMaxNode(Tree->Right);
	else return Tree;
}

//두 트리 합치기
Node* combineTree(Node * LTree, Node * RTree) {
	Node * newRoot = LTree;
	if (newRoot == NULL)
		return RTree;

	newRoot->Right = combineTree(newRoot->Right, RTree);
	return newRoot;
}

//노드 삭제
Node* removeNode(Node * Tree, int data) {
	bool wasLeftTree;
	Node * delNode = Tree;
	Node * prevNode;
	while (!(delNode == NULL || delNode->Data == data)) {
		prevNode = delNode;
		if (delNode->Data < data)
			delNode = delNode->Right;
		else
			delNode = delNode->Left;
	}

	if (delNode == NULL) {
		cout << ("해당하는 노드를 찾을 수 없습니다.");
		return NULL;
	}
	
	if (prevNode->Left == delNode)
		wasLeftTree = true;
	else
		wasLeftTree = false;

	Node * delNodeLeft = delNode->Left, * delNodeRight = delNode->Right;
	delete(delNode);
	delNode = combineTree(delNodeLeft, delNodeRight);
	if (wasLeftTree)
		prevNode->Left = delNode;
	else
		prevNode->Right = delNode;

	return delNode;
}

Node * removeNodeOther(Node * Tree, int data) {
	bool wasLeftTree;
	Node * delNode = Tree;
	Node * prevNode;
	while (!(delNode == NULL || delNode->Data == data)) {
		prevNode = delNode;
		if (delNode->Data < data)
			delNode = delNode->Right;
		else
			delNode = delNode->Left;
	}

	if (delNode == NULL) {
		cout << ("해당하는 노드를 찾을 수 없습니다.");
		return NULL;
	}

	if (prevNode->Left == delNode)
		wasLeftTree = true;
	else
		wasLeftTree = false;

	//삭제할 노드가 잎 노드인 경우
	if (delNode->Right == NULL && delNode->Left == NULL) {
		delete(delNode);
		if (wasLeftTree)
			prevNode->Left = NULL;
		else
			prevNode->Right = NULL;
	}

	//삭제할 노드가 하나의 자식을 가질 경우
	if (delNode->Right == NULL) {
		delNode->Data = delNode->Left->Data;
		delete(delNode->Left);
		delNode->Left = NULL;
	}
	else if (delNode->Left == NULL) {
		delNode->Data = delNode->Right->Data;
		delete(delNode->Right);
		delNode->Right = NULL;
	}

	//삭제할 노드가 두 개의 자식을 가질 경우
	//오른쪽 서브 트리에서 가장 작은 값으로 대체한다.
	else {
		Node * delNodeRight = delNode->Right;
		Node * minNode = delNodeRight;
		Node * minPrevNode = NULL;
		while (minNode->Left != NULL) {
			minPrevNode = minNode;
			minNode = minNode->Left;
		}
		delNode->Data = minNode->Data;

		if (minNode == delNodeRight)
			delNode->Right = NULL;

		if(minPrevNode != NULL)
			minPrevNode->Left = NULL;
	}
	return delNode;
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
		insertNode(root, new Node(data));
	}
	printTree(root);
	cout << endl;
	removeNodeOther(root, 72);
	printTree(root);
	cout << endl;
	return 0;
}