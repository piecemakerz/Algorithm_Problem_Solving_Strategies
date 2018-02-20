#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <bitset>
#define MAX 15
using namespace std;

const int INF = 987654321;
int k;
string answer;
vector<string> stringParts;
int myCache[MAX+1][(1 << MAX)+1];
// ���� § ���ȣ�� �˰���. �޸������̼��� ������ �� ������. (���ʿ� �ߺ������� ������� �� ���� ������ �˰����̴�.)
int restore(string curString, int selected = 0) {
	if (selected == (1 << k) - 1) {
		if (curString.length() < answer.length() || answer.empty())
			answer = curString;
		return curString.length();
	}

	int minlength = INF;

	for (int next = 0; next < k; next++) {
		if (selected & (1 << next)) continue;

		string checkStr = stringParts[next];
		if (curString.empty())
			minlength = min(minlength, restore(checkStr, selected + (1 << next)));

		else {
			int addLen;
			bool checked = false;
			for (int i = 0; i < curString.length(); i++) {	
				bool match = true;
				addLen = 1;
				if (checkStr[0] == curString[i]) {
					for (int j = i + 1; j < curString.length() && (j-i) < checkStr.length(); j++) {
						if (checkStr[j - i] != curString[j]) {
							match = false;
							break;
						}
						addLen++;
					}

					if (match) {
						minlength = min(minlength, restore(curString + checkStr.substr(addLen, checkStr.length() - addLen), selected + (1 << next)));
						checked = true;
						break;
					}
				}
			}
			if (!checked)
				minlength = min(minlength, restore(curString + checkStr, selected + (1 << next)));
		}
	}
	return minlength;
}

//å�� ���� ���� �޸������̼��� ������ �� �˰���.
int restore2(string curString, int selected = 0, int last=0) {
	if (selected == (1 << k) - 1) {
		//cout << endl<<"endOfLevel:" << curString << endl<<endl;
		if (answer.empty() || curString.length() < answer.length())
			answer = curString;
		return curString.length();
	}

	int minlength = INF;
	//cout << curString << "	selected: "<< bitset<4>(selected)<<endl;
	for (int next = 0; next < k; next++) {
		string checkStr = stringParts[next];

		if (selected & (1 << next))	continue;

		int& ret = myCache[last][selected];
		if (ret != -1) continue;
		if(last != 0)
			ret = INF;

		if (curString.empty())
			minlength = min(minlength, restore2(checkStr, selected + (1 << next), next+1));
		else if (curString.find(checkStr) != string::npos)
			minlength = min(minlength, restore2(curString, selected + (1 << next), next+1));

		else {
			int addLen = 1;
			bool checked = false;
			for (int i = 0; i < curString.length(); i++) {
				bool match = true;
				if (checkStr[0] == curString[i]) {
					for (int j = i + 1; j < curString.length() && (j - i) < checkStr.length(); j++) {
						if (checkStr[j - i] != curString[j]) {
							match = false;
							break;
						}
						addLen++;
					}

					if (match) {
						minlength = min(minlength, restore2(curString + checkStr.substr(addLen, checkStr.length() - addLen), selected + (1 << next), next+1));
						checked = true;
						break;
					}
				}
			}
			if (!checked)
				minlength = min(minlength, restore2(curString + checkStr, selected + (1 << next), next+1));
		}
		if(last != 0)
			ret = min(ret, minlength);
	}
	return minlength;
}

//å�� �˰���. ��ó�� �������� �ƿ� �ٸ� ���ڿ��� ���ԵǴ� ���ڿ��� ������������,
//�˰��� �߰��� ��ġ�� ������ ���ߴ� �� �˰���� �޸� �� �ܾ�� ��ġ�� ���� ���̸� �̸� ����Ͽ�
//overlap 2���� �迭�� �����ߴ�.

const int MAX_N = 15;
//int k;
//string word[MAX_N]; -> vector<string> stringParts�� ��ü��
int cache[MAX_N][1 << MAX_N], overlap[MAX_N][MAX_N];
//�Է¹��� ���ڿ��� �ٸ� ���ڿ��� ���ԵǴ��� Ȯ���ϴ� �Լ�
bool EraseOverlapped(string inputStr) {
	for (int i = 0; i < stringParts.size(); i++) {
		if (stringParts[i].find(inputStr) != string::npos)
			return true;
	}
	return false;
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
			string a = stringParts[i], b = stringParts[j];
			string::iterator aiter = a.begin(), biter = b.begin();
			while (aiter != a.end() && biter != b.end()) {
				if (*aiter != *biter) {
					n = 0;
					aiter++;
				}
				else {
					aiter++;
					biter++;
					n++;
				}
			}
			overlap[i][j] = n;
		}
	}
}
//�������� ������ ���� last�� ���ݱ��� ������ ������ ���� used�� �־��� ��, ������ ������ �߰��ؼ� ���� �� �ִ�
//overlaps�� �ִ� ���� ���ϴ� ���� ��ȹ�� �˰���.
int restore(int last, int used) {
	//�������
	if (used == (1 << k) - 1) return 0;
	//�޸������̼�
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
		cin >> k;
		memset(myCache, -1, sizeof(myCache));
		string inputStr;
		for (int i = 0; i < k; i++) {
			cin >> inputStr;
			if (EraseOverlapped(inputStr))
				continue;

			stringParts.push_back(inputStr);
		}
		k = stringParts.size();
		restore2("");
		cout << answer << endl;
		answer.clear();
		stringParts.clear();
	}
}
