#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int C, n, m;
vector<int> preference;
vector<int> prices;

//int cache[21474837];

//ȸ���ʹ� ������ �ذ��ϴ� �� �޸������̼� ���� ��ȹ�� �˰���
//������� curPrice�� �ݾ��� ������� ��, ���� �ݾ��� ��� 
//����Ͽ� ���� �� �ִ� �ִ� ��ȣ�� ���� ��ȯ�Ѵ�.
//�� Ǯ�̴� �뷫 20�ﰳ�� int�� �����ϴ� �迭�� ��ƾ��ϱ� ������
//���� �����÷ΰ� �߻��Ѵ�.
/*
int sushi(int curPrice) {
	int& ret = cache[curPrice];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = 0; i < n; i++)
		if (curPrice + prices[i] <= m)
			ret = max(ret, preference[i] + sushi(curPrice + prices[i]));

	return ret;
}
*/

//å�� ȸ���ʹ� ������ �ذ��ϴ� �ݺ��� ���� ��ȹ�� �˰���
int c[200];
//�ִ� �������� ���� ��ȯ�Ѵ�.
//m�� price[]�� �̹� 100���� ������ �ִٰ� �����Ѵ�.
int sushi3() {
	int ret = 0;
	c[0] = 0;
	for (int budget = 1; budget <= m; budget++) {
		//c[budget % 201]�� ���� ����� ���� ����� �����̹Ƿ� 0���� �ʱ�ȭ�Ѵ�.
		//c[budget % 201]�� ����ϱ� ���� c[budget % 201]�� ���� ����� ���� �����Ƿ� 0���� �ʱ�ȭ�ص�
		//�Ի꿡 ������ ��ġ�� �ʴ´�.
		c[budget % 201] = 0;
		for (int dish = 0; dish < n; dish++)
			if (budget >= prices[dish])
				c[budget % 201] = max(c[budget % 201], c[(budget - prices[dish]) % 201] + preference[dish]);
		ret = max(ret, c[budget % 201]);
	}
	return ret;
}
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(c, 0, sizeof(c));
		cin >> n >> m;
		m /= 100;
		int price, pref;
		for (int i = 0; i < n; i++) {
			cin >> price >> pref;
			price /= 100;
			prices.push_back(price);
			preference.push_back(pref);
		}
		cout << sushi3() << endl;
		prices.clear();
		preference.clear();
	}
	return 0;
}