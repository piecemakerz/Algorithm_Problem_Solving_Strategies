#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

//각 판자의 높이를 저장하는 배열
vector<int> h;
//스택을 사용한 O(n) 해법
int solveStack() {
	//남아 있는 판자(right가 정해지지 않은 판자)들의 위치들을 저장한다.
	//남아 잇는 판자들의 right가 결정되려면 
	//현재 확인하는 판자의 높이가 남아 있는 판자의 높이보다 낮아야 한다.

	//남아있는 판자의 높이와 현재 확인하는 판자의 높이가 같을 경우
	//남아있는 판자의 최대 사각형과 현재 확인하는 판자의 최대 사각형이 일치하므로
	//고려할 필요 없이 이 판자를 남아있는 판자 스택에서 삭제한다.
	stack<int> remaining;
	h.push_back(0); // h의 오른쪽 끝에 높이가 0인 가상의 판자 추가
	int ret = 0;
	for (int i = 0; i < h.size(); i++) {
		//현재 판자와 남아 있는 모든 판자들 간의 비교
		//남아 있는 판자들 중 오른쪽 끝 판자(j=remaining.top())가 h[i]보다 높다면
		//이 판자의 최대 사각형은 i에서 끝난다. (right[j] = i)
		while (!remaining.empty() && h[remaining.top()] >= h[i]) {
			int j = remaining.top(); // 스택 제일 위의 요소 가져오기
			remaining.pop(); // 스택 제일 위의 요소 제거
			int width = -1;
			//j번째 판자 왼쪽에 판자가 하나도 안 남아 있는 경우 left[j] = -1,
			//아닌 경우 left[j] = 남아 있는 판자 중 가장 오른쪽에 있는 판자의 번호
			//가 된다.
			if (remaining.empty())
				width = i;
			else
				width = (i - remaining.top() - 1);
			ret = max(ret, h[j] * width); // 최대 사각형 넓이 갱신
		}
		remaining.push(i); // 현재 판자를 남아 있는 판자에 추가한다.
	}
	return ret;
}