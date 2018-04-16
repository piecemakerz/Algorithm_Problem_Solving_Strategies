#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N;
typedef struct TreeNode {
public:
	int label;
	bool visited;
	TreeNode* parent, *left, *right;
	TreeNode(int inputLabel) : label(inputLabel) {
		parent = NULL; left = NULL; right = NULL; visited = false;
	};

}Node;

Node* treeRoot; // 트리의 루트 노드

//내 풀이1: 전위 순회의 입력 순서대로 이진 트리를 만들어, 
//완성된 트리를 기준으로 후위 순회한 결과를 반환한다.
//이 방법으로 생성한 이진 트리는 중위 순회는 물론 전위 순회의 순서도 
//입력받은 순서와 일치하지 않는다.
/*
void MakeRealTree(vector<int>& labels) {
	treeRoot = new Node(labels[0]); //전위순회에서 가장 먼저 방문하는 노드는 트리의 루트노드이다.
	for (int i = 1; i < N; i++) {
		Node* curNode = treeRoot; // 루트노드에서부터 탐색 시작

		while (true) {
			if (labels[i] < curNode->label)
				if (curNode->left == NULL) {
					curNode->left = new Node(labels[i]);
					curNode->left->parent = curNode;
					break;
				}
				else {
					curNode = curNode->left;
				}

			else
				if (curNode->right == NULL) {
					curNode->right = new Node(labels[i]);
					curNode->right->parent = curNode;
					break;
				}
				else {
					curNode = curNode->right;
				}
		}
	}
}

vector<int> postorderTraverse() {
	vector<int> visitedOrder; // 후위 순회 순서
	Node* curNode = treeRoot; // 순회는 루트 노드에서부터 시작
	while (!treeRoot->visited) {
		//현재 노드를 아직 방문하지 않았다면
		if (!curNode->visited) {
			//왼쪽 자식 노드가 존재하며 아직 방문하지 않았다면
			if (curNode->left != NULL && !curNode->left->visited)
				curNode = curNode->left;
			//오른쪽 자식 노드가 존재하며 아직 방문하지 않았다면
			else if (curNode->right != NULL && !curNode->right->visited)
				curNode = curNode->right;
			//왼쪽&오른쪽 자식 노드들을 모두 확인했다면
			else {
				curNode->visited = true;
				visitedOrder.push_back(curNode->label);
				curNode = curNode->parent;
			}
		}
	}
	return visitedOrder;
}
*/

//내 풀이2: 입력받은 전위 순회를 기준으로 왼쪽 편향 트리를 생성한 후
//중위 순회를 만족시킬 수 있도록 트리를 변형한다.
//기준 1. 만일 중위순회중인 노드의 왼쪽 자식노드가 존재하고 아직 방문되지 않았다면
//이를 오른쪽 자식노드로 옮긴다.
//기준 2. 만일 중위순회중인 노드의 왼쪽 자식노드가 존재하고 이들이 방문되었다면 
//이전에 방문한 노드의 오른쪽 자식노드를 이 노드의 오른쪽 자식노드로 옮긴다.
//기준 3. 기준 1과 2가 모두 성립하지 않는다면 위치를 변경하지 않는다.

Node* nodePos[1001]; // i의 값을 가지고 있는 노드의 위치

//전위 순회를 기준으로 왼쪽 편향 이진트리 생성
void MakePreorderTree(const vector<int>& labels) {
	treeRoot = new Node(labels[0]);
	treeRoot->parent = treeRoot;
	nodePos[labels[0]] = treeRoot;
	Node* curPos = treeRoot;

	for (int i = 1; i < N; i++) {
		Node * child = new Node(labels[i]);
		nodePos[labels[i]] = child;
		curPos->left = child;
		child->parent = curPos;
		curPos = child;
	}
}

//중위 순회를 만족시킬 수 있는 이진트리 생성
void MakeInorderTree(const vector<int>& labels) {
	Node * curNode;
	for (int i = 0; i < N; i++) {
		curNode = nodePos[labels[i]];
		if (curNode->left != NULL) {
			if (!curNode->left->visited) {
				curNode->right = curNode->left;
				curNode->left = NULL;
			}
			else {
				curNode->right = nodePos[labels[i - 1]]->right;
				if(curNode->right != NULL)
					curNode->right->parent = curNode;
				nodePos[labels[i - 1]]->right = NULL;
			}
		}
		curNode->visited = true;
	}
	//각 노드의 visited변수 false로 초기화
	for (int i = 0; i < N; i++) {
		nodePos[labels[i]]->visited = false;
	}
}

//완성된 이진트리를 기준으로 후위 순회
vector<int> postorderTraverse() {
	Node* curNode = treeRoot;
	vector<int> labels;
	while (!treeRoot->visited) {
		if (curNode->left != NULL && !curNode->left->visited)
			curNode = curNode->left;
		else if (curNode->right != NULL && !curNode->right->visited)
			curNode = curNode->right;
		else {
			curNode->visited = true;
			labels.push_back(curNode->label);
			curNode = curNode->parent;
		}
	}
	return labels;
}

//책의 답
//트리 순회 순서 변경 문제를 해결하는 재귀 호출 코드
vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}
//트리의 전위탐색 결과와 중위탐색 결과가 주어질 때 후위탐색 결과를 출력한다.
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
	//트리에 포함된 노드 수
	const int N = preorder.size();
	//기저 사례: 텅 빈 트리면 곧장 종료
	if (preorder.empty()) return;
	//이 트리의 루트는 전위 탐색 결과로부터 곧장 알 수 있다.
	const int root = preorder[0];
	//이 트리의 왼쪽 서브트리의 크기는 중위 탐색 결과에서 루트의 위치를 찾아서 알 수 있다.
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	//오른쪽 서브트리의 크기는 N에서 왼쪽 서브트리와 루트를 빼면 알 수 있다.
	const int R = N - 1 - L;
	//왼쪽과 오른쪽 서브트리의 순회 결과를 출력
	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	//후위 순회이므로 루트를 가장 마지막에 출력한다.
	cout << root << ' ';
}
int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(nodePos, NULL, sizeof(nodePos));
		cin >> N;
		int inputLabel;

		vector<int> preorderTraverse; // 전위 순회 순서
		for (int i = 0; i < N; i++) {
			cin >> inputLabel;
			preorderTraverse.push_back(inputLabel);
		}
		MakePreorderTree(preorderTraverse); // 전위 순회를 만족하는 왼쪽 편향 트리 생성

		vector<int> inorderTraverse; // 중위 순회 순서
		for (int i = 0; i < N; i++) {
			cin >> inputLabel;
			inorderTraverse.push_back(inputLabel);
		}
		MakeInorderTree(inorderTraverse); // 중위 순회를 만족하는 트리 생성
		
		vector<int> postorderLabel;
		postorderLabel = postorderTraverse(); // 후위 순회 순서 저장
		for (int i = 0; i < N; i++) {
			cout << postorderLabel[i] << ' ';
		}
		cout << endl;

		for (int i = 0; i < N; i++) {
			delete nodePos[preorderTraverse[i]];
		}
	}
	return 0;
}