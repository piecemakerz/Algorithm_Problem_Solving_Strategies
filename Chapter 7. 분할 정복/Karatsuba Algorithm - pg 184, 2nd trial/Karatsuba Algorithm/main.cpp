#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void normalize(vector<int>& num) {
	num.push_back(0); // 미리 최상위 자릿수를 위한 자리 마련
	for (int i = 0; i < num.size(); i++) {
		if (num[i] < 0) {
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i] += borrow * 10; // 음수를 양수로 변경
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i] %= 10;
		}
	}
	while (num.size() > 1 && num.back() == 0) num.pop_back(); // 비어있는 최상위 자릿수들 삭제
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}
	normalize(c);
	return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) { // a += b * (10^k)
	vector<int> tempB = b;
	for(int i=0; i<k; i++)
		tempB.push_back(0);
	for (int i = 0; i < tempB.size(); i++)
		a[i] += tempB[i];

	normalize(a);
}

void subFrom(vector<int>& a, const vector<int>& b) { // a -= b;
	for (int i = 0; i < b.size(); i++)
		a[i] -= b[i];

	normalize(a);
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	// a가 b보다 짧을 경우 둘을 바꾼다.
	if (an < bn) return karatsuba(b, a);
	// 기저사례: a나 b가 비어 있는 경우
	if (an == 0 || bn == 0) return vector<int>();
	// 기저사례: a가 비교적 짧은 경우 일반 곱셈으로 변경한다.
	if (an < 50) return multiply(a, b);

	int half = an / 2;
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);
	addTo(a0, a1, 0); addTo(b0, b1, 0);
	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0); subFrom(z1, z2);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}
