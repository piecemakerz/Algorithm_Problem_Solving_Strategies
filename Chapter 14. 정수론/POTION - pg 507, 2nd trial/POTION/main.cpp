#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int c, n;
vector<int> r, p;

//��Ŭ���� �˰����� ����
int gcd(int p, int q) {
	if (q == 0) return p;
	return gcd(q, p%q);
}

//toAdd�� �� �־�� �ϴ� �� ����� �ּҷ��� �����Ѵ�.
void solve(vector<int>& toAdd) {
	double toMul = 1;
	//���� ���� ��ᰡ �� ���� ����� ���� �־�� �ϴ� �ּҷ�����
	//���ٸ� �ּҷ���ŭ ä���(��� �� ���� ������ �ϹǷ�), �ּҷ����� �� 
	//���� �־��ٸ� �ּҷ����� �� �� �� �־������� ����� �� ���� ū ����� �����Ѵ�.
	for (int i = 0; i < n; i++)
		if (p[i] < r[i]) {
			toAdd[i] += (r[i] - p[i]);
			p[i] = r[i];
		}
		else if (p[i] > r[i])
			toMul = max(toMul, (double)p[i] / r[i]);

	//���� r�� ��� ���� ���� �ִ������� ����Ѵ�. ���� r�� �� �ִ�������
	//��� ������ ���� ����� ���� �ʿ��� ������ ������ ���� �� �ִ�.
	int curgcd = r[0];
	for (int i = 1; i < n; i++)
		curgcd = gcd(curgcd, r[i]);
	
	//���� ����� ���� �ʿ��� ������ ������ toMul�� ���� �� ���� p�� ���� ����
	//�� �־�� �ϴ� �� ����� �ּҷ��� ���� �� �ִ�.
	toMul = (int)ceil(toMul * curgcd);
	for (int i = 0; i < n; i++)
		toAdd[i] += (r[i] / curgcd * toMul - p[i]);
}

//å�� ������ �� ������ �ذ��ϴ� �ܼ��� �˰���

//������ �� �����ǿ� �̹� ���� ����� ���� �־��� ��, �� ���� ����� ���� ���Ѵ�.
vector<int> solveSimulation(const vector<int>& recipe, vector<int> put) {
	vector<int> oa = put;
	int n = recipe.size();
	vector<int> ret(n); //�� ���� ����� ��
	//�� ��Ḧ �ּ��� recipe�� ���� ��ŭ�� �־�� �Ѵ�.
	for (int i = 0; i < n; i++) {
		ret[i] = max(recipe[i] - put[i], 0);
		put[i] += ret[i];
	}
	//������ ���� ���� ������ ��Ḧ ��� �߰�����.
	int iter = 0;
	while (true) {
		iter++;
		//���� ��Ḧ �� ���� �ʾƵ� �� ������ �ݺ��Ѵ�.
		bool ok = true;
		for(int i=0; i<n; i++)
			for (int j = 0; j < n; j++) {
				//i��° ��ῡ ���ϸ� ��� ���� put[i]/recipe[i] = X�� �̻��� �־�� �Ѵ�.
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

//������ �� ������ �ذ��ϴ� å�� O(n) �˰���. �� �˰���� ����
//���� ����Ǿ���.

//�м� a/b���� ���ų� ū �ּ��� �ڿ����� ��ȯ�Ѵ�.
int ceil(int a, int b) {
	return (a + b - 1) / b;
}
//������ �� �����ǿ� �̹� ���� ����� ���� �־��� ��, �� ���� ����� ���� ���Ѵ�.
vector<int> solve(const vector<int>& recipe, const vector<int>& put) {
	int n = recipe.size();
	//��� recipe[]�� �ִ������� ���Ѵ�.
	int b = recipe[0];
	for (int i = 1; i < n; i++) b = gcd(b, recipe[i]);
	//�ּ��� b/b = 1��� ������ �ϹǷ�, a�� �ʱ� ���� b�� �д�.
	int a = b;
	//X�� ���� ���ϴ� ��� ceil(put[i]*b, recipe[i])�� �ִ밪�� ���Ѵ�.
	for (int i = 0; i < n; i++)
		a = max(a, (int)ceil(put[i] * b, recipe[i]));
	//a/b�� �з��� ����� �ȴ�.
	vector<int> ret(n);
	for (int i = 0; i < n; i++)
		ret[i] = recipe[i] * a / b - put[i];
	return ret;
}
int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		cin >> n;
		r.resize(n), p.resize(n);
		vector<int> toAdd = vector<int>(n, 0);
		for (int i = 0; i < n; i++)
			cin >> r[i];
		for (int i = 0; i < n; i++)
			cin >> p[i];
		solve(toAdd);
		for (int i = 0; i < n; i++)
			cout << toAdd[i] << ' ';
		cout << endl;
	}
}