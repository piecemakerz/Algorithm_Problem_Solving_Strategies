#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C, N, W;

string name[100];
int weight[100], urgency[100];

vector<string> items;

//cache[start+1][weight] = ������� weight �뷮�� ����� ��,
//start ������ ���ǵ��� ��� ���� �� �ִ� �ִ� ���ڵ��� ��.
int cache[101][1001];
//package[start+1][weight] = ������� weight �뷮�� ����� ��,
//�ִ� ���ڵ��� ��� ���� ��ƾ� �ϴ� start ������ ���� ��ȣ.
int package[101][1001];

//�� Ǯ��. å�� Ǯ�̿� �޸� ���±��� ������ ���ǵ��� �뷮��
//�Լ��� �Է����� �ָ�, å�� 'start+1�� ������ ��°�/���� �ʴ°�'
//�� ������ ���� ������ ���ȣ���� �� �Ͱ� �޸� start+1�� ������
//���ǵ� �� ������ ���� �� �ִ� ��� ���ǿ� ���� ���ȣ���� �Ͽ���.

//����, å�� �亸�� ���� 10�� �̻� ������, �̴� å�� Ǯ�̿� �� Ǯ����
//�κй��� ���� O(NW)�� ������, �� Ǯ�̴� �κ� ������ �ذ��ϴµ� ��� �ð���
//�ɸ��� å�� Ǯ�̿� �޸� O(N)�� �ð��� �ɸ��Ƿ� ��ǻ� �˰����� �ð����⵵��
//O(NW^2)�̱� �����̴�.
int mypack(int start, int totalW) {
	if (totalW > W)
		return 0;

	int& ret = cache[start + 1][totalW];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = start + 1; i < N; i++) {
		int result = mypack(i, totalW + weight[i]);
		if (result > ret) {
			ret = result;
			package[start + 1][totalW] = i;
		}
	}

	ret += urgency[start];
	return ret;
}

void myreconstruct(int start, int curW) {
	int nextitem = package[start + 1][curW];
	if (nextitem == -1)
		return;

	items.push_back(name[nextitem]);
	myreconstruct(nextitem, curW + weight[nextitem]);
}

//å�� ��. ���� �� �α� ������ �ذ��ϴ� ���� ��ȹ�� �˰���
//ĳ��� ���� �뷮�� capacity�� ��, item ������ ���ǵ���
//��� ���� �� �ִ� �ִ� ���ڵ��� ���� ��ȯ�Ѵ�.

//�� �κ� ������ �������� �� ���ۿ� ���� ������ ���� ������ �������� �ʰ�
//���� �������� �� ������, ���� ������ �����ϰ��� �Ѵٸ� bool save[item][capacity]
//�� �����Ͽ�, ������ �� save[item][capacity] == true���
//reconstruct(capacity + weight[item], item+1, picked)�� ȣ���ϰ�, false���
//reconstruct(capacity, item+1, picked)�� ȣ���ϸ� �� ���̴�.
int save[101][1001];
int pack(int capacity, int item) {
	//���� ���: �� ���� ������ ���� ��
	if (item == N) return 0;
	int& ret = cache[item][capacity];
	if (ret != -1) return ret;
	//�� ������ ���� ���� ���
	ret = pack(capacity, item + 1);
	//�� ������ ���� ���
	if (capacity >= weight[item]) {
		ret = max(ret, pack(capacity - weight[item], item + 1) + urgency[item]);
		/*
		int result = pack(capacity - weight[item], item + 1) + urgency[item];
		if (result > ret) {
			ret = result;
			save[item][capacity] = 1;
		}
		*/
	}
	return ret;
}

//å�� ���� �� �α� ������ ���� �������ϴ� ��� ȣ�� �˰���
//pack(capacity, item)�� ������ ���ǵ��� ����� picked�� �����Ѵ�.
//�� ��ü�� cache�� �̹� ����Ǿ� �ֱ� ������ pack�Լ��� ���� ȣ���Ѵٰ�
//�ص� �ð��� �ҿ���� �ʴ´�.
//�ּ� ó���� �κ��� ������ �����Ͽ� �������ϴ� ����̴�.
void reconstruct(int capacity, int item, vector<string>& picked) {
	//���� ���: ��� ������ �� �������
	if (item == N) return;
	/*
	if (save[item][capacity]) {
		picked.push_back(name[item]);
		reconstruct(capacity - weight[item], item + 1, picked);
	}
	else
		reconstruct(capacity, item + 1, picked);
	*/

	//�� ���� ���ٸ� item�� �������� �ʰ� �ִ� ���ڵ��� ���� �� �ִ�.
	if(pack(capacity, item) == pack(capacity, item+1))
		reconstruct(capacity, item + 1, picked);
	//�� ���� �ٸ��ٸ� item�� �����ؾ� �ִ� ���ڵ��� ���� �� �ִ�.
	else {
		picked.push_back(name[item]);
		reconstruct(capacity - weight[item], item + 1, picked);
	}

}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		memset(package, -1, sizeof(package));
		memset(save, 0, sizeof(save));
		
		cin >> N >> W;
		for (int i = 0; i < N; i++)
			cin >> name[i] >> weight[i] >> urgency[i];
		//cout << mypack(-1, 0) << ' ';
		cout << pack(W, 0) << ' ';
		//myreconstruct(-1, 0);
		reconstruct(W, 0, items);
		cout << items.size() << endl;

		for (int i = 0; i < items.size(); i++)
			cout << items[i] << endl;
		items.clear();
	}
	return 0;
}