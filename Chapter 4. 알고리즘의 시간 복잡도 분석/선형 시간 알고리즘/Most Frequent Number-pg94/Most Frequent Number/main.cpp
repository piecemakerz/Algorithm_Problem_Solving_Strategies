#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

#define MAX_NUM 100
using namespace std;

int majority(const vector<int>& A) {
	int N = A.size();
	vector<int> frequency(MAX_NUM + 1, 0);

	for (int i = 0; i < N; i++) {
		frequency[A[i]]++;
	}

	int majority = 0;
	for (int i = 1; i <= MAX_NUM; i++) {
		if (frequency[i] > frequency[majority]) {
			majority = i;
		}
	}
	return majority;
}

int main(void) {
	srand(time(NULL));
	int N;
	cin >> N;

	vector<int> scores(MAX_NUM + 1, 0);
	int input;
	for (int i = 0; i < N; i++) {
		input = rand() % 100 + 1;
		cout << input<<' ';
		scores[i] = input;
	}

	cout << '\n' << majority(scores) << endl;
	return 0;
}