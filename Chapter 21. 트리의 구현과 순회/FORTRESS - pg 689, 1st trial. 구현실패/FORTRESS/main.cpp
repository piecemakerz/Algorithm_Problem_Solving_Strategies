#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int c, n;
int y[100], x[100], radius[100];

struct TreeNode {
	vector<TreeNode*> children;
};

//두 성벽 a, b의 중심점 간의 거리의 제곱을 반환한다.
int sqrdist(int a, int b) {
	return pow(sqrt(x[a] - x[b]), 2) + pow(sqrt(y[a] - y[b]), 2);
}
//성벽 a가 성벽 b를 포함하는지 확인한다.
//성벽 a가 성벽 b를 포함하려면 성벽 a의 중점과 b의 중점 사이의 거리가
//두 성벽의 반지름의 차보다 작아야 한다.
bool encloses(int a, int b) {
	return radius[a] > radius[b] &&
		sqrdist(a, b) < pow(radius[a] - radius[b], 2);
}
//'성벽' 트리에서 parent가 child의 부모인지 확인한다.
//parent는 child를 꼭 직접 포함해야 한다.
bool isChild(int parent, int child) {
	//parent가 child를 아예 포함하지 않는다면 무조건 false 리턴
	if (!encloses(parent, child)) return false;
	//parent가 i번째 성벽을 포함하고 i번째 성벽이 child를 포함한다면
	//parent와 child성벽 사이에 다른 성벽이 존재하므로 false 리턴
	for (int i = 0; i < n; i++)
		if (i != parent && i != child &&
			encloses(parent, i) && encloses(i, child))
			return false;
	return true;
}

//주어진 번호의 성벽에 포함된 구역들을 표현하는 트리를 생성한다.
//root성벽을 루트로 하는 트리를 생성한다.
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int ch = 0; ch < n; ch++)
		//ch성벽이 root성벽에 직접적으로 포함되어 있다면
		//트리를 만들고 자손 목록에 추가한다.
		if (isChild(root, ch))
			ret->children.push_back(getTree(ch));
	return ret;
}

//지금까지 찾은 가장 긴 잎-잎 경로의 길이를 저장한다.
int longest;
//root를 루트로 하는 서브트리(원 트리의 부분트리)의 높이를 반환한다.
int height(TreeNode* root) {
	//root의 각 자식을 루트로 하는 서브트리의 높이를 계산한다.
	vector<int> heights;
	for (int i = 0; i < root->children.size(); i++)
		heights.push_back(height(root->children[i]));
	//만약 자식이 하나도 없다면 0을 반환한다. (잎 노드의 경우 트리의 높이가 0이므로)
	if (heights.empty()) return 0;
	sort(heights.begin(), heights.end());
	//root를 최상위 노드로 하는 경로를 고려하자
	//자식이 하나밖에 없는 루트노드의 경우 높이는 '자식노드의 높이 + 1'이므로 if문을 생략할 수 있다.
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	//트리의 높이는 서브트리 높이의 최대치에 1을 더해 계산한다.
	return heights.back() + 1;
}
//두 노드(가장 긴 루프-잎 경로& 가장 긴 잎-잎 경로) 사이의 가장 긴 경로의 길이를 계산한다.
int solve(TreeNode* root) {
	longest = 0;
	//트리의 높이와 최대 잎-잎 경로 길이 중 큰 것을 선택한다.
	//h = 전체 트리의 높이 = 가장 긴 루프-잎 경로
	int h = height(root);
	return max(longest, h);
}

int main(void) {
	cin >> c;
	for (int testCase = 0; testCase < c; testCase++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> x[i] >> y[i] >> radius[i];
		TreeNode * root = getTree(0);
		cout << solve(root) << endl;
	}
}