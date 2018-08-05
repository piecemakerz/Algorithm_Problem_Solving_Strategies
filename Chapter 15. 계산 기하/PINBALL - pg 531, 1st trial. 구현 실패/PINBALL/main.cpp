#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

const double PI = 2.0 * acos(0.0);
const double EPSILON = 1e-9;
const double INFTY = 1e200;

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
int c, n;
int radius[100];
vector2 center[100];

//��ֹ����� �浹 ������ ã�� �Լ��� ����

//2�� ������ ax^2 + bx + c = 0�� ��� �Ǳ��� ũ�� ������� ��ȯ�Ѵ�.
vector<double> solve2(double a, double b, double c) {
	double d = b * b - 4 * a*c;
	//�ذ� ���� ���
	if (d < -EPSILON) return vector<double>();
	//�߱�
	if (d < EPSILON) return vector<double>(1, -b / (2 * a));
	vector<double> ret;
	ret.push_back((-b - sqrt(d)) / (2 * a));
	ret.push_back((-b + sqrt(d)) / (2 * a));
	return ret;
}
//here�� �ִ� ���� 1�ʸ��� dir��ŭ ������ ��, center�� �߽����� �ϰ�
//������ radius�� ��ֹ��� �� �� �Ŀ� �浹�ϴ��� ��ȯ�Ѵ�.
//�浹���� ���� ��� '���� ū ��' INFTY�� ��ȯ�Ѵ�.
double hitCircle(vector2 here, vector2 dir,
	vector2 center, int radius) {
	double a = dir.dot(dir);
	double b = 2 * dir.dot(here - center);
	double c = center.dot(center) + here.dot(here)
		- 2 * here.dot(center) - radius * radius;
	vector<double> sols = solve2(a, b, c);
	if (sols.empty() || sols[0] < EPSILON) return INFTY;
	return sols[0];
}

//���� ��ֹ��� �ε��� ���� ������ ������ ����ϴ� reflect()�� ����

//here�� �ִ� ���� dir �������� ������ center�� �߽����� �ϴ� ��ֹ�����
//contact ��ġ���� �浹���� �� ���� ���ο� ������ ��ȯ�Ѵ�.
vector2 reflect(vector2 dir, vector2 center, vector2 contact) {
	return (dir - dir.project(contact - center) * 2).normalize();
}

//�ɺ� �ùķ��̼� ������ �ذ��ϴ� �ùķ��̼� �ڵ�

//���� ���� ��ġ�� ������ �־��� �� �ִ� 10���� �浹�� ����Ѵ�.
void simulate(vector2 here, vector2 dir) {
	//������ �׻� ���� ���ͷ� ��������.
	dir = dir.normalize();
	int hitCount = 0;
	while (hitCount < 100) {
		//�̹��� �浹�� ��ֹ��� ã�´�.
		int circle = -1;
		double time = INFTY * 0.5;
		//�� ��ֹ��� ��ȸ�ϸ� ���� ���� ������ ��ֹ��� ã�´�.
		for (int i = 0; i < n; i++) {
			double cand = hitCircle(here, dir, center[i], radius[i] + 1);
			if (cand < time) {
				time = cand;
				circle = i;
			}
		}
		//���̻� ��ֹ��� �浹���� �ʰ� �������� ��� ���
		if (circle == -1) break;
		//�ε����� ��ֹ��� ��ȣ�� ����Ѵ�.
		if (hitCount++) cout << " ";
		cout << circle;
		//���� �� ��ġ�� ����Ѵ�.
		vector2 contact = here + dir * time;
		//�ε��� ��ġ�� �� �������� here�� dir�� �����Ѵ�./
		dir = reflect(dir, center[circle], contact);
		here = contact;
	}
}

int main(void) {
	int x, y, dx, dy;
	cin >> c;
	for (int test = 0; test < c; test++) {
		cin >> x >> y >> dx >> dy >> n;
		vector2 dir(dx, dy), here(x, y);
		int xi, yi, ri;
		for (int i = 0; i < n; i++) {
			cin >> xi >> yi >> ri;
			radius[i] = ri;
			center[i] = vector2(xi, yi);
		}
		simulate(here, dir);
		cout << endl;
	}
}