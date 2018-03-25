#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <bitset>
#define MAX 15
using namespace std;

int k;
string answer;
const int MAX_N = 15;
vector<string> stringParts;
//å�� �˰���. ��ó�� �������� �ƿ� �ٸ� ���ڿ��� ���ԵǴ� ���ڿ��� ������������,
//�˰��� �߰��� ��ġ�� ������ ���ߴ� �� �˰���� �޸� �� �ܾ�� ��ġ�� ���� ���̸� �̸� ����Ͽ�
//overlap 2���� �迭�� �����ߴ�.

int cache[MAX_N][1 << MAX_N], overlap[MAX_N][MAX_N];

//�Է¹��� ���ڿ��� �ٸ� ���ڿ��� ���ԵǴ��� Ȯ���ϰ� ������ ���Եȴٸ� �� ���ڿ� ������ ���Ϳ��� �����ϴ� �Լ�.
void EraseOverlapped() {
	//���ڿ� ������ ���̼����� ����
	int vectorLen = stringParts.size();
	for (int i = 0; i < vectorLen - 1; i++) {
		for (int j = i + 1; j < vectorLen; j++) {
			if (stringParts[i].length() < stringParts[j].length()) {
				string temp = stringParts[i];
				stringParts[i] = stringParts[j];
				stringParts[j] = temp;
			}
		}
	}

	//���ԵǴ� ���ڿ� ���� ����
	vector<string>::iterator iter;
	for (int i = 0; i < vectorLen - 1; i++) {
		for (int j = i + 1; j < vectorLen; j++) {
			if (stringParts[i].find(stringParts[j]) != string::npos) {
				iter = stringParts.begin() + j;
				stringParts.erase(iter);
				j--;
				vectorLen--;
			}
		}
	}
}

//�� �ܾ�� ��ġ�� ���� ���̸� ���Ͽ� overlap �迭�� �����ϴ� �Լ�
void findOverlappedLength() {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			if (i == j) {
				overlap[i][j] = stringParts[i].size();
				continue;
			}

			int n = 0;
			bool checking = false;
			string a = stringParts[i], b = stringParts[j];
			string::iterator aiter = a.begin(), biter = b.begin();
			string::iterator tempAiterPos;
			while (aiter != a.end() && biter != b.end()) {
				if (*aiter != *biter) {
					n = 0;
					if (!checking)
						aiter++;
					else
						aiter = tempAiterPos + 1;
					biter = b.begin();
					checking = false;
				}
				else {
					if (!checking)
						tempAiterPos = aiter;
					aiter++;
					biter++;
					n++;
					checking = true;
				}
			}
			overlap[i][j] = n;
		}
	}
}
//�������� ������ ���� last�� ���ݱ��� ������ ������ ���� used�� �־��� ��, ������ ������ �߰��ؼ� ���� �� �ִ�
//overlaps�� �ִ� ���� ���ϴ� ���� ��ȹ�� �˰���. ó�� ����� �� last�� -1, used�� 0�� �־�����.
int maxStart;
int restore(int last, int used) {
	//�������
	if (used == (1 << k) - 1) return 0;
	//�޸������̼�
	if (last == -1) {
		int ret = 0;
		for (int next = 0; next < k; next++) {
			int cand = restore(next, used + (1 << next));
			//cout << "max overlap starting with " << next << ":" << cand << endl;
			if ((ret = max(ret, cand)) == cand)
				maxStart = next;
		}
		return ret;
	}

	int& ret = cache[last][used];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = 0; next < k; next++) {
		if ((used & (1 << next)) == 0) {
			int cand = overlap[last][next] + restore(next, used + (1 << next));
			ret = max(ret, cand);
		}
	}
	return ret;
}
//���� ������ ���� ���ڿ��� ã�� �˰���
//ó�� ȣ�� �� last�� restore()�� �ִ��� ��ȯ�� ���� �ܾ��, used�� 1<<last�� �д�.
string reconstruct(int last, int used) {
	//���� ���
	if (used == (1 << k) - 1) return "";
	//������ �� ���ڿ� ������ ã�´�.
	for (int next = 0; next < k; next++) {
		//next�� �̹� ���Ǿ����� ����
		if (used & (1 << next)) continue;
		//next�� ������� ����� ���� �����ؿ� ���ٸ� next�� ����Ѵ�.
		int ifUsed = restore(next, used + (1 << next)) + overlap[last][next];
		if (restore(last, used) == ifUsed)
			return (stringParts[next].substr(overlap[last][next]) +
				reconstruct(next, used + (1 << next)));
	}
	//������ �߸��� ���
	return "****oops****";
}
//�� Ǯ�̿� ���� main �Լ�
int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(cache, -1, sizeof(cache));
		memset(overlap, 0, sizeof(overlap));
		cin >> k;
		string inputStr;
		for (int i = 0; i < k; i++) {
			cin >> inputStr;
			stringParts.push_back(inputStr);
		}
		EraseOverlapped();
		k = stringParts.size();
		findOverlappedLength();
		/*for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				cout << overlap[i][j] << ' ';
			}
			cout << endl;
		}
		*/
		restore(-1, 0);
		cout << stringParts[maxStart] + reconstruct(maxStart, 1 << maxStart) << endl;
		stringParts.clear();
		maxStart = -1;
	}
}