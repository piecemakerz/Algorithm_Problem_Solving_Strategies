#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
using namespace std;

/*
#define MAX_SIZE 1000

char decompressed[MAX_SIZE][MAX_SIZE];
void decompress(string::iterator& it, int y, int x, int size) {
char head = *(it++);
if (head == 'b' || head == 'w') {
for (int dy = 0; dy < size; dy++) {
for (int dx = 0; dx < size; dx++)
decompressed[y + dy][x + dx] = head;
}
}
else {
int half = size / 2;
decompress(it, y, x, half);
decompress(it, y, x + half, half);
decompress(it, y + half, x, half);
decompress(it, y + half, x + half, half);
}
}
*/
#define MAX_LEN 1000

string reverse(string::iterator& it) {
	char head = *it;
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);
	//각각 위와 아래 조각들의 위치를 바꾼다.
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main(void) {
	int testtime;
	char temp;
	char input[MAX_LEN];
	scanf("%d", &testtime);
	scanf("%c", &temp);
	for (int i = 0; i < testtime; i++) {
		int idx = 0;
		while (true) {
			scanf("%c", &temp);
			if (temp == '\n')
				break;
			input[idx++] = temp;
		}
		string str(input);
		string::iterator it = str.begin();
		cout << reverse(it) << endl;
		str.clear();
	}
}