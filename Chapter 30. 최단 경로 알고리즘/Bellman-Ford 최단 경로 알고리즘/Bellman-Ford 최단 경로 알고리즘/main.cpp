#include <vector>
using namespace std;

//����-���� �˰����� ����

const int MAX_V = 10;
const int INF = 987654321;
//������ ����
int V;
//�׷����� ���� ����Ʈ. (����� ���� ��ȣ, ���� ����ġ) ���� ��´�.
vector<pair<int, int>> adj[MAX_V];
//���� ����Ŭ�� ���� ��� �� �� �迭�� ��ȯ
vector<int> bellmanFord(int src) {
	//�������� ������ ��� ���������� �ִ� �Ÿ� ������ INF�� �д�.
	vector<int> upper(V, INF);
	upper[src] = 0;
	bool updated = 0;
	//V�� ��ȸ�Ѵ�.
	for (int iter = 0; iter < V; iter++) {
		updated = false;
		for (int here = 0; here < V; here++)
			for (int i = 0; i < adj[here].size(); i++) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				//(here, there) ������ ���� ��ȭ�� �õ��Ѵ�.
				if (upper[there] > upper[here] + cost) {
					//����
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		//��� ������ ���� ��ȭ�� �������� ��� V-1���� �� �ʿ� ���� ���� �����Ѵ�.
		if (!updated) break;
	}
	//V��° ��ȸ������ ��ȭ�� �����ߴٸ� ���� ����Ŭ�� �ִ�.
	if (updated) upper.clear();
	return upper;
}