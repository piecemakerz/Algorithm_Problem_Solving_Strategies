#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
//ũ�罺Į �˰����� ����ġ(�Ÿ�)�� ���� ª�� ���е��� �켱������ ���� ������ �� ������ ������ �� ���� ���̴�.
//���� �׷����� ����� ���� ���¿��� �����õ��� ������, ���߿� ũ�罺Į �˰������� �����غ���.

int C, N;
// �� ���� ������ �Ÿ��� �̸� ����صд�.
double dist[100][100];
// �Ÿ��� d ������ �����鸸�� �������� �� ��� ������ ����Ǵ��� ���θ� ��ȯ�Ѵ�.
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
		for (int there = 0; there < N; there++) {
			if (!visited[there] && dist[here][there] <= d) { // ���� ������ �湮���� �ʾҰ� �Ÿ��� d������ ��
				visited[there] = true;
				q.push(there);
			}
		}
		return seen == N;
	}
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