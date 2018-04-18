//BƮ���� ���� Ʈ���� �׻� ������ �̷�� �����ν� �˻� �ð��� ����, �ٸ������ ���̸� ���� �������ִ� �������� ���� Ʈ���̴�.
//BƮ������ �����͸� ������ ���� ��ġ ������ ���Ҿ� Ʈ���� balance ���·� �����ϱ� ���� '�籸��'�ܰ谡 �߰��� �ʿ��ϴ�.

//BƮ���� ���� Ʈ���� �޸� ���� �����͸� ������.
//�� ��忡 �ִ� M���� �ڷᰡ ��ġ�� �� ������ M�� BƮ����� �Ѵ�.
//M�� ¦���� Ȧ���Ŀ� ���� �˰����� ����� �ٸ���.
//2-3 Ʈ���� 2�� BƮ���� ���� ���̰�, 2-3-4 Ʈ���� 3�� BƮ���� ����.

//<BƮ���� ��Ģ>
//1. ����� ������ ���� N�̸� �ڽ��� ���� �׻� N+1�̾�� �Ѵ�. 
//(ex.��尡 �� ���� �����͸� �����ٸ� �� ����� �ڽ��� �ݵ�� 3������ �Ѵ�.
//2. ��峻�� �����ʹ� �ݵ�� ���ĵ� ���¿��� �Ѵ�.
//3. ��� D�� ���� ����Ʈ���� D�� �����ͺ��� ���� �����͵�� �̷���� �־�� �ϸ�,
//D�� ������ ����Ʈ���� D���� ū �����͵�� �̷���� �־�� �Ѵ�. (���� �˻� Ʈ���� ����)
//4. ��Ʈ ��Ʈ�� ������ ��� ���� ��� M/2���� �����͸� ������ �־�� �Ѵ�.
//(ex. 5�� BƮ����� ��� 2���� �����͸� ��������)
//5. �ٳ��� ��� ���� ������ �����Ѵ�.
//6. �Է� �ڷ�� �ߺ��� �� ����.

//2-3 BƮ��(2���� Ű��, 3���� ������)�� ����

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct Node {
public:
	int data[2];
	Node * parent;
	Node * children[3];
	Node(int inputdata) {
		data[0] = inputdata;
		data[1] = -1;
		children[0] = children[1] = children[2] = NULL;
	}
} Node;

bool isLeaf(Node * node) {
	return node->children[0] == NULL;
}

bool isOverflowed(Node * node) {
	return (node->data[0] != -1 && node->data[1] != -1);
}

void insert(Node * Tree, int data) {
	Node * curNode = Tree;
	Node * prevNode;

	while (!isLeaf(curNode)) {
		prevNode = curNode;

		if (curNode->data[0] > data)
			curNode = Tree->children[0];

		else if (curNode->data[0] < data)
			if (curNode->data[1] > data)
				curNode = Tree->children[1];
			else
				curNode = Tree->children[2];
	}

	if (!isOverflowed(curNode)) {
		curNode->data[1] = data;
	}
	else {
		vector<int> nodeData;
		nodeData.push_back(curNode->data[0]);
		nodeData.push_back(curNode->data[1]);
		nodeData.push_back(data);
		sort(nodeData.begin(), nodeData.end());

	}

}