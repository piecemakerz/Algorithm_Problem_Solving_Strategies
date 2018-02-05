#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> numArray;
int arrayMin, arrayMax;
//int cache[1001];
const int INF = 987654321;
int N, S;

//내가 짠 알고리즘. numArray를 크기 순으로 정렬하는 것 까지는 좋았으나 S개의 묶음으로 나눌 생각을 못했다. 즉, 
//또한, 한 묶음에서의 오차제곱을 최소화하는 값을 찾는 공식을 생각해내지 못했다.
//이 알고리즘은 절대로 시간 안에 답을 낼 수 없다. 값이 범위가 1000이하까지이므로, 
//S가 10이라고 할 때 가능한 quantArray의 가짓수는 1000_C_10(조합. 1000개의 자연수 중에서 10개 고르기)개가 된다.

int calculateDifferences(const vector<int>& quantArray) { // 내가 짠 오차 제곱의 합 무식하게 푸는 알고리즘
	int diffSum = 0;
	for (int i = 0; i < N; i++)
		diffSum += pow<int>(numArray[i] - quantArray[i], 2);
	return diffSum;
}

vector<int> DecideQuantizationNumbers(const vector<int>& currentChoice) { // 내가 짠 표현할 수 선택하는 무식한 알고리즘
	vector<int> quantArray;
	for (int i = 0; i < N; i++) {
		int mindiff = abs(numArray[i] - currentChoice[0]);
		int minChoice = 0;
		for (int j = 1; j < S; j++) {
			int diff = abs(numArray[i] - currentChoice[j]);
			if (mindiff > diff) {
				mindiff = diff;
				minChoice = j;
			}
		}
		quantArray.push_back(currentChoice[minChoice]);
	}
	return quantArray;
}

int Quantization(vector<int> currentChoice) {
	if (currentChoice.size() == S) {
		vector<int> quantArray = DecideQuantizationNumbers(currentChoice);
		return calculateDifferences(quantArray);
	}

	int start, ret = INF;
	if (currentChoice.empty())
		start = arrayMin;
	else {
		if (currentChoice.back() >= arrayMax)
			return ret;
		else
			start = currentChoice.back() + 1;
	}

	if (start > arrayMax)
		return ret;

	for (int i = start; i <= arrayMax; i++) {
		currentChoice.push_back(i);
		ret = min(ret, Quantization(currentChoice));
		currentChoice.pop_back();
	}
	return ret;
}

//책의 답
int n;
int A[101], pSum[101], pSqSum[101]; 
// A[]: 양자화해야 할 수열, 정렬한 상태
// pSum[]: A[]의 부분합 저장. pSum[i]는 A[0]..A[i]의 합
// pSqSum[]: A[]제곱의 부분합을 저장한다. pSqSum[i]는 A[0]^2...A[i]^2의 합

void precalc() { // A를 정렬하고 각 부분합을 계산한다.
	sort(A, A + n);
	pSum[0] = A[0];
	pSqSum[0] = pow<int>(A[0], 2);
	for (int i = 1; i < n; i++) {
		pSum[i] = pSum[i - 1] + A[i];
		pSqSum[i] = pSqSum[i - 1] + pow<int>(A[i], 2);
	}
}
//A[lo]...A[hi] 구간을 하나의 숫자로 표현할 때 최소 오차 합을 계산한다.
int minError(int lo, int hi) {
	int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo - 1]); // 부분합을 통해 A[lo] ~ A[hi]까지의 합을 구한다.
	int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo - 1]); //A[lo]^2 ~ A[hi]^2까지의 합을 구한다.
	int m = int(0.5 + (double)sum / (hi - lo + 1)); // 평균을 반올림한 값으로 구간 값들을 표현한다.
	int ret = sqSum - 2 * m*sum + m*m*(hi - lo + 1); // 최소 오차 합 반환
	return ret;
}

int cache[101][11];
int quantize(int from, int parts) {
	//기저 사례: 모든 숫자를 다 양자화했을 때
	if (from == n) return 0;
	//기저 사례: 숫자는 아직 남았는데 더 묶을 수 없을 때 아주 큰 값을 반환한다.
	if (parts == 0) return INF;
	int& ret = cache[from][parts];
	if (ret != -1) return ret;
	ret = INF;
	// 조각의 길이를 변화시켜 가며 최소치를 찾는다.
	for (int partSize = 1; from + partSize <= n; partSize++)
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		int input;
		cin >> N >> S;
		memset(cache, -1, sizeof(cache));
		for (int i = 0; i < N; i++) {
			cin >> input;
			numArray.push_back(input);
		}
		sort(numArray.begin(), numArray.end());
		arrayMin = numArray.front();
		arrayMax = numArray.back();

		vector<int> temp;
		cout<<Quantization(temp)<<endl;
		numArray.clear();
	}
}