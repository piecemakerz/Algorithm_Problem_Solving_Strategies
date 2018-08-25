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

//���� �б� ������ �ذ��ϴ� �� ���� ��ȹ�� �˰���
//selSem = ������� ������ �б��� ��, curSem = ���� �б�
//curSub = ������� ������ ���� ���
//������û�� �ؾ� �ϴ� �ּ� �б��� ���� ��ȯ�Ѵ�. �޸������̼��� ������ �� ������, 
//å���� �Ű������� �ϳ� �� �����Ƿ� �޸������̼��� �ϱ� ���� ĳ�� �޸𸮰� �� ���� �ʿ��ϴ�.
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
		//�̹� �б⿡ i��° ������ ������, ���� i��° ������ �������� �ʾ�����,
		//i��° ������ ����������� ��� �������� �� i��° ������ ���� �����ϴ�.
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

//���� �б� ������ �ذ��ϴ� ���� ��ȹ�� �˰����� ����
const int INF = 987654321;
const int MAXN = 12;
//prerequisite[i] = i��° ������ ���������� ����
int prerequisite[MAXN];
//classes[i] = i��° �б⿡ �����Ǵ� ������ ����
int classes[10];
int cache[10][1 << MAXN];
//n�� ������ ǥ������ ���� ��Ʈ�� ���� ��ȯ�Ѵ�.
//å������ __builtin_popcount()�� ��������� �̴� gcc������ ��� �����ϴ�.
int bitCount(int n);
//�̹� �бⰡ semester��, ���ݱ��� ���� ������ ������ taken�� ��
//k�� �̻��� ������ ��� �������� �� �б⳪ �� �־�� �ϴ°�?
//�Ұ����� ��� INF�� ��ȯ�Ѵ�.
int graduate(int semester, int taken) {
	//���� ���: k�� �̻��� ������ �̹� ���� ���
	if (bitCount(taken) >= k) return 0;
	//���� ���: m �бⰡ ���� ���� ���
	if (semester == m) return INF;
	//�޸������̼�
	int& ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;
	//�̹� �б⿡ ���� �� �ִ� ���� �� ���� ���� ���� ������� ã�´�.
	int canTake = (classes[semester] & ~taken);
	//���� ������ �� ���� ���� ������� �ɷ�����.
	for (int i = 0; i < n; i++)
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) != prerequisite[i])
			canTake &= ~(1 << i);
	//�� ������ ��� �κ������� ��ȸ�Ѵ�.
	for (int take = canTake; take > 0;
		take = ((take - 1) & canTake)) {
		//�� �б⿡ l ��������� ���� �� �ִ�.
		if (bitCount(take) > l) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	//�̹� �б⿡ �ƹ� �͵� ���� ���� ���
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