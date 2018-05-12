#include <cstring>
using namespace std;

//Ʈ������ ��带 ǥ���ϴ� ��ü�� ����

//���ĺ� �빮�ڸ� �����ϴ� ��� �� ���� 26���� �ڼ��� ���� �� �ִ�.
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'; }
//Ʈ������ �� ��带 ��Ÿ���� ��ü
struct TrieNode {
	TrieNode* children[ALPHABETS];
	//�� ��尡 ���� ����ΰ�?
	bool terminal;
	TrieNode() : terminal(false) {
		memset(children, 0, sizeof(children));
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