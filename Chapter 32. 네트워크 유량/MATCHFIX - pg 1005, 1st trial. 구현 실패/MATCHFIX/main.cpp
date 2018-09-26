#include <vector>
#include <queue>
using namespace std;

const int INF = 987654321;
const int MAX_V = 100;
int V;
//capacity[u][v] = u���� v�� ���� �� �ִ� �뷮
//flow[u][v] = u���� v�� �귯���� ���� (�ݴ� ������ ��� ����)
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
//flow[][]�� ����ϰ� �� ������ ��ȯ�Ѵ�.
int networkFlow(int source, int sink) {
	//flow�� 0���� �ʱ�ȭ�Ѵ�.
	memset(flow, 0, sizeof(flow));
	int totalFlow = 0;
	while (true) {
		//�ʺ� �켱 Ž������ ���� ��θ� ã�´�.
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int there = 0; there < V; there++) {
				//�ܿ� �뷮�� ���� �ִ� ������ ���� Ž���Ѵ�.
				if (capacity[here][there] - flow[here][there] > 0 &&
					parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		//���� ��ΰ� ������ �����Ѵ�.
		if (parent[sink] == -1) break;
		//���� ��θ� ���� ������ �󸶳� ������ �����Ѵ�.
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		//���� ��θ� ���� ������ ������.
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		totalFlow += amount;
	}
	return totalFlow;
}

//��Ʈ��ũ ������ ���� �º� ���� ������ �ذ��ϴ� �Լ��� ����
int n, m;
int wins[20], match[200][2];
//0�� ������ �� totalWins������ ����� �� �ִ��� ���θ� Ȯ���Ѵ�.
bool canWinWith(int totalWins) {
	//�̹� totalWins�� �̻� �� ������ ������ �ȵȴ�.
	if (*max_element(wins + 1, wins + n) >= totalWins)
		return false;
	//0���� �ҽ�, 1���� ��ũ
	V = 2 + m + n;
	memset(capacity, 0, sizeof(capacity));
	for (int i = 0; i < m; i++) {
		//�ҽ����� �� ���� ���� ����
		capacity[0][2 + i] = 1;
		//�� ��⿡�� �� ������ ���� ����
		for (int j = 0; j < 2; j++)
			capacity[2 + i][2 + m + match[i][j]] = 1;
	}
	//�� �������� ��ũ��, ������ �ִ� �¼��� �뷮���� �ϴ� ������ �߰�
	for (int i = 0; i < n; i++) {
		int maxWin = (i == 0 ? totalWins : totalWins - 1);
		capacity[2 + m + i][1] = maxWin - wins[i];
	}
	//�̶� ��� ��⿡ ���ڸ� ������ �� �ִ°�?
	return networkFlow(0, 1) == m;
}