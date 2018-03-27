#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

const int INF = 987654321;
const int WHITE = 1;
const int BLACK = 0;

int maskSum[1024], maskLen[1024];
void calcMasks() {
	memset(maskSum, 0, sizeof(maskSum));
	memset(maskLen, 0, sizeof(maskLen));
	for (int mask = 0; mask < 1024; mask++) {
		for (int i = 0; i < 10; i++)
			if (mask & (1 << i)) {
				maskSum[mask] += i;
				maskLen[mask]++;
			}
	}
}
//mask�� ���� ������ ������ ��ȯ�Ѵ�.
int getSize(int mask) { return maskLen[mask]; }
//mask�� ���� ���ҵ��� ���� ��ȯ�Ѵ�
int getSum(int mask) { return maskSum[mask]; }

//len ĭ�� ���� sum�̰�, �� ĭ�鿡 �̹� ���� ���� ������ known �� ��
//������ ĭ�� �� �� �ִ� ������ ������ ��ȯ�Ѵ�.
int getCandidates(int len, int sum, int known) {
	int allSets = 0;
	// 1~9�� �κ������� ��� �����ϰ�, �� ��
	for (int set = 0; set < 1024; set += 2)
		//known�� �����ϰ�, ũ�Ⱑ len�̸�, ���� sum�� ������ ��� ã�´�.
		if ((set & known) == known && getSize(set) == len && getSum(set) == sum)
			allSets |= set;
	//known�� �̹� ���� ���ڵ��� �信�� �����Ѵ�.
	return allSets & ~known;
}

//candidates[len][sum][known] = getCandidates(len, sum, known)
int candidates[10][46][1024];
//candidates[][][]�� �̸� ����� �д�.
void generateCandidates() {
	//�켱 ���� 0���� �ʱ�ȭ
	memset(candidates, 0, sizeof(candidates));
	//1~9�� �κ������� ���� �����Ѵ�.
	for (int set = 0; set < 1024; set += 2) {
		//������ ũ��� ������ ���� ����� �д�.
		int l = getSize(set), s = getSum(set);

		//set�� ��� �κ����տ� ���� candidates[][][]�� ������Ʈ�Ѵ�.
		int subset = set;
		while (true) {
			//���� l���� ���� s�̰�, �̹� subset ���ڰ� ���� ���� ��
			//��ü ������ ������ set�� �ǵ��� ������ ���ڸ� ä������ �� �ִ�.
			candidates[l][s][subset] |= (set & ~subset);
			if (subset == 0) break;
			subset = (subset - 1) & set;
		}
	}
}

const int MAXN = 55;

//�������� ����
//color: �� ĭ�� ���� (0 = ���� ĭ Ȥ�� ��Ʈ ĭ, 1 = �� ĭ)
//value: �� �� ĭ�� �� ���� (���� ���� ���� ĭ�� 0)
//hint: �� ĭ�� �ش��ϴ� �� ��Ʈ�� ��ȣ
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];

//�� ��Ʈ�� ����
//sum: ��Ʈ ĭ�� ���� ����
//length: ��Ʈ ĭ�� �ش��ϴ� �� ĭ�� ��
//known: ��Ʈ ĭ�� �ش��ϴ� �� ĭ�� ���� ���ڵ��� ����
int q, sum[MAXN*MAXN], length[MAXN*MAXN], known[MAXN*MAXN];

//(y,x)�� val�� ����.
void put(int y, int x, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[y][x][h]] += (1 << val);
	value[y][x] = val;
}

//(y,x)�� �� val�� �����.
void remove(int y, int x, int val) {
	for (int h = 0; h < 2; h++)
		known[hint[y][x][h]] -= (1 << val);
	value[y][x] = 0;
}

//��Ʈ ��ȣ�� �־��� �� �ĺ��� ������ ��ȯ�Ѵ�.
int getCandHint(int hint) {
	return candidates[length[hint]][sum[hint]][known[hint]];
}

//��ǥ�� �־��� �� �ش� ĭ�� �� �� �ִ� �ĺ��� ������ ��ȯ�Ѵ�.
int getCandCoord(int y, int x) {
	return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

//value[][]�� ���� ���� ����Ѵ�
void printSolution() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			printf("%s%d", (j ? " " : ""), value[i][j]);
	printf("\n");
}

//���� ã������ true, �ƴϸ� false�� ��ȯ�Ѵ�.
bool search() {
	//���� ���ڸ� ���� ���� �� ĭ �� �ĺ��� ���� �ּ��� ĭ�� ã�´�.
	int y = -1, x = -1, minCands = 1023;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (color[i][j] == WHITE && value[i][j] == 0) {
				int cands = getCandCoord(i, j);
				if (getSize(minCands) > getSize(cands)) {
					minCands = cands;
					y = i, x = j;
				}
			}
	//�� ĭ�� �� ���ڰ� ������ ����
	if (minCands == 0) return false;

	//��� ĭ�� ä�������� ����ϰ� �����Ѵ�
	if (y == -1) {
		printSolution();
		return true;
	}
	
	//���ڸ� �ϳ��� ä������
	for(int val = 1; val <= 9; val++)
		if (minCands & (1 << val)) {
			put(y, x, val);
			if (search()) return true;
			remove(y, x, val);
		}
	return false;
}