#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

//m = 원문에 출현 가능한 단어 수, q = 처리해야 할 문장의 수
//n = 분류기로 인식한 문장의 길이
int m, q, n;

/*이후 주어지는 확률 값들은 매우 작기 때문에 이들을 수백 번씩 곱하면
확률 값이 너무 작아지고, 결과적으로 언더플로가 일어나기 쉬우므로 확률 값을
그대로 쓸 수 없다. 따라서 확률의 로그 값을 구하면 각 각의 확률들의
로그 값을 더하기만 하면 되기 때문에 언더플로를 방지할 수 있다.
내 이전 답을 이를 간과하여 오답처리되었다.
*/

//B[i] = i번 단어가 문장의 처음에 출현할 확률(의 로그값)
double B[500];
//T[i][j] = i번 단어의 다음 단어가 j번 단어일 확률(의 로그값)
//M[i][j] = 분류기에서 i번 단어를 j번 단어로 분류할 확률(의 로그값)
double T[500][500], M[500][500];

//word = 원문에 출현 가능한 단어 목록
vector<string> word;
//classified = 분류기에서 인식한 결과 문장을 이루는 단어들의 번호
vector<int> classified;

//origin[count][prev+1] = 원본 문장 Q를 이루는 단어 중 Q[count-1]를 word[prev]로
//정했을 때, Q[count] 이후를 채워서 얻을 수 있는 모든 문장 중 조건부 출현 확률이 가장 높은 
//문장의 count번째 단어 번호.
//원본 문장을 재구성할 때 필요하다.
int origin[501][501];

//cache[count][prev+1] =  원본 문장 Q를 이루는 단어 중 Q[count-1]를 word[prev]로 정했을 때,
//Q[count] 이후를 채워서 얻을 수 있는 최대 조건부 출현 확률의 로그값.
double cache[501][501];

const double MIN = log(0.0);
//ORC(count, prev) = 원본 문장 Q[count-1]를 word[prev]로 정했을 때,
//Q[count] 이후를 채워서 얻을 수 있는 최대 조건부 확률의 로그 값을 반환한다.
double ORC(int count, int prev) {
	//기저 사례: Q의 n-1번째 단어까지 모두 정했을 경우
	if (count == n)
		return 0;

	double& ret = cache[count][prev + 1];
	if (ret != 1.0)
		return ret;

	//log(0) = 음의 무한대에 해당하는 값
	ret = MIN;

	//curStr = 분류기에서 인식한 문장의 count번째 단어 번호
	int curStr = classified[count];
	double result;

	for (int sel = 0; sel < m; sel++) {
		//Q[0] 선정
		if (prev == -1) {
			//word[sel]이 Q[0]에 위치할 확률이 0이라면 이후를 확인하지 않는다.
			if (B[sel] == MIN)
				continue;
			//OCR(count+1, sel) * 'word[sel]이 Q[0]일 확률' * 'word[sel]을 분류기가 'word[curStr]로 분류했을 확률
			//로그 값을 취했으므로 곱하는 대신 더한다.
			result = ORC(count + 1, sel) + B[sel] + M[sel][curStr];
		}
		//Q[0] 이후 단어 선정
		else {
			//word[prev]이후에 word[sel]이 나올 확률이 0이거나 word[sel]이 word[curStr]로
			//분류된 확률이 0이라면 확인하지 않는다.
			if (T[prev][sel] == MIN || M[sel][curStr] == MIN)
				continue;
			//OCR(count+1, sel) * 'word[prev]의 다음 단어가 word[sel]일 확률' * 'word[sel]을 분류기가 'word[curStr]로
			//분류했을 확률. 로그 값을 취했으므로 곱하는 대신 더한다.
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
		scanf("%lf", &dinput);
		B[i] = log(dinput);
	}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			scanf("%lf", &dinput);
			T[i][j] = log(dinput);
		}

	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++) {
			scanf("%lf", &dinput);
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

		//원본 문장 재구성. 원본 문장의 첫번째 단어 번호는 origin[0][0]에 저장되어 있다.
		int nextStr = origin[0][0];
		for (int i = 1; i <= n; i++) {
			cout<<word[nextStr]<<' ';
			nextStr = origin[i][nextStr + 1];
		}
		cout << endl;
		classified.clear();
	}
}