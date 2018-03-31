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
		vector<int> selectedNum; // 소인수 분해의 밑수 결과
		int num = i;
		while (num > 1) {
			if (!checked[minFactor[num]]) { // 해당 밑수를 체크하지 않았다면
				checked[minFactor[num]] = true;
				selectedNum.push_back(minFactor[num]); // 밑수 결과에 저장
			}
			ret[minFactor[num]]++; // 지수 증가
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
		vector<int> ret(hi + 1); // 소인수 분해 지수 결과
		vector<bool> checked(hi + 1); // 해당 밑수를 체크했는가
		cout << factor(ret, checked) << endl;
	}
	return 0;
}
*/
const int TM = 10000000;
int minFactor[TM + 1];
//minFactorPower[i] = i의 소인수 분해에는 minFactor[i]의 몇 승이 포함되어 있는가?
int minFactorPower[TM + 1];
//factors[i] = i가 가진 약수의 수
int factors[TM + 1];
