#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

/*const int MAX = 10000001;
int minFactor[MAX];
int C, hi, lo, n;

void eratosthenes() {
	minFactor[0] = minFactor[1] = -1;
	for (int i = 2; i <= MAX; i++)
		minFactor[i] = i;
	int sqrtn = int(sqrt(MAX));
	for (int i = 2; i <= sqrtn; i++) {
		if (minFactor[i] == i) {
			for (int j = i*i; j <= MAX; j += i)
				if (minFactor[j] == j)
					minFactor[j] = i;
		}
	}
}

int factor(vector<int>& ret, vector<bool>& checked) {
	int passwordCount = 0;

	for (int i = lo; i <= hi; i++) {
		vector<int> selectedNum; // ���μ� ������ �ؼ� ���
		int num = i;
		while (num > 1) {
			if (!checked[minFactor[num]]) { // �ش� �ؼ��� üũ���� �ʾҴٸ�
				checked[minFactor[num]] = true;
				selectedNum.push_back(minFactor[num]); // �ؼ� ����� ����
			}
			ret[minFactor[num]]++; // ���� ����
			num /= minFactor[num];
		}
		int numOfdivisor = 1;
		for (int i = 0; i < selectedNum.size(); i++) {
			numOfdivisor *= (ret[selectedNum[i]] + 1);
			checked[selectedNum[i]] = false;
			ret[selectedNum[i]] = 0;
		}

		if (numOfdivisor == n)
			passwordCount++;
		
	}
	return passwordCount;
}

int main(void) {
	eratosthenes();
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n >> lo >> hi;
		vector<int> ret(hi + 1); // ���μ� ���� ���� ���
		vector<bool> checked(hi + 1); // �ش� �ؼ��� üũ�ߴ°�
		cout << factor(ret, checked) << endl;
	}
	return 0;
}
*/
const int TM = 10000000;
int minFactor[TM + 1];
//minFactorPower[i] = i�� ���μ� ���ؿ��� minFactor[i]�� �� ���� ���ԵǾ� �ִ°�?
int minFactorPower[TM + 1];
//factors[i] = i�� ���� ����� ��
int factors[TM + 1];
