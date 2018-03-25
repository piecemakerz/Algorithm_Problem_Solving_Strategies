#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

int C, n;
int stringArr[100];

//�� Ǯ��
int least() {
	vector<int> curStrings(n);
	for (int i = 0; i < n; i++)
		curStrings[i] = stringArr[i];

	int ret = 0;
	for (int i = 0; i < n - 1; i++) {
		sort(curStrings.begin(), curStrings.end());
		curStrings[0] += curStrings[1];
		ret += curStrings[0];
		curStrings.erase(curStrings.begin()+1);
	}
	return ret;
}

//å�� ��
//���ڿ����� ���̰� �־��� �� �ϳ��� ��ġ�� �ּ� ����� ��ȯ�Ѵ�.
int concat(const vector<int>& lengths) {
	//�ּ� ť�� �����Ѵ�.
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < lengths.size(); i++)
		pq.push(lengths[i]);
	int ret = 0;
	//���Ұ� �ϳ� �̻� ���� ���� �ݺ��Ѵ�.
	while (pq.size() > 1) {
		//���� ª�� ���ڿ� �� ���� ã�Ƽ� ��ġ�� ť�� �ִ´�.
		int min1 = pq.top(); pq.pop();
		int min2 = pq.top(); pq.pop();
		pq.push(min1 + min2);
		ret += min1 + min2;
	}
	return ret;
}
int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> stringArr[i];
		cout << least() << endl;
	}
	return 0;
}
