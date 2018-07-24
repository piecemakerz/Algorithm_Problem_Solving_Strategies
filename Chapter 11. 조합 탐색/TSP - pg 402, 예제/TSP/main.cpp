#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>
using namespace std;

const double INF = 1e200;
const int MAX = 30;
int n; // ������ ��
double dist[MAX][MAX]; // �� ���ð��� �Ÿ��� �����ϴ� �迭

//best: ���ݱ��� ã�� ������. ���� ������ ���ݱ��� ã�� �������� ���̸�
//������ �θ� Ž�� �߿� �� �����ظ� �߰��� ���ɼ��� ���� ������
//�ĳ��� ��������.
double best;

//TSP�� �ذ��ϴ� ���� Ž���� ����

//path: ���ݱ��� ���� ���
//visited: �� ������ �湮 ����
//currentLength: ���ݱ��� ���� ����� ����
//������ ���õ��� ��� �湮�ϴ� ��ε��� ����� ���� �����ϸ� �����ظ� �����Ѵ�.
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//������ ����ġ��: ���ݱ��� ã�� ���� ���� �� �̻��� ��� �ߴ�
	if (best <= currentLength) return;
	int here = path.back();
	//���� ���: ��� ���ø� �� �湮���� ���� 0�� ���÷� ���ư��� �����Ѵ�.
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//���� �湮�� ���ø� ���� �õ��� ����.
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

//�ܼ��� �޸���ƽ�� �̿��� ����ġ���� ����

//�� ���ÿ� ������ ���� �� ���� ª�� ���� �̸� ã�� �д�.
double minEdge[MAX];
//���� �ܼ��� ������ �޸���ƽ. ���� �湮���� ���� ���õ鿡 ����
//������ ���� �� ���� ª�� ������ ���̸� ���Ѵ�. �� ������ �ߺ����õ�
//�����ϴ�.
double simpleHeuristic(vector<bool>& visited) {
	double ret = minEdge[0]; //�������� ���������� ���ư� �� ����� ����
	for (int i = 0; i < n; i++)
		if (!visited[i])
			ret += minEdge[i];
	return ret;
}
//�ܼ��� �޸���ƽ�� ������ search �˰���
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//�ܼ��� �޸���ƽ�� �̿��� ����ġ��
	if (best <= currentLength + simpleHeuristic(visited)) return;
	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	for (int next = 0; next < n; next++) {
		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

//����� �������� �湮�ϴ� ����ȭ�� ����. ���ø� ��ȣ ������� �湮�ϴ� ���,
//�� ����� �ͺ��� �湮�ϸ� ���� ���� �� ���� ã�Ƴ� �� �ִ� ��찡 �ִ�.
vector<int> nearest[MAX];
//����� �������� �湮�ϴ� ����ȭ�� ������ search �˰���
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//�ܼ��� �޸���ƽ�� �̿��� ����ġ��
	if (best <= currentLength + simpleHeuristic(visited)) return;
	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//���� �湮�� ���ø� ���� �õ��� ����.
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];

		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

//������ ��θ� �̿��ϴ� �� ���� ����ġ�� ������ ����

//path�� ������ �� ���� ���� �� ��� �ִ� �� ������ ������ �ٲ��� ��
//��ΰ� �� ª�������� ���θ� ��ȯ�Ѵ�. �� ª�����ٸ� ���� ��ȯ�Ѵ�.
bool pathSwapPruning(const vector<int>& path) {
	if (path.size() < 4) return false;
	int p = path[path.size() - 4];
	int a = path[path.size() - 3];
	int b = path[path.size() - 2];
	int q = path[path.size() - 1];
	return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}
//���� ���ÿ� ���� ���ø� ������ path�� ��� �κ� ��θ�
//������ ���� �� ª�������� Ȯ���Ѵ�. �� ª�����ٸ� ���� ��ȯ�Ѵ�.
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

//������ ��θ� �̿��� ����ġ�⸦ �ϴ� ����ȭ�� ������ search �˰���
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//�ܼ��� �޸���ƽ�� �̿��� ����ġ��
	if (best <= currentLength + simpleHeuristic(visited)) return;
	//�κ� ��θ� �������� �� ��� ���̰� ª�����ٸ� �����ذ� �ƴϹǷ� �ٷ� �����Ѵ�.
	if (pathReversePruning(path)) return;

	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//���� �湮�� ���ø� ���� �õ��� ����.
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];

		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

//MST �޸���ƽ�� ����. 

//Union-Find ��ȣ ������ ���� (���� ���Ұ� ���� ����)�ڷ� ������ �����Ѵ�.
//Union-Find�� Disjoint Set���ε� �Ҹ��� ��ȣ ����������
//�̷���� ������ ȿ�������� ǥ���ϱ� ���� ������� �ڷᱸ����,
//ũ�罺Į �˰��򿡼� ���� ���� ���� ���θ� �Ǵ��ϴµ� ����Ѵ�.
//
struct UnionFind
{
	//n = ����� �� ����, componenets = ������ ����
	int n, components;
	//parent[i] = i�� ���� ������ Ʈ�������� i�� �θ� ��� ��ȣ
	//rank[i] = i�� ���� ������ Ʈ�� ����
	vector<int> parent, rank;
	//��ȣ ������ ������ �ʱ�ȭ�� ���� �� ��忡 �����ϴ� ������ �ϳ��� �����Ѵ�.
	UnionFind(int n) : n(n), components(n), parent(n), rank(n)
	{
		for (int i = 0; i < n; ++i) { parent[i] = i; rank[i] = 0; }
	}
	//find(here) = here�� ���� ������ Ʈ�� ��Ʈ ��� ��ȣ�� ��ȯ�Ѵ�.
	int find(int here) { return parent[here] == here ? here : (parent[here] = find(parent[here])); }
	//merge(a, b) = a�� ���� ���հ� b�� ���� ������ ��ģ��.
	//a�� b�� ���� ���տ� �����ִٸ� false�� ��ȯ�Ѵ�.
	bool merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return false;
		//a ������ ���̰� b ���պ��� ���ٸ� b ������ a ���� ��Ʈ�� �Ʒ��� ��ģ��.
		if (rank[a] > rank[b])
			parent[b] = a;
		else
		{
			parent[a] = b;
			//��ġ���� �� ������ ���̰� ���� ���ٸ� ������ ���� Ʈ���� ���̸� �ϳ� ������Ų��.
			if (rank[a] == rank[b]) rank[b]++;
		}
		--components;
		return true;
	}
};

//��� ���� ���� ���θ� ���� ������ ������ ������ �д�.
vector<pair<double, pair<int, int>>> edges;
//here�� ������, ���� �湮���� ���� ���õ��� ��� �����ϴ� MST�� ã��
//MST�� ���̸� ��ȯ�Ѵ�.
double mstHeuristic(int here, const vector<bool>& visited) {
	//Kruskal's MST
	UnionFind sets(n);
	double taken = 0;
	for (int i = 0; i < edges.size(); i++) {
		int a = edges[i].second.first, b = edges[i].second.second;
		if (a != 0 && a != here && visited[a]) continue;
		if (b != 0 && b != here && visited[b]) continue;
		if (sets.merge(a, b))
			taken += edges[i].first;
	}
}

//MST �޸���ƽ�� �̿��� ����ġ�⸦ ������ search �˰���
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	//MST �޸���ƽ�� �̿��� ����ġ��
	if (best <= currentLength + mstHeuristic(path.back(), visited)) return;
	//�κ� ��θ� �������� �� ��� ���̰� ª�����ٸ� �����ذ� �ƴϹǷ� �ٷ� �����Ѵ�.
	if (pathReversePruning(path)) return;

	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	//���� �湮�� ���ø� ���� �õ��� ����.
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];

		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}

//�κ������� �޸������̼��� ����ϴ� ����ȭ�� ����

//���� ������ ���� CACHED_DEPTH ���ϸ� ���� ��ȹ������ �ٲ۴�.
const int CACHED_DEPTH = 5;
//dp()���� cache�� ���� ��ġ, ���� ������ ���� �ε����� ���� map�� 2���� �迭��,
//��ǻ� 3���� �迭�̴�. map�� �����ϴ� ����� ������ ���� Ŀ���� Ŀ������ �þ�Ƿ�,
//���� ������ ������ map�� ������ �����ϴ� �� ��� �ð��� �����̳��� ���� �� �ִ�.
//dp(here, visited) = cache[here][���� ������ ��][visited]
map<int, double> cache[MAX][CACHED_DEPTH + 1];
//here: ���� ��ġ
//visited: �� ������ �湮 ����
//�� ��, ������ ���ø� ��� �湮�ϰ� ���������� ���ư��� �ִ� ����� ���̸� ��ȯ�Ѵ�.
double dp(int here, int visited) {
	bitset<24> bitVisited(visited);
	//���� ���: �� �湮�� ���ð� ������ ���������� ���ư���.
	if (visited == (1 << n) - 1) return dist[here][0];
	//�޸������̼�
	//__builtin_popcount(i)�� i�� ���Ե� 1��Ʈ�� ���� ��ȯ�ϴ� �Լ���,
	//GCC�� �����ϴ� ������� visual c++������ ����� �� ����. ����
	//visited�� bitset���� ��ȯ�Ͽ� bitset�� �����Լ��� ����Ͽ���.
	int remaining = n - bitVisited.count();
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

//�κ��� �޸������̼��� ������ search �˰���
void search(vector<int>& path, vector<bool>& visited, double currentLength) {
	if (best <= currentLength + mstHeuristic(path.back(), visited)) return;
	//���� ���: ���� ���� ���� CACHED_DEPTH ���ϸ� ���� ��ȹ������ �ٲ۴�.
	/*if (path.size() + CACHED_DEPTH >= n) {
		best = min(best, currentLength + dp(path.back(), visited));
		return;
	}
	*/
	int here = path.back();
	if (path.size() == n) {
		best = min(best, currentLength + dist[here][0]);
		return;
	}
	for (int i = 0; i < nearest[here].size(); i++) {
		int next = nearest[here][i];

		if (visited[next]) continue;
		path.push_back(next);
		visited[next] = true;
		search(path, visited, currentLength + dist[here][next]);
		visited[next] = false;
		path.pop_back();
	}
}
double solve() {
	//cache �ʱ�ȭ
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j <= CACHED_DEPTH; j++)
			cache[i][j].clear();

	//edges �ʱ�ȭ
	edges.clear();
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
	sort(edges.begin(), edges.end());

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

	//simpleHeuristic()�� ���� �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		minEdge[i] = INF;
		for (int j = 0; j < n; j++)
			if (i != j) minEdge[i] = min(minEdge[i], dist[i][j]);
	}

	//best�� �ſ� ū ������ �ʱ�ȭ
	best = INF;
	vector<bool> visited(n, false);
	vector<int> path(1, 0);
	visited[0] = true;
	search(path, visited, 0);
	return best;
}