#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX_V = 100;
const int INF = 987654321;

//���� ���� �˰����� �̿��� �ð����� ���� �ذ��ϱ�
int V;
vector<pair<int, int>> adj[MAX_V];
//reachable[u][v] = u���� v�� ���� ��ΰ� �ִ°�?
bool reachable[MAX_V][MAX_V];
//src���� target���� ���� �ִ� �Ÿ��� ����Ѵ�.
//����ġ�� ���� ���Ѵ��� ��ΰ� ������ -INF�� ��ȯ�Ѵ�.
int bellman2(int src, int target) {
	//�������� ������ ��� ���������� �ִ� �Ÿ� ������ INF�� �д�.
	vector<int> upper(V, INF);
	upper[src] = 0;
	//V-1�� ��ȸ�Ѵ�.
	for(int iter=0; iter<V-1; iter++)
		for(int here = 0; here < V; here++)
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				//(here, there) ������ ���� ��ȭ�� �õ��Ѵ�.
				upper[there] = min(upper[there], upper[here] + cost);
			}
	//���� ����Ŭ�� ���� ���θ� Ȯ������.
	for (int here = 0; here < V; here++)
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