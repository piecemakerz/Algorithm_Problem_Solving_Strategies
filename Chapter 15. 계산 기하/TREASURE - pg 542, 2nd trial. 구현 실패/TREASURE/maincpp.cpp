#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
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
//두 직선의 교차점을 계산하는 lineIntersection() 함수의 구현
//(a, b)를 포함하는 선과 (c, d)를 포함하는 선의 교점을 x에 반환한다.
//두 선이 평행이면 (겹치는 경우를 포함) 거짓을, 아니면 참을 반환한다.
bool lineIntersection(vector2 a, vector2 b,
	vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	//두 선이 평행인 경우
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}
//보물섬 문제를 해결하는 다각형 클리핑 알고리즘의 구현

typedef vector<vector2> polygon;
//반평면과 단순 다각형의 교집합을 구한다.
//(a, b)를 포함하는 직선으로 다각형 p를 자른 뒤, (a, b)의 왼쪽에 있는 부분들을 반환한다.
polygon curPoly(const polygon& p,
	const vector2& a, const vector2& b) {
	int n = p.size();
	//각 점이 반평면 내에 있는지 여부를 우선 확인한다.
	vector<bool> inside(n);
	for (int i = 0; i < n; i++)
		inside[i] = ccw(a, b, p[i]) >= 0;
	polygon ret;
	//다각형의 각 변을 순회하면서 결과 다각형의 각 점을 발견한다.
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		//반평면 내에 있는 점 p[i]는 항상 결과 다각형에 포함된다.
		if (inside[i]) ret.push_back(p[i]);
		//변 p[i] - p[j]가 직선과 교차하면 교차점을 결과 다각형에 포함시킨다.
		if (inside[i] != inside[j]) {
			vector2 cross;
			assert(lineIntersection(p[i], p[j], a, b, cross));
			ret.push_back(cross);
		}
	}
	return ret;
}
//서덜랜드-호치맨(Sutherland-Hodgman) 알고리즘을 이용한 다각형 클리핑
polygon intersection(const polygon& p, double x1, double y1,
	double x2, double y2) {
	vector2 a(x1, y1), b(x2, y1), c(x2, y2), d(x1, y2);
	polygon ret = curPoly(p, a, b);
	ret = curPoly(ret, b, c);
	ret = curPoly(ret, c, d);
	ret = curPoly(ret, d, a);
	return ret;
}
int main(void) {

}