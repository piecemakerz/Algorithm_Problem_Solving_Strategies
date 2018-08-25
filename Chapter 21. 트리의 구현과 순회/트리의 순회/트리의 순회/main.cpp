#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//트리의 노드를 표현하는 객체의 구현
struct TreeNode {
	string label; //저장할 자료
	TreeNode * parent; //부모 노드를 가리키는 포인터
	vector<TreeNode*> children; //자손 노드들을 가리키는 포인터의 배열
};

//트리를 순회하며 모든 노드에 포함된 값을 출력하기
//주어진 트리의 각 노드에 저장된 값을 모두 출력한다.
void printLabels(TreeNode* root) {
	//루트에 저장된 값을 출력한다.
	cout << root->label << endl;
	//각 자손들을 루트로 하는 서브트리에 포함된 값들을 재귀적으로 출력한다.
	for (int i = 0; i < root->children.size(); i++)
		printLabels(root->children[i]);
}

//순회를 이용해 트리의 높이를 계산하기
//root를 루트로 하는 트리의 높이를 구한다.
int height(TreeNode* root) {
	int h = 0;
	for (int i = 0; i < root->children.size(); i++)
		h = max(h, 1 + height(root->children[i]));
}