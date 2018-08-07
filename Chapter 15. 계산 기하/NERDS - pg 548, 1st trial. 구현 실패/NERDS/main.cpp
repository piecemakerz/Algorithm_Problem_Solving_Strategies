#include <iostream>
#include <vector>
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
//�� q�� �ٰ��� p�ȿ� ���ԵǾ� ���� ��� ��, �ƴ� ��� ������ ��ȯ�Ѵ�.
//q�� �ٰ����� ��� ���� �ִ� ����� ��ȯ ���� ���ǵǾ� ���� �ʴ�.
bool isInside(vector2 q, const vector<vector2>& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		// (p[i], p[j])�� �������� ���η� ���������°�?
		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			//���������� x��ǥ�� ����Ѵ�.
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y)
				/ (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX)
				crosses++;
		}
	}
	return crosses % 2 > 0;
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

typedef vector<vector2> polygon;
int c, n;
polygon nerds, notnerds;

//���� ������ ã�� ���� ���� �˰����� ����

//points�� �ִ� ������ ��� �����ϴ� �ּ��� ���� �ٰ����� ã�´�.
polygon giftWrap(const polygon& points) {
	int n = points.size();
	polygon hull;
	//���� ���� �Ʒ� ���� ã�´�. �� ���� ������ �ݵ�� ���Եȴ�.
	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);
	while (true) {
		//ph = ���� �ֱٿ� ���� ������ ���� ��
		//ph���� �����ϴ� ���Ͱ� ���� ������ �� next�� ã�´�.
		//������ ���� ���� �� ������ ���� �� ���� �����Ѵ�.
		vector2 ph = hull.back(), next = points[0];
		for (int i = 1; i < n; i++) {
			//ph�� �������� points[i]�� next���� ���ʿ� ������ ���,
			//�����ʿ� ������ ����, ph, points[i], next�� �������� ������
			//0�� ��ȯ�Ѵ�.
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() -
				(points[i] - ph).norm();
			//ph, points[i], next�� �������� �ִ� ��� ph�κ���
			//���� �ָ� ������ �ִ� ���� ���� ������ �����Ѵ�.
			if (cross > 0 || (cross == 0 && dist < 0))
				next = points[i];
		}
		//���������� ���ƿ����� �����Ѵ�.
		if (next == pivot) break;
		//next�� ���� ������ ���Խ�Ų��.
		hull.push_back(next);
	}
	return hull;
}

//�� ���� �ٰ����� ���� ���θ� Ȯ���ϴ� polygonIntersects() �Լ��� ����

//�� �ٰ����� ���� ��ų� ��ġ���� ���θ� ��ȯ�Ѵ�.
//�� ���̶� ��ģ�ٸ� true�� ��ȯ�Ѵ�.
bool polygonIntersects(const polygon& p, const polygon& q) {
	int n = p.size(), m = q.size();
	//�켱 �� �ٰ����� �ٸ� �ٰ����� ���ԵǾ� �ִ� ��츦 Ȯ������.
	if (isInside(p[0], q) || isInside(q[0], p)) return true;
	//�� ���� ���, �� �ٰ����� ���� ��ģ�ٸ� ���� ��� �� ���� �ݵ�� �����Ѵ�.
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