#include <vector>
#include <queue>
using namespace std;

const int MAX_V = 10;
const int INF = 987654321;
//������ ����
int V;
//�׷����� ���� ����Ʈ. (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<pair<int, int>> adj[MAX_V];

//���ͽ�Ʈ���� �ִ� �Ÿ� �˰����� ����

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

//�켱���� ť�� ������� �ʴ� ���ͽ�Ʈ�� �˰����� ����

vector<int> dijkstra2(int src) {
	vector<int> dist(V, INF);
	//�� ������ �湮�ߴ��� ���θ� �����Ѵ�.
	vector<bool> visited(V, false);
	dist[src] = 0; visited[src] = true;
	while (true) {
		//���� �湮���� ���� ���� �� ���� ����� ������ ã�´�.
		int closest = INF, here;
		for (int i = 0; i < V; i++)
			if (dist[i] < closest && !visited[i]) {
				here = i;
				closest = dist[i];
			}
		if (closest == INF) break;
		//���� ����� ������ �湮�Ѵ�.
		visited[here] = true;
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			if (visited[there]) continue;
			int nextDist = dist[here] + adj[here][i].second;
			dist[there] = min(dist[there], nextDist);
		}
	}
	return dist;
}