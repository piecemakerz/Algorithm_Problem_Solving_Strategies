#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

int c, n, p, l;

//p�� �ִ��� 10��, l�� �ִ��� 50�̹Ƿ� ����ؾ� �ϴ� ���ڴ�
//�ִ� ���ڿ��� 1000000049��° �����̴�.
const long long MAX = 1000000050;

//'X'�� 'Y'�� ageLeft�� ���븦 ������ �� ġȯ�Ǵ� �巡�� Ŀ�� ���ڿ���
//���̸� ���Ѵ�.
int maxcache[51];
int findMaxLength(int ageLeft) {
	int& ret = maxcache[ageLeft];
	if (ret != -1) return ret;

	ret = 1;
	long long numOfXandY = 1;

	for (int i = 1; i <= ageLeft; i++) {
		ret = min(MAX, (long long)ret + (3 * numOfXandY));
		numOfXandY = min(MAX, numOfXandY * 2);
	}
	return ret;
}

//�� Ǯ�� 2. �� ��츶�� ġȯ�Ǵ� ���ڿ��� ���̸� �̸� ����Ͽ�
//�� ������ �پ�Ѿ� ���� ����ϴ� �˰���.
int curve2(string curStr, int curP, int age) {
	//�������: �̹� ��� ���ڵ��� ����� ���
	if (l <= 0)
		return curP + 1;

	int len = curStr.length();

	if (age == n) {
		if (curP + len <= p)
			return curP + len;
		else {
			int idx = 0;
			while (l > 0 && idx < len) {
				if (curP + idx >= p) {
					cout << curStr[idx];
					l--;
				}
				idx++;
			}
			return curP + len;
		}
	}

	for (int i = 0; i < len; i++) {
		if (curStr[i] == 'X' || curStr[i] == 'Y') {	
			//���� 'X'�� 'Y'�� ���� ������� n��������� ġȯ�� ������ ��
			//ġȯ�� ���ڿ��� �츮�� ����Ϸ��� ������ ���ڿ��� �ƴ϶��
			//���� ġȯ������ ��ġ�� �ʰ� ġȯ�Ǵ� ���ڿ��� ���� ��ŭ �ǳʶڴ�.
			if (curP + findMaxLength(n - age) <= p) {
				curP += findMaxLength(n - age);
				continue;
			}

			if (curStr[i] == 'X')
				curP = curve2("X+YF", curP, age + 1);
			else
				curP = curve2("FX-Y", curP, age + 1);
		}
		else {
			if (l > 0 && curP >= p) {
				cout << curStr[i];
				l--;
			}
			curP++;
		}
	}
	return curP;
}

//�� Ǯ�� 1. ��� ���� Ȯ���غ��� ��� ȣ�� �˰���. ���� �°� ������
//�翬���� �ð��ʰ��� �߻��Ѵ�.
int curve(string curStr, int curP, int age) {
	if (l <= 0)
		return curP + 1;

	int len = curStr.length();

	if (age == n){
		if(curP + len <= p)
			return curP + len;

		else{
			int idx = 0;
			while (l > 0 && idx < len) {
				if (curP + idx >= p) {
					cout << curStr[idx];
					l--;
				}
				idx++;
			}
			return curP + len;
		}
	}

	for (int i = 0; i < curStr.length(); i++) {
		if (curStr[i] == 'X') {
			curP = curve("X+YF", curP, age + 1);
		}
		else if (curStr[i] == 'Y') {
			curP = curve("FX-Y", curP, age + 1);
		}
		else {
			if (curP >= p && l > 0) {
				cout << curStr[i];
				l--;
			}
			curP++;
		}
	}
	return curP;
}

//å�� Ǯ�� 1. �巡�� Ŀ�� ���ڿ��� �����ϴ� ��� ȣ�� �˰���
//�ʱ� ���ڿ� seed�� generations���� ��ȭ��Ų ����� ����Ѵ�.
//�� �ڵ忡�� p��° ���ڸ��� ����ϵ��� �Ϸ���, �ǳʶپ�� �ϴ� ������ ��
//skip�� ���� ������ �����ϸ鼭, ���ڿ� Ȥ�� ���ڸ� ����� ������ skip��
//����� �κ��� ���̸� ���ϸ� �ȴ�.
void curve(const string& seed, int generations) {
	//���� ���
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

//å�� Ǯ�� 2. ���ڿ��� ���̸� �̸� ����Ͽ� ���ϴ� ���ڿ���
//������ ã�Ƴ��� �˰���.
const int bMAX = 1000000000 + 1;
//length[i] = X�� Y�� i�� ġȯ�� ���� ����
int length[51];
void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++)
		length[i] = min(bMAX, length[i - 1] * 2 + 2);
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";
//dragonCurve�� generations ��ȭ��Ų ������� skip��° ���ڸ� ��ȯ�Ѵ�.
//���� ���ϴ� ���ڿ��� ���� ����ϱ� ���ؼ��� expand�� l�� �ݺ� ȣ���ؾ� �Ѵ�.
char expand(const string& dragonCurve, int generations, int skip) {
	//���� ���
	if (generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	for (int i = 0; i < dragonCurve.size(); i++) {
		//���ڿ��� Ȯ��Ǵ� ���
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y') {
			if (skip >= length[generations])
				skip -= length[generations];
			else if (dragonCurve[i] == 'X')
				return expand(EXPAND_X, generations - 1, skip);
			else
				return expand(EXPAND_Y, generations - 1, skip);
		}
		//Ȯ����� ������ �ǳʶپ�� �� ���
		else if (skip > 0)
			skip--;
		//���� ã�� ���
		else
			return dragonCurve[i];
	}
	return '#';
}

int main(void) {
	cin >> c;
	//memset(maxcache, -1, sizeof(maxcache));
	precalc();
	for (int test = 0; test < c; test++) {
		cin >> n >> p >> l;
		//curve2("FX", 1, 0);
		for (int skip = p-1; skip < p + l - 1; skip++)
			cout << expand("FX", n, skip);
		cout << endl;
	}
	return 0;
}