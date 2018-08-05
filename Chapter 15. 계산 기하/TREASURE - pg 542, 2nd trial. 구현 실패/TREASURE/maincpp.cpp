#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
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
//������ ������ �ذ��ϴ� �ٰ��� Ŭ���� �˰����� ����

typedef vector<vector2> polygon;
//������ �ܼ� �ٰ����� �������� ���Ѵ�.
//(a, b)�� �����ϴ� �������� �ٰ��� p�� �ڸ� ��, (a, b)�� ���ʿ� �ִ� �κе��� ��ȯ�Ѵ�.
polygon curPoly(const polygon& p,
	const vector2& a, const vector2& b) {
	int n = p.size();
	//�� ���� ����� ���� �ִ��� ���θ� �켱 Ȯ���Ѵ�.
	vector<bool> inside(n);
	for (int i = 0; i < n; i++)
		inside[i] = ccw(a, b, p[i]) >= 0;
	polygon ret;
	//�ٰ����� �� ���� ��ȸ�ϸ鼭 ��� �ٰ����� �� ���� �߰��Ѵ�.
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		//����� ���� �ִ� �� p[i]�� �׻� ��� �ٰ����� ���Եȴ�.
		if (inside[i]) ret.push_back(p[i]);
		//�� p[i] - p[j]�� ������ �����ϸ� �������� ��� �ٰ����� ���Խ�Ų��.
		if (inside[i] != inside[j]) {
			vector2 cross;
			assert(lineIntersection(p[i], p[j], a, b, cross));
			ret.push_back(cross);
		}
	}
	return ret;
}
//��������-ȣġ��(Sutherland-Hodgman) �˰����� �̿��� �ٰ��� Ŭ����
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