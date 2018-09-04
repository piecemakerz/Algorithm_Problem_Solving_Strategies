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


//내 풀이
//wordToFreq[단어] = 출현 빈도
map<string, int> wordToFreq;
//freqToWord[출현 빈도] = 해당 출현빈도를 가지는 단어들의 set. 
//단어들은 사전순으로 정렬되어 있다.
vector<set<string, less<string>>> freqToWord;
struct TrieNode;
//트라이의 루트노드. 루트노드는 비어있다.
TrieNode * root;

struct TrieNode {
	TrieNode* children[ALPHAPETS];
	//이 노드가 종료 노드인가?
	bool terminal;
	//이 노드의 최대 출현 빈도
	int maxFreq;
	//최대 출현 빈도를 가지는 단어들의 갯수
	int maxFreqCount;
	TrieNode() : terminal(false), maxFreq(0), maxFreqCount(0) {
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHAPETS; i++)
			if (children[i])
				delete children[i];
	}

	//이 노드를 루트로 하는 트라이에 freq의 출현 빈도를 가지는 문자열 key를 추가한다.
	void insert(const char* key, int freq) {
		if (*key == 0)
			terminal = true;
		else {
			int next = toNumber(*key);
			//해당 자식 노드가 없다면 생성한다.
			if (children[next] == NULL) {
				children[next] = new TrieNode();
			}
			//해당 자식 노드로 재귀 호출
			children[next]->insert(key + 1, freq);
		}
		//key의 출현 빈도가 노드의 최대 출현 빈도와 같다면 maxFreqCount를 증가시킨다.
		if (freq == maxFreq)
			maxFreqCount++;
		//key의 출현 빈도가 노드의 최대 출현 빈도보다 크다면 최대 출현 빈도를 갱신한다.
		else if (freq > maxFreq) {
			maxFreqCount = 1;
			maxFreq = freq;
		}
	}
	//이 노드에서 원하는 단어를 추천받을 수 있는지 확인하고, 추천받을 수 있다면
	//여태까지 입력한 문자의 수 + 1 (탭 키)를 반환한다.
	//단어의 마지막까지 확인한 경우 입력한 문자의 수를 반환한다. (이 경우 탭 키를 누를 필요가 없다)
	//단어가 트라이 상에 존재하지 않을 경우 0를 반환한다.
	int find(const char* key, string prevStr, string ordiStr, int freq, int types = 0) {
		if (*key == 0) return types; 
		//찾는 단어의 출현 빈도가 현재 노드의 최대 출현 빈도일 경우
		//단어를 바로 추천받을 수 있는지 확인한다.
		if (this != root && freq == maxFreq) {
			set<string>::iterator findIter = freqToWord[freq].begin();
			//같은 출현 빈도를 가지는 단어가 2개 이상 존재할 경우
			//찾는 문자열이 사전순으로 가장 앞에 나올 때만 바로 원하는 단어를 찾을 수 있다.
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
			//같은 출현 빈도를 가지는 단어가 1개만 존재할 경우
			//원하는 단어를 바로 찾을 수 있다.
			else {
				return types + 1;
			}
		}
		//원하는 단어를 추천받을 수 없다면 재귀호출한다.
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
			//트라이에 해당 단어가 등록되어 있지 않다면
			//해당 단어의 문자 수만큼 입력해야 한다.
			if (freqit == wordToFreq.end())
				ret += strlen(str);
			else {
				cout << root->find(str, "", findStr, freqit->second) << endl;
				ret += root->find(str, "", findStr, freqit->second);
			}//스페이스바
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
//책의 풀이
struct TrieNode {
	TrieNode* children[ALPHAPETS];
	//이 노드에서 종료하는 문자열의 번호. 없으면 -1
	int terminal;
	//이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호. -1로 초기화
	//가장 먼저 추가된 문자열이 항상 추천됨.
	int first;
	TrieNode() : terminal(-1), first(-1){
		memset(children, 0, sizeof(children));
	}
	~TrieNode() {
		for (int i = 0; i < ALPHAPETS; i++)
			if (children[i])
				delete children[i];
	}
	//이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가한다.
	void insert(const char* key, int id) {
		//first를 우선 갱신
		if (first == -1) first = id;
		//문자열이 끝났다면 terminal만 바꾸고 종료
		if (*key == 0)
			terminal = id;
		else {
			int next = toNumber(*key);
			//해당 자식 노드가 없다면 생성한다
			if (children[next] == NULL)
				children[next] = new TrieNode();
			//해당 자식 노드로 재귀 호출
			children[next]->insert(key + 1, id);
		}
	}
	//이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다.
	//없으면 NULL을 반환한다.
	TrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}
	//이 노드까지 타이핑해 왔을 때, 번호 id인 key를 타이핑하기 위해
	//최소 몇 번의 키를 더 눌러야 하나?
	int type(const char* key, int id) {
		//문자열 종료시
		if (*key == 0) return 0;
		//이 노드에서 추천되는 문자열이 이 문자열이면 탭 누르고 종료
		if (first == id) return 1;
		//아니면 다음 문자를 타이핑한다.
		int next = toNumber(*key);
		return 1 + children[next]->type(key + 1, id);
	}
};

//사전을 나타내는 트라이가 주어질 때, 단어 word를 타이핑하는 데
//몇 번이나 키를 눌러야 하는지 계산한다.
int countKeys(TrieNode* trie, const char* word) {
	//이 문자열에 사전이 있는지 확인하고, 있다면 번호를 구한다.
	TrieNode* node = trie->find(word);
	//사전에 없으면 직접 타이핑할 수밖에 없다.
	if (node == NULL || node->terminal == -1)
		return strlen(word);
	//탐색하면서 타이핑할 방법을 찾는다.
	return trie->type(word, node->terminal);
}

//입력에 주어지는 단어들을 정렬해서 트라이로 변환한다.
TrieNode* readInput(int words) {
	//단어들을 출현 빈도의 내림차순, 단어의 오름차순으로 정렬한다.
	vector<pair<int, string>> input;
	for (int i = 0; i < words; i++) {
		char buf[11];
		int freq;
		scanf("%s %d", buf, &freq);
		input.push_back(make_pair(-freq, buf));
	}
	//pair을 sort함수로 정렬할 경우 pair의 첫 번째 원소를 기준으로 정렬이 되고
	//첫 번째 원소가 같을 경우 두 번째 원소를 사용해서 비교한다.
	sort(input.begin(), input.end());
	//이때 앞에 있는 단어일수록 우선순위가 높다.
	//배열의 인덱스를 각 단어의 번호로 쓰자.
	TrieNode* trie = new TrieNode();
	for (int i = 0; i < input.size(); i++)
		trie->insert(input[i].second.c_str(), i);
	trie->first = -1;
	return trie;
}
*/