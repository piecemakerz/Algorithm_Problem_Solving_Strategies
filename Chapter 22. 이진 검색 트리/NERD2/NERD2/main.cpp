#include <iostream>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

int C, N;
//���� �ٸ� ���� ��������� �ʴ� ������ ����� �����Ѵ�.
//coords[x] = y
map<int, int> coords;

//�� ���� �ٸ� ���� ������ϴ��� Ȯ���ϴ� �Լ�
//���ο� �� (x, y)�� ������ �ٸ� ���鿡 ������ϴ��� Ȯ���Ѵ�.
bool isDominated(int x, int y) {
	//x���� �����ʿ� �ִ� �� �� ���� ���ʿ� �ִ� ���� ã�´�.
	map<int, int>::iterator it = coords.lower_bound(x);
	//�׷� ���� ������ (x, y)�� ��������� �ʴ´�.
	if (it == coords.end()) return false;
	//�� ���� x���� �����ʿ� �ִ� �� �� ���� ���� �ִ� ���̹Ƿ�,
	//(x, y)�� ��� ���� ����Ƿ��� �� ������ ����Ǿ�� �Ѵ�.
	return y < it->second;
}

//����Ǵ� ������ �����ϴ� �Լ�
//���ο� �� (x, y)�� ������ϴ� ������ Ʈ������ �����.
void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	//(x, y)���� ���ʿ� �ִ� ���� ���� ���
	if (it == coords.begin()) return;
	--it;
	//�ݺ��� �Һ���: it�� (x, y)�� �ٷ� ���ʿ� �ִ� ��
	while (true) {
		//(x, y) �ٷ� ���ʿ� ���� ���� ã�´�.
		//it�� ǥ���ϴ� ���� (x, y)�� ������� �ʴ´ٸ� ���� ����
		if (it->second > y) break;
		//���� ���� �� �����Ƿ� it�� ����� �����Ѵ�.
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		//���� ������ �ݺ��ڸ� �ϳ� �Ű� ���� it�� �����.
		else {
			map<int, int>::iterator jt = it;
			jt--;
			coords.erase(it);
			it = jt;
		}
	}
}
//�� �� (x, y)�� �߰��Ǿ��� �� coords�� �����ϰ�,
//�ٸ� ���� ��������� �ʴ� ������ ������ ��ȯ�Ѵ�.
int registered(int x, int y) {
	//(x, y)�� �̹� ������ϴ� ��쿡�� �׳� (x, y)�� ������.
	if (isDominated(x, y)) return coords.size();
	//������ �ִ� �� �� (x, y)�� ������ϴ� ������ �����.
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		int prob, ramen, ret = 0, possCnt = 0;
		cin >> N;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &prob, &ramen);
			p.insert(make_pair(prob, ramen));
		}
		
		cout << ret << endl;
		p.clear();
	}
}