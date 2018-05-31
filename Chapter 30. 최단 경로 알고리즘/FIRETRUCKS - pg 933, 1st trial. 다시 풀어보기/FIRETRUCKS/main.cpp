#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 987654321;
//V = ����� ��, E = ������ ��, n = ȭ�� ����� ��, m = �ҹ漭�� ��
int C, V, E, n, m;

//�׷����� ���� ����Ʈ (����� ���� ��ȣ, ���� ����ġ)
vector<vector<pair<int, int>>> adj;
//�� �ҹ漭�� ���� �ش� �������� ������� �ɸ��� �ּ� �ð�
vector<vector<int>> shortestPaths;

/*
//�� Ǯ��
vector<int> dijkstra(int src) {
	//dist[i] = src���� i��° ���������� �ִܰŸ�
	vector<int> dist(V, INF);
	dist[src] = 0;
	//�켱���� ť. (���������� �Ÿ�, ������ ��ȣ) ���� ��´�.
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		//���� ���� ���� �ͺ��� �� ª�� ��θ� �˰� �ִٸ� ���� ���� ���� �����Ѵ�.
		if (dist[here] < cost) continue;
		//������ �������� ��� �����Ѵ�.
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			//�� ª�� ��θ� �߰��ϸ�, dist[]�� �����ϰ� �켱���� ť�� �ִ´�.
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return dist;
}
*/

//å�� ��
vector<int> dijkstraBook(int src) {
	//dist[i] = src���� i��° ���������� �ִܰŸ�
	vector<int> dist(V+1, INF);
	dist[src] = 0;
	//�켱���� ť. (���������� �Ÿ�, ������ ��ȣ) ���� ��´�.
	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();
		//���� ���� ���� �ͺ��� �� ª�� ��θ� �˰� �ִٸ� ���� ���� ���� �����Ѵ�.
		if (dist[here] < cost) continue;
		//������ �������� ��� �����Ѵ�.
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
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
	cin >> C;
	for (int test = 0; test < C; test++) {
		//V = ����� ��, E = ������ ��, n = ȭ�� ����� ��, m = �ҹ漭�� ��
		cin >> V >> E >> n >> m;
		adj = vector<vector<pair<int, int>>>(V+1);
		//shortestPaths = vector<vector<int>>(V);
		/*
		int from, to, weight;
		for (int i = 0; i < E; i++) {
			cin >> from >> to >> weight;
			adj[from-1].push_back(make_pair(to-1, weight));
			adj[to - 1].push_back(make_pair(from - 1, weight));
		}

		vector<int> placeOnFire(n);
		for (int i = 0; i < n; i++) {
			cin >> placeOnFire[i];
			placeOnFire[i] -= 1;
		}

		vector<int> fireStation(m);
		for (int i = 0; i < m; i++) {
			cin >> fireStation[i];
			fireStation[i] -= 1;
		}

		//�� �ҹ漭�� ���� �� ���������� �ִܰŸ��� ���Ѵ�.
		for (int i = 0; i < m; i++) {
			vector<int> result = dijkstra(fireStation[i]);
			for (int j = 0; j < n; j++) 
				shortestPaths[placeOnFire[j]].push_back(result[placeOnFire[j]]);
		}

		long timeSum = 0;
		for (int i = 0; i < n; i++) {
			int goal = placeOnFire[i];
			sort(shortestPaths[goal].begin(), shortestPaths[goal].end());
			timeSum += shortestPaths[goal].front();
		}
		cout << timeSum << endl;
		*/
		int from, to, weight;
		for (int i = 0; i < E; i++) {
			cin >> from >> to >> weight;
			adj[from].push_back(make_pair(to, weight));
			adj[to].push_back(make_pair(from, weight));
		}

		vector<int> placeOnFire(n);
		for (int i = 0; i < n; i++)
			cin >> placeOnFire[i];

		vector<int> fireStation(m);
		for (int i = 0; i < m; i++) {
			cin >> fireStation[i];
			adj[0].push_back(make_pair(fireStation[i], 0));
		}
		
		long timeSum = 0;
		vector<int> result = dijkstraBook(0);
		for (int i = 0; i < n; i++)
			timeSum += result[placeOnFire[i]];
		cout << timeSum << endl;
	}
	return 0;
}