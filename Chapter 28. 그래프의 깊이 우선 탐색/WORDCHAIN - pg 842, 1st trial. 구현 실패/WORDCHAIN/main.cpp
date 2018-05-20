#include <iostream>
#include <vector>
#include <string>
using namespace std;

int C, n;

//그래프의 인접 행렬 표현. adj[i][j] = i와 j사이의 간선의 수
vector<vector<int>> adj;
//graph[i][j] = i로 시작해서 j로 끝나는 단어의 목록
vector<string> graph[26][26];
//indegree[i] = i로 들어오는 간선의 수
//outdegree[i] = i에서 나가는 간선의 수
vector<int> indegree, outdegree;
//끝말잇기 문제의 입력을 그래프로 만들기
void makeGraph(const vector<string>& words) {
	//전역 변수 초기화
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
			graph[i][j].clear();
	adj = vector<vector<int>>(26, vector<int>(26, 0));
	indegree = outdegree = vector<int>(26, 0);
	//각 단어를 그래프에 추가한다.
	for (int i = 0; i < words.size(); i++) {
		int a = words[i][0] - 'a';
		int b = words[i][words[i].size() - 1] - 'a';
		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

//유향 그래프의 인접 행렬 adj가 주어질 때 오일러 서킷 또는 트레일을 계산한다.
void getEulerCircuit(int here, vector<int>& circuit) {
	for(int there = 0; there < adj.size(); there++)
		while (adj[here][there] > 0) {
			adj[here][there]--; // 간선을 지운다.
			getEulerCircuit(there, circuit);
		}
	circuit.push_back(here);
}
//현재 그래프에 오일러 서킷/트레일이 존재할 때,
//현재 그래프의 오일러 트레일이나 서킷을 반환한다.
vector<int> getEulerTrailOrCircuit() {
	vector<int> circuit;
	//우선 트레일을 찾아본다: 시작점이 존재하는 경우
	for(int i=0; i<26; i++)
		if (outdegree[i] == indegree[i] + 1) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	//아니면 서킷이니, 간선에 인접한 아무 정점에서나 시작한다.
	for (int i = 0; i < 26; i++) 
		if (outdegree[i]) {
			getEulerCircuit(i, circuit);
			return circuit;
		}
	//모두 실패한 경우 빈 배열을 반환한다.
	return circuit;
}
//현재 그래프의 오일러 서킷/트레일 존재 여부를 확인한다.
bool checkEuler() {
	//예비 시작점과 끝점의 수
	int plus1 = 0, minus1 = 0;
	for (int i = 0; i < 26; i++) {
		int delta = outdegree[i] - indegree[i];
		//모든 정점의 차수는 -1, 1 또는 0 이어야 한다.
		if (delta < -1 || 1 < delta) return false;
		if (delta == 1) plus1++;
		if (delta == -1) minus1++;
	}
	//시작점과 끝점은 각 하나씩 있거나 하나도 없어야 한다.
	return (plus1 == 1 && minus1 == 1) || (plus1 == 0 && minus1 == 0);
}

string solve(const vector<string>& words) {
	makeGraph(words);
	//차수가 맞지 않으면 실패!
	if (!checkEuler()) return "IMPOSSIBLE";
	//오일러 서킷이나 경로를 찾아낸다.
	vector<int> circuit = getEulerTrailOrCircuit();
	//모든 간선을 방문하지 못했으면 실패!
	if (circuit.size() != words.size() + 1) return "IMPOSSIBLE";

	//아닌 경우 방문 순서를 뒤집은 뒤 간선들을 모아 문자열로 만들어 반환한다.
	reverse(circuit.begin(), circuit.end());
	string ret;
	for (int i = 1; i < circuit.size(); i++) {
		//a로 시작하고 b로 끝나는 단어를 찾는다.
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