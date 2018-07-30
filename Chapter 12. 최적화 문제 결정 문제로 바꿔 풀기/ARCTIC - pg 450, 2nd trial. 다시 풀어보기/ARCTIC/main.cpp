#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

int C, N;
//mindis = ������ �����ϴ� ��� ���� �� ���� ª�� ����
//maxdis = ������ �����ϴ� ��� ���� �� ���� �� ����
double mindis, maxdis;
const double MAX = 987654321.0;
//coord[i] = (i�� y��ǥ, i�� x��ǥ)
vector<pair<double, double>> coord;
//dist[i][j] = i�� ������ j�� ������ �����ϴ� ������ ����
double dist[100][100];

vector<pair<double, pair<int, int>>> edges;
int visited[100];

//�� ���� ������ ���̸� ����ϰ�, mindis�� maxdis�� �����Ѵ�.
void generateDistance() {
	mindis = MAX, maxdis = 0;
	for (int i = 0; i < N; i++) {
		double x1 = coord[i].second, y1 = coord[i].first;
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			double x2 = coord[j].second, y2 = coord[j].first;
			dist[i][j] = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			if (mindis > dist[i][j]) mindis = dist[i][j];
			if (maxdis < dist[i][j]) maxdis = dist[i][j];
			edges.push_back(make_pair(dist[i][j], make_pair(i, j)));
		}
	}
	sort(edges.begin(), edges.end());
}

//��� ������ �ϳ��� �����ϵ�, ���� �� �� ���� ���� �Ÿ��� d
//������ �������� �ִ°�?
bool solve(double gap) {
	int selected[100];
	memset(selected, 0, sizeof(selected));
	queue<int> q;
	q.push(0);
	selected[0] = 1;

	while(!q.empty()) {
		int curPos = q.front();
		for (int i = 0; i < N; i++) {
			if (i == curPos || selected[i]) continue;

			if (dist[curPos][i] <= gap) {
				selected[i] = 1;
				q.push(i);
			}
		}
		q.pop();
	}
	for (int i = 0; i < N; i++)
		if (!selected[i])
			return false;
	return true;
}

//������ �ּ� ��� �ݰ��� ��ȯ�Ѵ�.
double myoptimize() {
	double lo = mindis, hi = maxdis;
	//�ݺ��� �Һ���: !solve(lo) && solve(hi)
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2.0;
		//�ݰ��� mid�� �� ��� ������ ����� �� �ִٸ� ���� [lo, mid]�� �ִ�.
		if (solve(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

//ũ�罺Į�� �ּ� ���д� Ʈ�� �˰������� �ذ��� ���
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

double MSTsolve() {
	UnionFind sets(N);
	double maxLen = 0;
	for (int i = 0; i < edges.size(); i++) {
		int a = edges[i].second.first, b = edges[i].second.second;
		if (sets.merge(a, b))
			maxLen = max(maxLen, edges[i].first);
	}
	return maxLen;
}

//å�� ���� ���� ������ ���� ������ �ٲ� �ذ��ϴ� �̺й� �˰���
//�׷����� �ʺ� �켱 Ž�� �˰����� �̿��Ѵ�. ���� �Ÿ��� d ������
//������ ���� ������ �ִٰ� �����ϰ� �׷����� ���� ��, �� ��������
//������ Ž�� �˰����� �̿��� �ٸ� �������� ���� �湮�� �� �ִ����� Ȯ���Ѵ�.

//�Ÿ� d ������ �����鸸�� �������� �� ��� ������ ����Ǵ��� ���θ� ��ȯ�Ѵ�.
bool decision(double d) {
	vector<bool> visited(N, false);
	visited[0] = true;
	queue<int> q;
	q.push(0);
	int seen = 0;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		seen++;
		for(int there = 0; there < N; there++)
			if (!visited[there] && dist[here][there] <= d) {
				visited[there] = true;
				q.push(there);
			}
	}
	return seen == N;
}
//��� ������ ������ �� �ִ� �ּ��� d�� ��ȯ�Ѵ�.
double optimize() {
	double lo = 0, hi = 1416.00;
	for (int it = 0; it < 100; it++) {
		double mid = (lo + hi) / 2;
		//mid�� �����ϴٸ�, �� ���� (����) ���� ã�´�.
		if (decision(mid))
			hi = mid;
		//mid�� �Ұ����ϴٸ�, �� ���� (ū) ���� ã�´�.
		else
			lo = mid;
	}
	return hi;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> N;
		coord = vector<pair<double, double>>(N);
		double x, y;
		for (int i = 0; i < N; i++) {
			cin >> x >> y;
			coord[i] = make_pair(y, x);
		}
		generateDistance();
		printf("%.2f\n", MSTsolve());
		coord.clear();
		edges.clear();
	}
}