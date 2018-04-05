#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int C,n;

//å�� �� 1 - �ܼ��ϰ� ������������ �ð��� ���� �ɸ��� �˰���
//������ �� �����ǿ� �̹� ���� ����� ���� �־��� ��, �� ���� ����� ���� ���Ѵ�.
vector<int> solveSimulation(const vector<int>& recipe, vector<int> put) {
	vector<int> ret(n); // �� ���� ����� ��

	//�� ��Ḧ �ּ��� recipe�� ���� ��ŭ�� �־�� �Ѵ�.
	for (int i = 0; i < n; i++) {
		ret[i] = max(recipe[i] - put[i], 0);
		put[i] += ret[i];
	}
	//������ ���� ���� ������ ��Ḧ ��� �߰�����.
	while (true) {
		//���� ��Ḧ �� ���� �ʾƵ� �� ������ �ݺ��Ѵ�.
		bool ok = true;
		for(int i=0; i<n; i++)
			for (int j = 0; j < n; j++) {
				//i��° ��ῡ ���ϸ� ��� ���� put[i] / recipe[i] = X�� �̻��� �־�� �Ѵ�.
				//���� put[j]�� recipe[j] * X �̻��� ������ �Ǿ�� �Ѵ�.
				int required = (put[i] * recipe[j] + recipe[i] - 1) / recipe[i];
				//�� �־�� �ϴ°�?
				if (required > put[j]) {
					ret[j] += required - put[j];
					put[j] = required;
					ok = false;
				}
			}
		if (ok) break;
	}
	return ret;
}

//å�� �� 2 - ��Ŭ���� �˰����� �̿��� O(n) �˰���

//�� ���� �ִ������� ���ϴ� ��Ŭ���� �˰���
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a%b);
}

//�м� a/b���� ���ų� ū(�ø���) �ּ��� �ڿ����� ��ȯ�Ѵ�.
int ceil(int a, int b) {
	return (a + b - 1) / b;
}

//������ �� �����ǿ� �̹� ���� ����� ���� �־��� ��, �� ���� ����� ���� ���Ѵ�.
vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
	//��� recipe[]�� �ִ������� ���Ѵ�.
	int b = recipe[0];
	for (int i = 1; i < n; i++)	b = gcd(b, recipe[i]);
	//�ּ��� b/b = 1��� ������ �ϹǷ� a�� �ʱ� ���� b�� �д�.
	int a = b;
	//X�� ���� ���ϴ� ��� ceil(put[i]*b, recipe[i])�� �ִ밪�� ���Ѵ�.
	for (int i = 0; i < n; i++)
		a = max(a, ceil(put[i] * b, recipe[i]));
	//a/b�� �з��� ����� �ȴ�.
	vector<int> ret(n);
	for (int i = 0; i < n; i++)
		ret[i] = recipe[i] * a / b - put[i];
	return ret;
}

int main(void) {
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> n;
		vector<int> recipe(n), put(n);
		for (int i = 0; i < n; i++)
			cin >> recipe[i];
		for (int i = 0; i < n; i++)
			cin >> put[i];

		vector<int> result = solveSimulation(recipe, put);
		for (int i = 0; i < n; i++)
			cout << result[i] << ' ';
		cout << endl;
	}
	return 0;
}