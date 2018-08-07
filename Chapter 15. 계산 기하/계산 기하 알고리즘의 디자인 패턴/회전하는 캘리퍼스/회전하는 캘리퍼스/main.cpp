#include <algorithm>
#include <vector>
using namespace std;

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
typedef vector<vector2> polygon;
//���� �ٰ����� ������ ��� ȸ���ϴ� Ķ���۽� �˰���

//�ð� �ݴ� �������� �־��� ���� �ٰ������� ���� �� ������ �� ������ �Ÿ��� ��ȯ�Ѵ�.
double diameter(const polygon& p) {
	int n = p.size();
	//�켱 ���� ���ʿ� �ִ� ���� �����ʿ� �ִ� ���� ã�´�.
	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();
	//p[left]�� p[right]�� ���� �������� ���δ�. �� �������� ����
	//���ݴ� ������ ����Ű�Ƿ�, A�� ���⸸�� ǥ���ϸ� �ȴ�.
	vector2 calipersA(0, 1);
	double ret = (p[right] - p[left]).norm();
	//toNext[i] = p[i]���� ���� �������� ������ ��Ÿ���� ���� ����
	vector<vector2> toNext(n);
	for (int i = 0; i < n; i++)
		toNext[i] = (p[(i + 1) % n] - p[i]).normalize();
	//a�� b�� ���� �� ������ ��� ���� ä�� ȸ���ϰ� �ִ����� ��Ÿ����.
	int a = left, b = right;
	//�� ���� ���Ƽ� �� ������ ���� ��ġ�� �ٲ� �� ���� ����Ѵ�.
	while (a != right || b != left) {
		//a���� ���� �������� ������ b���� ���� �������� ���� �� ��� ���� ������ Ȯ��
		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);
		if (cosThetaA > cosThetaB) { //thetaA < thetaB
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = vector2(-toNext[b].x, -toNext[b].y);
			b = (b + 1) % n;
		}
		ret = max(ret, (p[a] - p[b]).norm());
	}
	return ret;
}