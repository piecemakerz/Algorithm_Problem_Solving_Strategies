#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
using namespace std;

int n, p, l;
string answer;
const int MAX = 1000000050;
// �� Ǯ��. �ۼ��ϴµ� 5�ð� �ɸ�.
int curveCount(int generation) {
	int num = 0;
	if (n - generation >= 30)
		return MAX;
	for (int i = 0; i < (n - generation); i++)
		num = min<int>(num + 3 * pow<int>(2, i), MAX);
	return num;
}

int dragonCurve(int	curPos = 1, string curPat = "FX", int generation = 0) {
	if (answer.length() < l) {
		for (int i = 0; i < curPat.length(); i++) {
			//cout << curPos << ' ' << curPat << ' ' << curPat[i] << ' ' << generation<<endl;
			//cout << answer << endl;
			if (answer.length() >= l)
				break; 

			if (curPos >= p && !(curPat[i] == 'X' || curPat[i] == 'Y'))
				answer += curPat[i];

			else {
				if (curPat[i] == 'X') {
					if (curPos >= p && generation == n)
						answer += curPat[i];
					else {
						int curvecount = curveCount(generation);
						if (curPos + curvecount < p)
							curPos += curvecount;
						else
							curPos = dragonCurve(curPos, "X+YF", generation + 1) - 1;
					}
				}
				else if (curPat[i] == 'Y') {
					if (curPos >= p && generation == n)
						answer += curPat[i];
					else {
						int curvecount = curveCount(generation);
						if (curPos + curvecount < p)
							curPos += curvecount;
						else
							curPos = dragonCurve(curPos, "FX-Y", generation + 1) - 1;
					}
				}
			}

			curPos++;
		}
		return curPos;
	} 
	return 0;
}

// å�� �巡�� Ŀ�� ���ڿ� ���� ��� ȣ�� �˰���
// �ʱ� ���ڿ� seed�� generations���� ��ȭ�� ����� ���
void curve(const string& seed, int generations) {
	if (generations == 0) {
		cout << seed;
		return;
	}
	for (int i = 0; i < seed.size(); i++) {
		if (seed[i] == 'X')
			curve("X+YF", generations - 1);
		else if (seed[i] == 'Y')
			curve("FX-Y", generations - 1);
		else
			cout << seed[i];
	}
}
// å�� ��
// const int MAX = 1000000000 + 1;
int length[51]; // length[i] = X�� Y�� i�� ġȯ�� ���� ����
void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++)
		length[i] = min(MAX, length[i - 1] * +2);
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";
//dragonCurve�� generations ��ȭ��Ų ������� skip��° ���ڸ� ��ȯ�Ѵ�.
char expand(const string& dragonCurve, int generations, int skip) {
	if (generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	for (int i = 0; i < dragonCurve.size(); i++) {
		// ���ڿ��� Ȯ��Ǵ� ���
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= length[generations])
				skip -= length[generations];
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, generations - 1, skip);
			else
				return expand(EXPAND_Y, generations - 1, skip);
		}
		// Ȯ����� ������ �ǳʶپ�� �� ���
		else if (skip > 0)
			skip--;
		else // ���� ã�� ���
			return dragonCurve[i];

	}
	return '#'; // �� ���� ������� ����
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n >> p >> l;
		dragonCurve();
		cout << answer << endl;
		answer.clear();
	}
}