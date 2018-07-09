#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

//m = 원문에 출현 가능한 단어 수, q = 처리해야 할 문장의 수
//n = 분류기로 인식한 문장의 길이
int m, q, n;
//B[i] = i번 단어가 문장의 처음에 출현할 확률
double B[500];
//T[i][j] = i번 단어의 다음 단어가 j번 단어일 확률
//M[i][j] = i번 단어가 적힌 조각을 j번 단어로 분류할 확률
double T[500][500], M[500][500];

//word[i] = 원문에 출현 가능한 i번째 단어
vector<string> word;
//classified = 분류기에서 인식한 결과 문장의 번호
vector<int> classified;
//origin[count][prev+1] = count 이후의 단어에 대하여
//이전에 선택한 단어가 prev일 때, 조건부 출현 확률이 가장 높은 문장의
//다음 단어 번호
int origin[501][501];

//cache[count][prev+1] = count 이후의 단어에 대하여 이전에
//선택한 단어가 prev일 때, 최대 조건부 출현 확률.
double cache[501][501];

//count = 문장의 count번째 단어
//prev = 이전에 문장의 count-1번째 단어로 선택한 단어 번호

//ORC(count, prev) = 이전에 문장의 count-1번째 단어로
//prev번째 단어를 선택했을 때, 이후 만들 수 있는 문장들의
//최대 조건부 출현 확률을 반환한다.

double ORC(int count, int prev) {
	if (count == n)
		return 0;

	double& ret = cache[count][prev + 1];
	if (ret != 1.0)
		return ret;

	ret = -1e200;
	//curStr = 분류기에서 인식한 문장의 count번째 단어
	int curStr = classified[count];
	double result;

	for (int sel = 0; sel < m; sel++) {
		//문장의 첫 번째 단어 선정
		if (prev == -1) {
			//if (B[sel] == log(0.0))
				//continue;
			//원본 문장의 첫번째 단어가 sel번 단어일 확률 반환
			result = ORC(count + 1, sel) + B[sel] + M[sel][curStr];
		}
		//문장의 첫 번째 이후 단어 선정
		else {
			//if (T[prev][sel] == log(0.0) || M[sel][curStr] == log(0.0))
				//continue;
			result = ORC(count + 1, sel) + T[prev][sel] + M[sel][curStr];
		}

		if (result > ret) {
			origin[count][prev + 1] = sel;
			ret = result;
		}
	}
	return ret;
}

int main(void) {
	cin >> m >> q;
	word = vector<string>(m);
	double dinput;

	for (int i = 0; i < m; i++)
		cin >> word[i];
	for (int i = 0; i < m; i++) {
		cin >> dinput;
		B[i] = log(dinput);
	}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			cin >> dinput;
			T[i][j] = log(dinput);
		}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			cin >> dinput;
			M[i][j] = log(dinput);
		}

	for (int test = 0; test < q; test++) {
		vector<string>::iterator it;
		for (int i = 0; i <= m; i++)
			for (int j = 0; j <= m; j++)
				cache[i][j] = 1.0;

		cin >> n;
		classified = vector<int>(n);
		memset(origin, -1, sizeof(origin));
		string input;
		for (int i = 0; i < n; i++) {
			cin >> input;
			it = find(word.begin(), word.end(), input);
			classified[i] = it - word.begin();
		}
		ORC(0, -1);

		int nextStr = origin[0][0];
		for (int i = 1; i <= n; i++) {
			cout << word[nextStr] << ' ';
			nextStr = origin[i][nextStr + 1];
		}
		cout << endl;
		classified.clear();

	}
}