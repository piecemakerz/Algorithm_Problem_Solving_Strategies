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
		if ((semester[curSem] & (1 << i)) && !(curSub & (1 << i))
			&& ((curSub & presubject[i]) == presubject[i]))
			canlist |= (1 << i);
	}
	if (canlist != 0) {
		bitset<12> canlistBit(canlist);
		if (canlistBit.count() <= l)
			ret = min(ret, solve(selSem + 1, curSem + 1, curSub | canlist));
		else {
			for (int subset = canlist; subset <= (subset & -subset);
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