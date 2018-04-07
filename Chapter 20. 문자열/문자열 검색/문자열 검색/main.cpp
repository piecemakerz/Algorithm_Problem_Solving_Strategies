#include <iostream>
#include <vector>
#include <string>
using namespace std;

//단순한 문자열 검색 알고리즘의 구현
//H의 부분 문자열로 N문자열이 출현하는 시작 위치들을 모두 반환한다.
vector<int> naiveSearch(const string& H, const string& N) {
	vector<int> ret;
	//모든 시작 위치를 다 시도해 본다.
	for (int begin = 0; begin + N.size() <= H.size(); begin++) {
		bool matched = true;
		for(int i=0; i<N.size(); i++)
			if (H[begin + i] != N[i]) {
				matched = false;
				break;
			}
		if (matched) ret.push_back(begin);
	}
	return ret;
}