#include <vector>
#include <queue>
#include <limits>
#include <iostream>
using namespace std;

const int MAX_N = 10000;
const double INF = numeric_limits<double>::infinity();

int t, n, m;
//�׷����� ���� ����Ʈ(����� ���� ��ȣ, ���� ����ġ)
vector<pair<int, double>> adj[MAX_N];

vector<double> dijkstra(int src) {
	//dist[i] = src���� i��° ���������� �ִܰŸ�
	vector<double> dist(n, INF);
	dist[src] = 1.0;
	//�켱���� ť. (���������� �Ÿ�, ������ ��ȣ) ���� ��´�.
	priority_queue<pair<double, int>> pq;
	pq.push(make_pair(-1.0, src));
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
			//�� ª�� ��θ� �߰��ϸ�, dist[]�� �����ϰ� �켱���� ť�� �ִ´�.
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
		int a, b; double c;
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> c;
			adj[a].push_back(make_pair(b, c));
			adj[b].push_back(make_pair(a, c));
		}

		printf("%.10f\n", dijkstra(0)[n-1]);
		for (int i = 0; i < MAX_N; i++)
			adj[i].clear();
	}
}