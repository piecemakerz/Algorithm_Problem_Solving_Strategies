#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//블록의 회전된 형태를 계산하고 상대좌표의 목록으로 변환하기
vector<vector<pair<int, int>>> rotations;
//블록의 크기
int blockSize;
//2차원 배열 arr을 시계방향으로 90도 돌린 결과를 반환한다.
vector<string> rotate(const vector<string>& arr) {
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[0].size(); j++)
			ret[j][arr.size() - i - 1] = arr[i][j];
	return ret;
}
//block의 네 가지 회전 형태를 만들고 이들을 상대 좌표의 목록으로 변환한다.
void generateRotations(vector<string> block) {
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		int originY = -1, originX = -1;
		for(int i=0; i<block.size(); i++)
			for(int j=0; j<block[i].size(); j++)
				if (block[i][j] == '#') {
					if (originY == -1) {
						//가장 윗줄 맨 왼쪽에 있는 칸이 원점이 된다.
						originY = i;
						originX = j;
					}
					//각 칸의 위치를 원점으로부터의 상대좌표로 표현한다.
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
		//블록을 시계 방향으로 90도 회전한다.
		block = rotate(block);
	}
	//네 가지 화전 형태 중 중복이 있을 경우 이를 제거한다.
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	//블록이 몇 칸 짜리인지 저장해 둔다.
	blockSize = rotations[0].size();
}

//게임판 덮기 2 문제를 해결하는 완전 탐색 알고리즘
//게임판의 정보
int boardH, boardW;
vector<string> board;
//게임판의 각 칸이 덮였는지를 나타낸다. 1이면 검은 칸이거나 이미 덮은 칸, 0이면 빈 칸
int covered[10][10];
//지금까지 찾은 최적해
int best;
//(y, x)를 왼쪽 위칸으로 해서 주어진 블록을 delta = 1이면 놓고, -1이면 없앤다.
//블록을 놓을 때 이미 놓인 블록이나 검은 칸과 겹치면 거짓을, 아니면 참을 반환한다.
bool set(int y, int x, const vector<pair<int, int>>& block, int delta);
//placed: 지금까지 놓은 블록의 수
void search(int placed) {
	//아직 채우지 못한 빈 칸 중 가장 윗줄 왼쪽에 있는 칸을 찾는다.
	int y = -1, x = -1;
	for (int i = 0; i < boardH; i++){
		for(int j=0; j<boardW; j++)
			if (covered[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		if (y != -1) break;
	}
	//기저 사례: 게임판의 모든 칸을 처리한 경우
	if (y == -1) {
		best = max(best, placed);
		return;
	}
	//이 칸을 덮는다.
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1))
			search(placed + 1);
		set(y, x, rotations[i], -1);
	}
	//이 칸을 덮지 않고 '막아'둔다.
	covered[y][x] = 1;
	search(placed);
	covered[y][x] = 0;
}
int solve() {
	best = 0;
	//covered 배열을 초기화한다.
	for (int i = 0; i < boardH; i++)
		for (int j = 0; j < boardW; j++)
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
	search(0);
	return best;
}

int main(void) {

}