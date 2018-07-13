#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
//digits: e의 자릿수들을 정렬한 것
string e, digits;
int n, m;
int cache[1 << 14][20][2];
//과거 가격을 앞 자리부터 채워나가고 있다.
//index: 이번에 채울 자리의 인덱스
//taken: 지금까지 사용한 자릿수들의 집합
//mod: 지금까지 만든 가격의 m에 대한 나머지
//less: 지금까지 만든 가격이 이미 e보다 작으면 1, 아니면 0
int price(int index, int taken, int mod, int less) {
	//기저 사례

	
}
