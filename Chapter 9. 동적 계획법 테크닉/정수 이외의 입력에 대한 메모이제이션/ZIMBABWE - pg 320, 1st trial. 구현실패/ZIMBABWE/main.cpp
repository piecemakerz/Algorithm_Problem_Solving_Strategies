#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//digits: e�� �ڸ������� ������ ��
string e, digits;
int n, m;
const int MOD = 1000000007;

//������� ������ ���� ��� ã�� ���� Ž�� �˰���
//e�� �ڸ����� ���� �� �ִ� ���ڵ��� ��� ����Ѵ�.
//price: ���ݱ��� ���� ����
//taken: �� �ڸ����� ��� ����
void generate(string price, bool taken[15]) {
	//���� ���
	if (price.size() == n) {
		if (price < e)
			cout << price << endl;
		return;
	}
	for(int i=0; i<n; i++)
		if (!taken[i] && (i == 0 || digits[i - 1] != digits[i] || taken[i - 1])) {
			taken[i] = true;
			generate(price + digits[i], taken);
			taken[i] = false;
		}
}

//������� ������ �ذ��ϴ� ���� ��ȹ�� �˰���

int cache[1 << 14][20][2];
//���� ������ �� �ڸ����� ä�������� �ִ�.
//index: �̹��� ä�� �ڸ��� �ε���
//taken: ���ݱ��� ����� �ڸ������� ����
//mod: ���ݱ��� ���� ������ m�� ���� ������
//less: ���ݱ��� ���� ������ �̹� e���� ������ 1, �ƴϸ� 0
int price(int index, int taken, int mod, int less) {
	//���� ���
	if (index == n)
		return (less && mod == 0) ? 1 : 0;
	//�޸������̼�
	int& ret = cache[taken][mod][less];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = 0; next < n; next++) 
		if ((taken & (1 << next)) == 0) {
			//���� ������ �� ���ݺ��� �׻� �۾ƾ߸� �Ѵ�.
			if (!less && e[index] < digits[next])
				continue;
			//���� ���ڴ� �� ���� �����Ѵ�.
			if (next > 0 && digits[next - 1] == digits[next] && (taken & (1 << (next - 1))) == 0)
				continue;
			int nextTaken = taken | (1 << next);
			int nextMod = (mod * 10 + digits[next] - '0') % m;
			int nextLess = less || e[index] > digits[next];
			ret += price(index + 1, nextTaken, nextMod, nextLess);
			ret %= MOD;
		}
	return ret;
}