#include <iostream>
#include <vector>
#include <string>
using namespace std;

int C, n;

//�׷����� ���� ��� ǥ��. adj[i][j] = i�� j������ ������ ��
vector<vector<int>> adj;
//graph[i][j] = i�� �����ؼ� j�� ������ �ܾ��� ���
vector<string> graph[26][26];
//indegree[i] = i�� ������ ������ ��
//outdegree[i] = i���� ������ ������ ��
vector<int> indegree, outdegree;
//�����ձ� ������ �Է��� �׷����� �����
void makeGraph(const vector<string>& words) {
	//���� ���� �ʱ�ȭ
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			graph[i][j].clear();
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);
	//�� �ܾ �׷����� �߰��Ѵ�.
	for (int i = 0; i < words.size(); i++) {
		int a = words[i][0] - 'a';
		int b = words[i][words[i].size() - 1] - 'a';
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

//���� �׷����� ���� ��� adj�� �־��� �� ���Ϸ� ��Ŷ �Ǵ� Ʈ������ ����Ѵ�.
void getEulerCircuit(int here, vector<int>& circuit) {
	for(int there = 0; there < adj.size(); there++)
		while (adj[here][there] > 0) {
			adj[here][there]--; // ������ �����.
			getEulerCircuit(there, circuit);
		}
	circuit.push_back(here);
}
//���� �׷����� ���Ϸ� ��Ŷ/Ʈ������ ������ ��,
//���� �׷����� ���Ϸ� Ʈ�����̳� ��Ŷ�� ��ȯ�Ѵ�.
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;
	//�켱 Ʈ������ ã�ƺ���: �������� �����ϴ� ���
	for(int i=0; i<26; i++)
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	//�ƴϸ� ��Ŷ�̴�, ������ ������ �ƹ� ���������� �����Ѵ�.
	for (int i = 0; i < 26; i++) 
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	//��� ������ ��� �� �迭�� ��ȯ�Ѵ�.
	return circuit;
}
//���� �׷����� ���Ϸ� ��Ŷ/Ʈ���� ���� ���θ� Ȯ���Ѵ�.
bool checkEuler() {
	//���� �������� ������ ��
	int plus1 = 0, minus1 = 0;
	for (int i = 0; i < 26; i++) {
		int delta = outdegree[i] - indegree[i];
		//��� ������ ������ -1, 1 �Ǵ� 0 �̾�� �Ѵ�.
		if (delta < -1 || 1 < delta) return false;
		if (delta == 1) plus1++;
		if (delta == -1) minus1++;
	}
	//�������� ������ �� �ϳ��� �ְų� �ϳ��� ����� �Ѵ�.
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

string solve(const vector<string>& words) {
	makeGraph(words);
	//������ ���� ������ ����!
	if (!checkEuler()) return "IMPOSSIBLE";
	//���Ϸ� ��Ŷ�̳� ��θ� ã�Ƴ���.
	vector<int> circuit = getEulerTrailOrCircuit();
	//��� ������ �湮���� �������� ����!
	if (circuit.size() != words.size() + 1) return "IMPOSSIBLE";

	//�ƴ� ��� �湮 ������ ������ �� �������� ��� ���ڿ��� ����� ��ȯ�Ѵ�.
	reverse(circuit.begin(), circuit.end());
	string ret;
	for (int i = 1; i < circuit.size(); i++) {
		//a�� �����ϰ� b�� ������ �ܾ ã�´�.
		int a = circuit[i - 1], b = circuit[i];
		if (ret.size()) ret += " ";
		ret += graph[a][b].back();
		graph[a][b].pop_back();
	}
	return ret;
}
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n;
		vector<string> inputWords;
		string inputStr;
		for (int i = 0; i < n; i++) {
			cin >> inputStr;
			inputWords.push_back(inputStr);
		}

	}
}