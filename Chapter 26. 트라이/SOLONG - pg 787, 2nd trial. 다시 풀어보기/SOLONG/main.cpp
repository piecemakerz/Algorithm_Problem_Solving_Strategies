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
	//maxPriority = 해당 노드의 자식들 중 가장 출현 빈도가 높은 노드의 출현빈도
	//해당 노드에서 끝나는 단어의 출현 빈도도 포함한다.
	//maxCnt = 가장 높은 출현 빈도를 가지는 노드들의 수
	//priority = 해당 노드에서 끝나는 문자가 있을 때, 그 문자의 출현 빈도
	//maxIdx = 가장 높은 출현 빈도를 가지는 자식의 인덱스. 만일 가장 높은 출현 빈도를
	//가지는 자식이 2개 이상 존재할 시 사전순으로 가장 앞에 오는 자식노드의 인덱스가 저장된다.
	//해당 노드에서 끝나는 단어의 출현 빈도도 포함한다.
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

//안녕히, 그리고 물고기는 고마웠어요 문제를 해결하는 내 알고리즘.
//트라이는 접두사를 기준으로 설계된 자료구조임에도 불구하고 접미사를
//기준으로 문제를 해결했다는 점을 눈여겨볼 만 하다.
//단어 key를 추천받기 위해 타이핑해야 하는 수를 반환한다.
//만익 key가 사전에 없다면, key의 길이를 그대로 반환한다.
//아래에서 위로 올라오는, bottom-up 접근법을 사용하였다.
int types(TrieNode* root, string key) {
	//typeCnt = 해당 단어를 추천받기 위해 타이핑해야 하는 수
	int typeCnt = key.length();
	//result = 해당 단어가 끝나는 노드
	TrieNode* result = root->find(key.c_str());
	//해당 단어가 사전에 등록되어 있지 않거나 단어의 일부만
	//등록되어 있을 경우
	if (result == NULL || !(result->priority))
		return typeCnt;

	//keyPriority = 찾으려는 단어의 출현 빈도
	int keyPriority = result->priority;
	TrieNode* prevNode = result;
	result = result->parent;

	//현재 확인하는 노드의 최대 출현 빈도가 찾으려는 단어의 출현 빈도보다 크다면,
	//더 이상 찾으려는 단어를 추천받을 확률이 없으므로 반복문에서 나온다.
	while (result->maxPriority == keyPriority) {
		if (result == root) break;
		
		//사전순으로 단어들을 정렬했으므로 같은 우선순위를 가졌다면
		//사전순으로 앞에 오는 단어가 추천될 것이다.
		if (result->maxCnt > 1)
			if (prevNode != result->children[result->maxIdx])
				break;

		prevNode = result;
		result = result->parent;
		typeCnt--;
	}
	//찾으려는 단어의 길이만큼 이미 타이핑했다면 탭키를 누를 필요가 없다.
	if (typeCnt == key.length())
		return typeCnt;
	return typeCnt + 1;
}

//안녕히, 그리고 물고기는 고마웠어요 문제를 해결하는 책의 트라이 노드 구현

//트라이의 한 노드를 나타내는 객체
struct BookTrieNode {
	BookTrieNode* children[ALPHABETS];
	//이 노드에서 종료하는 문자열의 번호. 없으면 -1
	int terminal;
	//이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호. -1로 초기화
	int first;
	BookTrieNode() : terminal(false){
		memset(children, 0, sizeof(children));
	}
	~BookTrieNode() {
		for (int i = 0; i < ALPHABETS; i++)
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
			//해당 자식 노드가 없다면 생성한다.
			if (children[next] == NULL)
				children[next] = new BookTrieNode();
			//해당 자식 노드로 재귀 호출
			children[next]->insert(key + 1, id);
		}
	}

	BookTrieNode* find(const char* key) {
		if (*key == 0) return this;
		int next = toNumber(*key);
		if (children[next] == NULL) return NULL;
		return children[next]->find(key + 1);
	}

	//이 노드까지 타이팽해 왔을 때, 번호 id인 key를 타이핑하기 위해
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

//안녕히, 그리고 물고기는 고마웠어요 문제를 해결하는 책의 알고리즘.

//사전을 나타내는 트라이가 주어질 때, 단어 word를 타이핑하는 데
//몇 번이나 키를 눌러야 하는지 계산한다.
int countKeys(BookTrieNode* trie, const char* word) {
	//이 문자열이 사전에 있는지 확인하고, 있다면 번호를 구한다.
	BookTrieNode* node = trie->find(word);
	//사전에 없으면 직접 타이핑할 수밖에 없다.
	if (node == NULL || node->terminal == -1) return strlen(word);
	//탐색하면서 타이핑할 방법을 찾는다.
	return trie->type(word, node->terminal);
}

//안녕히, 그리고 물고기는 고마웠어요 문제의 입력을 받아 트라이를 생성하는 책의 함수

//입력에 주어지는 단어들을 정렬해서 트라이로 변환한다.
BookTrieNode* readInput(int words) {
	//단어들을 출현 빈도의 내림차순, 단어의 오름차순으로 정렬한다.
	vector<pair<int, string>> input;
	for (int i = 0; i < words; i++) {
		char buf[11];
		int freq;
		scanf("%s %d", buf, &freq);
		input.push_back(make_pair(-freq, buf));
	}
	sort(input.begin(), input.end());
	//이때 앞에 있는 단어일수록 우선순위가 높다.
	//배열의 인덱스를 각 단어의 번호로 쓰자.
	BookTrieNode* trie = new BookTrieNode();
	for (int i = 0; i < input.size(); i++)
		trie->insert(input[i].second.c_str(), i);
	//아무 글자도 입력하지 않을 경우에는 자동 완성이 되지 않는 것으로 되어 있으므로
	//루트의 first 멤버를 -1로 바꿔 준다.
	trie->first = -1;
	return trie;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		TrieNode* root = new TrieNode();
		cin >> N >> M;
		int priority, result = 0;

		//입력으로 주어지는 사전의 단어들을 사전순으로 정렬하여
		//차례대로 트라이에 삽입한다.
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
		//문장의 마지막 단어를 입력할 때는 공백 문자를 입력하지 않는다.
		result--;
		cout << result << endl;
		input.clear();
	}
}
