#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	int x, y, r;
	Node(int _x, int _y, int _r) : x(_x), y(_y), r(_r) {}
	Node* parent;
	vector<Node*> children;
};

int C, N;
vector<pair<int, pair<int, int>>> walls;

//순회를 이용해 트리의 높이를 계산하기
//root를 루트로 하는 트리의 높이를 구한다.
int calHeight(Node* root) {
	int h = 0;
	for (int i = 0; i < root->children.size(); i++)
		h = max(h, 1 + calHeight(root->children[i]));
	return h;
}

bool contains(Node* wall1, Node* wall2) {
	int x1 = wall1->x, x2 = wall2->x, y1 = wall1->y, y2 = wall2->y;
	int sqrdist = pow<int>(x1 - x2, 2) + pow<int>(y1 - y2, 2);
	if (wall1->r > wall2->r && (sqrdist < pow<int>(wall1->r - wall2->r, 2)))
		return true;
	return false;
}

void makeTree(Node* root, Node* curWall) {
	vector<Node*>& children = root->children;

	for (int i = 0; i < children.size(); i++) {
		if (contains(children[i], curWall)) {
			makeTree(children[i], curWall);
			return;
		}
	}
	curWall->parent = root;
	children.push_back(curWall);
}

//지금까지 찾은 가장 긴 잎-잎 경로의 길이를 저장한다.
int longest;
//root를 최상위노드로 하는 잎-잎 경로의 최대길이를 계산한다.
//내 풀이는 트리에서 가장 긴 경로를 찾는 이 부분의 구현에 실패했다.
int height(Node* root) {
	//각 자식을 루트로 하는 서브트리의 높이를 계산한다.
	vector<int> heights;
	for (int i = 0; i < root->children.size(); i++)
		heights.push_back(height(root->children[i]));
	if (heights.empty())
		return 0;
	sort(heights.begin(), heights.end(), greater<int>());
	//root를 최상위 노드로 하는 경로를 고려한다.
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[0] + heights[1]);
	//트리의 높이는 서브트리의 높이의 최대치에 1을 더해 계산한다.
	return heights.back() + 1;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		longest = 0;
		int x, y, r;
		cin >> N;
		for (int i = 0; i < N; i++) {
			cin >> x >> y >> r;
			walls.push_back(make_pair(r, make_pair(x, y)));
		}
		sort(walls.begin(), walls.end(), greater<pair<int, pair<int, int>>>());

		Node* root = new Node(walls[0].second.first, walls[0].second.second, walls[0].first);
		for (int i = 1; i < walls.size(); i++) {
			Node* next = new Node(walls[i].second.first, walls[i].second.second, walls[i].first);
			makeTree(root, next);
		}
				
		cout << max(longest, height(root)) << endl;
		walls.clear();
	}
}