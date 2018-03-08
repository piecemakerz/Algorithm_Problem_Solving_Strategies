/*
<Question>
If there are 'k' pieces of partial strings given,
calculate shortest string that includes all partial strings.
All strings consist only lowercase alphabets.
If there are more than 1 result strings that satisfy all conditions with same length,
choose any string.

<Input>
In the first line of input, number of test case 'C'(C<=50) is given.
In each test case, number of partial string 'k'(1<=k<=15) is given in the first line,
and in next k lines partial strings are given.
Length of partial string is between 1 to 40.

<Output>
For each testcase, print shortest string that includes all partial strings.

<Sample Input>
3
3
geo
oji
jing
2
world
hello
3
abrac
cadabra
dabr

<Sample Output>
geojing
helloworld
cadabrac
*/

/*
<Description>
Saved all input partial strings in vector 'stringParts'.
Saved current shortest string result in global variable 'answer'.
Used 'cache' array for memoization - to skip repeated function call.

Algorithm I designed to solve this problem is divided into two function - restore() & eraseOverlapped().

restore() function calculates shortest string that includes all partial strings in 'stringParts'.
Result of resotre() is saved in 'answer'.

For restore(), there are three parameters - 'curString', 'selected' and 'last'.
'curString' stands for currently selected and overlapped string result.
'selected' stands for currently selected elements of 'stringParts'. Used bitmask to make my algorithm concise.
'last' stands for last selected element of 'stringParts' for making 'curString'.

eraseOverlapped() function does preprocessing - it deletes elements of 'stringParts' that can be completly included
to other elements before executing restore().

*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#define MAX 15
using namespace std;

int k;

vector<string> stringParts;
string cache[MAX + 1][(1 << MAX) + 1]; //[last selected string][set of selected strings in Bitmask]

string restore(int selected = 0, int last = -1) {
	//base case 1
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

	//base case 2 - memoization
	string& ret = cache[last][selected];
	if (!ret.empty()) return ret;

	string curString = stringParts[last];
	for (int next = 0; next < k; next++) {
		if (selected & (1 << next)) continue;

		string checkStr = restore(selected + (1 << next), next);
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
//check if there are strings that can be completely included by other strings, and delete that string.
void EraseOverlapped() {
	//arranging string vector in ascending order of string length
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

	//deleting included strings
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
