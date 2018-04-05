#include <iostream>
#include <list>
using namespace std;

int C, N, K;

//내 풀이
list<int> findSurvivor(list<int> & romans) {
	list<int>::iterator iter = romans.begin();
	while (romans.size() > 2) {
		iter = romans.erase(iter);
		if (iter == romans.end())
			iter = romans.begin();

		for (int i = 0; i < K-1; i++) {
			iter++;

			if (iter == romans.end())
				iter = romans.begin();
		}
	}
	return romans;
}

//책의 답
//STL에서 list의 크기를 구하는 size()연산은 O(N)의 시간이 걸리기 때문에
//리스트에 포함된 원소의 수를 n에 직접 유지한다.
void josephus(int n, int k) {
	//리스트를 준비한다
	list<int> survivors;
	for (int i = 1; i <= n; i++) survivors.push_back(i);
	//이번에 죽을 사람을 나타내는 포인터
	list<int>::iterator kill = survivors.begin();
	while (n > 2) {
		//첫 번째 사람이 자살한다. erase()는 지운 원소의 다음 원소를 반환한다.
		kill = survivors.erase(kill);
		if (kill == survivors.end()) kill = survivors.begin();
		n--;
		//k-1번 다음 사람으로 옮긴다.
		for (int i = 0; i < k - 1; i++) {
			kill++;
			if (kill == survivors.end()) kill = survivors.end();
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> N >> K;
		list<int> romans(N);
		list<int>::iterator iter = romans.begin();

		for (int i = 0; i < N; i++)
			*(iter++) = i + 1;
		list<int> result = findSurvivor(romans);
		list<int>::iterator resultIter = result.begin();
		for (int i = 0; i < result.size(); i++)
			cout << *(resultIter++) << ' ';
		cout << endl;
	}
	return 0;
}