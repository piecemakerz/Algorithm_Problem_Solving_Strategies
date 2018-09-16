#include <cstring>
#include <vector>
#include <queue>
using namespace std;

//Ʈ������ ��带 ǥ���ϴ� ��ü�� ����

//���ĺ� �빮�ڸ� �����ϴ� ��� �� ���� 26���� �ڼ��� ���� �� �ִ�.
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }
//Ʈ������ �� ��带 ��Ÿ���� ��ü
struct TrieNode {
	TrieNode* children[ALPHABETS], * next[ALPHABETS];
	//�� ��ġ���� ������ ���ڿ��� ��ȣ
	int terminal, no;
	//���� ����: �� ��忡�� ��Ī�� �������� �� �� ������ ���� ����Ѵ�.
	//�� ��忡 �����Ǵ� ���ڿ��� ���̻��̸鼭 Ʈ���̿� ���Ե� �ִ� ���ڿ�
	TrieNode* fail;
	//��� ���ڿ� ���: �� ��尡 �湮�Ǿ��� �� �����ϴ� �ٴ� ���ڿ����� ��ȣ
	vector<int> output;
	TrieNode() : terminal(false) {
		memset(children, 0, sizeof(children));
		memset(next, 0, sizeof(next));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}

	//�� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ���ڿ� key�� �߰��Ѵ�.
	void insert(const char* key) {
		//���ڿ��� ������ terminal�� ������ �ٲٰ� ����
		if (*key == 0)
			terminal = true;
		else {
			int next = toNumber(*key);
			//�ش� �ڽ� ��尡 ���ٸ� �����Ѵ�.
			if (children[next] == NULL)
				children[next] = new TrieNode();
			//�ش� �ڽ� ���� ��� ȣ��
			children[next]->insert(key + 1);
		}
	}
	//�� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ���ڿ� key�� �����Ǵ� ��带 ã�´�.
	//������ NULL�� ��ȯ�Ѵ�.
	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
};

//Ʈ���̰� �־��� �� �� ��忡 ���� ���� ����� ��� ���ڿ� ����� ����Ѵ�.
void computeFailFunc(TrieNode* root) {
	//��Ʈ�������� ������ �� �ܰ辿 �Ʒ��� �������� �� ����� ���� ������ ����Ѵ�.
	queue<TrieNode*> q;
	//��Ʈ�� ���� ������ �ڱ� �ڽ�
	root->fail = root;
	q.push(root);
	while (!q.empty()) {
		TrieNode* here = q.front();
		q.pop();
		//here�� ��� �ڼտ� ���� ���� ������ ����ϰ� �̵��� ť�� �ִ´�.
		//child�� ���� ���ڿ� ¤���� ���ڿ��� ������ �� �����ϴ� ��쿡 ���� 
		//���� ������ ����Ѵ�.
		for (int edge = 0; edge < ALPHABETS; edge++) {
			TrieNode* child = here->children[edge];
			if (!child) continue;
			//1���� ����� ���� ������ �׻� ��Ʈ
			if (here == root)
				child->fail = root;
			else {
				//�ƴ� ��� �θ��� ���� ������ ���󰡸鼭 ���� ������ ã�´�.
				TrieNode* t = here->fail;
				while (t != root && t->children[edge] == NULL)
					t = t->fail;
				if (t->children[edge]) t = t->children[edge];
				child->fail = t;
			}
			//��� ���ڿ� ���: ���� ������ ���� ��忡�� �����ؿ� ��,
			//�� ��ġ���� ������ �ٴ� ���ڿ��� ������ �߰��Ѵ�.
			child->output = child->fail->output;
			if (child->terminal != -1)
				child->output.push_back(child->terminal);
			q.push(child);
		}
	}
}

//���������� ������ �ذ��ϴ� å�� ���� ��ȹ�� �˰���

const int MOD = 10007;
int cache[101][1001];

//������ length ���ڸ� �� ������ �ϴµ�, ��ȣ-�ڶ�� �˰�����
//���� ���°� state�� �־��� �� IDS�� �ɸ��� �ʴ� ���ڿ��� ����?
int count(int length, TrieNode* state) {
	//���� ���: �� ���¿��� ���ڿ��� �����ϸ� ���� ����
	if (state->output.size()) return 0;
	//���� ���: ���ڿ��� ���� ���� ���
	if (length == 0) return 1;
	int& ret = cache[length][state->no];
	if (ret != -1) return ret;
	ret = 0;
	//�������� letter ���ڸ� ���� ���
	for (int letter = 0; letter < ALPHABETS; letter++) {
		ret += count(length - 1, state->next[letter]);
		ret %= MOD;
	}
	return ret;
}

//Ʈ������ �� ��忡 no�� next ���̺��� ����ϴ� ��� �Լ��� ����

//���� ���� ���� ���̺��� next[]�� ä���. computeFailFunc()�� ����
//�̹� ���� �Լ��� ���Ǿ� �ִٰ� �����Ѵ�.
void computeTransition(TrieNode* here, int& nodeCounter) {
	//0���� �����ϴ� ��ȣ�� �ű��: cache[]�� �ε���
	here->no = nodeCounter++;
	//here �ڿ� ���� chr�� �ٿ��� �� ��� ���·� ���°�?
	for (int chr = 0; chr < ALPHABETS; chr++) {
		//next[] ���� ����� �����Ѵ�.
		TrieNode* next = here;
		while (next != next->fail && next->children[chr] == NULL)
			next = next->fail;
		if (next->children[chr]) next = next->children[chr];
		here->next[chr] = next;
		//��������� ��� ��忡 ���� ���� ���̺��� ����Ѵ�.
		if (here->children[chr])
			computeTransition(here->children[chr], nodeCounter);
	}
}