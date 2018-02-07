#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int volume[100], urgency[100];
int cache[1001][101];
int maxW;
int choosed[101];
vector<string> productName;
int N;

int CalculateMaxUrgency(int curProduct, int totalW) {
	if (totalW > maxW)
		return -urgency[curProduct - 1];
	else if (curProduct >= N)
		return 0;

	int& ret = cache[totalW][curProduct];
	if (ret != -1) return ret;
	int nonUrg = CalculateMaxUrgency(curProduct + 1, totalW);
	int Urg = CalculateMaxUrgency(curProduct + 1, totalW + volume[curProduct]) + urgency[curProduct];
	int maxUrg;

	if (nonUrg < Urg) {
		choosed[curProduct] = 1;
		maxUrg = Urg;
	}
	else
		maxUrg = nonUrg;

	return ret = maxUrg;
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(cache, -1, sizeof(cache));
		memset(choosed, 0, sizeof(choosed));
		productName.clear();
		cin >> N >> maxW;
		int inputNum;
		string inputString;
		for (int i = 0; i < N; i++) {
			cin >> inputString;
			productName.push_back(inputString);
			cin >> inputNum;
			volume[i] = inputNum;
			cin >> inputNum;
			urgency[i] = inputNum;
		}
		cout << CalculateMaxUrgency(0, 0) << ' '<< sizeof(choosed) << endl;
		for (int i = 0; i < N; i++) {
			if(choosed[i])
				cout << productName[i] << endl;
		}
	}
}