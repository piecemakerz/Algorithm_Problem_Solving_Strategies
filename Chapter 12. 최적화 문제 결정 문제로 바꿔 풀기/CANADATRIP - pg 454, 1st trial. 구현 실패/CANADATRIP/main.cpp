#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

int n, k;
int l[5000], m[5000], g[5000];
//���� ����: dist �������� ���鼭 k�� �̻��� ǥ������ ���� �� �ִ°�?
bool decision(int dist) {
	int ret = 0;
	for (int i = 0; i < n; i++)
		//i��° ���� ǥ������ �ϳ� �̻� ���� �Ǵ°�?
		if (dist >= l[i] - m[i])
			ret += (min(dist, l[i]) - (l[i] - m[i])) / g[i] + 1;
	return ret >= k;
}
// k��° ǥ������ ������ ������ ��ġ�� ����Ѵ�.
int optimize() {
	//�ݺ��� �Һ���: decision(lo) == false, decision(hi) == true
	int lo = -1, hi = 8030001;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (decision(mid))
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}