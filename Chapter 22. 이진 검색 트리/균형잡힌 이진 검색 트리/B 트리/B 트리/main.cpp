//B트리는 이진 트리가 항상 균형을 이루게 함으로써 검색 시간을 줄인, 잎마디들의 깊이를 같게 유지해주는 균형잡힌 이진 트리이다.
//B트리에서 데이터를 삽입할 때는 위치 결정과 더불어 트리를 balance 상태로 유지하기 위한 '재구성'단계가 추가로 필요하다.

//B트리는 이진 트리와 달리 여러 데이터를 가진다.
//리프 노드가 아닌 노드가 최대 M개의 자식 노드를 가질 수 있을 때 M차 B트리라고 한다.
//(B트리의 차수는 어떻게 정의하느냐에 따라 달라지는데, 노드가 최대 M개의 데이터를 가질 수
//있을 때 M차 B트리라고 정의하기도 한다.)
//2-3 트리는 3차 B트리와 같은 것이고, 2-3-4 트리는 4차 B트리와 같다.

//<M차 B트리의 규칙>
//1. 모든 노드는 최대 M개의 자식 노드를 가질 수 있다.
//2. 리프 노드가 아닌 모든 노드(루트 제외)들은 적어도 (M/2, 올림)개의 자식노드를 가진다.
//3. 루트 노드는 리프 노드가 아닐 경우 적어도 2개의 자식노드를 가진다.
//4. 리프 노드가 아닌 모든 노드는 k개의 자식노드와 k-1개의 데이터를 가진다.
//5. 모든 리프노드는 같은 레벨에 존재한다.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int M;
int MAX; // 한 노드가 가질 수 있는 최대 데이터
int MIN; // 한 노드가 가질 수 있는 최소 데이터

typedef struct Node {
public:
	vector<int> data;
	vector<Node*> children;
	Node * parent;
	int count; // 현재 데이터의 수

	Node(int inputdata) {
		//overflow의 구현을 위해 배열들의 크기를 하나씩 더 크게 잡는다.
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
	
	//현재 노드가 overflow상태인지 확인
	bool isOverflowed() {
		return count > MAX;
	}
	
	//현재 노드가 underflow상태인지 확인
	bool isUnderflowed() {
		return (count < MIN) && (parent != NULL);
	}

	//데이터를 하나 제거했을 때 underflow가 되는지 확인
	bool canUnderflow() {
		return count <= MIN;
	}
	
	//데이터 하나를 다른 노드에게 줘도 적어도 최소 데이터 수를 가지고 있다면
	bool canGiveData() {
		return count > MIN;
	}
	Node * leftChildOf(int idx) {
		return children[idx];
	}
	Node* rightChildOf(int idx) {
		return children[idx + 1];
	}

	//현재 노드를 왼쪽 자식으로 가지는 부모 노드의 데이터 인덱스를 반환한다.
	//부모 노드가 존재하지 않는다면 -1을 반환한다.
	int leftParentIdx() {
		if(parent != NULL)
			for (int i = 0; i < parent->count; i++) {
				if (parent->children[i] == this)
					return i;
			}
		return -1;		
	}
	//현재 노드를 오른쪽 자식으로 가지는 부모 노드의 데이터 인덱스를 반환한다.
	int rightParentIdx() {
		if (parent != NULL)
			for (int i = 0; i < parent->count; i++) {
				if (parent->children[i + 1] == this)
					return i;
			}
		return -1;
	}

	//해당 데이터를 가지고 있는 배열 인덱스를 반환한다.
	//데이터가 없다면 -1을 반환한다.
	int findData(int searchData) {
		for (int i = 0; i < count; i++)
			if (data[i] == searchData)
				return i;
		return -1;
	}

	//데이터 삽입은 리프 노드에 데이터를 직접 삽입하는 경우와
	//트리 재조정 시 노드의 중간값을 부모 노드에 삽입하는 경우만 간주한다.
	//노드 상의 새로운 데이터의 위치(index)를 리턴한다.
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

	//삭제할 데이터가 노드에 없거나 삭제 후에 해당 노드에서 underflow가 발생한다면 false를 반환한다.
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

	//data[idx]의 직후노드 리턴. 직후노드를 찾는 경우는 삭제할 노드가 리프노드가
	//아닐 경우밖에 없으며, 리프노드가 아닌 B트리의 노드는 각각 데이터에 대한 왼쪽
	//자식과 오른쪽 자식이 모두 존재한다. 따라서 data[idx]의 직후노드가 존재하지 않는
	//경우에 대한 예외처리를 하지 않아도 된다.
	Node* findSuccessor(int idx) {
		Node * successor = children[idx + 1];
		while (!successor->isLeaf()) {
			successor = successor->children[0];
		}
		return successor;
	}
} Node;

Node * root;

//data를 가지고 있는 노드를 반환한다.
//data를 가지고 있는 노드가 없다면 NULL을 반환한다.
//현재 노드의 data배열을 돌면서 입력 데이터보다 큰 값을 가진
//배열의 왼쪽 자식 노드를 검사한다.
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

//트리 분할
//오버플로우가 발생한 node를 두 개의 트리로 분할한다. 분할한 두 트리는 각각 부모 노드의
//parentData 양 옆의 왼쪽 자식, 오른쪽 자식이 되며, node의 가운데 값은 부모 노드에 삽입된다.
//연산 후 node의 부모 노드를 반환한다.
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

//B트리의 삽입
//B트리에서 모든 삽입은 리프 노드에서 이루어진다.
//리프 노드가 꽉 차지 않았다면 단순히 리프 노드에 삽입하며,
//꽉 찼다면 트리를 재조정한다.
void insertData(int data) {
	Node * curNode = root;
	if (root == NULL) {
		root = new Node(data);
		return;
	}
	//현재 노드가 리프 노드가 될 때까지 반복하며,
	//현재 노드에서 찾는 데이터보다 더 큰 값을 가지는 데이터의 왼쪽 자식으로 이동한다.
	while (!curNode->isLeaf()) {
		int childIdx = 0;
		for (; childIdx < curNode->count; childIdx++) {
			if (data < curNode->data[childIdx]) break;
		}
		curNode = curNode->children[childIdx];
	}
	//리프노드에 데이터 삽입
	curNode->insertData(data, NULL, NULL);
	//오버플로우가 발생한다면 트리를 재조정 해준다.
	//더 이상 오버플로우가 발생하지 않을 때까지 재귀한다.
	while (curNode->isOverflowed()) {
		curNode = nodeSplit(curNode);
	}
}

//B트리에서의 데이터 삭제
void deleteData(int data) {
	bool needsRebalancing = false;
	//delNode는 삭제할 데이터가 있는 노드를 가리키며, 
	//재조정 과정에서는 underflow가 발생하는 데이터를 가리키기도 한다.
	Node * delNode = searchNode(data);
	if (delNode == NULL)
		return;
	int delIdx = delNode->findData(data);

	//delNode가 리프노드일 때
	if (delNode->isLeaf()) {
		//삭제 후 delNode에서 underflow가 발생하면 재조정 과정을 거친다.
		if(!delNode->deleteData(delNode->data[delIdx]))
			needsRebalancing = true;
	}

	//delNode가 리프노드가 아닐 때
	else{
		//직후노드의 가장 작은 데이터를 delIdx의 원소로 교체한다.
		Node * successor = delNode->findSuccessor(delIdx);
		delNode->data[delIdx] = successor->data[0];
		//삭제 후 직후노드에서 underflow가 발생하면 재조정 과정을 거친다.
		if (!successor->deleteData(successor->data[0]))
			needsRebalancing = true;

		delNode = successor;
	}

	Node * underflowNode = delNode;
	//underflow가 발생한다면 '부족한' 노드에서부터 트리 재조정을 시작한다.
	//delNode의 자식들은 모두 정렬된 상태이기 때문에 건드리지 않는다.
	while (needsRebalancing) {
		cout << "underflow occured" << endl;

		Node * sibling;
		Node * parent = underflowNode->parent;
		int seperator = underflowNode->leftParentIdx();

		//만약 '부족한' 노드의 오른쪽 형제가 존재하며 오른쪽 형제노드가 underflow될 가능성이 없다면
		if (seperator != -1 && parent->rightChildOf(seperator) != NULL && parent->rightChildOf(seperator)->canGiveData()) {
			cout << "right sibling exists" << endl;
			sibling = parent->rightChildOf(seperator);
			cout << "sibling node: ";
			for (int i = 0; i < sibling->count; i++)
				cout << sibling->data[i] << ' ';
			cout << endl;
			//왼쪽 회전을 한다.
			//seperator를 '부족한 노드'의 끝에 삽입한다.
			//오른쪽 형제의 맨 처음 자식은 삽입한 seperator의 오른쪽 자식이 되도록 한다.
			underflowNode->insertData(parent->data[seperator], underflowNode->children[underflowNode->count], sibling->children.front());
			if (underflowNode->children[underflowNode->count] != NULL)
				underflowNode->children[underflowNode->count]->parent = underflowNode;
			//오른쪽 형제의 맨 앞 원소를 seperator위치에 삽입한다.
			parent->data[seperator] = sibling->data[0];
			//오른쪽 형제 노드에서 맨 앞 데이터를 삭제한다. 이 노드는 underflow될 가능성이 없으므로
			//삭제해도 B트리의 균형이 틀어지지 않는다.
			cout << "Fixed underflowNode Node: " << endl;
			for (int i = 0; i < underflowNode->count; i++)
				cout << underflowNode->data[i] << ' ';
			cout << endl;
			sibling->deleteData(sibling->data[0]);
			needsRebalancing = false;
			break;
		}
		seperator = underflowNode->rightParentIdx();
		//만약 '부족한' 노드의 왼쪽 형제가 존재하며 왼쪽 형제노드가 underflow될 가능성이 없다면
		if (seperator != -1 && parent->leftChildOf(seperator) != NULL && parent->leftChildOf(seperator)->canGiveData()) {
			cout << "left sibling exists" << endl;
			sibling = parent->leftChildOf(seperator);
			cout << "sibling node: ";
			for (int i = 0; i < sibling->count; i++)
				cout << sibling->data[i] << ' ';
			cout << endl;
			//오른쪽 회전을 한다.
			//seperator를 '부족한 노드'의 맨 앞에 삽입한다.
			//왼쪽 형제의 맨 마지막 자식은 삽입한 seperator의 왼쪽 자식이 되도록 한다.
			underflowNode->insertData(parent->data[seperator], sibling->children[sibling->count], underflowNode->children[1]);
			if(underflowNode->children[0] != NULL)
				underflowNode->children[0]->parent = underflowNode;
			//왼쪽 형제의 마지막 데이터를 seperator위치에 삽입한다.
			parent->data[seperator] = sibling->data[(sibling->count)-1];
			//왼쪽 형제 노드에서 마지막 데이터를 삭제한다. 이 노드는 underflow될 가능성이 없으므로
			//삭제해도 B트리의 균형이 틀어지지 않는다.
			cout << "Fixed underflowNode Node: " << endl;
			for (int i = 0; i < underflowNode->count; i++)
				cout << underflowNode->data[i] << ' ';
			cout << endl;
			sibling->deleteData(sibling->data[(sibling->count)-1]);
			needsRebalancing = false;
			break;
		}
		cout << "left sibling and right sibling has no enough data" << endl;
		//만약 왼쪽 형제노드와 오른쪽 형제노드 모두에서 데이터를 가져와 '부족한 노드'에 채워넣을 수 없다면
		Node * leftTree, * rightTree;
		//왼쪽 형제노드가 존재할 때 leftTree는 왼쪽 형제 노드, rightTree는 현재 노드를 가리킨다.
		if (underflowNode->rightParentIdx() != -1) {
			seperator = underflowNode->rightParentIdx();
			leftTree = parent->children[seperator];
			rightTree = underflowNode;
		}
		//존재하지 않는다면 leftTree는 현재 노드, rightTree는 오른쪽 형제 노드를 가리킨다.
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
		//seperator의 데이터를 왼쪽 트리의 끝에 삽입한다.
		leftTree->insertData(parent->data[seperator], leftTree->children[leftTree->count], NULL);
		//오른쪽 트리의 모든 데이터를 왼쪽 트리로 옮긴다. 
		for (int i = 0; i < rightTree->count; i++) {
			leftTree->insertData(rightTree->data[i], rightTree->children[i], rightTree->children[i + 1]);
			if(rightTree->children[i] != NULL)
				rightTree->children[i]->parent = leftTree;
			if(rightTree->children[i] != NULL)
				rightTree->children[i + 1]->parent = leftTree;
		}
		//이후 왼쪽 트리 노드는 '부족한' 상태에서 벗어나게 된다.
		//seperator의 데이터를 삭제하고 빈 오른쪽 노드를 삭제한다.
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
			//만약 새로운 underflow 노드가 루트 노드이고 데이터가 하나도 없다면
			//루트 노드를 병합한 노드로 교체한다. (병합한 노드는 '부족할' 가능성이 없는 노드이다)
			if (underflowNode->count == 0) {
				cout << "root has no node.";
				//만약 전체 트리가 비었다면 root를 NULL로 바꾼다.
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
		//만약 새로운 underflow 노드에서 underflow가 발생한다면 merge를 반복한다.
		if (!underflowNode->isUnderflowed()) {
			needsRebalancing = false;
			break;
		}
	}
}

//중위순회 출력
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
	cout << "차수: ";
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