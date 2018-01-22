#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;
//�ߺ��� �������� ���� ���� ��� �˰���
int bino(int n, int r) {
	if (r == 0 || n == r) return 1;
	return bino(n - 1, r - 1) + bino(n - 1, r);
}

//�޸������̼��� �̿��� (ĳ�� �迭 ����) �ߺ��� ������ ���� ��� �˰���
int cache[30][30];
int bino2(int n, int r) {
	if (r == 0 || n == r) return 1;
	if (cache[n][r] != -1) {
		return cache[n][r];
	}
	return cache[n][r] = bino2(n - 1, r - 1) + bino2(n - 1, r);
}

int main(void) {
	memset(cache, -1, sizeof(cache)); // memset���� ���� �迭�� 0 Ȥ�� -1�� ä�� �� �ִ�.
	clock_t start, end;
	double duration;

	start = clock();
	cout<<bino(29, 15)<<endl;
	end = clock();
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "�ɸ� �ð� : " << duration << "��"<< endl;

	memset(cache, -1, sizeof(cache));

	start = clock();
	cout << bino2(29, 15) << endl;
	end = clock();
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "�ɸ� �ð� : " << duration << "��" << endl;
	
}