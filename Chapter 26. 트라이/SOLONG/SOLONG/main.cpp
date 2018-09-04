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
	//해당 단어가 사전에 등록되어 있지 않거나 단어의 일부만
	//등록되어 있을 경우
	if (result == NULL || !(result->terminal))
		return typeCnt;

	int keyPriority = result->priority;
	//cout << "keyPriority: " << keyPriority << "typeCnt: "<<typeCnt<<endl;
	TrieNode* prevNode = result;
	result = result->parent;

	while (true) {
		if (result->maxPriority != keyPriority)
			break;
		
		//우선순위가 같고 이전에 끝나는 단어가 있을 경우 그 단어가 추천될 것이다.
		if (result == root || result->priority == keyPriority)
			break;
		
		//사전순으로 단어들을 정렬했으므로 같은 우선순위를 가졌다면
		//사전순으로 앞에 오는 단어가 추천될 것이다.
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
	//이 노드에서 종료하는 문자열의 번호. 없으면 -1
	int terminal;
	//이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호. -1로 초기화
	//가장 먼저 추가된 문자열이 항상 추천됨.
	int first;
	BookTrieNode() : terminal(-1), first(-1) {
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
			//해당 자식 노드가 없다면 생성한다
			if (children[next] == NULL)
				children[next] = new BookTrieNode();
			//해당 자식 노드로 재귀 호출
			children[next]->insert(key + 1, id);
		}
	}
	//이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾는다.
	//없으면 NULL을 반환한다.
	BookTrieNode* find(const char* key) {
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
int countKeys(BookTrieNode* trie, const char* word) {
	//이 문자열에 사전이 있는지 확인하고, 있다면 번호를 구한다.
	BookTrieNode* node = trie->find(word);
	//사전에 없으면 직접 타이핑할 수밖에 없다.
	if (node == NULL || node->terminal == -1)
		return strlen(word);
	//탐색하면서 타이핑할 방법을 찾는다.
	return trie->type(word, node->terminal);
}

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
	//pair을 sort함수로 정렬할 경우 pair의 첫 번째 원소를 기준으로 정렬이 되고
	//첫 번째 원소가 같을 경우 두 번째 원소를 사용해서 비교한다.
	sort(input.begin(), input.end());
	//이때 앞에 있는 단어일수록 우선순위가 높다.
	//배열의 인덱스를 각 단어의 번호로 쓰자.
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