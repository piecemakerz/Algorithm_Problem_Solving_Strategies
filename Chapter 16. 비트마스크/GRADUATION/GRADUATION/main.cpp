#include <vector>
#include <algorithm>
#include <bitset>
#include <iostream>
using namespace std;

const int MAX = 11;
int c, n, k, m, l;
//presubject[i] = i�� ������ ��� ���� �����ؾ� �ϴ� �������� ���
//����� ��Ʈ����ũ�� ����Ǿ� �ִ�.
vector<int> presubject;
//semester[i] = i�� �б⿡ ������ �� �ִ� ���� ���
//����� ��Ʈ����ũ�� ����Ǿ� �ִ�.
vector<int> semester;

int solve(int selSem, int curSem, int curSub) {
	bitset<12> cursubBit(curSub);
	//���� ���: ���� k�� �̻��� ������ ��û���� ���
	if (cursubBit.count() >= k) return selSem;
	//���� ���: �� �̻� ��û�� �� �ִ� �бⰡ ���ٸ�
	if (curSem >= m) return MAX;
	
	//���� ������ ���� ���
	int canlist = 0;
	int ret = MAX;
	//i��° ������ �̹� �б⿡ ���� �����Ѱ�?
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