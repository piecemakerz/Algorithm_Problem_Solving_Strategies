#include <vector>
#include <string>
using namespace std;

const int MAX_N = 100;
const int MAX_M = 100;

// A�� B�� ������ ����
int n, m;

// adj[i][j] = A_i �� B_j �� ����Ǿ� �ִ°�?
bool adj[MAX_N][MAX_M];

// �� ������ ��Ī�� ��� ������ ��ȣ�� �����Ѵ�.
vector<int> aMatch, bMatch;

// dfs() �� �湮 ����
vector<bool> visited;

// A�� ������ a���� B�� ��Ī���� ���� �������� ���� ��θ� ã�´�.
bool dfs(int a) {
	if (visited[a]) return false;
	visited[a] = true;
	for (int b = 0; b < m; ++b)
		if (adj[a][b])
			if (bMatch[b] == -1 || dfs(bMatch[b])) {
				// ���� ��� �߰�!! a �� b �� ��ġ��Ų��.
				aMatch[a] = b;
				bMatch[b] = a;
				return true;
			}
	return false;
}

// aMatch, bMatch �迭�� ����ϰ� �ִ� ��Ī�� ũ�⸦ ��ȯ�Ѵ�.
int bipartiteMatch() {
	// ó������ � ������ ����Ǿ� ���� �ʴ�
	aMatch = vector<int>(n, -1);
	bMatch = vector<int>(m, -1);

	int size = 0;
	for (int start = 0; start < n; ++start) {
		visited = vector<bool>(n, false);
		// ���� �켱 Ž���� �̿��� start���� �����ϴ� ���� ��θ� ã�´�
		if (dfs(start))
			++size;
	}
	return size;
}

//���̳�� ���簢�� ä��� ���� �ذ��ϱ�
const int dx[4] = { 1, -1, 0, 0 };
const int dy[4] = { 0, 0, 1, -1 };
//(y, x)�� ���簢�� ���� ���� ĭ���� Ȯ���Ѵ�.
bool inRange(int y, int x);
//���簢���� ����
int H, W;
vector<string> board;
//�־��� ���簢���� ���̳븦 ä�� �� �ִ��� ���θ� ��ȯ�Ѵ�.
bool fillDomino() {
	//�� ĭ�� ǥ���ϴ� ������ ��ȣ�� ����Ѵ�.
	vector<vector<int>> id(H, vector<int>(W, -1));
	//�� ĭ�� ��ȸ�ϸ� ��ȣ�� �ű��.
	n = m = 0;
	for(int y=0; y<H; y++)
		for(int x=0; x<W; x++)
			if (board[y][x] != '#') {
				if ((y + x) % 2 == 0)
					id[y][x] = n++;
				else
					id[y][x] = m++;
			}
	//adj[][]�� ä���.
	memset(adj, 0, sizeof(adj));
	//A�� ���� ��� ĭ�� ���� ������ ĭ�� �˻��Ѵ�.
	for(int y1 = 0; y1<H; y1++)
		for(int x1=0; x1<W; x1++)
			if ((y1 + x1) % 2 == 0 && board[y1][x1] != '#') {
				//(y1, x1)�� ��� ������ ĭ�� �˻��Ѵ�.
				for (int k = 0; k < 4; k++) {
					int y2 = y1 + dy[k], x2 = x1 + dx[k];
					//(y2, x2)�� ���� �ȿ� �ִ� ĭ�̶�� �� ������ �����Ѵ�.
					if (inRange(y2, x2) && board[y2][x2] != '#')
						adj[id[y1][x1]][id[y2][x2]] = 1;
				}
			}
	//�̺� ��Ī�� ũ�Ⱑ �� ĭ�� ���� �����̾�� �Ѵ�.
	return bipartiteMatch() * 2 == (n + m);
}