#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
/*
// �� Ǯ��
// ó���� ret, checked�� factor()�Լ� ���� ���ͷ� �����߰�, selectedNum���͵� for�� ���ο��� �����Ͽ�
// for���� �����ϸ� �ڵ����� ���Ͱ� �޸𸮿��� �����ǰ� �ٽ� �Ҵ��ϴ� ������� �˰����� �ۼ��ߴ�.
// ������, for���� �ִ� �鸸���� ����, �� ���� ���� ��ü�� �迭 �������� �ξ� ���� �ɸ��� �۾��̱� ������
// �ð��ʰ��� ������. �̴� ret�� checked���͸� �����迭�� �����ϰ�, selectedNum���͸� for�� �ۿ� �����Ͽ�
// for���� ������ clear()���ִ� ������ �ذ��� �� �־���.

const int MAX = 10000001;
int minFactor[MAX];
int ret[MAX]; // ���μ� ���� Ƚ��
bool checked[MAX]; // �ش� ���μ� üũ ����
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

int factor() {
	int passwordCount = 0;
	vector<int> selectedNum; // �ش� ������ ���μ� �ؼ���
	for (int i = lo; i <= hi; i++) {
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
		selectedNum.clear();
	}
	return passwordCount;
}

int main(void) {
	eratosthenes();
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n >> lo >> hi;
		cout << factor() << endl;
	}
	return 0;
}
*/

//å�� Ǯ��
const int TM = 10000000;
int minFactor[TM + 1];
//minFactorPower[i] = i�� ���μ� ���ؿ��� minFactor[i]�� �� ���� ���ԵǾ� �ִ°�?
int minFactorPower[TM + 1];
//factors[i] = i�� ���� ����� ��
int factors[TM + 1];

void getFactorSmart() {
	factors[1] = 1;
	for (int n = 2; n <= TM; n++) {
		//�Ҽ��� ��� ����� �� �� �ۿ� ����.
		if (minFactor[n] == n) {
			minFactorPower[n] = 1;
			factors[n] = 2;
		}
		//�Ҽ��� �ƴ� ���, ���� ���� ���μ��� ���� ��(m)��
		//����� ���� ������ n�� ����� ���� ã�´�.
		else {
			int p = minFactor[n];
			int m = n / p;
			//m�� p�� ���̻� ���������� �ʴ� ���
			if (p != minFactor[m])
				minFactorPower[n] = 1;
			else
				minFactorPower[n] = minFactorPower[m] + 1;
			int a = minFactorPower[n];
			factors[n] = (factors[m] / a) * (a + 1);
		}
	}
}

//å�� Ǯ�� 2 - ��� ���� ����� ���� ����ϴ� �ܼ��� �˰���
void getFactorsBrute() {
	memset(factors, 0, sizeof(factors));
	for (int div = 1; div <= TM; div++)
		for (int multiple = div; multiple <= TM; multiple += div)
			factors[multiple] += 1;
}