#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int T, N, K;
int L[5000], M[5000], G[5000];
int numOfSigns[8030001];

//ĳ���� ���� ������ �ذ��ϴ� �� ������ �˰���
//�ð��ʰ��� �߻��Ѵ�.
int simpleSolve() {
	//�� �κп��� �ð��ʰ��� �߻��Ѵ�.
	//numOfSigns�� ���� �����ϴ� ������ �� ǥ���� ������ŭ �̷�����µ�,
	//�� ǥ���� ������ ��� k �̻��̸� k�� �ص� �ִ��� 2^31-1�̱� �����̴�. 
	for (int i = 0; i < N; i++)
		for (int j = L[i] - M[i]; j <= L[i]; j += G[i])
			numOfSigns[j]++;

	int curSigns = 0;
	for (int i = 0; i < 8030001; i++) {
		curSigns += numOfSigns[i];
		if (curSigns >= K)
			return i;
	}
	return -1;
}

//ĳ���� ���� ������ ���� ������ �ٲ� Ǫ�� �̺й� �˰���

//���� ����: dist �������� ���鼭 k�� �̻��� ǥ������ ���� �� �ִ°�?
bool decision(int dist) {
	int ret = 0;
	for (int i = 0; i < N; i++)
		//i��° ���� ǥ������ �ϳ� �̻� ���� �Ǵ°�?
		if (dist >= L[i] - M[i])
			ret += (min(dist, L[i]) - (L[i] - M[i])) / G[i] + 1;
	return ret >= K;
}
//k��° ǥ������ ������ ������ ��ġ�� ����Ѵ�.
int optimize() {
	//�ݺ��� �Һ���: !decision(lo) && decision(hi)
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

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		memset(numOfSigns, 0, sizeof(numOfSigns));
		cin >> N >> K;
		for (int i = 0; i < N; i++)
			scanf("%d %d %d", &L[i],  &M[i], &G[i]);
		cout << simpleSolve() << endl;
	}
}