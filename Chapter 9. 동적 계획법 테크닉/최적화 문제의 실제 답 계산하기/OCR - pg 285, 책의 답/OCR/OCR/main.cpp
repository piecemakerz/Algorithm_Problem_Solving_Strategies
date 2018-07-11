#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m;
//�з��Ⱑ ��ȯ�� ����. �ܾ� ��ȣ�� ��ȯ�Ǿ� ����.
int R[100];
//T[i][j] = i�ܾ� ���Ŀ� j�ܾ ���� Ȯ���� �αװ�
double T[501][501];
//M[i][j] = i�ܾ j�ܾ�� �з��� Ȯ���� �α� ��
double M[501][501];
int choice[102][502];
double cache[102][502]; // 1�� �ʱ�ȭ�Ѵ�.

//å�� ���� ���� �ν� ������ �ذ��ϴ� ���� ��ȹ�� �˰���
//Q[segment] ���ĸ� ä���� ���� �� �ִ� �ִ� g() ���� �α� ���� ��ȯ�Ѵ�.
//Q[segment-1] == previousMatch��� �����Ѵ�.
double recognize(int segment, int previousMatch) {
	if (segment == n) return 0;
	double& ret = cache[segment][previousMatch];
	if (ret != 1.0) return ret;
	ret = -1e200; //log(0) = ���� ���Ѵ뿡 �ش��ϴ� ��
	int& choose = choice[segment][previousMatch];
	//R[segment]�� �����Ǵ� �ܾ ã�´�.
	for (int thisMatch = 0; thisMatch < m; thisMatch++) {
		//g(thisMatch) = T(previousMatch, thisMatch) * M(thisMatch, R[segment])
		double cand = T[previousMatch][thisMatch] + M[thisMatch][R[segment]]
			+ recognize(segment + 1, thisMatch);
		if (ret < cand) {
			ret = cand;
			choose = thisMatch;
		}
	}
	return ret;
}

//���� ���� �ν� ������ ���� �� ����ϱ�
//�Է¹��� �ܾ���� ���
string corpus[50];
string reconstruct(int segment, int previousMatch) {
	int choose = choice[segment][previousMatch];
	string ret = corpus[choose];
	if (segment < n - 1)
		ret = ret + " " + reconstruct(segment + 1, choose);
	return ret;
}