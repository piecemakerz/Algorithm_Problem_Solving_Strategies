#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MOD = 10000000;
int cache[101][101];

int poly(int n, int first) { // first = �̹� ���� �簢�� ����, second = ���� ���� �簢�� ����
	if (n == first) return 1;
	int& ret = cache[n][first];
	if (ret != -1) return ret;
	ret = 0;
	for (int second = 1; second <= n-first; second++) {
		int add = second + first - 1;
		add *= poly(n - first, second); // �̹� �� �簢�� ��ġ �� ���� �� �簢�� ���� ����
		add %= MOD;
		ret += add;
		ret %= MOD;
	}
	return ret;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		int n;
 		memset(cache, -1, sizeof(cache));
		cin >> n;
		int add = 0;
		for (int i = 1; i <= n; i++) {
			add += poly(n, i);
			add %= MOD;
		}
		cout << add << endl;
	}
	return 0;
}