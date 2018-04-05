#include <iostream>
using namespace std;

//최적화되지 않은 유클리드 알고리즘
int gcd(int p, int q) {
	if (p < q) swap(p, q);
	if (q == 0) return p;
	return gcd(p - q, q);
}

//최적화된 유클리드 알고리즘
int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p%q);
}