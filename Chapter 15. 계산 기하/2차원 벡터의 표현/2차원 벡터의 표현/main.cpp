#include <cmath>
#include <algorithm>
using namespace std;

#define EPSILON 0.0001
//2���� ���͸� ǥ���ϴ�  vector2 Ŭ������ ����
const double PI = 2.0 * acos(0.0);
//2���� ���͸� ǥ���Ѵ�.
struct vector2 {
	double x, y;
	//�����ڸ� explicit���� �����ϸ� vector2�� ���� ���� �߸���
	//�Ǽ��� ���� ���� �������ش�.
	explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	//�� ������ ��
	bool operator == (const vector2& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}
	//������ ������ ����
	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}
	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}
	//�Ǽ��� ����
	vector2 operator * (double rhs) const {
		return vector2(x*rhs, y*rhs);
	}
	//������ ���̸� ��ȯ�Ѵ�.
	double norm() const { return hypot(x, y); }
	//������ ���� ���� ����(unit vector)�� ��ȯ�Ѵ�.
	//�����Ϳ� ���� ȣ���� ��� ��ȯ ���� ���ǵ��� �ʴ´�.
	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}
	//x���� ���� �������κ��� �� ���ͱ��� �ݽð� �������� �� ����
	//fmod(x, y) = x/y�� �ε� �Ҽ��� ������
	double polar() const { return fmod(atan2(y, x) + 2 * PI, 2 * PI); }
	//����/������ ����
	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	double cross(const vector2& rhs) const {
		return x * rhs.y - rhs.x * y;
	}
	//�� ���͸� rhs�� �翵�� ���
	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

//�� ������ ���⼺�� �Ǵ��ϴ� ccw() �Լ��� ����
//�������� ���� b�� ���� a�� �ݽð� �����̸� ���, �ð� �����̸� ����
double ccw(vector2 a, vector2 b) {
	return a.cross(b);
}
//�� p�� �������� ���� b�� ���� a�� �ݽð� �����̸� ���
//�ð� �����̸� ����, �����̸� 0�� ��ȯ�Ѵ�.
double ccw(vector2 p, vector2 a, vector2 b) {
	return ccw(a - p, b - p);
}

//�� ������ �������� ����ϴ� lineIntersection() �Լ��� ����
//(a, b)�� �����ϴ� ���� (c, d)�� �����ϴ� ���� ������ x�� ��ȯ�Ѵ�.
//�� ���� �����̸� (��ġ�� ��츦 ����) ������, �ƴϸ� ���� ��ȯ�Ѵ�.
bool lineIntersection(vector2 a, vector2 b,
	vector2 c, vector2 d, vector2& x) {
	double det = (b - a).cross(d - c);
	//�� ���� ������ ���
	if (fabs(det) < EPSILON) return false;
	x = a + (b - a) * ((c - a).cross(d - c) / det);
	return true;
}
//���а� ������ �������� ����ϴ� segmentIntersection()�� ����
//(a, b)�� (c, d)�� ������ �� ������ �� �̵��� �� ������ ��ġ���� Ȯ���Ѵ�.
bool parallelSegments(vector2 a, vector2 b,
	vector2 c, vector2 d, vector2& p) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);
	//�� ���� ���� ���ų� �� ������ ��ġ�� �ʴ� ��츦 �켱 �ɷ�����.
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;
	//�� ������ Ȯ���� ��ģ��. �������� �ϳ� ã��.
	if (a < c) p = c; else p = a;
	return true;
}
//p�� (a, b)�� ���θ鼭 �� ���� x, y�࿡ ������ �ּ� �簢�� ���ο� �ִ��� Ȯ���Ѵ�.
//a, b, p�� ������ �� �ִٰ� �����Ѵ�.
bool isBoundingRectangle(vector2 p, vector2 a, vector2 b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}
//(a, b) ���а� (c, d) ������ ������ p�� ��ȯ�Ѵ�.
//������ ���� ���� ��� �ƹ� ���̳� ��ȯ�Ѵ�.
//�� ������ �������� ���� ��� false�� ��ȯ�Ѵ�.
bool segmentIntersection(vector2 a, vector2 b,
	vector2 c, vector2 d, vector2& p) {
	//�� ������ ������ ��츦 �켱 ���ܷ� ó���Ѵ�.
	if (!lineIntersection(a, b, c, d, p))
		return parallelSegments(a, b, c, d, p);
	//p�� �� ���п� ���ԵǾ� �ִ� ��쿡�� ���� ��ȯ�Ѵ�.
	return isBoundingRectangle(p, a, b) &&
		isBoundingRectangle(p, c, d);
}
//�� ������ ���� ���θ� �� �� �����ϰ� Ȯ���ϴ� segmentIntersects() �Լ��� ����
//�� ������ ���� �����ϴ��� ���θ� ��ȯ�Ѵ�.
bool segmentIntersects(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	//�� ������ �� ���� ���� �ְų� ������ ��ġ�� ���
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}
//���� �� ������ �Ÿ��� ����ϴ� �Լ� pointToLine()�� ����
//�� p���� (a, b) ������ ���� ������ ���� ���Ѵ�.
vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b) {
	return a + (p - a).project(b - a);
}
//�� p�� (a, b) ���� ������ �Ÿ��� ���Ѵ�.
double pointToLine(vector2 p, vector2 a, vector2 b) {
	return  (p - perpendicularFoot(p, a, b)).norm();
}