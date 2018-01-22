#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#define MAX_SIZE 1024

using namespace std;
// 내 풀이
void QuadTree(const string& arr) {
	if (arr.length() == 1 || arr[0] != 'x') {
		cout << arr[0];
		return;
	}

	cout << 'x';
	// 범위를 지정해 주는데 많은 고민을 함. 책의 풀이는 반복자 참조자를 사용하여 굳이 범위를 지정해주지 않았다는 점이 의미있음.
	int start[4], end[4];
	int curIdx = 1, check;
	for (int i = 0; i < 4; i++) {
		start[i] = curIdx, check = 1;
		while (check > 0) {
			if (arr[curIdx] == 'x')
				check += 4;
			curIdx++, check--;
		}
		end[i] = curIdx-1;
	}

	QuadTree(arr.substr(start[2], end[2]+1));
	QuadTree(arr.substr(start[3], end[3]+1));
	QuadTree(arr.substr(start[0], end[0]+1));
	QuadTree(arr.substr(start[1], end[1]+1));
	return;
}


// 책의 풀이 - 과정1
char decompressed[MAX_SIZE][MAX_SIZE];
void decompress(string::iterator& it, int y, int x, int size) {
	char head = *it;
	it++;

	if (head == 'b' || head == 'w') {
		for (int dy = 0; dy < size; dy++)
			for (int dx = 0; dx < size; dx++)
				decompressed[y + dy][x + dx] = head;
	}
	else {
		int half = size / 2;
		decompress(it, y, x, half);
		decompress(it, y, x + half, half);
		decompress(it, y + half, x, half);
		decompress(it, y + half, x + half, half);
	}
}

//책의 풀이 - 과정2
string reverse(string::iterator& it) {
	char head = *it;
	it++;

	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);

	return string("x") + upperLeft + upperRight + lowerLeft + lowerRight;
}
int main(void){
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		string inputStr;
		cin>>inputStr;
		QuadTree(inputStr);
		cout << endl;
	}
	return 0;
}