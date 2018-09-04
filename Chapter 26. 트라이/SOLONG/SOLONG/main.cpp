#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ALPHABETS = 26;
int C, N, M;

int toNumber(char ch) { return ch - 'A'; }
struct TrieNode {
	TrieNode* children[ALPHABETS], *parent;
	int maxPriority, maxCnt, priority, maxIdx;
	bool terminal;
	TrieNode() : terminal(false), maxIdx(-1), maxPriority(-1), maxCnt(1), priority(0) {
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
			if (*key != 0 && maxIdx == -1)
				maxIdx = toNumber(*key);
			maxCnt = 1;
		}
		else if (maxPriority == priority)
			maxCnt++;

		if (*key == 0) {
			terminal = true;
			this->priority = priority;
		}
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

int types(TrieNode* root, string key) {
	int typeCnt = key.length();
	TrieNode* result = root->find(key.c_str());
	//�ش� �ܾ ������ ��ϵǾ� ���� �ʰų� �ܾ��� �Ϻθ�
	//��ϵǾ� ���� ���
	if (result == NULL || !(result->terminal))
		return typeCnt;

	int keyPriority = result->priority;
	//cout << "keyPriority: " << keyPriority << "typeCnt: "<<typeCnt<<endl;
	TrieNode* prevNode = result;
	result = result->parent;

	while (true) {
		if (result->maxPriority != keyPriority)
			break;
		
		//�켱������ ���� ������ ������ �ܾ ���� ��� �� �ܾ ��õ�� ���̴�.
		if (result == root || result->priority == keyPriority)
			break;
		
		//���������� �ܾ���� ���������Ƿ� ���� �켱������ �����ٸ�
		//���������� �տ� ���� �ܾ ��õ�� ���̴�.
		if (result->maxCnt > 1) {
			if (prevNode != result->children[result->maxIdx])
				break;
		}
		prevNode = result;
		result = result->parent;
		typeCnt--;
	}
	if (typeCnt == key.length())
		return typeCnt;
	return typeCnt + 1;
}

void printTree(TrieNode* node, int num) {
	cout << "Alpha: " << (char)(num + 'A');
	cout << "maxPriority: " << node->maxPriority << " maxCnt: " << node->maxCnt << " maxIdx: " << (char)('A' + node->maxIdx) << endl;
	for (int i = 0; i < ALPHABETS; i++) {
		if (node->children[i] != NULL)
			printTree(node->children[i], i);
	}
}

vector<string> generatedStr;
void randomGenerator(vector<pair<string, int>>& input, vector<pair<int, string>>& bookInput) {
	int length = rand() % 10 + 1;
	string randStr;
	for (int i = 0; i < length; i++)
		randStr += (char)(rand() % ALPHABETS + 'A');
	generatedStr.push_back(randStr);

	int priority = rand() % 100000 + 1;
	input.push_back(make_pair(randStr, priority));
	bookInput.push_back(make_pair(-priority, randStr));
}

struct BookTrieNode {
	BookTrieNode* children[ALPHABETS];
	//�� ��忡�� �����ϴ� ���ڿ��� ��ȣ. ������ -1
	int terminal;
	//�� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ���� ���� �߰��� �ܾ��� ��ȣ. -1�� �ʱ�ȭ
	//���� ���� �߰��� ���ڿ��� �׻� ��õ��.
	int first;
	BookTrieNode() : terminal(-1), first(-1) {
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
			//�ش� �ڽ� ��尡 ���ٸ� �����Ѵ�
			if (children[next] == NULL)
				children[next] = new BookTrieNode();
			//�ش� �ڽ� ���� ��� ȣ��
			children[next]->insert(key + 1, id);
		}
	}
	//�� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ���ڿ� key�� �����Ǵ� ��带 ã�´�.
	//������ NULL�� ��ȯ�Ѵ�.
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

//������ ��Ÿ���� Ʈ���̰� �־��� ��, �ܾ� word�� Ÿ�����ϴ� ��
//�� ���̳� Ű�� ������ �ϴ��� ����Ѵ�.
int countKeys(BookTrieNode* trie, const char* word) {
	//�� ���ڿ��� ������ �ִ��� Ȯ���ϰ�, �ִٸ� ��ȣ�� ���Ѵ�.
	BookTrieNode* node = trie->find(word);
	//������ ������ ���� Ÿ������ ���ۿ� ����.
	if (node == NULL || node->terminal == -1)
		return strlen(word);
	//Ž���ϸ鼭 Ÿ������ ����� ã�´�.
	return trie->type(word, node->terminal);
}

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
	//pair�� sort�Լ��� ������ ��� pair�� ù ��° ���Ҹ� �������� ������ �ǰ�
	//ù ��° ���Ұ� ���� ��� �� ��° ���Ҹ� ����ؼ� ���Ѵ�.
	sort(input.begin(), input.end());
	//�̶� �տ� �ִ� �ܾ��ϼ��� �켱������ ����.
	//�迭�� �ε����� �� �ܾ��� ��ȣ�� ����.
	BookTrieNode* trie = new BookTrieNode();
	for (int i = 0; i < input.size(); i++)
		trie->insert(input[i].second.c_str(), i);
	trie->first = -1;
	return trie;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		srand(time(NULL));
		TrieNode* root = new TrieNode();
		cin >> N >> M;
		int priority, result = 0, bookResult = 0;

		vector<pair<string, int>> input;
		vector<pair<int, string>> bookInput;
		/*for (int i = 0; i < N; i++) {
			char word[11];
			scanf("%s %d", word, &priority);
			input.push_back(make_pair(word, priority));
		}
		*/
		for (int i = 0; i < N; i++)
			randomGenerator(input, bookInput);

		sort(input.begin(), input.end());
		sort(bookInput.begin(), bookInput.end());
		for (int i = 0; i < N; i++) {
			root->insert(input[i].first.c_str(), input[i].second);
		}

		BookTrieNode* trie = new BookTrieNode();
		for (int i = 0; i < bookInput.size(); i++)
			trie->insert(bookInput[i].second.c_str(), i);
		trie->first = -1;
		//printTree(root, -1);

		/*for (int i = 0; i < M; i++) {
			char word[11];
			scanf("%s", word);
			result += (types(root, word) + 1);
		}
		*/
		for (int i = 0; i < generatedStr.size(); i++) {
			result += (types(root, generatedStr[i]) + 1);
		}
		for (int i = 0; i < generatedStr.size(); i++) {
			bookResult += (countKeys(trie, generatedStr[i].c_str()) + 1);
		}
		result--;
		bookResult--;
		cout << result << endl;
		cout << bookResult << endl;
		input.clear();
		bookInput.clear();
		generatedStr.clear();
	}
}