#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

//���ͽ�Ʈ�� �˰����� �̿��� ö�� N�� ��� ������ �ذ��ϱ�

int C, M;
//������ ����
int V;
//�׷����� ���� ����Ʈ. (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<pair<int, int>> adj[410];
const int START = 401;
const int INF = 987654321;

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

//(A�� ������ ���� �ð� - B�� ������ ���� �ð�)�� ���� ��ȣ�� ��ȯ�Ѵ�.
int vertex(int delta) {
	return delta + 200;
}
//a[] = A�� ������ ���� ���� �ð�
//b[] = B�� ������ ���� ���� �ð�
int solve(const vector<int>& a, const vector<int>& b) {
	//�׷����� �����.
	V = 402;
	for (int i = 0; i < V; i++) adj[i].clear();
	//������ ���������� �����Ѵ�.
	for (int i = 0; i < a.size(); i++) {
		int delta = a[i] - b[i];
		adj[START].push_back(make_pair(vertex(delta), a[i]));
	}
	//���� ����
	for (int delta = -200; delta <= 200; delta++) {
		//i�� ������ �ڿ� ���δٸ�?
		for (int i = 0; i < a.size(); i++) {
			int next = delta + a[i] - b[i];
			//�ð� ������ ���� ���� 200�� �Ѵ� ������ ���� �ʿ䰡 ����.
			if (abs(next) > 200) continue;
			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));
		}
	}
	vector<int> shortest = dijkstra(START);
	int ret = shortest[vertex(0)];
	if (ret == INF) return -1;
	return ret;
}

vector<int> atime, btime;

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> M;
		atime = vector<int>(M), btime = vector<int>(M);
		int a, b;
		for (int i = 0; i < M; i++) {
			cin >> a >> b;
			atime[i] = a; btime[i] = b;
		}
		int result = solve(atime, btime);
		if (result == -1) cout << "IMPOSSIBLE" << endl;
		else cout << result << endl;
		atime.clear(); btime.clear();
		for(int i=0; i<401; i++)
			adj[i].clear();
	}
}