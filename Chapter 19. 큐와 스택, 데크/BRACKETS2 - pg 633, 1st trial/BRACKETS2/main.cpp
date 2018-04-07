#include <iostream>
#include <stack>
#include <string>
#include <cstring>
using namespace std;

//�� Ǯ��
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

//å�� Ǯ��
bool wellMatched(const string& formula) {
	//���� ��ȣ ���ڵ�� �ݴ� ��ȣ ���ڵ�
	const string opening("({["), closing(")}]");
	//�̹� ���� ��ȣ���� ������� ��� ����
	stack<char> openStack;
	for (int i = 0; i < formula.size(); i++) {
		//���� ��ȣ���� �ݴ� ��ȣ���� Ȯ���Ѵ�
		if (opening.find(formula[i]) != -1)
			//���� ��ȣ��� ������ ���ÿ� ����ִ´�.
			openStack.push(formula[i]);
		else {
			//�� ���� ��� ���� �� ���� ���ڿ� ���纸��.
			//������ ��� �ִ� ��쿡�� ����
			if (openStack.empty()) return false;
			//���� ¦�� ���� �ʾƵ� ����
			if (opening.find(openStack.top()) != closing.find(formula[i]))
				return false;
			//¦�� ���� ��ȣ�� ���ÿ��� ����.
			openStack.pop();
		}
	}
	//������ �ʴ� ��ȣ�� ����� ����
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