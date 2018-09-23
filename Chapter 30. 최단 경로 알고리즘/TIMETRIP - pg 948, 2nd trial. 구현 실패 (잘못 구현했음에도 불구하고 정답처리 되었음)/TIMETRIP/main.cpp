#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int C, G, W;

const int INF = 987654321;
//�׷����� ���� ����Ʈ. (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<vector<pair<int, int>>> adj;

bool upperInf, lowerInf;

//�ð����� ������ �ذ��ϴ� �� Ǯ��.
//�и� ��� ������ �ֿ� ���� �� �������� �ٸ� ��������
//���� ����� ���� ���θ� Ȯ������ �ʾ������� ����� ������ ������
//������ ����, �쿬�� ���� ó���� �� �� ����. ��, �� �˰����� Ʋ�ȴ�.
void bellmanFord(vector<int>& upper, vector<int>& lower, int src) {
	upper[src] = 0, lower[src] = 0;
	bool upperUpdated = false, lowerUpdated = false;
	//G�� ��ȸ�Ѵ�.
	for (int iter = 0; iter < G; iter++) {
		upperUpdated = false, lowerUpdated = false;
		for(int here = 0; here < G; here++)
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[there] > upper[here] + cost) {
					upper[there] = upper[here] + cost;
					upperUpdated = true;
				}
				if (lower[there] < lower[here] + cost) {
					lower[there] = lower[here] + cost;
					lowerUpdated = true;
				}
			}
		if (!upperUpdated && !lowerUpdated) break;
	}
	if (upperUpdated) upperInf = true;
	if (lowerUpdated) lowerInf = true;
}

//�ð����� ������ �ذ��ϴ� å�� ���� ���� �˰���
int V;
const int MAX_V = 100;
vector<pair<int, int>> adj[MAX_V];
//reachable[u][v] = u���� v�� ���� ��ΰ� �ִ°�?
bool reachable[MAX_V][MAX_V];
//src���� target���� ���� �ִ� �Ÿ��� ����Ѵ�.
//����ġ�� ���� ���Ѵ��� ��ΰ� ������ -INF�� ��ȯ�Ѵ�.
//����ġ�� ��ȣ�� ��� �ٲ� ���� �ִ� ��θ� ���ϸ�
//���������� ���������� ���� ���� ��θ� ã�� �� �ִ�.
int bellman2(int src, int target) {
	//�������� ������ ��� ���������� �ִ� �Ÿ� ������ INF�� �д�.
	vector<int> upper(V, INF);
	upper[src] = 0;
	//V-1�� ��ȸ�Ѵ�.
	for(int iter = 0; iter < V-1; iter++)
		for(int here = 0; here < V; here++)
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				//(here, there) ������ ���� ��ȭ�� �õ��Ѵ�.
				upper[there] = min(upper[there], upper[here] + cost);
			}
	//���� ����Ŭ�� ���� ���θ� Ȯ������.
	for(int here = 0; here < V; here++)
		for (int i = 0; i < adj[here].size(); i++) {
			int there = adj[here][i].first;
			int cost = adj[here][i].second;
			//��ȭ�� �����Ѵٸ� here�� ���� ����Ŭ�� ��� �ִ�.
			if (upper[here] + cost < upper[there])
				//�� ���� ����Ŭ�� �����ϴ� ��ΰ� �ִ°�?
				if (reachable[src][here] && reachable[here][target])
					return -INF;
		}
	return upper[target];
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> G >> W;
		adj = vector<vector<pair<int, int>>>(G);
		upperInf = false, lowerInf = false;
		int a, b, d;

		for (int i = 0; i < W; i++) {
			cin >> a >> b >> d;
			adj[a].push_back(make_pair(b, d));
		}
		vector<int> upper(G, INF), lower(G, -INF);
		bellmanFord(upper, lower, 0);
		
		if (upper[1] > INF - 1000000)
			cout << "UNREACHABLE" << endl;
		else {
			if (upperInf)
				cout << "INFINITY ";
			else
				cout << upper[1] << ' ';

			if (lowerInf)
				cout << "INFINITY" << endl;
			else
				cout << lower[1] << endl;
		}
		adj.clear();
	}
}