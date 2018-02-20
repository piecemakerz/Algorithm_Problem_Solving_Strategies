#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

//내 풀이로 최대 절박도 합은 구할 수 있었으나 가져갈 물건들의 개수와 가져갈 물건들의 이름 출력은 불가능했다.
//내 풀이에서는 남은 용량인 capacity 대신 현재까지 선택한 물건들의 용량 합을 사용했었다.
int n, capacity;
int volume[100], need[100];
int cache[1001][100]; // cache[남은 용량][item]
string name[100];
int pickedNum;
//캐리어에 남은 용량이 capacity일 때, item 이후의 물건들을 담아
//얻을 수 있는 최대 절박도의 합을 반환한다.
int pack(int capacity, int item) {
	// 기저 사례: 더 담을 물건이 없을 때
	if (item == n) return 0;
	int& ret = cache[capacity][item];
	if (ret != -1) return ret;
	//item을 담지 않을 경우
	ret = pack(capacity, item + 1);
	//item을 담을 경우
	if (capacity >= volume[item]) {
		ret = max(ret, pack(capacity - volume[item], item + 1) + need[item]);
	}
	return ret;
}
//pack(capacity, item)이 선택한 물건들의 목록을 picked에 저장한다.
void reconstruct(int capacity, int item, vector<string>& picked) {
	//기저 사례: 모든 물건을 다 고려했음
	if (item == n) return;
	if (pack(capacity, item) == pack(capacity, item + 1)) {
		reconstruct(capacity, item + 1, picked);
	}
	else {
		picked.push_back(name[item]);
		pickedNum++;
		reconstruct(capacity - volume[item], item + 1, picked);
	}
}

int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		pickedNum = 0;
		memset(cache, -1, sizeof(cache));
		vector<string> pickedItems;
		cin >> n >> capacity;
		for (int i = 0; i < n; i++) {
			cin >> name[i] >> volume[i] >> need[i];
		}
		cout << pack(capacity, 0) << ' ';
		reconstruct(capacity, 0, pickedItems);
		cout << pickedNum << endl;
		for (int i = 0; i < pickedItems.size(); i++)
			cout << pickedItems[i] << endl;
	}
	return 0;
}