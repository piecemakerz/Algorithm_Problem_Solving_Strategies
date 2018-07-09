#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int C, N, W;

string name[100];
int weight[100], urgency[100];

vector<string> items;

//cache[start+1][weight] = 현재까지 weight 용량을 골랐을 때,
//start 이후의 물건들을 담아 얻을 수 있는 최대 절박도의 합.
int cache[101][1001];
//package[start+1][weight] = 현재까지 weight 용량을 골랐을 때,
//최대 절박도를 얻기 위해 담아야 하는 start 이후의 물건 번호.
int package[101][1001];

//내 풀이. 책의 풀이와 달리 여태까지 선택한 물건들의 용량을
//함수의 입력으로 주며, 책이 'start+1번 물건을 담는가/담지 않는가'
//두 가지의 경우로 나누어 재귀호출을 한 것과 달리 start+1번 이후의
//물건들 중 다음에 담을 수 있는 모든 물건에 대해 재귀호출을 하였다.

//따라서, 책의 답보다 거의 10배 이상 느린데, 이는 책의 풀이와 내 풀이의
//부분문제 수가 O(NW)로 같으나, 내 풀이는 부분 문제를 해결하는데 상수 시간이
//걸리는 책의 풀이와 달리 O(N)의 시간이 걸리므로 사실상 알고리즘의 시간복잡도가
//O(NW^2)이기 때문이다.
int mypack(int start, int totalW) {
	if (totalW > W)
		return 0;

	int& ret = cache[start + 1][totalW];
	if (ret != -1) return ret;

	ret = 0;
	for (int i = start + 1; i < N; i++) {
		int result = mypack(i, totalW + weight[i]);
		if (result > ret) {
			ret = result;
			package[start + 1][totalW] = i;
		}
	}

	ret += urgency[start];
	return ret;
}

void myreconstruct(int start, int curW) {
	int nextitem = package[start + 1][curW];
	if (nextitem == -1)
		return;

	items.push_back(name[nextitem]);
	myreconstruct(nextitem, curW + weight[nextitem]);
}

//책의 답. 여행 짐 싸기 문제를 해결하는 동적 계획법 알고리즘
//캐리어에 남은 용량이 capacity일 때, item 이후의 물건들을
//담아 얻을 수 있는 최대 절박도의 합을 반환한다.

//각 부분 문제에 선택지가 두 개밖에 없기 때문에 따로 선택을 저장하지 않고도
//답을 역추적할 수 있으나, 굳이 선택을 저장하고자 한다면 bool save[item][capacity]
//에 저장하여, 역추적 시 save[item][capacity] == true라면
//reconstruct(capacity + weight[item], item+1, picked)를 호출하고, false라면
//reconstruct(capacity, item+1, picked)를 호출하면 될 것이다.
int save[101][1001];
int pack(int capacity, int item) {
	//기저 사례: 더 담을 물건이 없을 떄
	if (item == N) return 0;
	int& ret = cache[item][capacity];
	if (ret != -1) return ret;
	//이 물건을 담지 않을 경우
	ret = pack(capacity, item + 1);
	//이 물건을 담을 경우
	if (capacity >= weight[item]) {
		ret = max(ret, pack(capacity - weight[item], item + 1) + urgency[item]);
		/*
		int result = pack(capacity - weight[item], item + 1) + urgency[item];
		if (result > ret) {
			ret = result;
			save[item][capacity] = 1;
		}
		*/
	}
	return ret;
}

//책의 여행 짐 싸기 문제의 답을 역추적하는 재귀 호출 알고리즘
//pack(capacity, item)이 선택한 물건들의 목록을 picked에 저장한다.
//답 자체가 cache에 이미 저장되어 있기 때문에 pack함수를 직접 호출한다고
//해도 시간이 소요되지 않는다.
//주석 처리된 부분은 선택을 저장하여 역추적하는 방법이다.
void reconstruct(int capacity, int item, vector<string>& picked) {
	//기저 사례: 모든 물건을 다 고려했음
	if (item == N) return;
	/*
	if (save[item][capacity]) {
		picked.push_back(name[item]);
		reconstruct(capacity - weight[item], item + 1, picked);
	}
	else
		reconstruct(capacity, item + 1, picked);
	*/

	//두 값이 같다면 item을 선택하지 않고도 최대 절박도를 얻을 수 있다.
	if(pack(capacity, item) == pack(capacity, item+1))
		reconstruct(capacity, item + 1, picked);
	//두 값이 다르다면 item을 선택해야 최대 절박도를 얻을 수 있다.
	else {
		picked.push_back(name[item]);
		reconstruct(capacity - weight[item], item + 1, picked);
	}

}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		memset(package, -1, sizeof(package));
		memset(save, 0, sizeof(save));
		
		cin >> N >> W;
		for (int i = 0; i < N; i++)
			cin >> name[i] >> weight[i] >> urgency[i];
		//cout << mypack(-1, 0) << ' ';
		cout << pack(W, 0) << ' ';
		//myreconstruct(-1, 0);
		reconstruct(W, 0, items);
		cout << items.size() << endl;

		for (int i = 0; i < items.size(); i++)
			cout << items[i] << endl;
		items.clear();
	}
	return 0;
}