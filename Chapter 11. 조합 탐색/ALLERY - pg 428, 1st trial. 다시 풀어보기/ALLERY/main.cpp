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
int friendEat[50]; //i��° ģ���� �̹� ���� �� �ִ� ������ �ִ����� ����
int best;
//�� Ǯ��
/*
//���� ���� �� �ִ� ������ ���� ������� ���� ���� �԰� �� �� �ִ� ���� ������ ����.
	vector<pair<int,int>> arrangeMostUncommon() {
	vector<pair<int,int>> foodCount(m);//��ġ�� ������ ��
	for (int i = 0; i < m; i++)
		foodCount[i] = make_pair(0, i);

	for (int i = 0; i < m; i++) //i��° ����
		for (int j = 0; j < food[i].size(); j++)
			if(friendEat[food[i][j]] == 0) //���� i��° ������ ���� �ʾҴٸ�
				foodCount[i].first -= 1;
	sort(foodCount.begin(), foodCount.end());

	return foodCount;
}
*/
void arrangeFood() {
	for (int i = 0; i < m - 1; i++)
		for (int j = i + 1; j < m; j++)
			if (food[i].size() < food[j].size())
				swap(food[i], food[j]);
}

int canEverybodyEat(const int * ret) {
	for (int i = 0; i < n; i++)
		if (ret[i] == 0)
			return false;
	return true;
}

/*void allergy(int choose) {
	//���� ���: ���� ������ ���� ���� ������ �� �̻��̶�� ����
	if (choose >= best)
		return;
	//���� ���: ��� ģ������ ���� �� �ִٸ� �� ����
	if (canEverybodyEat() || choose >= m) {
		best = min(best, choose);
		return;
	}

	vector<pair<int,int>> foodOrder = arrangeMostUncommon();

	for (int i=0; i < foodOrder.size(); i++) {
		int curFood = foodOrder[i].second;
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
*/
bool heuristic(int curFood) {
	int ret[50];
	for(int i=0; i<n; i++)
		ret[i] = friendEat[i];

	for (int i = curFood; i < m; i++) {
		for (int j = 0; j < food[i].size(); j++)
			ret[food[i][j]] += 1;
	}
	return canEverybodyEat(ret);
}

void allergy(int choose, int curFood) {
	//����ġ��: ���� ������ ���� ���� ������ �� �̻��� ��� ����
	if (choose >= best)
		return;
	//���� ���: ��� ģ������ ���� �� �ִٸ� �� ����
	if (curFood == m){
		if(canEverybodyEat(friendEat))
			best = min(best, choose);
		return;
	}

	//������ �޸���ƽ: ���� ���ĵ��� ��� ����ٰ� �ص� ��� ģ������ ���� �� ���� �� ����
	if (!heuristic(curFood)) {
		return;
	}

	//curFood�� ���� ���
	for (int i = 0; i < food[curFood].size(); i++)
		friendEat[food[curFood][i]] += 1;
	allergy(choose + 1, curFood + 1);

	//curFood�� ���� �ʴ� ���
	for (int i = 0; i < food[curFood].size(); i++)
		friendEat[food[curFood][i]] -= 1;
	allergy(choose, curFood + 1);
	return;
}

//å�� ��

//canEat[i]: i�� ģ���� ���� �� �ִ� ������ ����
//eaters[i]: i�� ������ ���� �� �ִ� ģ������ ����
vector<int> canEat[50], eaters[50];
int best;
//chosen: ���ݱ��� ������ ������ ��
//edible[i]: ���ݱ��� �� ���� �� i�� ģ���� ���� �� �ִ� ������ ��
void search(vector<int>& edible, int chosen) {
	//������ ����ġ��
	if (chosen >= best) return;
	//���� ���� ������ ���� ù ��° ģ���� ã�´�.
	int first = 0;
	while (first < n && edible[first]>0)	first++;
	//��� ģ���� ���� ������ �ִ� ��� �����Ѵ�.
	if (first == n) { best = chosen; return; }
	//�� ģ���� ���� �� �ִ� ������ �ϳ� �����.
	for (int i = 0; i < canEat[first].size(); i++) {
		int food = canEat[first][i];
		for (int j = 0; j < eaters[food].size(); j++)
			edible[eaters[food][j]]++;
		search(edible, chosen + 1);
		for(int j=0; j<eaters[food].size(); j++)
			edible[eaters[food][j]]++;
	}
}
int main(void) {
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		memset(friendEat, 0, sizeof(friendEat));
		best = INF;
		string inputStr;
		int canEatCount;
		cin >> n >> m; // n = ģ�� ��, m = ���� ��
		for (int i = 0; i < m; i++)
			food[i] = vector<int>(0);

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

		arrangeFood();
		allergy(0,0);
		cout << best << endl;
		for (int i = 0; i < m; i++)
			food[i].clear();
		friends.clear();
	}
	return 0;
}