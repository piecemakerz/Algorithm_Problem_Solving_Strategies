#include <iostream>
#include <stack>
#include <string>
#include <cstring>
using namespace std;

//내 풀이
int C;
bool isPair[128][128];

bool isAllPaired(const string& inputStr) {
	stack<int> openBrackets;

	for (int i = 0; i < inputStr.length(); i++) {
		char curBracket = inputStr[i];

		if (curBracket == '(' || curBracket == '{' || curBracket == '[')
			openBrackets.push(curBracket);

		else {
			if (openBrackets.empty())
				return false;
			else {
				if (!isPair[openBrackets.top()][curBracket])
					break;
				else
					openBrackets.pop();
			}
		}
	}

	return openBrackets.empty();
}

//책의 풀이
bool wellMatched(const string& formula) {
	//여는 괄호 문자들과 닫는 괄호 문자들
	const string opening("({["), closing(")}]");
	//이미 열린 괄호들을 순서대로 담는 스택
	stack<char> openStack;
	for (int i = 0; i < formula.size(); i++) {
		//여는 괄호인지 닫는 괄호인지 확인한다
		if (opening.find(formula[i]) != -1)
			//여는 괄호라면 무조건 스택에 집어넣는다.
			openStack.push(formula[i]);
		else {
			//이 외의 경우 스택 맨 위의 문자와 맞춰보자.
			//스택이 비어 있는 경우에는 실패
			if (openStack.empty()) return false;
			//서로 짝이 맞지 않아도 실패
			if (opening.find(openStack.top()) != closing.find(formula[i]))
				return false;
			//짝을 맞춘 괄호는 스택에서 뺀다.
			openStack.pop();
		}
	}
	//닫히지 않는 괄호가 없어야 성공
	return openStack.empty();
}
int main(void) {
	cin >> C;
	memset(isPair, 0, sizeof(isPair));
	isPair['{']['}'] = true;
	isPair['('][')'] = true;
	isPair['['][']'] = true;

	for (int testCase = 0; testCase < C; testCase++) {
		string input;
		cin >> input;
		cout << (isAllPaired(input) ? "YES" : "NO") << endl;
	}
	return 0;
}