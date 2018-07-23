#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

int T, Z;
long long N, M;

//å�� Ǯ�̸� �����Ͽ� �ۼ��� �� �˰���.
//������ �𸣰����� �˰����� �Ҿ����ϴ�.
const int MAX = 2000000000;
int findMinWins() {
	long long lo = 0;
	long long hi = MAX;

	if (Z == (int)((((double)M + MAX) / ((double)N + MAX)) * 100))
		return -1;

	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		int result = (((double)M + mid) / ((double)N + mid)) * 100;
		if (result > Z)
			hi = mid;
		else
			lo = mid;
	}
	return hi;
}

//�·� �ø��� ������ �ذ��ϴ� å�� �̺й� �˰���
long long L = 2000000000;
//b���� �� a���� �¸����� ���� �·�
int ratio(long long b, long long a) {
	return (a * 100) / b;
}
//�ּ� �� �����ؾ� �·��� �ö󰥱�?
int neededGames(long long games, long long won) {
	//�Ұ����� ��츦 �̸� �ɷ�����.
	if (ratio(games, won) == ratio(games + L, won + L))
		return -1;
	long long lo = 0, hi = L;
	//�ݺ��� �Һ���:
	//1. lo���� �̱�� �·��� ������ �ʴ´�.
	//2. hi���� �̱�� �·��� ���Ѵ�.
	while (lo + 1 < hi) {
		long long mid = (lo + hi) / 2;
		if (ratio(games, won) == ratio(games + mid, won + mid))
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}

//å�� ���а����� ����� ��� �ð��� ������ �ذ��ϴ� �˰���
int findMinWinsMath() {
	if (Z == ratio(N + L, M + L))
		return -1;

	int aimZ = Z + 1;
	return ceil((double)((aimZ * N) - (100 * M)) / (100 - aimZ));
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		cin >> N >> M;
		//c++������ long double�� double���� ���� ����Ʈ���� ��ȿ���ڸ� ������
		//�ڷ����̳�, M�� double�� ĳ�����ϸ� ������ ������, long double�� ĳ�����ϸ�
		//������ ���´�. å�� ���� ��Ĵ�� 100�� ���� ���� �� ������ ����
		//������ �� �ϴ�.
		Z = ((long double)M / N) * 100;
		cout << findMinWins() << endl;
	}
	return 0;
}