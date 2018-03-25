//내 이전 알고리즘
/*
int k;
string answer; 
vector<string> stringParts;
bool cache[MAX + 1][(1 << MAX) + 1]; 

void restore(string curString, int selected = 0, int last = 0) {
	if (selected == (1 << k) - 1) {
		if (answer.empty() || curString.length() < answer.length())
			answer = curString;
		return;
	}
	
	bool& ret = cache[last][selected];
	if (ret != false) return;

	for (int next = 0; next < k; next++) {
		string checkStr = stringParts[next];
		if (selected & (1 << next)) continue;

		if (curString.empty())
			restore(checkStr, selected + (1 << next), next + 1);
		else {
			int check = false;
			for (int i = (checkStr.length() > curString.length() ? curString.length() : checkStr.length())
				; i > 0; i--) {
				if (curString.substr(curString.size() - i, i) == checkStr.substr(0, i)) {
					restore(curString + checkStr.substr(i, checkStr.length() - i), selected + (1 << next), next + 1);
					check = true;
					break;
				}
			}
			if (!check) {
				restore(curString + checkStr, selected + (1 << next), next + 1);
			}
		}
	}
	ret = true;
}

void eraseOverlapped() {
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
*/

//이전 알고리즘을 수정한 새 알고리즘
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#define MAX 15
using namespace std;

int k;

vector<string> stringParts;
string cache[MAX + 1][(1 << MAX) + 1];

string restore(int selected = 0, int last = -1) {
	if (selected == (1 << k) - 1) {
		return stringParts[last];
	}

	if (last == -1) {
		string ret = "";
		for (int next = 0; next < k; next++) {
			string resultStr = restore(selected + (1 << next), next);
			if (ret.empty() || ret.length() > resultStr.length())
				ret = resultStr;
		}
		return ret;
	}

	string& ret = cache[last][selected];
	if (!ret.empty()) {
		cout << "cache used in [" << last << "][" << selected << "]" << endl;
		return ret;
	}

	string curString = stringParts[last];
	for (int next = 0; next < k; next++) {
		if (selected & (1 << next)) continue;

		string checkStr = restore(selected + (1 << next), next);
		int check = false;
		string resultStr;
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

int main(void) {
	int C;
	cin >> C; // testcase
	for (int testCase = 0; testCase < C; testCase++) {
		cin >> k; // number of partial strings
		for (int i = 0; i < MAX + 1; i++) {
			for (int j = 0; j < (1 << MAX) + 1; j++)
				cache[i][j] = "";
		}
		string inputStr;
		for (int i = 0; i < k; i++) {
			cin >> inputStr;
			stringParts.push_back(inputStr);
		}
		EraseOverlapped();
		k = stringParts.size();
		string resultStr = restore();
		//cout << "Final result: " << resultStr << " length: " << resultStr.length()<< endl;
		cout << resultStr << endl;
		stringParts.clear();
	}
}
