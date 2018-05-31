#include <vector>
#include <queue>
#include <iostream>
#include <cstdio>
#include <limits>
using namespace std;

const double INF = numeric_limits<double>::infinity();
int t;
//��ǻ���� ��, ȸ���� ��
int n, m;
//�׷����� ���� ����Ʈ (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<vector<pair<int, double>>> adj;

vector<double> routing(int src) {
	//dist[i] = src���� i��° ���������� �ִܰŸ�
	vector<double> dist(n, INF);
	dist[src] = 1.0;
	//�켱���� ť. (���������� �Ÿ�, ������ ��ȣ) ���� ��´�.
	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(1.0, src));
	while (!pq.empty()) {
		double cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		//���� ���� ���� �ͺ��� �� ª�� ��θ� �˰� �ִٸ� ���� ���� ���� �����Ѵ�.
		if (dist[here] < cost) continue;
		//������ �������� ��� �����Ѵ�.
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			double nextDist = cost * adj[here][i].second;
			//�� ª�� ��θ� �߰��ϸ�, dist[]�� �����ϰ� �켱���� ť�� �����Ѵ�.
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}

int main(void) {
	cin >> t;
	for (int test = 0; test < t; test++) {
		cin >> n >> m;
		int from, to;
		double weight;
		adj = vector<vector<pair<int, double>>>(n);
		for (int i = 0; i < m; i++) {
			scanf("%d %d %lf", &from, &to, &weight);
			adj[from].push_back(make_pair(to,weight));
			adj[to].push_back(make_pair(from, weight));
		}
		printf("%f\n", -routing(0)[n - 1]);
	}
	return 0;
}