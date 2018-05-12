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

map<string, int> wordToFreq;
vector<set<string, less<string>>> freqToWord;
struct TrieNode;
TrieNode * root;

struct TrieNode {
	TrieNode* children[ALPHAPETS];
	bool terminal;
	int maxFreq;
	int maxFreqCount;
	TrieNode() : terminal(false), maxFreq(0), maxFreqCount(0) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHAPETS; i++)
			if (children[i])
				delete children[i];
	}

	void insert(const char* key, int freq) {
		if (*key == 0)
			terminal = true;
		else {
			int next = toNumber(*key);
			if (children[next] == NULL) {
				children[next] = new TrieNode();
			}
			children[next]->insert(key + 1, freq);
		}
		if (freq == maxFreq)
			maxFreqCount++;
		else if (freq > maxFreq) {
			maxFreqCount = 1;
			maxFreq = freq;
		}
	}
	int find(const char* key, string prevStr, string ordiStr, int freq, int types = 0) {
		if (*key == 0) return types; 
		//ã�� ���ڿ��� ���� �󵵰� ���� ����� �ִ� ���� ���� ���
		if (this != root && freq == maxFreq) {
			set<string>::iterator findIter = freqToWord[freq].begin();
			//���� ���� �󵵸� ������ �ܾ 2�� �̻� ������ ���
			//ã�� ���ڿ��� ���������� ���� �տ� ���� ���� �ٷ� ���ڿ��� ã�� �� �ִ�.
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
			else {
				//���� ���� �󵵸� ������ �ܾ 1���� ������ ���
				//ã�� ���ڿ��� �ٷ� ã�� �� �ִ�.
				return types + 1;
			}
		}
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
			if (freqit == wordToFreq.end())
				ret += strlen(str);
			else
				ret += root->find(str, "", findStr, freqit->second);
			//�����̽���
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