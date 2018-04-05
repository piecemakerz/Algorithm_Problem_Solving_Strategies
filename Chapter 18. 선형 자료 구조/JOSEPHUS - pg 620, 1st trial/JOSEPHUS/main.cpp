#include <iostream>
#include <list>
using namespace std;

int C, N, K;

//�� Ǯ��
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

//å�� ��
//STL���� list�� ũ�⸦ ���ϴ� size()������ O(N)�� �ð��� �ɸ��� ������
//����Ʈ�� ���Ե� ������ ���� n�� ���� �����Ѵ�.
void josephus(int n, int k) {
	//����Ʈ�� �غ��Ѵ�
	list<int> survivors;
	for (int i = 1; i <= n; i++) survivors.push_back(i);
	//�̹��� ���� ����� ��Ÿ���� ������
	list<int>::iterator kill = survivors.begin();
	while (n > 2) {
		//ù ��° ����� �ڻ��Ѵ�. erase()�� ���� ������ ���� ���Ҹ� ��ȯ�Ѵ�.
		kill = survivors.erase(kill);
		if (kill == survivors.end()) kill = survivors.begin();
		n--;
		//k-1�� ���� ������� �ű��.
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