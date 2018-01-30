#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int n, m, A[100], B[100];
int cache[101][101];

int jlis(int indexA, int indexB) {
	int& ret = cache[indexA][indexB];
	if (ret != -1) return ret;
	ret = 2;
	int a = (indexA == -1 ? NEGINF : A[indexA]);
	int b = (indexB == -1 ? NEGINF : B[indexB]);
	int maxElement = max(a, b);

	for (int nextA = indexA + 1; nextA < n; nextA++)
		if (A[nextA] > maxElement)
			ret = max(ret, jlis(nextA, indexB)+1);
	for (int nextB = indexB + 1; nextB < n; nextB++)
		if (B[nextB] > maxElement)
			ret = max(ret, jlis(indexA, nextB)+1);
	return ret;
}