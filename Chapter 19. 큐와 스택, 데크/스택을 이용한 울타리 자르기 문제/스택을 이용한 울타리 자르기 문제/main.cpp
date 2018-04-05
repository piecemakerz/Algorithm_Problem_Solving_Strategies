#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

//�� ������ ���̸� �����ϴ� �迭
vector<int> h;
//������ ����� O(n) �ع�
int solveStack() {
	//���� �ִ� ����(right�� �������� ���� ����)���� ��ġ���� �����Ѵ�.
	//���� �մ� ���ڵ��� right�� �����Ƿ��� 
	//���� Ȯ���ϴ� ������ ���̰� ���� �ִ� ������ ���̺��� ���ƾ� �Ѵ�.

	//�����ִ� ������ ���̿� ���� Ȯ���ϴ� ������ ���̰� ���� ���
	//�����ִ� ������ �ִ� �簢���� ���� Ȯ���ϴ� ������ �ִ� �簢���� ��ġ�ϹǷ�
	//����� �ʿ� ���� �� ���ڸ� �����ִ� ���� ���ÿ��� �����Ѵ�.
	stack<int> remaining;
	h.push_back(0); // h�� ������ ���� ���̰� 0�� ������ ���� �߰�
	int ret = 0;
	for (int i = 0; i < h.size(); i++) {
		//���� ���ڿ� ���� �ִ� ��� ���ڵ� ���� ��
		//���� �ִ� ���ڵ� �� ������ �� ����(j=remaining.top())�� h[i]���� ���ٸ�
		//�� ������ �ִ� �簢���� i���� ������. (right[j] = i)
		while (!remaining.empty() && h[remaining.top()] >= h[i]) {
			int j = remaining.top(); // ���� ���� ���� ��� ��������
			remaining.pop(); // ���� ���� ���� ��� ����
			int width = -1;
			//j��° ���� ���ʿ� ���ڰ� �ϳ��� �� ���� �ִ� ��� left[j] = -1,
			//�ƴ� ��� left[j] = ���� �ִ� ���� �� ���� �����ʿ� �ִ� ������ ��ȣ
			//�� �ȴ�.
			if (remaining.empty())
				width = i;
			else
				width = (i - remaining.top() - 1);
			ret = max(ret, h[j] * width); // �ִ� �簢�� ���� ����
		}
		remaining.push(i); // ���� ���ڸ� ���� �ִ� ���ڿ� �߰��Ѵ�.
	}
	return ret;
}