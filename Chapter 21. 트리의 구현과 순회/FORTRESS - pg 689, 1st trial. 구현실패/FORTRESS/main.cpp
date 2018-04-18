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

//�� ���� a, b�� �߽��� ���� �Ÿ��� ������ ��ȯ�Ѵ�.
int sqrdist(int a, int b) {
	return pow(sqrt(x[a] - x[b]), 2) + pow(sqrt(y[a] - y[b]), 2);
}
//���� a�� ���� b�� �����ϴ��� Ȯ���Ѵ�.
//���� a�� ���� b�� �����Ϸ��� ���� a�� ������ b�� ���� ������ �Ÿ���
//�� ������ �������� ������ �۾ƾ� �Ѵ�.
bool encloses(int a, int b) {
	return radius[a] > radius[b] &&
		sqrdist(a, b) < pow(radius[a] - radius[b], 2);
}
//'����' Ʈ������ parent�� child�� �θ����� Ȯ���Ѵ�.
//parent�� child�� �� ���� �����ؾ� �Ѵ�.
bool isChild(int parent, int child) {
	//parent�� child�� �ƿ� �������� �ʴ´ٸ� ������ false ����
	if (!encloses(parent, child)) return false;
	//parent�� i��° ������ �����ϰ� i��° ������ child�� �����Ѵٸ�
	//parent�� child���� ���̿� �ٸ� ������ �����ϹǷ� false ����
	for (int i = 0; i < n; i++)
		if (i != parent && i != child &&
			encloses(parent, i) && encloses(i, child))
			return false;
	return true;
}

//�־��� ��ȣ�� ������ ���Ե� �������� ǥ���ϴ� Ʈ���� �����Ѵ�.
//root������ ��Ʈ�� �ϴ� Ʈ���� �����Ѵ�.
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	for (int ch = 0; ch < n; ch++)
		//ch������ root������ ���������� ���ԵǾ� �ִٸ�
		//Ʈ���� ����� �ڼ� ��Ͽ� �߰��Ѵ�.
		if (isChild(root, ch))
			ret->children.push_back(getTree(ch));
	return ret;
}

//���ݱ��� ã�� ���� �� ��-�� ����� ���̸� �����Ѵ�.
int longest;
//root�� ��Ʈ�� �ϴ� ����Ʈ��(�� Ʈ���� �κ�Ʈ��)�� ���̸� ��ȯ�Ѵ�.
int height(TreeNode* root) {
	//root�� �� �ڽ��� ��Ʈ�� �ϴ� ����Ʈ���� ���̸� ����Ѵ�.
	vector<int> heights;
	for (int i = 0; i < root->children.size(); i++)
		heights.push_back(height(root->children[i]));
	//���� �ڽ��� �ϳ��� ���ٸ� 0�� ��ȯ�Ѵ�. (�� ����� ��� Ʈ���� ���̰� 0�̹Ƿ�)
	if (heights.empty()) return 0;
	sort(heights.begin(), heights.end());
	//root�� �ֻ��� ���� �ϴ� ��θ� �������
	//�ڽ��� �ϳ��ۿ� ���� ��Ʈ����� ��� ���̴� '�ڽĳ���� ���� + 1'�̹Ƿ� if���� ������ �� �ִ�.
	if (heights.size() >= 2)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	//Ʈ���� ���̴� ����Ʈ�� ������ �ִ�ġ�� 1�� ���� ����Ѵ�.
	return heights.back() + 1;
}
//�� ���(���� �� ����-�� ���& ���� �� ��-�� ���) ������ ���� �� ����� ���̸� ����Ѵ�.
int solve(TreeNode* root) {
	longest = 0;
	//Ʈ���� ���̿� �ִ� ��-�� ��� ���� �� ū ���� �����Ѵ�.
	//h = ��ü Ʈ���� ���� = ���� �� ����-�� ���
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