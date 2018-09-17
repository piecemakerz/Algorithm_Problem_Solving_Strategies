#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

//그래프 모델링을 통해 어린이날 문제를 해결한느 알고리즘

//현재 정점 번호가 here이라면, 간선 번호 edge를
//따라갔을 때 나오는 정점의 번호는?
int append(int here, int edge, int mod) {
	int there = here * 10 + edge;
	if (there >= mod) return mod + there % mod;
	return there % mod;
}
//digits에 속한 숫자들만으로 구성되고,
//C mod n == m인 최소의 C를 찾는다.
string gifts(string digits, int n, int m) {
	//간선의 번호를 오름차순으로 정렬해 두면 사전순으로 가장 앞에
	//있는 경로를 찾을 수 있다.
	sort(digits.begin(), digits.end());
	//흰색 정점 i는 0~n-1, 회색 정점 i는 n~2n-1로 표현한다.
	//parent[i] = BFS 스패닝 트리에서 정점 i의 부모
	//choice[i]=parent[i] 에서 i로 연결된 간선의 번호
	vector<int> parent(2 * n, -1), choice(2 * n, -1);
	queue<int> q;
	//흰색 0번을 큐에 추가
	parent[0] = 0;
	q.push(0);

}