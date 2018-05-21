#include <vector>
#include <iostream>
using namespace std;

//������ �����ϴ� ���� �켱 Ž���� ����

//�׷����� ���� ����Ʈ ǥ��
vector<vector<int>> adj;
//discovered[i] = i�� ������ �߰� ����
//finished[i] = dfs(i)�� ���������� 1, �ƴϸ� 0
vector<int> discovered, finished;
//���ݰ��� �߰��� ������ ��
int counter;
void dfs2(int here) {
	discovered[here] = counter++;
	//��� ���� ������ ��ȸ�ϸ鼭
	for (int i = 0; i < adj[here].size(); i++) {
		int there = adj[here][i];
		cout << "(" << here << "," << there << ") is a ";
		//���� �湮�� �� ���ٸ� �湮�Ѵ�.
		if (discovered[there] == -1) {
			cout << "tree edge" << endl;
			dfs2(there);
		}
		//���� there�� here���� �ʰ� �߰߉����� there�� here�� �ļ��̴�.
		else if (discovered[here] < discovered[there])
			cout << "forward edge" << endl;
		//���� dfs(there)�� ���� ������� �ʾ����� there�� here�� ������.
		else if (finished[there] == 0)
			cout << "back edge" << endl;
		//�� ���� ���� ��� ���� ����
		else
			cout << "cross edge" << endl;
	}
	finished[here] = 1;
}
