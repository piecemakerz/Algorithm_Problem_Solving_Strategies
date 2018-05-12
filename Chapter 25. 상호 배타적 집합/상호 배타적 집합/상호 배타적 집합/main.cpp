#include <vector>
using namespace std;
//Ʈ���� �̿��� (�ܼ���) ��ȣ ��Ÿ�� ���� �ڷ� ������ ����

//Ʈ���� �̿��� ��ȣ ��Ÿ�� ������ �����Ѵ�.
struct NaiveDisjointSet {
	vector<int> parent;
	NaiveDisjointSet(int n) : parent(n) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	//u�� ���� Ʈ���� ���� ��ȣ�� ��ȯ�Ѵ�.
	int find(int u) const {
		if (u == parent[u]) return u;
		return find(parent[u]);
	}
	//u�� ���� Ʈ���� v�� ���� Ʈ���� ��ģ��.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		//u�� v�� �̹� ���� Ʈ���� ���ϴ� ��츦 �ɷ�����.
		if (u == v) return;
		parent[u] = v;
	}
};

//����ȭ�� ��ȣ ��Ÿ�� ������ ����
struct OptimizedDisjointSet {
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
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