#include <vector>
#include <algorithm>
using namespace std;

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

//�ܼ� �ٰ����� ���̸� ���ϴ� area() �Լ��� ����

//�־��� �ܼ� �ٰ��� p�� ���̸� ���Ѵ�.
//p�� �� �������� ��ġ ������ �������� �־�����.
double area(const vector<vector2>& p) {
	double ret = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return fabs(ret) / 2.0;
}

//�־��� ���� �ܼ� �ٰ��� ���ο� ���ԵǾ� �ִ��� Ȯ���ϴ� isInside() �Լ��� ����

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