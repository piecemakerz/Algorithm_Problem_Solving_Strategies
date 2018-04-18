//B트리는 이진 트리가 항상 균형을 이루게 함으로써 검색 시간을 줄인, 잎마디들의 깊이를 같게 유지해주는 균형잡힌 이진 트리이다.
//B트리에서 데이터를 삽입할 때는 위치 결정과 더불어 트리를 balance 상태로 유지하기 위한 '재구성'단계가 추가로 필요하다.

//B트리는 이진 트리와 달리 여러 데이터를 가진다.
//한 노드에 최대 M개의 자료가 배치될 수 있으면 M차 B트리라고 한다.
//M이 짝수냐 홀수냐에 따라 알고리즘이 상당히 다르다.
//2-3 트리는 2차 B트리와 같은 것이고, 2-3-4 트리는 3차 B트리와 같다.

//<B트리의 규칙>
//1. 노드의 데이터 수가 N이면 자식의 수는 항상 N+1이어야 한다. 
//(ex.노드가 두 개의 데이터를 가진다면 그 노드의 자식은 반드시 3개여야 한다.
//2. 노드내의 데이터는 반드시 정렬된 상태여야 한다.
//3. 노드 D의 왼쪽 서브트리는 D의 데이터보다 작은 데이터들로 이루어져 있어야 하며,
//D의 오른쪽 서브트리는 D보다 큰 데이터들로 이루어져 있어야 한다. (이진 검색 트리의 성질)
//4. 루트 노트를 제외한 모든 노드는 적어도 M/2개의 데이터를 가지고 있어야 한다.
//(ex. 5차 B트리라면 적어도 2개의 데이터를 가져야함)
//5. 잎노드는 모두 같은 레벨에 존재한다.
//6. 입력 자료는 중복될 수 없다.

//2-3 B트리(2개의 키값, 3개의 포인터)의 구현

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