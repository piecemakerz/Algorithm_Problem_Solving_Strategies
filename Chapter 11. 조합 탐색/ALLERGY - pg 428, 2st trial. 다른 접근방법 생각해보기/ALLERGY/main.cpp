#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

const int MAX = 987654321;
int T, n, m;
vector<string> friends;
vector<vector<int>> foods;
int maxKind;
int minRes;

//���±��� ������ �� ���� ģ���� �� �ش� ������ ���� �� 
//�ִ� ģ���� �� ���̶� �ִٸ� true�� ��ȯ�Ѵ�.
bool canAnyoneEat(int curFood, long long friendState) {
	for (int i = 0; i < foods[curFood].size(); i++) {
		if ((friendState & (1ULL << foods[curFood][i])) == 0)	
			return true;
	}
	return false;
}

void findMinFoods(int curFood, long long curFriendState, int selected) {
	//���� ���: ��� ģ������ ������ ���� �� ���� ���
	if (curFriendState == ((1ULL << n) - 1)) {
		minRes = min(minRes, selected);
		return;
	}
	//���� ���: ��� ������ üũ���� ���
	if (curFood == m)
		return;

	int friendsRemaining = 0;
	for (int i = 0; i < n; i++)
		if ((curFriendState & (1ULL << i)) == 0)
			friendsRemaining++;

	//������ ����ġ��: 
	if (selected + ceil((double)friendsRemaining / maxKind) >= minRes)
		return;

	//�ش� ������ ����� ���
	if (canAnyoneEat(curFood, curFriendState)) {
		long long nextState = curFriendState;
		for (int i = 0; i < foods[curFood].size(); i++)
			nextState |= (1ULL << foods[curFood][i]);
		findMinFoods(curFood + 1, nextState, selected + 1);
	}

	//�ش� ������ ������ �ʴ� ���
	findMinFoods(curFood + 1, curFriendState, selected);
}

//�˷��� ������ �ذ��ϴ� å�� ù ��° ���� Ž�� �˰���

//eaters[food] = food�� ���� �� �ִ� ģ������ ��ȣ
vector<int> eaters[50];
int best;
//food: �̹��� ����ؾ� �� ������ ��ȣ
//edible: ���ݱ��� �� ���� �� i�� ģ���� ���� �� �ִ� ������ ��
//chosen: ���ݱ��� �� ������ ��
void slowSearch(int food, vector<int>& edible, int chosen) {
	//������ ����ġ��
	if (chosen >= best) return;
	//���� ���: ��� ���Ŀ� ���� ������ ���θ� ����������,
	//��� ģ���� ������ ���� �� �ִ��� Ȯ���ϰ� �׷��ٸ� �����ظ� �����Ѵ�.
	if (food == m) {
		if (find(edible.begin(), edible.end(), 0) == edible.end())
			best = chosen;
		return;
	}
	//food�� ������ �ʴ� ���
	slowSearch(food + 1, edible, chosen);
	//food�� ����� ���
	for (int j = 0; j < eaters[food].size(); j++)
		edible[eaters[food][j]]++;
	slowSearch(food + 1, edible, chosen + 1);

	for (int j = 0; j < eaters[food].size(); j++)
		edible[eaters[food][j]]--;
}

//�˷��� ������ �ذ��ϴ� �� ��° ���� Ž�� �˰���
int n, m;
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
	while (first < n && edible[first]>0) first++;
	//��� ģ���� ���� ������ �ִ� ��� �����Ѵ�.
	if (first == n) { best = chosen; return; }
	//�� ģ���� ���� �� �ִ� ������ �ϳ� �����.
	for (int i = 0; i < canEat[first].size(); i++) {
		int food = canEat[first][i];
		for (int j = 0; j < eaters[food].size(); j++)
			edible[eaters[food][j]]++;
		search(edible, chosen + 1);
		for (int j = 0; j < eaters[food].size(); j++)
			edible[eaters[food][j]]--;
	}
}
int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		maxKind = 0, minRes = MAX;
		int kinds; string name;
		cin >> n >> m;
		friends = vector<string>(n);
		foods = vector<vector<int>>(m);

		for (int i = 0; i < n; i++)
			cin >> friends[i];
		for(int i = 0; i < m; i++) {
			cin >> kinds;
			maxKind = max(maxKind, kinds);
			for (int j = 0; j < kinds; j++) {
				cin >> name;
				foods[i].push_back(find(friends.begin(), friends.end(), name) - friends.begin());
			}
		}

		findMinFoods(0, 0, 0);
		cout << minRes << endl;
		friends.clear();
		for (int i = 0; i < foods.size(); i++)
			foods[i].clear();
		foods.clear();
	}
}