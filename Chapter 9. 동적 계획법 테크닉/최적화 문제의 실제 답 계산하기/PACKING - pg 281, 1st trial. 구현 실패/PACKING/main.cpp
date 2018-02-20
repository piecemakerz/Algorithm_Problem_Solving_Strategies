#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

//�� Ǯ�̷� �ִ� ���ڵ� ���� ���� �� �־����� ������ ���ǵ��� ������ ������ ���ǵ��� �̸� ����� �Ұ����ߴ�.
//�� Ǯ�̿����� ���� �뷮�� capacity ��� ������� ������ ���ǵ��� �뷮 ���� ����߾���.
int n, capacity;
int volume[100], need[100];
int cache[1001][100]; // cache[���� �뷮][item]
string name[100];
int pickedNum;
//ĳ��� ���� �뷮�� capacity�� ��, item ������ ���ǵ��� ���
//���� �� �ִ� �ִ� ���ڵ��� ���� ��ȯ�Ѵ�.
int pack(int capacity, int item) {
	// ���� ���: �� ���� ������ ���� ��
	if (item == n) return 0;
	int& ret = cache[capacity][item];
	if (ret != -1) return ret;
	//item�� ���� ���� ���
	ret = pack(capacity, item + 1);
	//item�� ���� ���
	if (capacity >= volume[item]) {
		ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
	}
	return ret;
}
//pack(capacity, item)�� ������ ���ǵ��� ����� picked�� �����Ѵ�.
void reconstruct(int capacity, int item, vector<string>& picked) {
	//���� ���: ��� ������ �� �������
	if (item == n) return;
	if (pack(capacity, item) == pack(capacity, item + 1)) {
		reconstruct(capacity, item + 1, picked);
	}
	else {
		picked.push_back(name[item]);
		pickedNum++;
		reconstruct(capacity - volume[item], item + 1, picked);
	}
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		pickedNum = 0;
		memset(cache, -1, sizeof(cache));
		vector<string> pickedItems;
		cin >> n >> capacity;
		for (int i = 0; i < n; i++) {
			cin >> name[i] >> volume[i] >> need[i];
		}
		cout << pack(capacity, 0) << ' ';
		reconstruct(capacity, 0, pickedItems);
		cout << pickedNum << endl;
		for (int i = 0; i < pickedItems.size(); i++)
			cout << pickedItems[i] << endl;
	}
	return 0;
}