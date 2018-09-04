#include <iostream>
#include <map>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;

int C, N, M;
const int ALPHAPETS = 26;
int toNumber(char ch) { return ch - 'A'; }


//�� Ǯ��
//wordToFreq[�ܾ�] = ���� ��
map<string, int> wordToFreq;
//freqToWord[���� ��] = �ش� �����󵵸� ������ �ܾ���� set. 
//�ܾ���� ���������� ���ĵǾ� �ִ�.
vector<set<string, less<string>>> freqToWord;
struct TrieNode;
//Ʈ������ ��Ʈ���. ��Ʈ���� ����ִ�.
TrieNode * root;

struct TrieNode {
	TrieNode* children[ALPHAPETS];
	//�� ��尡 ���� ����ΰ�?
	bool terminal;
	//�� ����� �ִ� ���� ��
	int maxFreq;
	//�ִ� ���� �󵵸� ������ �ܾ���� ����
	int maxFreqCount;
	TrieNode() : terminal(false), maxFreq(0), maxFreqCount(0) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHAPETS; i++)
			if (children[i])
				delete children[i];
	}

	//�� ��带 ��Ʈ�� �ϴ� Ʈ���̿� freq�� ���� �󵵸� ������ ���ڿ� key�� �߰��Ѵ�.
	void insert(const char* key, int freq) {
		if (*key == 0)
			terminal = true;
		else {
			int next = toNumber(*key);
			//�ش� �ڽ� ��尡 ���ٸ� �����Ѵ�.
			if (children[next] == NULL) {
				children[next] = new TrieNode();
			}
			//�ش� �ڽ� ���� ��� ȣ��
			children[next]->insert(key + 1, freq);
		}
		//key�� ���� �󵵰� ����� �ִ� ���� �󵵿� ���ٸ� maxFreqCount�� ������Ų��.
		if (freq == maxFreq)
			maxFreqCount++;
		//key�� ���� �󵵰� ����� �ִ� ���� �󵵺��� ũ�ٸ� �ִ� ���� �󵵸� �����Ѵ�.
		else if (freq > maxFreq) {
			maxFreqCount = 1;
			maxFreq = freq;
		}
	}
	//�� ��忡�� ���ϴ� �ܾ ��õ���� �� �ִ��� Ȯ���ϰ�, ��õ���� �� �ִٸ�
	//���±��� �Է��� ������ �� + 1 (�� Ű)�� ��ȯ�Ѵ�.
	//�ܾ��� ���������� Ȯ���� ��� �Է��� ������ ���� ��ȯ�Ѵ�. (�� ��� �� Ű�� ���� �ʿ䰡 ����)
	//�ܾ Ʈ���� �� �������� ���� ��� 0�� ��ȯ�Ѵ�.
	int find(const char* key, string prevStr, string ordiStr, int freq, int types = 0) {
		if (*key == 0) return types; 
		//ã�� �ܾ��� ���� �󵵰� ���� ����� �ִ� ���� ���� ���
		//�ܾ �ٷ� ��õ���� �� �ִ��� Ȯ���Ѵ�.
		if (this != root && freq == maxFreq) {
			set<string>::iterator findIter = freqToWord[freq].begin();
			//���� ���� �󵵸� ������ �ܾ 2�� �̻� ������ ���
			//ã�� ���ڿ��� ���������� ���� �տ� ���� ���� �ٷ� ���ϴ� �ܾ ã�� �� �ִ�.
			if (maxFreqCount > 1) {
				while (findIter != freqToWord[freq].end()) {
					if (prevStr.compare((*findIter).substr(0, prevStr.length())) == 0) {
						if ((*findIter).compare(ordiStr) == 0) {
								return types + 1;
						}
						else
							break;
					}
					findIter++;
				}
			}
			//���� ���� �󵵸� ������ �ܾ 1���� ������ ���
			//���ϴ� �ܾ �ٷ� ã�� �� �ִ�.
			else {
				return types + 1;
			}
		}
		//���ϴ� �ܾ ��õ���� �� ���ٸ� ���ȣ���Ѵ�.
		int next = toNumber(*key);
		if (children[next] == NULL) return 0;
		return children[next]->find(key + 1, prevStr + (*key), ordiStr, freq, types+1);
	}
};

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		root = new TrieNode();
		cin >> N >> M;
		int freq;
		freqToWord.resize(100001);
		for (int i = 0; i < N; i++) {
			char str[21];
			scanf("%s %d", str, &freq);
			root->insert(str, freq);
			string inputStr = str;
			wordToFreq.insert(pair<string, int>(inputStr, freq));
			freqToWord[freq].insert(inputStr);
		}
		int ret = 0;
		for (int i = 0; i < M; i++) {
			char str[21];
			scanf("%s", str);
			string findStr = str;
			map<string, int>::iterator freqit;
			freqit = wordToFreq.find(str);
			//Ʈ���̿� �ش� �ܾ ��ϵǾ� ���� �ʴٸ�
			//�ش� �ܾ��� ���� ����ŭ �Է��ؾ� �Ѵ�.
			if (freqit == wordToFreq.end())
				ret += strlen(str);
			else {
				cout << root->find(str, "", findStr, freqit->second) << endl;
				ret += root->find(str, "", findStr, freqit->second);
			}//�����̽���
			ret += 1;
		}
		ret -= 1;
		cout << ret << endl;

		wordToFreq.clear();
		freqToWord.clear();
		delete root;
	}
	return 0;
}

/*
//å�� Ǯ��
struct TrieNode {
	TrieNode* children[ALPHAPETS];
	//�� ��忡�� �����ϴ� ���ڿ��� ��ȣ. ������ -1
	int terminal;
	//�� ��带 ��Ʈ�� �ϴ� Ʈ���̿� ���� ���� �߰��� �ܾ��� ��ȣ. -1�� �ʱ�ȭ
	//���� ���� �߰��� ���ڿ��� �׻� ��õ��.
	int first;
	TrieNode() : terminal(-1), first(-1){
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHAPETS; i++)
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
				children[next] = new TrieNode();
			//�ش� �ڽ� ���� ��� ȣ��
			children[next]->insert(key + 1, id);
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
int countKeys(TrieNode* trie, const char* word) {
	//�� ���ڿ��� ������ �ִ��� Ȯ���ϰ�, �ִٸ� ��ȣ�� ���Ѵ�.
	TrieNode* node = trie->find(word);
	//������ ������ ���� Ÿ������ ���ۿ� ����.
	if (node == NULL || node->terminal == -1)
		return strlen(word);
	//Ž���ϸ鼭 Ÿ������ ����� ã�´�.
	return trie->type(word, node->terminal);
}

//�Է¿� �־����� �ܾ���� �����ؼ� Ʈ���̷� ��ȯ�Ѵ�.
TrieNode* readInput(int words) {
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
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < input.size(); i++)
		trie->insert(input[i].second.c_str(), i);
	trie->first = -1;
	return trie;
}
*/