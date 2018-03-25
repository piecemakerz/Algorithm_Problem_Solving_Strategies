#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//�� ȸ�Ǵ� [begin, end) ���� ���� ȸ�ǽ��� ����Ѵ�.
int n;
int meetBegin[100], meetEnd[100];
//Ž����� ����� �˰���
int schedule() {
	//���� ������ ������� �����Ѵ�.
	vector<pair<int, int>> order;
	for (int i = 0; i < n; i++)
		order.push_back(make_pair(meetEnd[i], meetBegin[i]));
	sort(order.begin(), order.end()); // order�� ù ��° ������ meetEnd[]�� �������� ����
	//earliest: ���� ȸ�ǰ� ������ �� �ִ� ���� ���� �ð�
	//selected: ���ݱ��� ������ ȸ���� ��
	int earliest = 0, selected = 0;
	for (int i = 0; i < order.size(); i++) {
		int meetingBegin = order[i].second, meetingEnd = order[i].first;
		if (earliest <= meetingBegin) {
			//earliest�� ������ ȸ�ǰ� ���� �ð� ���ķ� �����Ѵ�.
			earliest = meetingEnd;
			++selected;
		}
	}
	return selected;
}

int before[100];
//���� ��ȹ���� ����� �˰���
//schedule(int idx) = order[idx] Ȥ�� �� ������ ������ ȸ�ǵ� �� ������ �� �ִ� �ִ� ȸ���� ��.
int schedule(int idx) { // n-1���� ����
	if (idx == -1)
		return 0;

	int ret = 0;
	if(idx > 0)
		ret = schedule(idx - 1); // order[idx] �������� ����
	ret = max(ret, 1 + schedule(before[idx])); // order[idx] ����
	return ret;
}

int main(void) {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> meetBegin[i] >> meetEnd[i];

	/*vector<pair<int, int>> myorder;
	for (int i = 0; i < n; i++)
		myorder.push_back(make_pair(meetEnd[i], meetBegin[i]));
	sort(myorder.begin(), myorder.end());
	memset(before, -1, sizeof(before));
	for (int i = n - 1; i >= 0; i--)
		for (int j = i - 1; j >= 1; j--) {
			if (myorder[j].first <= myorder[i].second) {
				before[i] = j;
				break;
			}
		}
	*/
	cout << schedule() << endl;
}