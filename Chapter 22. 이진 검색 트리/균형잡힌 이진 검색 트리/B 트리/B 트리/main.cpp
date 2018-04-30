//BƮ���� ���� Ʈ���� �׻� ������ �̷�� �����ν� �˻� �ð��� ����, �ٸ������ ���̸� ���� �������ִ� �������� ���� Ʈ���̴�.
//BƮ������ �����͸� ������ ���� ��ġ ������ ���Ҿ� Ʈ���� balance ���·� �����ϱ� ���� '�籸��'�ܰ谡 �߰��� �ʿ��ϴ�.

//BƮ���� ���� Ʈ���� �޸� ���� �����͸� ������.
//���� ��尡 �ƴ� ��尡 �ִ� M���� �ڽ� ��带 ���� �� ���� �� M�� BƮ����� �Ѵ�.
//(BƮ���� ������ ��� �����ϴ��Ŀ� ���� �޶����µ�, ��尡 �ִ� M���� �����͸� ���� ��
//���� �� M�� BƮ����� �����ϱ⵵ �Ѵ�.)
//2-3 Ʈ���� 3�� BƮ���� ���� ���̰�, 2-3-4 Ʈ���� 4�� BƮ���� ����.

//<M�� BƮ���� ��Ģ>
//1. ��� ���� �ִ� M���� �ڽ� ��带 ���� �� �ִ�.
//2. ���� ��尡 �ƴ� ��� ���(��Ʈ ����)���� ��� (M/2, �ø�)���� �ڽĳ�带 ������.
//3. ��Ʈ ���� ���� ��尡 �ƴ� ��� ��� 2���� �ڽĳ�带 ������.
//4. ���� ��尡 �ƴ� ��� ���� k���� �ڽĳ��� k-1���� �����͸� ������.
//5. ��� �������� ���� ������ �����Ѵ�.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int M;
int MAX; // �� ��尡 ���� �� �ִ� �ִ� ������
int MIN; // �� ��尡 ���� �� �ִ� �ּ� ������

typedef struct Node {
public:
	vector<int> data;
	vector<Node*> children;
	Node * parent;
	int count; // ���� �������� ��

	Node(int inputdata) {
		//overflow�� ������ ���� �迭���� ũ�⸦ �ϳ��� �� ũ�� ��´�.
		data.resize(MAX + 1, -1);
		children.resize(MAX + 2, NULL);
		data[0] = inputdata;
		for (int i = 1; i < data.size(); i++)
			data[i] = -1;
		for (int i = 0; i < children.size(); i++)
			children[i] = NULL;
		count = 1;
	}

	bool isLeaf() {
		return children[0] == NULL;
	}
	
	//���� ��尡 overflow�������� Ȯ��
	bool isOverflowed() {
		return count > MAX;
	}
	
	//���� ��尡 underflow�������� Ȯ��
	bool isUnderflowed() {
		return (count < MIN) && (parent != NULL);
	}

	//�����͸� �ϳ� �������� �� underflow�� �Ǵ��� Ȯ��
	bool canUnderflow() {
		return count <= MIN;
	}
	
	//������ �ϳ��� �ٸ� ��忡�� �൵ ��� �ּ� ������ ���� ������ �ִٸ�
	bool canGiveData() {
		return count > MIN;
	}
	Node * leftChildOf(int idx) {
		return children[idx];
	}
	Node* rightChildOf(int idx) {
		return children[idx + 1];
	}

	//���� ��带 ���� �ڽ����� ������ �θ� ����� ������ �ε����� ��ȯ�Ѵ�.
	//�θ� ��尡 �������� �ʴ´ٸ� -1�� ��ȯ�Ѵ�.
	int leftParentIdx() {
		if(parent != NULL)
			for (int i = 0; i < parent->count; i++) {
				if (parent->children[i] == this)
					return i;
			}
		return -1;		
	}
	//���� ��带 ������ �ڽ����� ������ �θ� ����� ������ �ε����� ��ȯ�Ѵ�.
	int rightParentIdx() {
		if (parent != NULL)
			for (int i = 0; i < parent->count; i++) {
				if (parent->children[i + 1] == this)
					return i;
			}
		return -1;
	}

	//�ش� �����͸� ������ �ִ� �迭 �ε����� ��ȯ�Ѵ�.
	//�����Ͱ� ���ٸ� -1�� ��ȯ�Ѵ�.
	int findData(int searchData) {
		for (int i = 0; i < count; i++)
			if (data[i] == searchData)
				return i;
		return -1;
	}

	//������ ������ ���� ��忡 �����͸� ���� �����ϴ� ����
	//Ʈ�� ������ �� ����� �߰����� �θ� ��忡 �����ϴ� ��츸 �����Ѵ�.
	//��� ���� ���ο� �������� ��ġ(index)�� �����Ѵ�.
	int insertData(int inputData, Node * leftTree, Node * rightTree) {
		int i = count - 1;
		while (i >= 0 && data[i] > inputData) {
			data[i + 1] = data[i];
			children[i + 2] = children[i + 1];
			i--;
		}
		i++;
		data[i] = inputData;
		children[i] = leftTree, children[i + 1] = rightTree;
		count++;
		return i;
	}

	//������ �����Ͱ� ��忡 ���ų� ���� �Ŀ� �ش� ��忡�� underflow�� �߻��Ѵٸ� false�� ��ȯ�Ѵ�.
	bool deleteData(int delData) {
		int idx = findData(delData);
		if (idx == -1)
			return false;

		else {
			int i = idx + 1;
			if (idx == 0)
				children[0] = NULL;
			for (; i < count; i++) {
				data[i - 1] = data[i];
				children[i] = children[i + 1];
			}
		}

		children[count] = NULL;
		data[count-1] = -1;
		count--;

		if (isUnderflowed())
			return false;

		return true;
	}

	//data[idx]�� ���ĳ�� ����. ���ĳ�带 ã�� ���� ������ ��尡 ������尡
	//�ƴ� ���ۿ� ������, ������尡 �ƴ� BƮ���� ���� ���� �����Ϳ� ���� ����
	//�ڽİ� ������ �ڽ��� ��� �����Ѵ�. ���� data[idx]�� ���ĳ�尡 �������� �ʴ�
	//��쿡 ���� ����ó���� ���� �ʾƵ� �ȴ�.
	Node* findSuccessor(int idx) {
		Node * successor = children[idx + 1];
		while (!successor->isLeaf()) {
			successor = successor->children[0];
		}
		return successor;
	}
} Node;

Node * root;

//data�� ������ �ִ� ��带 ��ȯ�Ѵ�.
//data�� ������ �ִ� ��尡 ���ٸ� NULL�� ��ȯ�Ѵ�.
//���� ����� data�迭�� ���鼭 �Է� �����ͺ��� ū ���� ����
//�迭�� ���� �ڽ� ��带 �˻��Ѵ�.
Node *  searchNode(int data) {
	Node * curNode = root;
	while (curNode != NULL) {
		int idx = curNode->findData(data);
		if (idx != -1)
			return curNode;
		int childIdx = 0;
		for (; childIdx < curNode->count; childIdx++) {
			if (data < curNode->data[childIdx]) break;
		}
		curNode = curNode->children[childIdx];
	}
	return NULL;
}

//Ʈ�� ����
//�����÷ο찡 �߻��� node�� �� ���� Ʈ���� �����Ѵ�. ������ �� Ʈ���� ���� �θ� �����
//parentData �� ���� ���� �ڽ�, ������ �ڽ��� �Ǹ�, node�� ��� ���� �θ� ��忡 ���Եȴ�.
//���� �� node�� �θ� ��带 ��ȯ�Ѵ�.
Node* nodeSplit(Node * node) {
	int median;
	if ((node->count) % 2 == 0)
		median = ((node->count) / 2) - 1;
	else
		median = (node->count) / 2;

	int medianData = node->data[median];
	Node * LTree = node;
	Node * RTree = new Node(node->data[median+1]);
	RTree->children[0] = node->leftChildOf(median+1);
	RTree->children[1] = node->rightChildOf(median+1);
	if(RTree->children[0] != NULL)
		RTree->children[0]->parent = RTree;
	if(RTree->children[1] != NULL)
		RTree->children[1]->parent = RTree;

	for (int i = median + 2; i < node->count; i++) {
		RTree->insertData(node->data[i], RTree->children[RTree->count], node->rightChildOf(i));
		if(RTree->children[i-median] != NULL)
			RTree->children[i - median]->parent = RTree;
	}

	if (node == root) {
		root = new Node(medianData);
		LTree->parent = root;
		RTree->parent = root;
		root->children[0] = LTree;
		root->children[1] = RTree;
	}
	else {
		node->parent->insertData(medianData, LTree, RTree);
		LTree->parent = node->parent;
		RTree->parent = node->parent;
	}
	vector<int> deleteNode;	
	for (int i = median; i < node->count; i++)
		deleteNode.push_back(node->data[i]);

	for(int i=0; i<deleteNode.size(); i++)
		LTree->deleteData(deleteNode[i]);

	return node->parent;
}

//BƮ���� ����
//BƮ������ ��� ������ ���� ��忡�� �̷������.
//���� ��尡 �� ���� �ʾҴٸ� �ܼ��� ���� ��忡 �����ϸ�,
//�� á�ٸ� Ʈ���� �������Ѵ�.
void insertData(int data) {
	Node * curNode = root;
	if (root == NULL) {
		root = new Node(data);
		return;
	}
	//���� ��尡 ���� ��尡 �� ������ �ݺ��ϸ�,
	//���� ��忡�� ã�� �����ͺ��� �� ū ���� ������ �������� ���� �ڽ����� �̵��Ѵ�.
	while (!curNode->isLeaf()) {
		int childIdx = 0;
		for (; childIdx < curNode->count; childIdx++) {
			if (data < curNode->data[childIdx]) break;
		}
		curNode = curNode->children[childIdx];
	}
	//������忡 ������ ����
	curNode->insertData(data, NULL, NULL);
	//�����÷ο찡 �߻��Ѵٸ� Ʈ���� ������ ���ش�.
	//�� �̻� �����÷ο찡 �߻����� ���� ������ ����Ѵ�.
	while (curNode->isOverflowed()) {
		curNode = nodeSplit(curNode);
	}
}

//BƮ�������� ������ ����
void deleteData(int data) {
	bool needsRebalancing = false;
	//delNode�� ������ �����Ͱ� �ִ� ��带 ����Ű��, 
	//������ ���������� underflow�� �߻��ϴ� �����͸� ����Ű�⵵ �Ѵ�.
	Node * delNode = searchNode(data);
	if (delNode == NULL)
		return;
	int delIdx = delNode->findData(data);

	//delNode�� ��������� ��
	if (delNode->isLeaf()) {
		//���� �� delNode���� underflow�� �߻��ϸ� ������ ������ ��ģ��.
		if(!delNode->deleteData(delNode->data[delIdx]))
			needsRebalancing = true;
	}

	//delNode�� ������尡 �ƴ� ��
	else{
		//���ĳ���� ���� ���� �����͸� delIdx�� ���ҷ� ��ü�Ѵ�.
		Node * successor = delNode->findSuccessor(delIdx);
		delNode->data[delIdx] = successor->data[0];
		//���� �� ���ĳ�忡�� underflow�� �߻��ϸ� ������ ������ ��ģ��.
		if (!successor->deleteData(successor->data[0]))
			needsRebalancing = true;

		delNode = successor;
	}

	Node * underflowNode = delNode;
	//underflow�� �߻��Ѵٸ� '������' ��忡������ Ʈ�� �������� �����Ѵ�.
	//delNode�� �ڽĵ��� ��� ���ĵ� �����̱� ������ �ǵ帮�� �ʴ´�.
	while (needsRebalancing) {
		cout << "underflow occured" << endl;

		Node * sibling;
		Node * parent = underflowNode->parent;
		int seperator = underflowNode->leftParentIdx();

		//���� '������' ����� ������ ������ �����ϸ� ������ ������尡 underflow�� ���ɼ��� ���ٸ�
		if (seperator != -1 && parent->rightChildOf(seperator) != NULL && parent->rightChildOf(seperator)->canGiveData()) {
			cout << "right sibling exists" << endl;
			sibling = parent->rightChildOf(seperator);
			cout << "sibling node: ";
			for (int i = 0; i < sibling->count; i++)
				cout << sibling->data[i] << ' ';
			cout << endl;
			//���� ȸ���� �Ѵ�.
			//seperator�� '������ ���'�� ���� �����Ѵ�.
			//������ ������ �� ó�� �ڽ��� ������ seperator�� ������ �ڽ��� �ǵ��� �Ѵ�.
			underflowNode->insertData(parent->data[seperator], underflowNode->children[underflowNode->count], sibling->children.front());
			if (underflowNode->children[underflowNode->count] != NULL)
				underflowNode->children[underflowNode->count]->parent = underflowNode;
			//������ ������ �� �� ���Ҹ� seperator��ġ�� �����Ѵ�.
			parent->data[seperator] = sibling->data[0];
			//������ ���� ��忡�� �� �� �����͸� �����Ѵ�. �� ���� underflow�� ���ɼ��� �����Ƿ�
			//�����ص� BƮ���� ������ Ʋ������ �ʴ´�.
			cout << "Fixed underflowNode Node: " << endl;
			for (int i = 0; i < underflowNode->count; i++)
				cout << underflowNode->data[i] << ' ';
			cout << endl;
			sibling->deleteData(sibling->data[0]);
			needsRebalancing = false;
			break;
		}
		seperator = underflowNode->rightParentIdx();
		//���� '������' ����� ���� ������ �����ϸ� ���� ������尡 underflow�� ���ɼ��� ���ٸ�
		if (seperator != -1 && parent->leftChildOf(seperator) != NULL && parent->leftChildOf(seperator)->canGiveData()) {
			cout << "left sibling exists" << endl;
			sibling = parent->leftChildOf(seperator);
			cout << "sibling node: ";
			for (int i = 0; i < sibling->count; i++)
				cout << sibling->data[i] << ' ';
			cout << endl;
			//������ ȸ���� �Ѵ�.
			//seperator�� '������ ���'�� �� �տ� �����Ѵ�.
			//���� ������ �� ������ �ڽ��� ������ seperator�� ���� �ڽ��� �ǵ��� �Ѵ�.
			underflowNode->insertData(parent->data[seperator], sibling->children[sibling->count], underflowNode->children[1]);
			if(underflowNode->children[0] != NULL)
				underflowNode->children[0]->parent = underflowNode;
			//���� ������ ������ �����͸� seperator��ġ�� �����Ѵ�.
			parent->data[seperator] = sibling->data[(sibling->count)-1];
			//���� ���� ��忡�� ������ �����͸� �����Ѵ�. �� ���� underflow�� ���ɼ��� �����Ƿ�
			//�����ص� BƮ���� ������ Ʋ������ �ʴ´�.
			cout << "Fixed underflowNode Node: " << endl;
			for (int i = 0; i < underflowNode->count; i++)
				cout << underflowNode->data[i] << ' ';
			cout << endl;
			sibling->deleteData(sibling->data[(sibling->count)-1]);
			needsRebalancing = false;
			break;
		}
		cout << "left sibling and right sibling has no enough data" << endl;
		//���� ���� �������� ������ ������� ��ο��� �����͸� ������ '������ ���'�� ä������ �� ���ٸ�
		Node * leftTree, * rightTree;
		//���� ������尡 ������ �� leftTree�� ���� ���� ���, rightTree�� ���� ��带 ����Ų��.
		if (underflowNode->rightParentIdx() != -1) {
			seperator = underflowNode->rightParentIdx();
			leftTree = parent->children[seperator];
			rightTree = underflowNode;
		}
		//�������� �ʴ´ٸ� leftTree�� ���� ���, rightTree�� ������ ���� ��带 ����Ų��.
		else {
			seperator = underflowNode->leftParentIdx();
			leftTree = underflowNode;
			rightTree = parent->children[seperator+1];
		}
		cout << "left Tree : ";
		for (int i = 0; i < leftTree->count; i++) {
			cout << leftTree->data[i] << ' ';
		}
		cout << endl;
		cout << "right Tree: ";
		for (int i = 0; i < rightTree->count; i++) {
			cout << rightTree->data[i] << ' ';
		}
		cout << endl;
		//seperator�� �����͸� ���� Ʈ���� ���� �����Ѵ�.
		leftTree->insertData(parent->data[seperator], leftTree->children[leftTree->count], NULL);
		//������ Ʈ���� ��� �����͸� ���� Ʈ���� �ű��. 
		for (int i = 0; i < rightTree->count; i++) {
			leftTree->insertData(rightTree->data[i], rightTree->children[i], rightTree->children[i + 1]);
			if(rightTree->children[i] != NULL)
				rightTree->children[i]->parent = leftTree;
			if(rightTree->children[i] != NULL)
				rightTree->children[i + 1]->parent = leftTree;
		}
		//���� ���� Ʈ�� ���� '������' ���¿��� ����� �ȴ�.
		//seperator�� �����͸� �����ϰ� �� ������ ��带 �����Ѵ�.
		delete(rightTree);
		Node * saveEmptyLeft = parent->children[0];
		parent->data[seperator] = parent->data[seperator + 1];
		for (int idx = seperator + 1; idx < parent->count; idx++) {
			parent->data[idx] = parent->data[idx + 1];
			parent->children[idx] = parent->children[idx + 1];
		}

		parent->children[parent->count] = NULL;
		parent->data[(parent->count) - 1] = -1;
		parent->count--;
		cout << "left tree after fixed : ";
		for (int i = 0; i < leftTree->count; i++) {
			cout << leftTree->data[i] << ' ';
		}
		cout << endl;
		cout << "parent tree after delete : ";
		for (int i = 0; i < parent->count; i++) {
			cout << parent->data[i] <<' ';
		}
		cout << endl;
		underflowNode = parent;
		
		if (underflowNode == root) {
			//���� ���ο� underflow ��尡 ��Ʈ ����̰� �����Ͱ� �ϳ��� ���ٸ�
			//��Ʈ ��带 ������ ���� ��ü�Ѵ�. (������ ���� '������' ���ɼ��� ���� ����̴�)
			if (underflowNode->count == 0) {
				cout << "root has no node.";
				//���� ��ü Ʈ���� ����ٸ� root�� NULL�� �ٲ۴�.
				if (underflowNode->children[0] == NULL) {
					cout << "Tree is totally empty" << endl;
					delete(underflowNode);
					root = NULL;
					break;
				}

				cout << "changing root to left Tree : ";
				root = saveEmptyLeft;
				for (int i = 0; i < root->count; i++) {
					cout << root->data[i] << ' ';
				}
				cout << endl;
				root->parent = NULL;
				delete(underflowNode);
				needsRebalancing = false;
				break;
			}
			else {
				needsRebalancing = false;
				break;
			}
		}
		//���� ���ο� underflow ��忡�� underflow�� �߻��Ѵٸ� merge�� �ݺ��Ѵ�.
		if (!underflowNode->isUnderflowed()) {
			needsRebalancing = false;
			break;
		}
	}
}

//������ȸ ���
void printTree(Node * Tree)
{
	if (Tree == NULL) return;
	int idx = 0;
	for (; idx < Tree->count; idx++) {
		//if(Tree->children[idx]!=NULL)
			//cout << "childrend[" << idx << "]: ";
		printTree(Tree->children[idx]);
		//cout << "data[" << idx << "]: ";
		cout << Tree->data[idx] << ' ';
		//cout << endl;
	}
	//if(Tree->children[idx]!=NULL)
		//cout << "childrend[" << idx << "]: ";
	printTree(Tree->children[idx]);
}

int main(void) {
	root = NULL;
	int data;
	cout << "����: ";
	cin >> M;
	MAX = M - 1, MIN = ceil(M / 2.0)-1;
	cout << "MAX data: " << MAX << ", MIN data: " << MIN << endl;
	cout << "insert Data" << endl;
	while (true) {
		cin >> data;
		if (data == -1)
			break;
		insertData(data);
		printTree(root);
		cout << endl;
	}
	cout << "delete Data" << endl;
	while(true) {
		if (root == NULL)
			break;
		cin >> data;
		if (data == -1)
			break;
		deleteData(data);
		printTree(root);
		cout << endl;
		cout << "root: ";
		for (int i = 0; i < root->count; i++)
			cout << root->data[i] << ' ';
		cout << endl;
	}
	return 0;
}