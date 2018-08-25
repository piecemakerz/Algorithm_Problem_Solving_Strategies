#include <vector>
#include <algorithm>
#include <bitset>
#include <iostream>
using namespace std;

const int MAX = 11;
int c, n, k, m, l;
//presubject[i] = i번 과목을 듣기 위해 수강해야 하는 선수과목 목록
//목록은 비트마스크로 저장되어 있다.
vector<int> presubject;
//semester[i] = i번 학기에 수강할 수 있는 과목 목록
//목록은 비트마스크로 저장되어 있다.
vector<int> semester;

//졸업 학기 문제를 해결하는 내 동적 계획법 알고리즘
//selSem = 현재까지 수강한 학기의 수, curSem = 현재 학기
//curSub = 현재까지 수강한 과목 목록
//수강신청을 해야 하는 최소 학기의 수를 반환한다. 메모이제이션을 적용할 수 있으나, 
//책보다 매개변수가 하나 더 많으므로 메모이제이션을 하기 위한 캐시 메모리가 더 많이 필요하다.
int solve(int selSem, int curSem, int curSub) {
	bitset<12> cursubBit(curSub);
	//기저 사례: 현재 k개 이상의 과목을 신청했을 경우
	if (cursubBit.count() >= k) return selSem;
	//기저 사례: 더 이상 신청할 수 있는 학기가 없다면
	if (curSem >= m) return MAX;
	
	//수강 가능한 과목 목록
	int canlist = 0;
	int ret = MAX;
	//i번째 과목을 이번 학기에 수강 가능한가?
	for (int i = 0; i < n; i++) {
		//이번 학기에 i번째 과목이 열리고, 아직 i번째 과목을 수강하지 않았으며,
		//i번째 과목의 선수과목들을 모두 수강했을 때 i번째 과목을 수강 가능하다.
		if ((semester[curSem] & (1 << i)) && !(curSub & (1 << i))
			&& ((curSub & presubject[i]) == presubject[i]))
			canlist |= (1 << i);
	}
	if (canlist != 0) {
		bitset<12> canlistBit(canlist);
		if (canlistBit.count() <= l)
			ret = min(ret, solve(selSem + 1, curSem + 1, curSub | canlist));
		else {
			for (int subset = canlist; subset;
				subset = ((subset - 1) & canlist)) {
				bitset<12> subsetBit(subset);
				if (subsetBit.count() == l)
					ret = min(ret, solve(selSem + 1, curSem + 1, curSub | subset));
			}
		}
	}
	ret = min(ret, solve(selSem, curSem + 1, curSub));
	return ret;
}

//졸업 학기 문제를 해결하는 동적 계획법 알고리즘의 구현
const int INF = 987654321;
const int MAXN = 12;
//prerequisite[i] = i번째 과목의 선수과목의 집합
int prerequisite[MAXN];
//classes[i] = i번째 학기에 개설되는 과목의 집합
int classes[10];
int cache[10][1 << MAXN];
//n의 이진수 표현에서 켜진 비트의 수를 반환한다.
//책에서는 __builtin_popcount()를 사용했으나 이는 gcc에서만 사용 가능하다.
int bitCount(int n);
//이번 학기가 semester고, 지금까지 들은 과목의 집합이 taken일 때
//k개 이상의 과목을 모두 들으려면 몇 학기나 더 있어야 하는가?
//불가능한 경우 INF를 반환한다.
int graduate(int semester, int taken) {
	//기저 사례: k개 이상의 과목을 이미 들은 경우
	if (bitCount(taken) >= k) return 0;
	//기저 사례: m 학기가 전부 지난 경우
	if (semester == m) return INF;
	//메모이제이션
	int& ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;
	//이번 학기에 들을 수 있는 과목 중 아직 듣지 않은 과목들을 찾는다.
	int canTake = (classes[semester] & ~taken);
	//선수 과목을 다 듣지 않은 과목들을 걸러낸다.
	for (int i = 0; i < n; i++)
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i);
	//이 집합의 모든 부분집합을 순회한다.
	for (int take = canTake; take > 0;
		take = ((take - 1) & canTake)) {
		//한 학기에 l 과목까지만 들을 수 있다.
		if (bitCount(take) > l) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	//이번 학기에 아무 것도 듣지 않을 경우
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}

int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		cin >> n >> k >> m >> l;
		presubject = vector<int>(n, 0);
		semester = vector<int>(m, 0);

		int num, subjectNum;
		for (int i = 0; i < n; i++) {
			cin >> num;
			for (int j = 0; j < num; j++) {
				cin >> subjectNum;
				presubject[i] |= (1 << subjectNum);
			}
		}

		for (int i = 0; i < m; i++) {
			cin >> num;
			for (int j = 0; j < num; j++) {
				cin >> subjectNum;
				semester[i] |= (1 << subjectNum);
			}
		}
		int result = solve(0, 0, 0);
		if (result == MAX) cout << "IMPOSSIBLE" << endl;
		else cout << result << endl;
	}
}