#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

//내 풀이
//책의 답과 다른 점은 메모이제이션을 하지 않았다는 것과, 부분집합을 순회하는 부분에서
//내 알고리즘은 들을 수 있는 최대 과목의 수만큼을 포함하고 있는 부분집합만을 순회했으나
//책의 알고리즘은 L이하의 과목을 포함하고 있는 모든 부분집합에 대해 순회했다.
//최대 과목의 수만큼을 포함하고 있는 부분집합만을 순회하는 알고리즘이 모든 정답을 순회할 수 있는가에
//대해서는 생각해 볼 여지가 있다.

// N = 전공 과목 수, K = 들어야 할 과목 수, M = 학기의 수, L = 한 학기에 들을 수 있는 최대 과목 수
const int INF = 987654321;
int C, N, K, M, L; 
//prior[i] = i번째 과목의 선수 과목 목록, subject[i] = i번 학기에 개설되는 과목 목록
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

//curSubjects = 현재까지 들은 과목, semester = 현재 학기, curSelSemester = 현재까지 들은 학기 수
void calMinSemester(int curSubjects = 0, int semester = 0, int curSelSemester = 0) {
	//기저 사례: 들어야 할 과목 이상의 과목들을 수강했을 경우
	if (bitCount(curSubjects) >= K) {
		minSemester = min(minSemester, curSelSemester);
		return;
	}
	//기저 사례 2: 마지막 학기까지 체크했을 경우
	if (semester >= M)
		return;

	calMinSemester(curSubjects, semester + 1, curSelSemester); // 현재 학기를 휴학했을 경우

	int curSemSubject = subject[semester]; // 현재 학기에 개설되는 과목들
	int canAttend = ~curSubjects & curSemSubject; // 아직 듣지 못한 과목들 중 현재 학기에 들을 수 있는 과목 목록
	int maxSubjectCount = 0; // 선수 과목을 고려했을 때 들을 수 있는 최대 과목의 수
	for (int i = 0; i < N; i++) { // 선수 과목을 고려했을 때 현재 학기에 들을 수 있는 과목 목록
		if ((canAttend & (1 << i)) && ((curSubjects & prior[i]) == prior[i]))
			maxSubjectCount++;
		else // 선수 과목을 모두 이수하지 않은 경우 목록에서 삭제
			canAttend &= ~(1 << i); 
	}

	if (!maxSubjectCount) // 수강할 수 있는 과목이 하나도 없다면 해당 학기를 휴학한다.
		return;

	maxSubjectCount = min(L, maxSubjectCount);
	for (int subset = canAttend; subset; subset = ((subset - 1) & canAttend)){
		if (bitCount(subset) == maxSubjectCount)
			calMinSemester((curSubjects | subset), semester + 1, curSelSemester + 1);
	}
}

//책의 풀이
const int INF = 987654321;
const int MAXN = 12;
int n, k, m, l;
//prerequiste[i] = i번째 과목의 선수과목의 집합
int prerequisite[MAXN];
//classes[i] = i번째 학기에 개설되는 과목의 집합
int classes[10];
int cache[10][1 << MAXN];
//n의 이진수 표현에서 켜진 비트의 수를 반환한다.
int bitCount(int n);
//이번 학기가 semester이고, 지금까지 들은 과목의 집합이 taken일 때
//k개 이상의 과목을 전부 들으려면 몇 학기나 더 있어야 하는가?
//불가능한 경우 INF를 반환한다.
int graduate(int semester, int taken) {
	//기저 사례: k개 이상의 과목을 이미 들은 경우
	if (bitCount(taken) >= k) return 0;
	//기저 사례: m학기가 전부 지난 경우
	if (semester == m) return INF;
	//메모이제이션
	int& ret = cache[semester][taken];
	if (ret != -1) return ret;
	ret = INF;
	//이번 학기에 들을 수 있는 과목 중 아직 듣지 않은 과목들을 찾는다.
	int canTake = (classes[semester] & ~taken);
	//선수 과목을 다 듣지 않은 과목들을 걸러낸다.
	for (int i = 0; i < n; i++)
		if ((canTake & (1 << i)) && (taken & prerequisite[i]) == prerequisite[i])
			canTake &= ~(1 << i);
	//이 집합의 모든 부분집합을 순회한다.
	for (int take = canTake; take > 0; take = ((take - 1) & canTake)) {
		//한 학기에 l과목까지만 들을 수 있다.
		if (bitCount(take) > l) continue;
		ret = min(ret, graduate(semester + 1, taken | take) + 1);
	}
	//이번 학기에 아무 것도 듣지 않을 경우
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

		//선수 과목 정보 입력
		int priorSubjects;
		for (int i = 0; i < N; i++) {
			cin >> priorSubjects;
			int input;
			for (int j = 0; j < priorSubjects; j++) {
				cin >> input;
				prior[i] |= (1 << input);
			}
		}

		//학기별 개설 과목 목록
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