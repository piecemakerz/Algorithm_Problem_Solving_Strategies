#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

int C, k;
const int MAX = 987654321;

string strParts[16];
int overlap[16][16];
int cache[16][1 << 16];

//å�� ���� ������ ���� ������ �ذ��ϴ� ���� ��ȹ�� �˰���.
//�������� ������ ���� last�� ���ݱ��� ������ ������ ���� used��
//�־��� ��, ������ ������ �߰��ؼ� ���� �� �ִ� overlaps()�� �ִ� ����
//��ȯ�Ѵ�.
int restore(int last, int used) {
	//���� ���: ������ ���ڿ� ������ ����� ��
	if (used == (1 << k) - 1) return 0;
	int& ret = cache[last][used];
	if (ret != -1) return ret;
	ret = 0;

	for (int next = 0; next < k; next++) {
		if ((used & (1 << next)) == 0) {
			int cand = overlap[last][next] +
				restore(next, used + (1 << next));
			ret = max(ret, cand);
		}
	}
	return ret;
}

//restore�� ��ȯ���� ������ �˰���. ������ ������ �߰��ؼ� ���� �� �ִ�
//overlaps()�� �ִ� ���� ��ȯ�ϴ� restore�� �޸� ������ ������ �߰��ؼ� ����
//�� �ִ� �ּ� ���ڿ� ���̸� ��ȯ�Ѵ�.
int restore2(int last, int used) {
	//���� ���: ������ ���ڿ� ������ ����� ��
	if (used == (1 << k) - 1) strParts[last].length();

	int& ret = cache[last][used];
	if (ret != -1) return ret;
	ret = MAX;

	int cand;
	for (int next = 0; next < k; next++) {
		if ((used & (1 << next)) == 0) {
			int cand = restore2(next, used + (1 << next)) - overlap[last][next];
			ret = min(ret, cand);
		}
	}
	return ret;
}

//���� ������ ���� ������ ���� ���� ����ϴ� �˰���
//restore�Լ��� ���� �� ������ �˰���. ������ ������ġ last = k
//�������� �����Ѵ�.
string reconstruct(int last, int used) {
	//���� ���
	if (used == (1 << k) - 1) return "";
	//������ �� ���ڿ� ������ ã�´�.
	for (int next = 0; next < k; next++) {
		//next�� �̹� ���Ǿ����� ����
		if ((used & (1 << next))) continue;
		//next�� ������� ����� ���� �����ؿ� ���ٸ� next�� ����Ѵ�.
		int ifUsed = restore(next, used + (1 << next)) + overlap[last][next];
		if (restore(last, used) == ifUsed)
			return (strParts[next].substr(overlap[last][next]) +
				reconstruct(next, used + (1 << next)));
	}
	//���� �߸��� ���
	return "****oops****";
}

//restore2�Լ��� ���� �� ������ �˰���. ������ ������ġ last = k
//�������� �����Ѵ�.
string reconstruct2(int last, int used) {
	//���� ���
	if (used == (1 << k) - 1) return "";
	//������ �� ���ڿ� ������ ã�´�.
	for (int next = 0; next < k; next++) {
		//next�� �̹� ���Ǿ����� ����
		if (used & (1 << next)) continue;
		//next�� ������� ����� ���� �����ؿ� ���ٸ� next�� ����Ѵ�.
		int ifUsed = restore2(next, used + (1 << next)) - overlap[last][next];
		if (restore2(last, used) == ifUsed)
			return (strParts[next].substr(overlap[last][next]) +
				reconstruct2(next, used + (1 << next)));
	}
	//���� �߸��� ���
	return "****oops****";
}

//�ܾ� a�� b���� ��ġ�� �κ� ���̸� ����ϴ� �˰���.
//��ġ�� �κ��� ���ٸ� 0�� ��ȯ�Ѵ�.
int getOverlap(const string& a, const string& b) {
	for (int len = min(a.size(), b.size()); len > 0; len--) {
		if (a.substr(a.size() - len) == b.substr(0, len))
			return len;
	}
	return 0;
}

int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		memset(cache, -1, sizeof(cache));
		cin >> k;
		for (int i = 0; i < k; i++) cin >> strParts[i];
		//�� ���ڿ� ������ �ٸ� ���ڿ��� ���Ե� ��� ���ڿ� ���� ��Ͽ���
		//�ƿ� ���ܽ��ѹ����� ��ó�� ������ ��ģ��.
		while (true) {
			bool removed = false;
			//�߰��� ���ڿ� ������ �����Ǿ��ٸ� ó������ �ٽ� üũ�Ѵ�.
			for (int i = 0; i < k && !removed; i++) {
				for(int j=0; j<k; j++)
					//strParts[j]�� strParts[i]�� ������ ���Ե� ��� ���ܽ�Ų��.
					if (i != j && strParts[i].find(strParts[j]) != string::npos) {
						strParts[j] = strParts[k - 1];
						k--;
						removed = true;
					}
			}
			//�� �̻� ��ó�� ������ ��ĥ �ʿ䰡 ���ٸ� ������ ������.
			if (!removed) break;
		}
		strParts[k] = "";
		//������ �տ� ���� ���ڿ��� �켱���� ���ϱ� ���� ����.
		sort(strParts, strParts + k);
		//������ k��° ���ڿ��� ���� overlap�� ����س��´�. ���� �ذ� �˰�����
		//���� ��ġ�ν� ���Ǳ� ����. (overlap[k][i]�� overlap[i][k]�� ������ 0�̴�)
		for (int i = 0; i <= k; i++)
			for (int j = 0; j <= k; j++)
				overlap[i][j] = getOverlap(strParts[i], strParts[j]);

		//������ ���� ���ڿ� k�κ��� �����Ѵ�.
		restore2(k, 0);
		cout << reconstruct2(k, 0) << endl;
	}
	return 0;
}