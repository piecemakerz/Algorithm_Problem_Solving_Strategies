#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int C, n, k, m;
int L[50];
double T[50][50];
int Q;

//���Ͼ ������ �ذ��ϴ� ���ȣ�� ������ȹ�� �˰���.
//�ʹ� ū ũ���� ĳ�ù迭�� �ʿ�� �ϹǷ� ���� �����÷ΰ� �߻��Ѵ�.

//cache[i][j] = ���±��� ������ ������ i�� �ð��� ������,
//���� ��� ������ j�� ������ ��, k�� 30�ʿ� Q�� ������
//��� ���� Ȯ��
//double cache[1000005][50];
/*
double play(int timepassed, int cur) {
	if (timepassed > k)
		if (cur == Q)
			return 1.0;
		else
			return 0.0;

	double& ret = cache[timepassed][cur];
	if (ret != -1.0) return ret;

	ret = 0.0;
	for(int next = 0; next < n; next++)
		ret += play(timepassed + L[next], next) * T[cur][next];

	return ret;
}
*/

//���Ͼ ������ �ذ��ϴ� �ݺ��� ������ȹ�� �˰��� 1.
//�˰��� �ݺ������� �ٲ��� �� ū ũ���� ĳ�ù迭�� �ʿ�� �ϴ°��� �����ϹǷ�
//���� �����÷ΰ� �߻��Ѵ�.

//c[i][j] = ������� i�� �ð��� �귶�� ��, j�� ������ ���� ������ Ȯ��
//play2()�� �ѹ� ������ �� Ȯ���� ���ؾ� �ϴ� ��� Q�� ���Ͽ� 
//c[k-L[Q]+1...k][Q]�� ����ϸ� ������ ã�� �� �ִ�.
/*
double c[1000005][50];
void play2() {
	for (int timepassed = L[0]; timepassed <= k; timepassed++) {
		for (int prev = 0; prev < n; prev++)
			if (timepassed >= L[prev] && c[timepassed - L[prev]][prev] != 0.0)
				for (int next = 0; next < n; next++)
					c[timepassed][next] += c[timepassed - L[prev]][prev] * T[prev][next];
	}
}
*/

//���Ͼ ������ �ذ��ϴ� �ݺ��� ������ȹ�� �˰��� 2.
//ĳ�ù迭�� �����̵� ���� ��ũ���� �����Ͽ� ũ�⸦ ���� �ٿ����Ƿ�
//���� �����÷ΰ� �߻����� �ʴ´�.
double c[5][50];
void play3() {
	for (int timepassed = L[0]; timepassed <= k; timepassed++) {
		for (int i = 0; i < n; i++)
			//c[timepassed]�� ���� ���ϱ� ���ؼ��� c[timepassed-1...timepassed-4]�� ������ �ʿ��
			//�ϹǷ�, ���� for������ ����� ������� ������ c[timepassed % 5]�� ���� ��� 0���� �ٲ۴�.
			c[timepassed % 5][i] = 0.0;

		for (int prev = 0; prev < n; prev++) {
			if (timepassed >= L[prev] && c[(timepassed - L[prev])%5][prev] != 0.0) {
				for (int next = 0; next < n; next++) {
					c[timepassed % 5][next] += c[(timepassed - L[prev])%5][prev] * T[prev][next];
				}
			}
		}
	}
}

//å�� ���Ͼ ������ �ذ��ϴ� �ݺ��� ���� ��ȹ�� �˰���
vector<double> getProb1() {
	//c[time][song] = time�� �Ŀ� song�� �뷡�� ������ Ȯ��
	double c[5][50];
	memset(c, 0, sizeof(c));
	c[0][0] = 1.0;
	for(int time = 1; time <= k; time++)
		for (int song = 0; song < n; song++) {
			double& prob = c[time % 5][song];
			prob = 0;
			for (int last = 0; last < n; last++)
				prob += c[(time - L[last] + 5) % 5][last] * T[last][song];
		}
	vector<double> ret(n);
	//song�� �뷡�� ����ǰ� ���� Ȯ���� ����Ѵ�.
	for (int song = 0; song < n; song++)
		//song�� �뷡�� �������� �ð��� ��� ã�� ���Ѵ�.
		for (int start = k - L[song] + 1; start <= k; start++)
			ret[song] += c[start % 5][song];
	return ret;
}

//å�� ���Ͼ ������ �ذ��ϴ� ����� �ŵ����� ���� ��ȹ��
//k�� 30�� �Ŀ� �� ���� ����ǰ� ���� Ȯ���� ��ȯ�Ѵ�.
vector<double> getProb2() {
	SquareMatricx W(4 * n);
	//ù 3*n���� ���Ҵ� �״�� �����ؿ´�.
	for (int i = 0; i < 3 * n; i++)
		W[i][i + n] = 1.0;
	//������ n���� ���Ҵ� ���� ���ҵ��� ���� �������� �̷������.
	for (int i = 0; i < n; i++)
		//C[time+1][i] = C[time+1-L[j][j]] * T[j][i]
		for (int j = 0; j < n; j++)
			W[3 * n + i][(4 - L[j])*n + j] = T[j][i];
	SquareMatrix Wk = W.pow(k);
	vector<double> ret(n);
	//song�� �뷡�� ����ǰ� ���� Ȯ���� ����Ѵ�.
	for (int song = 0; song < n; song++)
		//song�� �뷡�� �������� �ð��� ��� ã�� ���Ѵ�.
		for (int start = 0; start < L[song]; start++)
			ret[song] += Wk[(3 - start)*n + song][3 * n];
	return ret;
}
int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		cin >> n >> k >> m;
		for (int i = 0; i < n; i++)
			cin >> L[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> T[i][j];

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 50; j++)
				c[i][j] = 0.0;

		c[0][0] = 1.0;
		play3();

		for (int i = 0; i < m; i++) {
			double ret = 0.0;
			cin >> Q;
			int length = L[Q];
			for (int i = 0; i < length; i++)
				ret += c[(k-i)%5][Q];
			printf("%.8lf ", ret);
		}
		cout << endl;
	}
	return 0;
}