#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
//digits: e�� �ڸ������� ������ ��
string e, digits;
int n, m;
int cache[1 << 14][20][2];
//���� ������ �� �ڸ����� ä�������� �ִ�.
//index: �̹��� ä�� �ڸ��� �ε���
//taken: ���ݱ��� ����� �ڸ������� ����
//mod: ���ݱ��� ���� ������ m�� ���� ������
//less: ���ݱ��� ���� ������ �̹� e���� ������ 1, �ƴϸ� 0
int price(int index, int taken, int mod, int less) {
	//���� ���

	
}
