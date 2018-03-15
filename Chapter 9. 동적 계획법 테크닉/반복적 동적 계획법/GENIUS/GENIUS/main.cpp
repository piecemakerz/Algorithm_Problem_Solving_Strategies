#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int n, k, m;
int Q[10];
int songLength[50];
double totalPer[50];
double T[50][50];
double cache[1000001][50]; // [지난 시간][현재 곡]

/*void calPercentage(int timePassed = songLength[0], int curSong = 0, double curPer = 1) {
	if (timePassed > k) {
		totalPer[curSong] += curPer; 
		return;
	}
	for (int nextSong = 0; nextSong < n; nextSong++) {
		calPercentage(timePassed + songLength[nextSong], nextSong, curPer * T[curSong][nextSong]);
	}
	return;

}*/
double calPercentage(int timePassed = songLength[0], int curSong = 0) {
	double& ret = cache[timePassed][curSong];
	if (ret != -1)
		return ret;
	for(int nextSong=0; nextSong<n; nextSong++)
		ret += calPercentage(timePassed + songLength[nextSong], nextSong);
}
int main(void) {
	int C;
	cin >> C;
	for (int testCase = 0; testCase < C; testCase++) {
		memset(cache, 0, sizeof(cache));

		cin >> n >> k >> m; // 곡 수/시간/좋아하는 곡 수
		for (int i = 0; i < n; i++)
			cin >> songLength[i];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> T[i][j];
		for (int i = 0; i < m; i++)
			cin >> Q[i];
		calPercentage();
		for (int i = 0; i < m; i++)
			cout << totalPer[Q[i]] << ' ';
		cout << endl;
	}
}