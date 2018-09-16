#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

const int ALPHABETS = 26;
int C, N, M;

int toNumber(char ch) { return ch - 'A'; }

struct TrieNode {
	TrieNode* children[ALPHABETS], *parent;
	//maxPriority = �ش� ����� �ڽĵ� �� ���� ���� �󵵰� ���� ����� ������
	//�ش� ��忡�� ������ �ܾ��� ���� �󵵵� �����Ѵ�.
	//maxCnt = ���� ���� ���� �󵵸� ������ ������ ��
	//priority = �ش� ��忡�� ������ ���ڰ� ���� ��, �� ������ ���� ��
	//maxIdx = ���� ���� ���� �󵵸� ������ �ڽ��� �ε���. ���� ���� ���� ���� �󵵸�
	//������ �ڽ��� 2�� �̻� ������ �� ���������� ���� �տ� ���� �ڽĳ���� �ε����� ����ȴ�.
	//�ش� ��忡�� ������ �ܾ��� ���� �󵵵� �����Ѵ�.
	int maxPriority, maxCnt, priority, maxIdx;
	TrieNode() : maxIdx(-1), maxPriority(-1), maxCnt(1), priority(0){
		memset(children, 0, sizeof(children));
		parent = this;
	}
	~TrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}

	void insert(const char* key, int priority) {
		if (maxPriority < priority) {
			maxPriority = priority;
			if (*key != 0)
				maxIdx = toNumber(*key);
			maxCnt = 1;
		}
		else if (maxPriority == priority)
			maxCnt++;

		if (*key == 0)
			this->priority = priority;
		else {
			int next = toNumber(*key);
			
			if (children[next] == NULL)
				children[next] = new TrieNode();
			children[next]->parent = this;
			children[next]->insert(key + 1, priority);
		}
	}

	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
};

//�ȳ���, �׸��� ������ ������� ������ �ذ��ϴ� �� �˰���.
//Ʈ���̴� ���λ縦 �������� ����� �ڷᱸ���ӿ��� �ұ��ϰ� ���̻縦
//�������� ������ �ذ��ߴٴ� ���� �����ܺ� �� �ϴ�.
//�ܾ� key�� ��õ�ޱ� ���� Ÿ�����ؾ� �ϴ� ���� ��ȯ�Ѵ�.
//���� key�� ������ ���ٸ�, key�� ���̸� �״�� ��ȯ�Ѵ�.
//�Ʒ����� ���� �ö����, bottom-up ���ٹ��� ����Ͽ���.
int types(TrieNode* root, string key) {
	//typeCnt = �ش� �ܾ ��õ�ޱ� ���� Ÿ�����ؾ� �ϴ� ��
	int typeCnt = key.length();
	//result = �ش� �ܾ ������ ���
	TrieNode* result = root->find(key.c_str());
	//�ش� �ܾ ������ ��ϵǾ� ���� �ʰų� �ܾ��� �Ϻθ�
	//��ϵǾ� ���� ���
	if (result == NULL || !(result->priority))
		return typeCnt;

	//keyPriority = ã������ �ܾ��� ���� ��
	int keyPriority = result->priority;
	TrieNode* prevNode = result;
	result = result->parent;

	//���� Ȯ���ϴ� ����� �ִ� ���� �󵵰� ã������ �ܾ��� ���� �󵵺��� ũ�ٸ�,
	//�� �̻� ã������ �ܾ ��õ���� Ȯ���� �����Ƿ� �ݺ������� ���´�.
	while (result->maxPriority == keyPriority) {
		if (result == root) break;
		
		//���������� �ܾ���� ���������Ƿ� ���� �켱������ �����ٸ�
		//���������� �տ� ���� �ܾ ��õ�� ���̴�.
		if (result->maxCnt > 1)
			if (prevNode != result->children[result->maxIdx])
				break;

		prevNode = result;
		result = result->parent;
		typeCnt--;
	}
	//ã������ �ܾ��� ���̸�ŭ �̹� Ÿ�����ߴٸ� ��Ű�� ���� �ʿ䰡 ����.
	if (typeCnt == key.length())
		return typeCnt;
	return typeCnt + 1;
}

//�ȳ���, �׸��� ������ ������� ������ �ذ��ϴ� å�� Ʈ���� ��� ����

//Ʈ������ �� ��带 ��Ÿ���� ��ü
struct BookTrieNode {
	BookTrieNode* children[ALPHABETS];
	//�� ��忡�� �����ϴ� ���ڿ��� ��ȣ. ������ -1
	int terminal;
	//�� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ���� ���� �߰��� �ܾ��� ��ȣ. -1�� �ʱ�ȭ
	int first;
	BookTrieNode() : terminal(false){
		memset(children, 0, sizeof(children));
	}
	~BookTrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
			if (children[i])
				delete children[i];
	}
	//�� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ��ȣ id�� ���ڿ� key�� �߰��Ѵ�.
	void insert(const char* key, int id) {
		//first�� �켱 ����
		if (first == -1) first = id;
		//���ڿ��� �����ٸ� terminal�� �ٲٰ� ����
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			//�ش� �ڽ� ��尡 ���ٸ� �����Ѵ�.
			if (children[next] == NULL)
				children[next] = new BookTrieNode();
			//�ش� �ڽ� ���� ��� ȣ��
			children[next]->insert(key + 1, id);
		}
	}

	BookTrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}

	//�� ������ Ÿ������ ���� ��, ��ȣ id�� key�� Ÿ�����ϱ� ����
	//�ּ� �� ���� Ű�� �� ������ �ϳ�?
	int type(const char* key, int id) {
		//���ڿ� �����
		if (*key == 0) return 0;
		//�� ��忡�� ��õ�Ǵ� ���ڿ��� �� ���ڿ��̸� �� ������ ����
		if (first == id) return 1;
		//�ƴϸ� ���� ���ڸ� Ÿ�����Ѵ�.
		int next = toNumber(*key);
		return 1 + children[next]->type(key + 1, id);
	}
};

//�ȳ���, �׸��� ������ ������� ������ �ذ��ϴ� å�� �˰���.

//������ ��Ÿ���� Ʈ���̰� �־��� ��, �ܾ� word�� Ÿ�����ϴ� ��
//�� ���̳� Ű�� ������ �ϴ��� ����Ѵ�.
int countKeys(BookTrieNode* trie, const char* word) {
	//�� ���ڿ��� ������ �ִ��� Ȯ���ϰ�, �ִٸ� ��ȣ�� ���Ѵ�.
	BookTrieNode* node = trie->find(word);
	//������ ������ ���� Ÿ������ ���ۿ� ����.
	if (node == NULL || node->terminal == -1) return strlen(word);
	//Ž���ϸ鼭 Ÿ������ ����� ã�´�.
	return trie->type(word, node->terminal);
}

//�ȳ���, �׸��� ������ ������� ������ �Է��� �޾� Ʈ���̸� �����ϴ� å�� �Լ�

//�Է¿� �־����� �ܾ���� �����ؼ� Ʈ���̷� ��ȯ�Ѵ�.
BookTrieNode* readInput(int words) {
	//�ܾ���� ���� ���� ��������, �ܾ��� ������������ �����Ѵ�.
	vector<pair<int, string>> input;
	for (int i = 0; i < words; i++) {
		char buf[11];
		int freq;
		scanf("%s %d", buf, &freq);
		input.push_back(make_pair(-freq, buf));
	}
	sort(input.begin(), input.end());
	//�̶� �տ� �ִ� �ܾ��ϼ��� �켱������ ����.
	//�迭�� �ε����� �� �ܾ��� ��ȣ�� ����.
	BookTrieNode* trie = new BookTrieNode();
	for (int i = 0; i < input.size(); i++)
		trie->insert(input[i].second.c_str(), i);
	//�ƹ� ���ڵ� �Է����� ���� ��쿡�� �ڵ� �ϼ��� ���� �ʴ� ������ �Ǿ� �����Ƿ�
	//��Ʈ�� first ����� -1�� �ٲ� �ش�.
	trie->first = -1;
	return trie;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		TrieNode* root = new TrieNode();
		cin >> N >> M;
		int priority, result = 0;

		//�Է����� �־����� ������ �ܾ���� ���������� �����Ͽ�
		//���ʴ�� Ʈ���̿� �����Ѵ�.
		vector<pair<string, int>> input;
		for (int i = 0; i < N; i++) {
			char word[11];
			scanf("%s %d", word, &priority);
			input.push_back(make_pair(word, priority));
		}
		sort(input.begin(), input.end());

		for (int i = 0; i < N; i++) {
			root->insert(input[i].first.c_str(), input[i].second);
		}

		for (int i = 0; i < M; i++) {
			char word[11];
			scanf("%s", word);
			result += (types(root, word) + 1);
		}
		//������ ������ �ܾ �Է��� ���� ���� ���ڸ� �Է����� �ʴ´�.
		result--;
		cout << result << endl;
		input.clear();
	}
}
