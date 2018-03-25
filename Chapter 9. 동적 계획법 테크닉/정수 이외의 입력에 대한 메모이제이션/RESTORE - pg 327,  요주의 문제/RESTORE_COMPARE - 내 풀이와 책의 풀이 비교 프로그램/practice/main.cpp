#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <bitset>
#include <cstdlib>
#define MAX 15
using namespace std;

const int INF = 987654321;
const int MAX_N = 15;
int k;
vector<string> mystringParts;
vector<string> stringParts;
string mycache[MAX + 1][(1 << MAX) + 1];
int cache[MAX_N][1 << MAX_N], overlap[MAX_N][MAX_N];

string myrestore(int selected = 0, int last = -1) {
	//base case 1
	if (selected == (1 << k) - 1) {
		return mystringParts[last];
	}

	if (last == -1) {
		string ret = "";
		for (int next = 0; next < k; next++) {
			string resultStr = myrestore(selected + (1 << next), next);
			if (ret.empty() || ret.length() > resultStr.length())
				ret = resultStr;
		}
		return ret;
	}

	//base case 2 - memoization
	string& ret = mycache[last][selected];
	if (!ret.empty()) {
		//mycache가 정확히 어떻게 쓰이는지 보기 위한 코드
		//cout << "cache used in [" << last << "][" << selected << "]" << ret<<endl;
		return ret;
	}

	string curString = mystringParts[last];
	for (int next = 0; next < k; next++) {
		if (selected & (1 << next)) continue;

		string checkStr = myrestore(selected + (1 << next), next);
		int check = false;
		string resultStr;
		//count max overlapping area of two strings and overlap two strings.
		for (int i = (checkStr.length() > curString.length() ? curString.length() : checkStr.length())
			; i > 0; i--) {
			if (curString.substr(curString.size() - i, i) == checkStr.substr(0, i)) {
				resultStr = curString + checkStr.substr(i, checkStr.length() - i);
				check = true;
				break;
			}
		}
		if (!check)
			resultStr = curString + checkStr;

		if (ret.empty() || ret.length() > resultStr.length())
			ret = resultStr;
	}
	return ret;
}

void myEraseOverlapped() {
	int vectorLen = mystringParts.size();
	for (int i = 0; i < vectorLen - 1; i++) {
		for (int j = i + 1; j < vectorLen; j++) {
			if (mystringParts[i].length() < mystringParts[j].length()) {
				string temp = mystringParts[i];
				mystringParts[i] = mystringParts[j];
				mystringParts[j] = temp;
			}
		}
	}

	vector<string>::iterator iter;
	for (int i = 0; i < vectorLen - 1; i++) {
		for (int j = i + 1; j < vectorLen; j++) {
			if (mystringParts[i].find(mystringParts[j]) != string::npos) {
				iter = mystringParts.begin() + j;
				mystringParts.erase(iter);
				j--;
				vectorLen--;
			}
		}
	}
}

void EraseOverlapped() {
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

int maxStart;
int restore(int last, int used) {
	if (used == (1 << k) - 1) return 0;
	if (last == -1) {
		int ret = 0;
		for (int next = 0; next < k; next++) {
			int cand = restore(next, used + (1 << next));
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

string reconstruct(int last, int used) {
	if (used == (1 << k) - 1) return "";
	for (int next = 0; next < k; next++) {
		if (used & (1 << next)) continue;
		int ifUsed = restore(next, used + (1 << next)) + overlap[last][next];
		if (restore(last, used) == ifUsed)
			return (stringParts[next].substr(overlap[last][next]) +
				reconstruct(next, used + (1 << next)));
	}
	return "****oops****";
}

void GenerateRandomString() {
	static const string alpha = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < k; i++) {
		int length = rand() % 5 + 1;
		string resultStr="";
		for (int j = 0; j < length; j++) {
			int select = rand() % alpha.length();
			resultStr.push_back(alpha[select]);
		}
		stringParts.push_back(resultStr);
		mystringParts.push_back(resultStr);
		cout << resultStr << endl;
	}
}
int main(void) {
	int C = 20;
	for (int testCase = 0; testCase < C; testCase++) {
		k = 5;
		memset(cache, -1, sizeof(cache));
		memset(overlap, 0, sizeof(overlap));
		for (int i = 0; i < MAX + 1; i++) {
			for (int j = 0; j < (1 << MAX) + 1; j++)
				mycache[i][j] = "";
		}
		GenerateRandomString();
		myEraseOverlapped();
		EraseOverlapped();
		k = stringParts.size();
		findOverlappedLength();
		//정렬된 문자열 목록 출력
		/*cout << "---Arranged string---" << endl;
		for (int i = 0; i < k; i++) {
			cout << mystringParts[i] << endl;
		}
		cout << "----------------------" << endl;
		*/
		string myresultStr = myrestore();
		restore(-1, 0);
		string resultStr = stringParts[maxStart] + reconstruct(maxStart, 1 << maxStart);
		cout << "myAlgorithm Result: " << myresultStr << "  length: "<< myresultStr.length() << endl;
		cout << "bookAlgorithm Result: " << resultStr << "  length: "<< resultStr.length() << endl;
		cout << "----------------------" << endl << endl;
		stringParts.clear();
		mystringParts.clear();
		maxStart = -1;
	}
}