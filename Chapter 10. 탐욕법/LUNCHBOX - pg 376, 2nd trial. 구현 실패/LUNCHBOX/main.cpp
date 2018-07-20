#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int C, n;
const int MAX = INT_MAX;
int M[10000], E[10000];
vector <pair<int, int>> ME;
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n;
		for (int i = 0; i < n; i++){
			cin >> M[i];
		for (int i = 0; i < n; i++)
			cin >> E[i];

		for (int i = 0; i < n; i++)
			ME.push_back(make_pair(M[i], E[i]));
		
		sort(ME.begin(), ME.end(), greater<int>());
		int minE = INT_MAX, maxM = ME.back().first;
		for (int i = n - 1; i >= 0; i--) {
			if()
		}
	}
}