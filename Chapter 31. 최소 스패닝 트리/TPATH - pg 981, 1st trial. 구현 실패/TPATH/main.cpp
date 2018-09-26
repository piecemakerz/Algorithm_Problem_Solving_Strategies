#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

//minUpperBound()�� �̿��� ���� ��� ���� �ذ��ϱ�

const int INF = 987654321;
const int MAX_V = 2000;
int V, E;
//�׷����� ���� ����Ʈ ǥ��
vector<pair<int, int>> adj[MAX_V];
//��� ������ ����ġ ���. ������ �д�.
vector<int> weights;
//����ġ�� weights[low] �̻��� �������� �������� �������� �����ϴ�
//��θ� ����� ���� �ʿ��� ����� �ּ� ������ ����Ѵ�. �� ������
//������ �� ���� ��� ū ���� ��ȯ�Ѵ�.
int minUpperBound(int low);
//0�� V-1�� �����ϴ� ��� �� ����ġ�� ���Ѱ� ���� ������
//�ּ� ���� ����Ѵ�.
int minWeightDifference() {
	int ret = INF;
	for(int i=0; i < weights.size(); i++)
		ret = min(ret, minUpperBound(i) - weights[i]);
	return ret;
}

//�̺� �˻����� minUpperBound() �����ϱ�

//0�� V-1�� �մ� ��� �� ��� ����ġ ������ [lo, hi] ����
//��ΰ� �ִ°�?
//���� �켱 Ž���̳� �ʺ� �켱 Ž������ �����Ѵ�.
bool hasPath(int lo, int hi) {
	vector<bool> discovered(V, false);
	queue<int> q;
	vector<int> order;
	discovered[0] = true;
	q.push(0);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		order.push_back(here);
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first, edge = adj[here][i].second;
			if (!discovered[there] && edge >= lo && edge <= hi) {
				q.push(there);
				discovered[there] = true;
			}
		}
		if (discovered[V - 1])
			return true;
	}
	return false;
}
int binarySearchMinUpperBound(int low) {
	//�ݺ��� �Һ���:
	//1. ����ġ�� [weights[low], weights[lo]]
	//������ �ִ� ������ ����ϸ� �� ������ ������ �� ����.
	//2. ����ġ�� [weights[low], weights[hi]] ������ �ִ�
	//������ ����ϸ� �� ������ ������ �� �ִ�.
	int lo = low - 1, hi = weights.size();
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (hasPath(weights[low], weights[mid]))
			hi = mid;
		else
			lo = mid;
	}
	if (hi == weights.size()) return INF;
	return weights[hi];
}

//������ ũ�罺Į �˰������� ���� ��� ���� �ذ��ϱ�

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

//(����ġ,(����1, ����2))�� ���. �̸� ������ �д�.
vector<pair<int, pair<int, int>>> edges;
int kruskalMinUpperBound(int low) {
	DisjointSet sets(V);
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].first < weights[low]) continue;
		//edges[i]�� �׷����� �߰�����.
		sets.merge(edges[i].second.first, edges[i].second.second);
		//0�� V-1�� ����Ǿ��ٸ� �������� �߰��� ������ ����ġ�� ��ȯ�Ѵ�.
		if (sets.find(0) == sets.find(V - 1))
			return edges[i].first;
	}
	return INF;
}

//���� ��� ������ �ذ��ϴ� ���� ������ �˰���

//��� ����/������ �ֿ� ���� ��ΰ� �����ϴ��� ���� Ȯ����
//����, ��ΰ� �����ϴ� �ּ� �ʺ� ��ȯ�Ѵ�.
int brute() {
	int ret = INF;
	for(int lo = 0; lo < weights.size(); lo++)
		for (int hi = lo; hi < weights.size(); hi++) {
			//����/������ ���� �־��� ��, �� ���� �մ� ��ΰ� �����ϴ°�?
			if (hasPath(weights[lo], weights[hi])) {
				ret = min(ret, weights[hi] - weights[lo]);
				break;
			}
		}
	return ret;
}

//���� ��� ������ �ذ��ϴ� ������ �˰����� ����ȭ�ϱ�

//brute()�� �� ������ ������ �˰���
int optimized() {
	//foundPathUsing = ��θ� ã�� ���� ���������� ����ߴ� ������ ��ġ
	int ret = INF, foundPathUsing = 0;
	for (int lo = 0; lo < weights.size(); lo++) {
		//�� ���ѿ� ���� ��θ� �߰��ߴ°�?
		bool foundPath = false;
		for (int hi = foundPathUsing; hi < weights.size(); hi++) {
			if (hasPath(weights[lo], weights[hi])) {
				ret = min(ret, weights[hi] - weights[lo]);
				foundPath = true;
				foundPathUsing = hi;
				break;
			}
		}
		//��ΰ� ���ٸ� ���� �����Ѵ�.
		if (!foundPath) break;
	}
	return ret;
}

//���� ��� ������ �ذ��ϴ� ������ �˰���

//����ġ ������ �Ⱦ���� ��ΰ� �����ϴ� ����ġ ������ �ּ� ũ�⸦ ã�´�.
int scanning() {
	int lo = 0, hi = 0, ret = INF;
	while (lo < weights.size() && hi < weights.size()) {
		if (hasPath(weights[lo], weights[hi])) {
			ret = min(ret, weights[hi] - weights[lo]);
			lo++;
		}
		else
			hi++;
	}
}