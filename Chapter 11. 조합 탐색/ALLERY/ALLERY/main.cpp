#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <functional>
using namespace std;

const int INF = 987654321;
int T, n, m;
vector<string> friends;
vector<int> food[50];//i��° ������ ���� �� �ִ� ģ�� ���
int chosen[50]; //i��° ������ �̹� �Ծ������� ����
int friendEat[50]; //i��° ģ���� �̹� ���� �� �ִ� ������ �ִ����� ����
int best;

//���� ���� �� �ִ� ������ ���� ������� ���� ���� �԰� �� �� �ִ� ���� ������ ����.
vector<int> arrangeMostUncommon() {
	vector<int> foodCount(m, 0);//��ġ�� ������ ��
	for (int i = 0; i < m; i++) //i��° ����
		for (int j = 0; j < food[i].size(); j++)
			if(friendEat[food[i][j]] == 0) //���� i��° ������ ���� �ʾҴٸ�
				foodCount[i] += 1;
	sort(foodCount.begin(), foodCount.end(), greater<int>());

	return foodCount;
}

int canEverybodyEat() {
	for (int i = 0; i < n; i++)
		if (friendEat[i] == 0)
			return false;
	return true;
}

void allergy(int choose) {
	//���� ���: ���� ������ ���� ���� ������ �� �̻��̶�� ����
	if (choose >= best)
		return;
	//���� ���: ��� ģ������ ���� �� �ִٸ� �� ����
	if (canEverybodyEat() || choose >= m) {
		best = min(best, choose);
		return;
	}

	vector<int> foodOrder = arrangeMostUncommon();

	for (int i=0; i < foodOrder.size(); i++) {
		int curFood = foodOrder[i];
		//�̹� ������ ����ٸ� üũ ����
		if (chosen[curFood])
			continue;
		//curFood�� ���� ����
		for (int i = 0; i < food[curFood].size(); i++)
			friendEat[food[curFood][i]] += 1;
		chosen[curFood] = 1;
		//���ȣ��
		allergy(choose + 1);

		chosen[curFood] = 0;
		for (int i = 0; i < food[curFood].size(); i++)
			friendEat[food[curFood][i]] -= 1;
	}
	return;
}
int main(void) {
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		memset(chosen, 0, sizeof(chosen));
		memset(friendEat, 0, sizeof(friendEat));
		best = INF;
		string inputStr;
		int canEatCount;
		cin >> n >> m; // n = ģ�� ��, m = ���� ��

		for (int i = 0; i < n; i++) {
			cin >> inputStr;
			friends.push_back(inputStr);
		}

		for (int i = 0; i < m; i++) {
			cin >> canEatCount;
			for (int j = 0; j < canEatCount; j++) {
				cin >> inputStr;
				for (int k = 0; k < n; k++)
					if (!inputStr.compare(friends[k])) {
						food[i].push_back(k);
						break;
					}
			}
		}

		allergy(0);
		cout << best << endl;
		for (int i = 0; i < m; i++)
			food[i].clear();
		friends.clear();
	}
	return 0;
}