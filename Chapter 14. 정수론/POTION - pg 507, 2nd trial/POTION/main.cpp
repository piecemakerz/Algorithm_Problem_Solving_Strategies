#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int c, n;
vector<int> r, p;

//유클리드 알고리즘의 구현
int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p%q);
}

//toAdd에 더 넣어야 하는 각 재료의 최소량을 저장한다.
void solve(vector<int>& toAdd) {
	double toMul = 1;
	//현재 넣은 재료가 한 병을 만들기 위해 넣어야 하는 최소량보다
	//적다면 최소량만큼 채우고(적어도 한 병은 만들어야 하므로), 최소량보다 더 
	//많이 넣었다면 최소량보다 몇 배 더 넣었는지를 계산한 후 가장 큰 배수를 갱신한다.
	for (int i = 0; i < n; i++)
		if (p[i] < r[i]) {
			toAdd[i] += (r[i] - p[i]);
			p[i] = r[i];
		}
		else if (p[i] > r[i])
			toMul = max(toMul, (double)p[i] / r[i]);

	//벡터 r의 모든 수에 대한 최대공약수를 계산한다. 벡터 r을 이 최대공약수로
	//모두 나누면 약을 만들기 위해 필요한 재료들의 비율을 구할 수 있다.
	int curgcd = r[0];
	for (int i = 1; i < n; i++)
		curgcd = gcd(curgcd, r[i]);
	
	//약을 만들기 위해 필요한 재료들의 비율에 toMul을 곱한 후 벡터 p의 값을 빼면
	//더 넣어야 하는 각 재료의 최소량을 구할 수 있다.
	toMul = (int)ceil(toMul * curgcd);
	for (int i = 0; i < n; i++)
		toAdd[i] += (r[i] / curgcd * toMul - p[i]);
}

//책의 마법의 약 문제를 해결하는 단순한 알고리즘

//마법의 약 레시피와 이미 넣은 재료의 양이 주어질 때, 더 넣을 재료의 양을 구한다.
vector<int> solveSimulation(const vector<int>& recipe, vector<int> put) {
	vector<int> oa = put;
	int n = recipe.size();
	vector<int> ret(n); //더 넣을 재료의 양
	//각 재료를 최소한 recipe에 적힌 만큼은 넣어야 한다.
	for (int i = 0; i < n; i++) {
		ret[i] = max(recipe[i] - put[i], 0);
		put[i] += ret[i];
	}
	//비율이 전부 맞을 때까지 재료를 계속 추가하자.
	int iter = 0;
	while (true) {
		iter++;
		//냄비에 재료를 더 넣지 않아도 될 때까지 반복한다.
		bool ok = true;
		for(int i=0; i<n; i++)
			for (int j = 0; j < n; j++) {
				//i번째 재료에 의하면 모든 재료는 put[i]/recipe[i] = X배 이상은 넣어야 한다.
				//따라서 put[j]는 recipe[j] * X 이상의 정수가 되어야 한다.
				int required = (put[i] * recipe[j] + recipe[i] - 1) / recipe[i];
				//더 넣어야 하는가?
				if (required > put[j]) {
					ret[j] += required - put[j];
					put[j] = required;
					ok = false;
				}
			}
		if (ok) break;
	}
	return ret;
}

//마법의 약 문제를 해결하는 책의 O(n) 알고리즘. 내 알고리즘과 같은
//논리로 설계되었다.

//분수 a/b보다 같거나 큰 최소의 자연수를 반환한다.
int ceil(int a, int b) {
	return (a + b - 1) / b;
}
//마법의 약 레시피와 이미 넣은 재료의 양이 주어질 때, 더 넣을 재료의 양을 구한다.
vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
	int n = recipe.size();
	//모든 recipe[]의 최대공약수를 구한다.
	int b = recipe[0];
	for (int i = 1; i < n; i++) b = gcd(b, recipe[i]);
	//최소한 b/b = 1배는 만들어야 하므로, a의 초기 값을 b로 둔다.
	int a = b;
	//X를 직접 구하는 대신 ceil(put[i]*b, recipe[i])의 최대값을 구한다.
	for (int i = 0; i < n; i++)
		a = max(a, (int)ceil(put[i] * b, recipe[i]));
	//a/b배 분량을 만들면 된다.
	vector<int> ret(n);
	for (int i = 0; i < n; i++)
		ret[i] = recipe[i] * a / b - put[i];
	return ret;
}
int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		cin >> n;
		r.resize(n), p.resize(n);
		vector<int> toAdd = vector<int>(n, 0);
		for (int i = 0; i < n; i++)
			cin >> r[i];
		for (int i = 0; i < n; i++)
			cin >> p[i];
		solve(toAdd);
		for (int i = 0; i < n; i++)
			cout << toAdd[i] << ' ';
		cout << endl;
	}
}