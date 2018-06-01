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
			for(int there = 0; there < V; there++)
				//�ܿ� �뷮�� ���� �ִ� ������ ���� Ž���Ѵ�.
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
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