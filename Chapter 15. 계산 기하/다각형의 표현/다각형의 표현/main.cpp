#include <vector>
#include <algorithm>
using namespace std;

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

//단순 다각형의 넓이를 구하는 area() 함수의 구현

//주어진 단순 다각형 p의 넓이를 구한다.
//p는 각 꼭지점의 위치 벡터의 집합으로 주어진다.
double area(const vector<vector2>& p) {
	double ret = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return fabs(ret) / 2.0;
}

//주어진 점이 단순 다각형 내부에 포함되어 있는지 확인하는 isInside() 함수의 구현

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