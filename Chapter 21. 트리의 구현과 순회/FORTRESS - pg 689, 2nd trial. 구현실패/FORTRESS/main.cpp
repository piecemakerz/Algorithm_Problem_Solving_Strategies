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

//��ȸ�� �̿��� Ʈ���� ���̸� ����ϱ�
//root�� ��Ʈ�� �ϴ� Ʈ���� ���̸� ���Ѵ�.
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

//���ݱ��� ã�� ���� �� ��-�� ����� ���̸� �����Ѵ�.
int longest;
//root�� �ֻ������� �ϴ� ��-�� ����� �ִ���̸� ����Ѵ�.
//�� Ǯ�̴� Ʈ������ ���� �� ��θ� ã�� �� �κ��� ������ �����ߴ�.
int height(Node* root) {
	//�� �ڽ��� ��Ʈ�� �ϴ� ����Ʈ���� ���̸� ����Ѵ�.
	vector<int> heights;
	for (int i = 0; i < root->children.size(); i++)
		heights.push_back(height(root->children[i]));
	if (heights.empty())
		return 0;
	sort(heights.begin(), heights.end(), greater<int>());
	//root�� �ֻ��� ���� �ϴ� ��θ� ����Ѵ�.
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[0] + heights[1]);
	//Ʈ���� ���̴� ����Ʈ���� ������ �ִ�ġ�� 1�� ���� ����Ѵ�.
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