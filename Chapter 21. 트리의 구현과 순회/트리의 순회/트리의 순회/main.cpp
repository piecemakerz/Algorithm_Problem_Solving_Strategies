#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

//Ʈ���� ��带 ǥ���ϴ� ��ü�� ����
struct TreeNode {
	string label; //������ �ڷ�
	TreeNode * parent; //�θ� ��带 ����Ű�� ������
	vector<TreeNode*> children; //�ڼ� ������ ����Ű�� �������� �迭
};

//Ʈ���� ��ȸ�ϸ� ��� ��忡 ���Ե� ���� ����ϱ�
//�־��� Ʈ���� �� ��忡 ����� ���� ��� ����Ѵ�.
void printLabels(TreeNode* root) {
	//��Ʈ�� ����� ���� ����Ѵ�.
	cout << root->label << endl;
	//�� �ڼյ��� ��Ʈ�� �ϴ� ����Ʈ���� ���Ե� ������ ��������� ����Ѵ�.
	for (int i = 0; i < root->children.size(); i++)
		printLabels(root->children[i]);
}

//��ȸ�� �̿��� Ʈ���� ���̸� ����ϱ�
//root�� ��Ʈ�� �ϴ� Ʈ���� ���̸� ���Ѵ�.
int height(TreeNode* root) {
	int h = 0;
	for (int i = 0; i < root->children.size(); i++)
		h = max(h, 1 + height(root->children[i]));
}