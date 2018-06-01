#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAX_N = 500;
const int MAX_M = 2000;
const int INF = 987654321;

int C, N, M;

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

//ũ�罺Į �ּ� ���д� Ʈ�� �˰����� �̿��� �� Ǯ��

//(����� ����, ����ġ)
vector<pair<int, double>> adj[MAX_N];
vector<int> xpos, ypos;

double kruskal(DisjointSet& sets) {
	double ret = 0;
	//(����ġ, (����1, ����2))�� ����� ��´�.
	vector<pair<double, pair<int, int>>> edges;
	for (int u = 0; u < N; u++)
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			double cost = adj[u][i].second;
			edges.push_back(make_pair(cost, make_pair(u, v)));
		}
	//����ġ ������ ����
	sort(edges.begin(), edges.end());
	//ó���� ��� ������ ���� �и��Ǿ� �ִ�.
	for (int i = 0; i < edges.size(); i++) {
		//���� (u, v)�� �˻��Ѵ�.
		double cost = edges[i].first;
		int u = edges[i].second.first, v = edges[i].second.second;
		//�̹� u�� v�� ����Ǿ� ���� ��� �����Ѵ�.
		if (sets.find(u) == sets.find(v)) continue;
		//�� ���� ��ģ��.
		sets.merge(u, v);
		ret += cost;
	}
	return ret;
}

//���� �˰����� ����� å�� Ǯ�� ����
double prim() {
	//�ش� ������ Ʈ���� ���ԵǾ� �ֳ�?
	vector<bool> added(N, false);
	//Ʈ���� ������ ���� �� �ش� ������ ��� �ּ� ������ ������ �����Ѵ�.
	vector<double> minWeight(N, INF);
	vector<int> parent(N, -1);
	//����ġ�� ���� ������ ����
	double ret = 0;
	//0�� ������ ����������: �׻� Ʈ���� ���� �߰��ȴ�.
	minWeight[0] = parent[0] = 0;
	//�켱���� ť. (minWeihgt[], ������ ��ȣ) ���� ��´�.
	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(0.0, 0));
	while (!pq.empty()) {
		//������ Ʈ���� �߰��� ���� u�� ã�´�.
		double weight = -pq.top().first;
		int u = pq.top().second;
		pq.pop();
		if (added[u]) continue;

		ret += weight;
		added[u] = true;
		//u�� ������ ���� (u, v)���� �˻��Ѵ�.
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			double weight = adj[u][i].second;
			if (!added[v] && minWeight[v] > weight) {
				parent[v] = u;
				minWeight[v] = weight;
				pq.push(make_pair(-weight, v));
			}
		}
	}
	return ret;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		int input;
		cin >> N >> M;
		for (int i = 0; i < N; i++) {
			cin >> input;
			xpos.push_back(input);
		}
		for (int i = 0; i < N; i++) {
			cin >> input;
			ypos.push_back(input);
		}

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (i == j) continue;
				adj[i].push_back(make_pair(j, sqrt(pow(xpos[i] - xpos[j], 2) + pow(ypos[i] - ypos[j], 2))));
			}

		/*
		DisjointSet sets(N);
		vector<pair<int, int>> selected;
		for (int i = 0; i < M; i++) {
			int n1, n2;
			cin >> n1 >> n2;
			sets.merge(n1, n2);
		}
		printf("%.10lf\n", kruskal(sets));
		*/

		for (int i = 0; i < M; i++) {
			int n1, n2;
			cin >> n1 >> n2;
			for(int i=0; i<adj[n1].size(); i++)
				if (adj[n1][i].first == n2) {
					adj[n1][i].second = 0.0;
					break;
				}
			for (int i = 0; i<adj[n2].size(); i++)
				if (adj[n2][i].first == n1) {
					adj[n2][i].second = 0.0;
					break;
				}
		}
		printf("%.10lf\n", prim());

		for (int i = 0; i < N; i++)
			adj[i].clear();
		xpos.clear();
		ypos.clear();
	}
	return 0;
}