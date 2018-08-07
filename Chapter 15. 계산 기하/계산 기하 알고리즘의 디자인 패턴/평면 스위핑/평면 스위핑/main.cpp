#include <vector>
#include <algorithm>
using namespace std;

//평면 스위핑을 이용하여 직사각형 합집합의 면적을 구하는 unionArea() 함수의 구현

//x1 < x2, y1 < y2
struct Rectangle {
	int x1, y1, x2, y2;
};

//직사각형들의 면적을 계산한다.
int unionArea(const vector<Rectangle>& rects) {
	if (rects.empty()) return 0;
	//이벤트 정보: (x좌표, 왼쪽인가 오른쪽인가, 사각형의 번호)
	typedef pair<int, pair<int, int>> Event;
	vector<Event> events;
	//ys = 사각형들의 모든 y좌표 모음
	vector<int> ys;
	//각 사각형을 순회하면서 y좌표의 모음과 이벤트의 집합을 찾는다.
	for (int i = 0; i < rects.size(); i++) {
		ys.push_back(rects[i].y1);
		ys.push_back(rects[i].y2);
		events.push_back(Event(rects[i].x1, make_pair(1, i)));
		events.push_back(Event(rects[i].x2, make_pair(-1, i)));
	}
	//y좌표의 집합을 정렬하고 중복을 제거
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end);
	//이벤트를 앞에서부터 체크하기 위해 이벤트 목록을 정렬
	sort(events.begin(), events.end());
	int ret = 0;
	//count[i] = ys[i]~ys[i+1] 구간에 겹쳐진 사각형의 수
	vector<int> count(ys.size() - 1, 0);
	for (int i = 0; i < events.size(); i++) {
		int x = events[i].first, delta = events[i].second.first;
		int rectangle = events[i].second.second;
		//count[]를 갱신
		int y1 = rects[rectangle].y1, y2 = rects[rectangle].y2;
		//events[i]가 직사각형의 왼쪽 변이라면 현재 사각형이
		//curLength에 반영될 것이고, 오른쪽 변이라면 현재 사각형의
		//넓이는 더 이상 cutLength에 반영되지 않는다.
		for (int j = 0; j < ys.size(); j++)
			if (y1 <= ys[j] && ys[j] < y2)
				count[j] += delta;
		//cutLength() 값을 계산한다.
		//ys[i]~ys[i+1] 구간에 사각형이 존재한다면 해당 구간의 길이를 curLength에 더한다.
		int cutLength = 0;
		for (int j = 0; j < ys.size() - 1; j++)
			if (count[j] > 0)
				cutLength += ys[j + 1] - ys[j];
		//다음 이벤트까지의 거리에 curLength를 곱한 값을 ret에 더한다.
		if (i + 1 < events.size())
			ret += cutLength * (events[i + 1].first - x);
	}
	return ret;
}