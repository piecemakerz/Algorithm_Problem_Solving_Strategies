#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

int C, V, M, N;
const int MAX_V = 200;
int adj[MAX_V][MAX_V];

//�� ������ �׷����� �߰��Ǿ��� �� �ִ� �Ÿ��� �����ϴ� å�� �˰���

//���� (a, b)�� �߰����� �� �׷����� �ִ� �Ÿ� �迭 adj��
//������ �����Ѵ�. ������ �ƹ��� �ǹ̰� ���� ��� false�� ��ȯ�Ѵ�.
bool update(int a, int b, int c) {
	if (adj[a][b] <= c) return false;
	for (int x = 0; x < V; x++)
		for (int y = 0; y < V; y++)
			//x~y �ִܰ�ΰ� (a, b)�� �̿��Ϸ���
			//x~a-b~y Ȥ�� x~b-a~y�� ���¸� ������ �Ѵ�.
			adj[x][y] = min(adj[x][y],
				min(adj[x][a] + c + adj[b][y], adj[x][b] + c + adj[a][y]));
}