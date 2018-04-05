#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//�� Ǯ��
//å�� ��� �ٸ� ���� �޸������̼��� ���� �ʾҴٴ� �Ͱ�, �κ������� ��ȸ�ϴ� �κп���
//�� �˰����� ���� �� �ִ� �ִ� ������ ����ŭ�� �����ϰ� �ִ� �κ����ո��� ��ȸ������
//å�� �˰����� L������ ������ �����ϰ� �ִ� ��� �κ����տ� ���� ��ȸ�ߴ�.
//�ִ� ������ ����ŭ�� �����ϰ� �ִ� �κ����ո��� ��ȸ�ϴ� �˰����� ��� ������ ��ȸ�� �� �ִ°���
//���ؼ��� ������ �� ������ �ִ�.

// N = ���� ���� ��, K = ���� �� ���� ��, M = �б��� ��, L = �� �б⿡ ���� �� �ִ� �ִ� ���� ��
const int INF = 987654321;
int C, N, K, M, L; 
//prior[i] = i��° ������ ���� ���� ���, subject[i] = i�� �б⿡ �����Ǵ� ���� ���
int prior[12], subject[10];
int minSemester;

int bitCount(int num) {
	int count = 0;
	while (num > 0) {
		if (num % 2 == 1)
			count++;
		num = num >> 1;
	}
	return count;
}

//curSubjects = ������� ���� ����, semester = ���� �б�, curSelSemester = ������� ���� �б� ��
void calMinSemester(int curSubjects = 0, int semester = 0, int curSelSemester = 0) {
	//���� ���: ���� �� ���� �̻��� ������� �������� ���
	if (bitCount(curSubjects) >= K) {
		minSemester = min(minSemester, curSelSemester);
		return;
	}
	//���� ��� 2: ������ �б���� üũ���� ���
	if (semester >= M)
		return;

	calMinSemester(curSubjects, semester + 1, curSelSemester); // ���� �б⸦ �������� ���

	int curSemSubject = subject[semester]; // ���� �б⿡ �����Ǵ� �����
	int canAttend = ~curSubjects & curSemSubject; // ���� ���� ���� ����� �� ���� �б⿡ ���� �� �ִ� ���� ���
	int maxSubjectCount = 0; // ���� ������ ������� �� ���� �� �ִ� �ִ� ������ ��
	for (int i = 0; i < N; i++) { // ���� ������ ������� �� ���� �б⿡ ���� �� �ִ� ���� ���
		if ((canAttend & (1 << i)) && ((curSubjects & prior[i]) == prior[i]))
			maxSubjectCount++;
		else // ���� ������ ��� �̼����� ���� ��� ��Ͽ��� ����
			canAttend &= ~(1 << i); 
	}

	if (!maxSubjectCount) // ������ �� �ִ� ������ �ϳ��� ���ٸ� �ش� �б⸦ �����Ѵ�.
		return;

	maxSubjectCount = min(L, maxSubjectCount);
	for (int subset = canAttend; subset; subset = ((subset - 1) & canAttend)){
		if (bitCount(subset) == maxSubjectCount)
			calMinSemester((curSubjects | subset), semester + 1, curSelSemester + 1);
	}
}

//å�� Ǯ��
const int INF = 987654321;
const int MAXN = 12;
int n, k, m, l;
//prerequiste[i] = i��° ������ ���������� ����
int prerequisite[MAXN];
//classes[i] = i��° �б⿡ �����Ǵ� ������ ����
int classes[10];
int cache[10][1 << MAXN];
//n�� ������ ǥ������ ���� ��Ʈ�� ���� ��ȯ�Ѵ�.
int bitCount(int n);
//�̹� �бⰡ semester�̰�, ���ݱ��� ���� ������ ������ taken�� ��
//k�� �̻��� ������ ���� �������� �� �б⳪ �� �־�� �ϴ°�?
//�Ұ����� ��� INF�� ��ȯ�Ѵ�.
int graduate(int semester, int taken) {
	//���� ���: k�� �̻��� ������ �̹� ���� ���
	if (bitCount(taken) >= k) return 0;
	//���� ���: m�бⰡ ���� ���� ���
	if (semester == m) return INF;
	//�޸������̼�
	int& ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;
	//�̹� �б⿡ ���� �� �ִ� ���� �� ���� ���� ���� ������� ã�´�.
	int canTake = (classes[semester] & ~taken);
	//���� ������ �� ���� ���� ������� �ɷ�����.
	for (int i = 0; i < n; i++)
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) == prerequisite[i])
			canTake &= ~(1 << i);
	//�� ������ ��� �κ������� ��ȸ�Ѵ�.
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		//�� �б⿡ l��������� ���� �� �ִ�.
		if (bitCount(take) > l) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	//�̹� �б⿡ �ƹ� �͵� ���� ���� ���
	ret = min(ret, graduate(semester + 1, taken));
	return ret;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(prior, 0, sizeof(prior));
		memset(subject, 0, sizeof(subject));
		minSemester = INF;

		cin >> N >> K >> M >> L;

		//���� ���� ���� �Է�
		int priorSubjects;
		for (int i = 0; i < N; i++) {
			cin >> priorSubjects;
			int input;
			for (int j = 0; j < priorSubjects; j++) {
				cin >> input;
				prior[i] |= (1 << input);
			}
		}

		//�б⺰ ���� ���� ���
		int openSubjects;
		for (int i = 0; i < M; i++) {
			cin >> openSubjects;
			int input;
			for (int j = 0; j < openSubjects; j++) {
				cin >> input;
				subject[i] |= (1 << input);
			}
		}
		calMinSemester();
		if (minSemester == INF)
			cout << "IMPOSSIBLE" << endl;
		else
			cout << minSemester << endl;
	}
}