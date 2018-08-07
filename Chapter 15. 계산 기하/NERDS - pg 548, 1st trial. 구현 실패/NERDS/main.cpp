#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define EPSILON 0.0001
//2차원 벡터를 표현하는  vector2 클래스의 구현
const double PI = 2.0 * acos(0.0);
//2차원 벡터를 표현한다.
struct vector2 {
	double x, y;
	//생성자를 explicit으로 지정하면 vector2를 넣을 곳에 잘못해
	//실수가 들어가는 일을 방지해준다.
	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	//두 벡터의 비교
	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	//벡터의 덧셈과 뺄셈
	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}
	//실수로 곱셈
	vector2 operator * (double rhs) const {
		return vector2(x*rhs, y*rhs);
	}
	//벡터의 길이를 반환한다.
	double norm() const { return hypot(x, y); }
	//방향이 같은 단위 벡터(unit vector)를 반환한다.
	//영벡터에 대해 호출한 경우 반환 값은 정의되지 않는다.
	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}
	//x축의 양의 방향으로부터 이 벡터까지 반시계 방향으로 잰 각도
	//fmod(x, y) = x/y의 부동 소수점 나머지
	double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }
	//내적/외적의 구현
	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	double cross(const vector2& rhs) const {
		return x * rhs.y - rhs.x * y;
	}
	//이 벡터를 rhs에 사영한 결과
	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};
//두 벡터의 방향성을 판단하는 ccw() 함수의 구현
//원점에서 벡터 b가 벡터 a의 반시계 방향이면 양수, 시계 방향이면 음수
double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}
//점 p를 기준으로 벡터 b가 벡터 a의 반시계 방향이면 양수
//시계 방향이면 음수, 평행이면 0을 반환한다.
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}
//점 q가 다각형 p안에 포함되어 있을 경우 참, 아닌 경우 거짓을 반환한다.
//q가 다각형의 경계 위에 있는 경우의 반환 값은 정의되어 있지 않다.
bool isInside(vector2 q, const vector<vector2>& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		// (p[i], p[j])가 반직선을 세로로 가로지르는가?
		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			//가로지르는 x좌표를 계산한다.
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y)
				/ (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
}
//두 선분의 교차 여부를 좀 더 간단하게 확인하는 segmentIntersects() 함수의 구현
//두 선분이 서로 접촉하는지 여부를 반환한다.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	//두 선분이 한 직선 위에 있거나 끝점이 겹치는 경우
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

typedef vector<vector2> polygon;
int c, n;
polygon nerds, notnerds;

//볼록 껍질을 찾는 선물 포장 알고리즘의 구현

//points에 있는 점들을 모두 포함하는 최소의 볼록 다각형을 찾는다.
polygon giftWrap(const polygon& points) {
	int n = points.size();
	polygon hull;
	//가장 왼쪽 아래 점을 찾는다. 이 점은 껍질에 반드시 포함된다.
	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);
	while (true) {
		//ph = 가장 최근에 볼록 껍질에 속한 점
		//ph에서 시작하는 벡터가 가장 왼쪽인 점 next를 찾는다.
		//평행인 점이 여러 개 있으면 가장 먼 것을 선택한다.
		vector2 ph = hull.back(), next = points[0];
		for (int i = 1; i < n; i++) {
			//ph를 기준으로 points[i]가 next보다 왼쪽에 있으면 양수,
			//오른쪽에 있으면 음수, ph, points[i], next가 일직선상에 있으면
			//0을 반환한다.
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() -
				(points[i] - ph).norm();
			//ph, points[i], next가 일직선상에 있는 경우 ph로부터
			//가장 멀리 떨어져 있는 점을 다음 점으로 선택한다.
			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		//시작점으로 돌아왔으면 종료한다.
		if (next == pivot) break;
		//next를 볼록 껍질에 포함시킨다.
		hull.push_back(next);
	}
	return hull;
}

//두 볼록 다각형의 교차 여부를 확인하는 polygonIntersects() 함수의 구현

//두 다각형이 서로 닿거나 겹치는지 여부를 반환한다.
//한 점이라도 겹친다면 true를 반환한다.
bool polygonIntersects(const polygon& p, const polygon& q) {
	int n = p.size(), m = q.size();
	//우선 한 다각형이 다른 다각형에 포함되어 있는 경우를 확인하자.
	if (isInside(p[0], q) || isInside(q[0], p)) return true;
	//이 외의 경우, 두 다각형이 서로 겹친다면 서로 닿는 두 변이 반드시 존재한다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (segmentIntersects(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
				return true;
	return false;
}

int main(void) {
	cin >> c;
	for (int test = 0; test < c; test++) {
		cin >> n;
		int x, y, isnerd;
		for (int i = 0; i < n; i++) {
			cin >> isnerd >> x >> y;
			if (isnerd) nerds.push_back(vector2(x, y));
			else notnerds.push_back(vector2(x, y));
		}
		polygon poly1 = giftWrap(nerds), poly2 = giftWrap(notnerds);
		if (polygonIntersects(poly1, poly2))
			cout << "THEORY IS INVALID" << endl;
		else
			cout << "THEORY HOLDS" << endl;
		nerds.clear(); notnerds.clear();
	}
}