#include <algorithm>
#include <vector>
using namespace std;

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
typedef vector<vector2> polygon;
//볼록 다각형의 지름을 재는 회전하는 캘리퍼스 알고리즘

//시계 반대 방향으로 주어진 볼록 다각형에서 가장 먼 꼭지점 쌍 사이의 거리를 반환한다.
double diameter(const polygon& p) {
	int n = p.size();
	//우선 가장 왼쪽에 있는 점과 오른쪽에 있는 점을 찾는다.
	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();
	//p[left]와 p[right]에 각각 수직선을 붙인다. 두 수직선은 서로
	//정반대 방향을 가리키므로, A의 방향만을 표현하면 된다.
	vector2 calipersA(0, 1);
	double ret = (p[right] - p[left]).norm();
	//toNext[i] = p[i]에서 다음 점까지의 방향을 나타내는 단위 벡터
	vector<vector2> toNext(n);
	for (int i = 0; i < n; i++)
		toNext[i] = (p[(i + 1) % n] - p[i]).normalize();
	//a와 b는 각각 두 선분이 어디에 붙은 채로 회전하고 있는지를 나타낸다.
	int a = left, b = right;
	//반 바퀴 돌아서 두 선분이 서로 위치를 바꿀 때 까지 계속한다.
	while (a != right || b != left) {
		//a에서 다음 점까지의 각도와 b에서 다음 점까지의 각도 중 어느 쪽이 작은지 확인
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