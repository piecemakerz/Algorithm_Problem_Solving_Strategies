#include <vector>
#include <algorithm>
using namespace std;

//����ȭ�� ��ȣ ��Ÿ�� ������ ����
struct DisjointSet {
	vector<int> parent, rank;
	DisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	//u�� ���� Ʈ���� ��Ʈ�� ��ȣ�� ��ȯ�Ѵ�.
	//�ѹ� u�� ���� find�� ȣ���ϸ� parent[u]�� Ʈ���� ��Ʈ�� ����Ű��
	//�ǹǷ� ������ ȣ���� �� ��θ� ���� �ö� �� ���� �ٷ� ��Ʈ�� ã�� �� �ִ�.
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}
	//u�� ���� Ʈ���� v�� ���� Ʈ���� ��ģ��.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		//u�� v�� �̹� ���� ���տ� ���ϴ� ��츦 �ɷ�����.
		if (u == v) return;
		if (rank[u] > rank[v]) swap(u, v);
		//rank[v]�� �׻� rank[u] �̻��̹Ƿ� u�� v�� �ڽ����� �ִ´�. 
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}
};

//ũ�罺Į �ּ� ���д� Ʈ�� �˰���

//Ʈ���� �̿��� ��ȣ ��Ÿ�� ������ �����Ѵ�.
const int MAX_V = 100;
//������ ����
int V;
//�׷����� ���� ����Ʈ. (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<pair<int, int>> adj[MAX_V];

//�־��� �׷����� ���� �ּ� ���д� Ʈ���� ���Ե� ������ ����� 
//selected�� �����ϰ�, ����ġ�� ���� ��ȯ�Ѵ�.
int kruskal(vector<pair<int, int>>& selected) {
	int ret = 0;
	selected.clear();
	//(����ġ, (����1, ����2))�� ����� ��´�.
	vector<pair<int, pair<int, int>>> edges;
	for (int u = 0; u < V; u++)
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}
	//����ġ ������ ����
	sort(edges.begin(), edges.end());
	//ó���� ��� ������ ���� �и��Ǿ� �ִ�.
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); i++) {
		//���� (u, v)�� �˻��Ѵ�.
		int cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		//�̹� u�� v�� ����Ǿ� ���� ��� �����Ѵ�.
		if (sets.find(u) == sets.find(v)) continue;
		//�� ���� ��ģ��.
		sets.merge(u, v);
		selected.push_back(make_pair(u, v));
		ret += cost;
	}
	return ret;
}