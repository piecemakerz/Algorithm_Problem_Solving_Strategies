#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int C, N;

struct Node {
	Node(int val) : val(val) {
		parent = NULL, left = NULL, right = NULL;
	}
	int val;
	Node* parent, *left, *right;
};

//내 풀이. 내 풀이는 단순히 후위 순회 순서를 출력한 책의 답과 달리
//완성된 트리의 루트를 반환하기도 한다.
Node* solve(queue<int>& preorderLeft, vector<int>& inorderLeft) {
	Node* root = new Node(preorderLeft.front());
	preorderLeft.pop();
	vector<int>::iterator it = find(inorderLeft.begin(), inorderLeft.end(), root->val);
	vector<int> left(inorderLeft.begin(), it), right(it + 1, inorderLeft.end());
	
	if (!left.empty()) {
		root->left = solve(preorderLeft, left);
		root->left->parent = root;
	}
	if (!right.empty()) {
		root->right = solve(preorderLeft, right);
		root->right->parent = root;
	}
	
	cout << root->val << ' ';
	return root;
}

//트리 순회 순서 변경 문제를 해결하는 책의 재귀 호출 코드
vector<int>  slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}
//트리의 전위탐색 결과와 중위탐색 결과가 주어질 때 후위탐색 결과를 출력한다.
void printPostOrder(const vector<int>& preorder, const vector<int>& inorder) {
	//트리에 포함된 노드의 수
	const int N = preorder.size();
	//기저 사례: 텅 빈 트리면 곧장 종료
	if (preorder.empty()) return;
	//이 트리의 루트는 전위 탐색 결과로부터 곧장 알 수 있다.
	const int root = preorder[0];
	//이 트리의 왼쪽 서브트리의 크기는 중위 탐색 결과에서 루트의 위치를 찾아서 알 수 있다.
	const int L = find(inorder.begin(), inorder.end(), root)
		- inorder.begin();
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
	for (int test = 0; test < C; test++) {
		cin >> N;
		int input;
		queue<int> preorder;
		vector<int> inorder(N);

		for (int i = 0; i < N; i++) {
			cin >> input;
			preorder.push(input);
		}
		for (int i = 0; i < N; i++)
			cin >> inorder[i];

		Node* root = solve(preorder, inorder);
		cout << endl;
	}
}