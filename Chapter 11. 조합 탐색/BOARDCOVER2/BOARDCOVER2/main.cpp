#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int boardH, boardW; // 게임판 정보
int covered[10][10]; // 게임판의 상태
vector<string> board;
int blockSize;
int best; //지금까지 찾은 최적해

//블록의 각 회전된 상태를 상대 좌표의 목록으로 저장해 둔다.
vector<vector<pair<int, int>>> rotations;

//2차월 배열 arr을 시계방향으로 90도 돌린 결과를 반환한다.
vector<string> rotate(const vector<string>& arr) {
	//arr.size() = 세로 길이, arr[0].size = 가로 길이
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[0].size(); j++)
			ret[j][arr.size() - i - 1] = arr[i][j];
	return ret;
}

//block의 4가지 회전 형태를 만들고 이들을 상대 좌표의 목록으로 변환한다.
void generateRotations(vector<string> block) {
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		int originY = -1, originX = -1;
		for (int i = 0; i < block.size(); i++) // block.size() = 블록의 높이
			for (int j = 0; j < block[i].size(); j++) //block[i].size() = 블록의 길이
				if (block[i][j] == '#') {
					if (originY == -1) {
						originY = i;
						originX = j;
					}
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
		// 블록을 시계 방향으로 90도 회전한다
		block = rotate(block);
	}
	// 4가지 회전 형태 중 중복이 있을 경우 이를 제거한다.
	sort(rotations.begin(), rotations.end());
	// 정렬되어있는 벡터의 시작과 끝 iterator 를 인자로 주면 모든 수들을 
	// 한번씩만 써서 정렬한 sequence 를 맨앞에 오도록 순서를 재배치 하고 
	// 그 끝 iterator 를 반환한다.
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	blockSize = rotations[0].size();
}

//(y,x)를 왼쪽 위칸으로 해서 주어진 블록을 delta=1이면 놓고, -1이면 없앤다.
//블록을 놓을 때 이미 놓인 블록인 검은 칸과 겹치면 거짓을, 아니면 참을 반환한다.
bool set(int y, int x, const vector<pair<int, int>>& block, int delta) {
	bool ok = true;
	for (int i = 0; i < block.size(); i++) {
		int cy = y + block[i].first, cx = x + block[i].second;
		if (cy < 0 || cx < 0 || cy >= boardH || cx >= boardW)
			ok = false;
		else {
			covered[cy][cx] += delta; //(y,x)를 덮지 않기로 결정한 경우에도 막아 둔다.
			if (covered[cy][cx] > 1) ok = false;
		}
	}
	return ok;
}

//placed: 지금까지 놓은 블록의 수
void search(int placed, int blanks) {
	//아직 채우지 못한 빈 칸 중 가장 왼줄 왼쪽에 있는 칸을 찾는다.
	int y = -1, x = -1;
	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++)
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

	int upperBound = blanks / blockSize + placed;
	if (upperBound <= best) return;

	//이 칸을 덮는다.
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1))
			search(placed + 1, blanks - blockSize);
		set(y, x, rotations[i], -1);
	}
	//이 칸을 덮지 않고 '막아'둔다.
	covered[y][x] = 1;
	search(placed, blanks-1);
	covered[y][x] = 0;
}

int solve() {
	best = 0;
	//covered 배열을 초기화한다.
	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++)
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
	}
	search(0, boardH*boardW);
	return best;
}