#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int c, n;
vector<int> strlist;

//���ڿ� ��ġ�� ������ �ذ��ϴ� �� Ž���� �˰���
int strjoin() {
	int result = 0;
	while (strlist.size() != 1) {
		sort(strlist.begin(), strlist.end(), greater<int>());
		int len = strlist.size() - 1;
		int sum = strlist[len] + strlist[len - 1];
		result += sum;
		strlist.pop_back(); strlist.pop_back();
		strlist.push_back(sum);
	}
	return result;
}

//���ڿ� ��ġ�� ������ �ذ��ϴ� å�� Ž���� �˰���
//�켱���� ť�� ����Ͽ� �˰����� ���۽ð��� ����ȭ�ߴ�.

//���ڿ����� ���̰� �־��� �� �ϳ��� ��ġ�� �ּ� ����� ��ȯ�Ѵ�.
int concat(const vector<int>& lengths) {
	//�ּ� ť�� �����Ѵ�.
	priority_queue<int, vector<int>, greater<int>()> pq;
	for (int i = 0; i < lengths.size(); i++)
		pq.push(lengths[i]);
	int ret = 0;
	//���Ұ� �ϳ� ���� ���� �ݺ��Ѵ�.
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
	cin >> c;
	for (int test = 0; test < c; test++) {
		cin >> n;
		int input;
		for (int i = 0; i < n; i++) {
			cin >> input;
			strlist.push_back(input);
		}
		cout << strjoin() << endl;
		strlist.clear();
	}
	return 0;
}