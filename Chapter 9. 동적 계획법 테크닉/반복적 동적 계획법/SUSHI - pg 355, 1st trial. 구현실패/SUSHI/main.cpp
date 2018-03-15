#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MAX_BUDGET = 1000000000;
int n, m, price[20], pref[20];
int cache[MAX_BUDGET + 1]; // 10�ﰳ¥�� �迭�� ���� ���� ����.
//budget��ŭ�� �������� �ʹ��� �Ծ ���� �� �ִ� �ִ� ��ȣ��
int sushi(int budget) {
	//�޸������̼�
	int& ret = cache[budget];
	if (ret != -1) return ret;
	ret = 0;
	for (int dish = 0; dish < n; dish++) {
		if (budget < price[dish]) continue;
		ret = max(ret, sushi(budget - price[dish]) + pref[dish]);
	}
	return ret;
}
//�ݺ��� ���� ��ȹ���� �����Ͽ� �޸� ��뷮�� ���� �˰���
//int c[20000 + 1]; // ���� budget��ŭ ������ ������ �� ���� �� �ִ� �ִ� ��ȣ�� ��.

int sushi2() {
	int ret = 0;
	for (int budget = 1; budget <= m; budget++) {
		int index = budget % 20001;
		for (int dish = 0; dish < n; dish++) {
			if (budget >= price[dish])
				c[index] = max(c[index], c[(budget - price[dish]) % 20001] + pref[dish]);
		}
		ret = max(ret, c[index]);
	} 
	return ret;
}
//�ִ� ������ ���� ��ȯ�Ѵ�.
//m�� price[]�� �̹� 100���� ������ �ִٰ� �����Ѵ�.
int c[201];
int sushi3() {
	int ret = 0;
	c[0] = 0;
	for (int budget = 1; budget <= m; budget++) {
		int cand = 0;
		for (int dish = 0; dish < n; dish++)
			if (budget >= price[dish])
				cand = max(cand, c[(budget - price[dish]) % 201] + pref[dish]);

		c[budget % 201] = cand;
		ret = max(ret, cand);
	}
	return ret;
}
int main(void) {
	int c;
	cin >> c;
	for (int testCase = 0; testCase < c; testCase++) {
		cin >> n >> m;
		m /= 100;
		for (int i = 0; i < n; i++) {
			cin >> price[i] >> pref[i];
			price[i] /= 100;
		}
		cout << sushi3() << endl;
	}
	return 0;
}