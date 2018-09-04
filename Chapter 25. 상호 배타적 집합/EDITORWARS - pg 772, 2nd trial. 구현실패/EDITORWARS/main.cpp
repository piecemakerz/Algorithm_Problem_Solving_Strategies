#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C, N, M;

//������ ���� ������ �ذ��ϴ� å�� ��ȣ ��Ÿ�� ������ ����
struct BipartiteUnionFind {
	//parent[i] = i�� �θ� ���. ��Ʈ��� i
	//rank[i] = i�� ��Ʈ�� ���, i�� ��Ʈ�� �ϴ� Ʈ���� ��ũ
	//enemy[i] = i�� ��Ʈ�� ���, �ش� ���հ� ���� ������ ������ ��Ʈ ��ȣ. (������ -1)
	//size[i] = i�� ��Ʈ�� ���, �ش� ������ ũ��
	vector<int> parent, rank, enemy, size;
	BipartiteUnionFind(int n) : parent(n), rank(n, 0),
		enemy(n, -1), size(n, 1) {
		for (int i = 0; i < n; i++) parent[i] = i;
	}
	int find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	int merge(int u, int v) {
		//u�� v�� �������� ��� ������ �ϳ��� ��ȯ�Ѵ�.
		if (u == -1 || v == -1) return max(u, v);
		u = find(u), v = find(v);
		//�̹� ���� ���� Ʈ���� ���� ���
		if (u == v) return u;
		if (rank[u] > rank[v]) swap(u, v);
		//���� �׻� rank[v]�� �� ũ�Ƿ� u�� v�� �ڽ����� �ִ´�.
		if (rank[u] == rank[v]) rank[v]++;
		parent[u] = v;
		size[v] += size[u];
		return v;
	}
	//u�� v�� ���� ���̴�. ����� �Ͼ�ٸ� false, �ƴϸ� true�� ��ȯ�Ѵ�.
	bool dis(int u, int v) {
		//�켱 ��Ʈ�� ã�´�.
		u = find(u), v = find(v);
		//���� ���տ� ���� ������ ����̴�.
		if (u == v) return false;
		//���� ���� ���� ����
		int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
		enemy[a] = b, enemy[b] = a;
		return true;
	}
	//u�� v�� ���� ������. ����� �Ͼ�ٸ� false, �ƴϸ� true�� ��ȯ�Ѵ�.
	bool ack(int u, int v) {
		//�켱 ��Ʈ�� ã�´�.
		u = find(u), v = find(v);
		//�� ������ ���� ���� ������ ���
		if (enemy[u] == v) return false;
		//������ ���� ���� ��
		int a = merge(u, v), b = merge(enemy[u], enemy[v]);
		enemy[a] = b;
		//�� ���� �� �����ϴ� ������ ������ b�� -1�� ���� �ִ�.
		if (b != -1) enemy[b] = a;
		return true;
	}
};

//��ȣ ��Ÿ�� ������ �־��� �� ������ ���� ������ ���� ���ϴ� �Լ��� ����

//BipartiteUnionFind �ν��Ͻ��� �־��� ��,
//�� ��Ƽ�� �� ���ɼ��� �ִ� �ִ� �ο��� ���Ѵ�.
int maxParty(const BipartiteUnionFind& buf) {
	int ret = 0;
	for(int node = 0; node < N; node++)
		if (buf.parent[node] == node) {
			int enemy = buf.enemy[node];
			//���� ���� ���� �� �� ���� �ʱ� ����, enemy < node�� ��츸 ����.
			//enemy == -1�� ��쵵 ��Ȯ�� �� ���� ���� �ȴ�.
			if (enemy > node) continue;
			int mySize = buf.size[node];
			int enemySize = (enemy == -1 ? 0 : buf.size[enemy]);
			//�� ���� �� ū ������ ���Ѵ�.
			ret += max(mySize, enemySize);
		}
	return ret;
}