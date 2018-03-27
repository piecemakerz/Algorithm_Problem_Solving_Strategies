#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <bitset>
using namespace std;

const double INF = 1e200;
const int MAX = 30;
int n; // ������ ��
double dist[MAX][MAX]; //�� ���ð��� �Ÿ��� �����ϴ� �迭
//���ݱ��� ã�� ������
double best;
//�� ���ÿ� ������ ���� �� ���� ª�� ���� �̸� ã�� �д�.
double minEdge[MAX];
//���� �ܼ��� ������ �޸���ƽ
double simpleHeuristic(vector<bool>& visited) {
	double ret = minEdge[0]; //�������� ���������� ���ư� �� ����� ����
	for (int i = 0; i < n; i++)
		if (!visited[i])
			ret += minEdge[i];
	return ret;
}

//�� ���ø��� �ٸ� ���õ��� ����� ������� ������ �д�.
vector<int> nearest[MAX];

//path�� ������ �� ���� ���� �� ��� �ִ� ������ �� ������ �ٲ��� ��
//��ΰ� �� ª�������� ���θ� ��ȯ�Ѵ�.
bool pathSwapPruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}
//���� ���ÿ� ���� ���ø� ������ path�� �κ� ��θ�
//������ ���� �� ª�������� Ȯ���Ѵ�.
bool pathReversePruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	for (int i = 0; i + 3 < path.size(); i++) {
		int p = path[i];
		int a = path[i + 1];
		//[..,p,a,...,b,q]�� [..,p,b,...,a,q]�� �ٲ㺻��.
		if (dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
			return true;
	}
	return false;
}

//��ȣ ��Ÿ�� ���� �ڷ� ������ �����Ѵ�.
struct DisjointSet {
	int n, components;
	vector<int> parent, rank;
	//n���� ���ҷ� ������ ���� �ڷ� ������ �����.
	DisjointSet(int n) : n(n), components(n), parent(n), rank(n) {
		for (int i = 0; i < n; i++) {
			parent[i] = i;
			rank[i] = 0;
		}
	}
	//here�� ���Ե� ������ ��ǥ�� ��ȯ�Ѵ�.
	int find(int here) {
		return parent[here] == here ? here : (parent[here] = find(parent[here]));
	}
	//a�� ���Ե� ���հ� b�� ���Ե� ������ ��ģ��.
	bool merge(int a, int b) {
		a = find(a); b = find(b);
		if (a == b) return false;
		if (rank[a] > rank[b])
			parent[b] = a;
		else {
			parent[a] = b;
			if (rank[a] == rank[b]) rank[b]++;
		}
		--components;
		return true;
	}
};
//��� ���� ���� ���θ� ���� ������ ������ ������ �д�.
vector <pair<double, pair<int, int>>> edges;
//here�� ������, ���� �湮���� ���� ���õ��� ��� �����ϴ� MST�� ã�´�.
double mstHeuristic(int here, const vector<bool>& visited) {
	//Kruskal's MST
	DisjointSet sets(n);
	double taken = 0; // ��� ������ ��(���� ����ġ�� ��)
	for (int i = 0; i < edges.size(); i++) {
		int a = edges[i].second.first, b = edges[i].second.second;
		if (a != 0 && a != here && visited[a]) continue;
		if (b != 0 && b != here && visited[b]) continue;
		if (sets.merge(a, b))
			taken += edges[i].first;
	}
	return taken;
}

//���� ������ ���� CACHED_DEPTH ���ϸ� ���� ��ȹ������ �ٲ۴�.
const int CACHED_DEPTH = 5;
//dp(here, visited) = cache[here][���� ������ ��][visited]
map<int, double> cache[MAX][CACHED_DEPTH + 1];
//here: ���� ��ġ
//visited: �� ������ �湮 ����
//�� ��, ������ ���ø� ��� �湮�ϰ� ���������� ���ư��� �ִ� ����� ���̸� ��ȯ�Ѵ�.
int popcount(int n) {
	int count = 0;
	while (n > 0) {
		if (n & 1)
			count++;
		n >>= 1;
	}
	return count;
}
double dp(int here, int visited) {
	//���� ���: �� �湮�� ���ð� ������ ���������� ���ư���.
	if (visited == (1 << n) - 1) return dist[here][0];
	//�޸������̼�
	int remaining = n - popcount(visited);
	double& ret = cache[here][remaining][visited];
	if (ret > 0) return ret;
	ret = INF;
	//���� ���ø� �ϳ��� �õ��Ѵ�.
	for (int next = 0; next < n; next++) {
		if (visited & (1 << next)) continue;
		ret = min(ret, dp(next, visited + (1 << next)) + dist[here][next]);
	}
	return ret;
}

//path: ���ݱ��� ���� ���
//visited: �� ������ �湮 ����
//currentLength: ���ݱ��� ���� ����� ����
//������ ���õ��� ��� �湮�ϴ� ��ε��� ����� ���� �����ϸ� �����ظ� �����Ѵ�.
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	int here = path.back();
	//���� ���: ��� ���ø� �� �湮���� ���� 0�� ���÷� ���ư��� �����Ѵ�.
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//������ ����ġ��: ���ݱ��� ã�� ���� ���� �� �̻��� ��� �ߴ�
	//if (best <= currentLength) return;

	//�ܼ��� �޸���ƽ�� �̿��� ����ġ��
	//if (best <= currentLength + simpleHeuristic(visited))	return;

	//���� ���: ���� ���� ���� CACHED_DEPTH ���ϸ� ���� ��ȹ������ �ٲ۴�.
	if (path.size() + CACHED_DEPTH >= n) {
		int mask = 0;
		for (int i = 0; i < n; i++) if (visited[i]) mask += (1 << i);
		best = min(best, currentLength + dp(path.back(), mask));
		return;
	}

	//���� �湮�� ���ø� ���� �õ��� ����.
	/*
	����� �������� �湮�ϴ� ����ȭ�� �������� ��
	for(int i = 0; i < nearest[here].size(); i++){
		int next = nearest[here][i];
	*/

	for (int next = 0; next < n; next++) {
		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		//������ ��θ� ��� ȣ���� ���� �ϼ��Ѵ�.
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

double solve() {
	/*
	//simpleHeuristic()�� ���� �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		minEdge[i] = INF;
		for (int j = 0; j < n; j++)
			if (i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
	}
	*/

	/*
	//nearest �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		vector<pair<double, int>> order;
		for (int j = 0; j < n; j++)
			if (i != j)
				order.push_back(make_pair(dist[i][j], j));
		sort(order.begin(), order.end());
		nearest[i].clear();
		for (int j = 0; j < n - 1; j++)
			nearest[i].push_back(order[j].second);
	}
	*/

	//edges �ʱ�ȭ
	edges.clear();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
	sort(edges.begin(), edges.end());

	//cache �ʱ�ȭ
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j <= CACHED_DEPTH; j++)
			cache[i][j].clear();

	//best�� �ſ� ū ������ �ʱ�ȭ
	best = INF;
	vector<bool> visited(n, false);
	vector<int> path(1, 0);
	visited[0] = true;
	search(path, visited, 0);
	return best;
}