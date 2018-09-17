#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

//�׷��� �𵨸��� ���� ��̳� ������ �ذ��Ѵ� �˰���

//���� ���� ��ȣ�� here�̶��, ���� ��ȣ edge��
//������ �� ������ ������ ��ȣ��?
int append(int here, int edge, int mod) {
	int there = here * 10 + edge;
	if (there >= mod) return mod + there % mod;
	return there % mod;
}
//digits�� ���� ���ڵ鸸���� �����ǰ�,
//C mod n == m�� �ּ��� C�� ã�´�.
string gifts(string digits, int n, int m) {
	//������ ��ȣ�� ������������ ������ �θ� ���������� ���� �տ�
	//�ִ� ��θ� ã�� �� �ִ�.
	sort(digits.begin(), digits.end());
	//��� ���� i�� 0~n-1, ȸ�� ���� i�� n~2n-1�� ǥ���Ѵ�.
	//parent[i] = BFS ���д� Ʈ������ ���� i�� �θ�
	//choice[i]=parent[i] ���� i�� ����� ������ ��ȣ
	vector<int> parent(2 * n, -1), choice(2 * n, -1);
	queue<int> q;
	//��� 0���� ť�� �߰�
	parent[0] = 0;
	q.push(0);

}