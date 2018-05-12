#include <vector>
using namespace std;
//트리를 이용한 (단순한) 상호 배타적 집합 자료 구조의 구현

//트리를 이용해 상호 배타적 집합을 구현한다.
struct NaiveDisjointSet {
	vector<int> parent;
	NaiveDisjointSet(int n) : parent(n) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	//u가 속한 트리의 투르 번호를 반환한다.
	int find(int u) const {
		if (u == parent[u]) return u;
		return find(parent[u]);
	}
	//u가 속한 트리와 v가 속한 트리를 합친다.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		//u와 v가 이미 같은 트리에 속하는 경우를 걸러낸다.
		if (u == v) return;
		parent[u] = v;
	}
};

//최적화된 상호 배타적 집합의 구현
struct OptimizedDisjointSet {
	vector<int> parent, rank;
	OptimizedDisjointSet(int n) : parent(n), rank(n, 1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}
	//u가 속한 트리의 루트의 번호를 반환한다.
	//한번 u에 대해 find를 호출하면 parent[u]가 트리의 루트를 가리키게
	//되므로 다음번 호출할 때 경로를 따라 올라갈 것 없이 바로 루트를 찾을 수 있다.
	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}
	//u가 속한 트리와 v가 속한 트리를 합친다.
	void merge(int u, int v) {
		u = find(u); v = find(v);
		//u와 v가 이미 같은 집합에 속하는 경우를 걸러낸다.
		if (u == v) return;
		if (rank[u] > rank[v]) swap(u, v);
		//rank[v]가 항상 rank[u] 이상이므로 u를 v의 자식으로 넣는다. 
		parent[u] = v;
		if (rank[u] == rank[v]) rank[v]++;
	}
};