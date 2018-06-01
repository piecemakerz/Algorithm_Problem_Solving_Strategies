#include <vector>
#include <queue>
using namespace std;

const int MAX_V = 100;
const int INF = 987654321;
//������ ����
int V;
//�׷����� ���� ����Ʈ. (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<pair<int, int>> adj[MAX_V];
//�־��� �׷����� ���� �ּ� ���д� Ʈ���� ���Ե� ������ ����� selected��
//�����ϰ�, ����ġ�� ���� ��ȯ�Ѵ�.
int prim(vector<pair<int, int>>& selected) {
	selected.clear();
	//�ش� ������ Ʈ���� ���ԵǾ� �ֳ�?
	vector<bool> added(V, false);
	//Ʈ���� ������ ���� �� �ش� ������ ��� �ּ� ������ ������ �����Ѵ�.
	vector<int> minWeight(V, INF), parent(V, -1);
	//����ġ�� ���� ������ ����
	int ret = 0;
	//0�� ������ ����������: �׻� Ʈ���� ���� �߰��ȴ�.
	minWeight[0] = parent[0] = 0;
	//�켱���� ť. (minWeihgt[], ������ ��ȣ) ���� ��´�.
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, 0));
	while(!pq.empty()) {
		//������ Ʈ���� �߰��� ���� u�� ã�´�.
		int weight = -pq.top().first;
		int u = pq.top().second;
		pq.pop();
		if (added[u]) continue;

		//parent([u], u)�� Ʈ���� �߰��Ѵ�.
		if (parent[u] != u)
			selected.push_back(make_pair(parent[u], u));

		ret += weight;
		added[u] = true;
		//u�� ������ ���� (u, v)���� �˻��Ѵ�.
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, weight = adj[u][i].second;
			if (!added[v] && minWeight[v] > weight) {
				parent[v] = u;
				minWeight[v] = weight;
				pq.push(make_pair(-weight, v));
			}
		}
	}
	return ret;
}