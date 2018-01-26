#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> selected;
void stringArrange() {
	for (int i = 0; i < selected.size() - 1; i++) {
		for (int j = i+1; j < selected.size(); j++) { 
			if (selected[i].compare(selected[j]) > 0)
				swap(selected[i], selected[j]);
		}
	}
}

// 책의 동적 계획법 알고리즘 1
bool match(const string& w, const string& s) {
	int pos = 0;
	while (pos < w.size() && pos < s.size() && (w[pos] == '?' || w[pos] == s[pos]))
		pos++;
	
	if (pos == w.size())
		return pos == s.size();
	if (w[pos] == '*') {
		for (int step = 0; step + pos <= s.size(); step++) {
			if (match(w.substr(pos + 1), s.substr(step + pos)))
				return true;
		}
	}

	return false;
}

// 메모이제이션을 적용한 책의 동적 계획법 알고리즘 2
int cache[101][101];
string W, S;

bool match2(int w, int s) {
	int& ret = cache[w][s];
	if (ret != -1) return ret;

	while (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s])) {
		w++;
		s++;
	}

	if (w == W.size())
		return ret = (s == S.size());

	if (W[w] == '*') {
		for (int step = 0; step + s <= S.size(); step++) {
			if (match2(w + 1, s + step))
				return ret = 1;
		}
	}

	return ret = 0;
}

// 알고리즘 2를 O(n^2) 시간에 풀도록 개선한 알고리즘
bool improvedMatch(int w, int s) {
	int& ret = cache[w][s];
	if (ret != -1) return ret;

	if (w < W.size() && s < S.size() && (W[w] == '?' || W[w] == S[s]))
		return ret = improvedMatch(w + 1, s + 1);

	if (w == W.size())
		return ret = (s == S.size());

	if (W[w] == '*') {
		if (improvedMatch(w + 1, s) || (s < S.size() && improvedMatch(w, s + 1)))
			return ret = 1;
	}

	return ret = 0;
}
int main(void) {
	
}