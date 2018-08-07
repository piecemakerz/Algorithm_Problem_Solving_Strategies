#include <vector>
#include <algorithm>
using namespace std;

//��� �������� �̿��Ͽ� ���簢�� �������� ������ ���ϴ� unionArea() �Լ��� ����

//x1 < x2, y1 < y2
struct Rectangle {
	int x1, y1, x2, y2;
};

//���簢������ ������ ����Ѵ�.
int unionArea(const vector<Rectangle>& rects) {
	if (rects.empty()) return 0;
	//�̺�Ʈ ����: (x��ǥ, �����ΰ� �������ΰ�, �簢���� ��ȣ)
	typedef pair<int, pair<int, int>> Event;
	vector<Event> events;
	//ys = �簢������ ��� y��ǥ ����
	vector<int> ys;
	//�� �簢���� ��ȸ�ϸ鼭 y��ǥ�� ������ �̺�Ʈ�� ������ ã�´�.
	for (int i = 0; i < rects.size(); i++) {
		ys.push_back(rects[i].y1);
		ys.push_back(rects[i].y2);
		events.push_back(Event(rects[i].x1, make_pair(1, i)));
		events.push_back(Event(rects[i].x2, make_pair(-1, i)));
	}
	//y��ǥ�� ������ �����ϰ� �ߺ��� ����
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end);
	//�̺�Ʈ�� �տ������� üũ�ϱ� ���� �̺�Ʈ ����� ����
	sort(events.begin(), events.end());
	int ret = 0;
	//count[i] = ys[i]~ys[i+1] ������ ������ �簢���� ��
	vector<int> count(ys.size() - 1, 0);
	for (int i = 0; i < events.size(); i++) {
		int x = events[i].first, delta = events[i].second.first;
		int rectangle = events[i].second.second;
		//count[]�� ����
		int y1 = rects[rectangle].y1, y2 = rects[rectangle].y2;
		//events[i]�� ���簢���� ���� ���̶�� ���� �簢����
		//curLength�� �ݿ��� ���̰�, ������ ���̶�� ���� �簢����
		//���̴� �� �̻� cutLength�� �ݿ����� �ʴ´�.
		for (int j = 0; j < ys.size(); j++)
			if (y1 <= ys[j] && ys[j] < y2)
				count[j] += delta;
		//cutLength() ���� ����Ѵ�.
		//ys[i]~ys[i+1] ������ �簢���� �����Ѵٸ� �ش� ������ ���̸� curLength�� ���Ѵ�.
		int cutLength = 0;
		for (int j = 0; j < ys.size() - 1; j++)
			if (count[j] > 0)
				cutLength += ys[j + 1] - ys[j];
		//���� �̺�Ʈ������ �Ÿ��� curLength�� ���� ���� ret�� ���Ѵ�.
		if (i + 1 < events.size())
			ret += cutLength * (events[i + 1].first - x);
	}
	return ret;
}