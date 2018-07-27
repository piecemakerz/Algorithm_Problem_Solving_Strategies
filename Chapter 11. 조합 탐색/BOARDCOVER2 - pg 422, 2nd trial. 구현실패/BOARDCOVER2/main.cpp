#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

int T, R, C;
//����� ũ��
int blockSize;
//����� ȸ���� ���¸� ����ϰ� �����ǥ�� ������� ��ȯ�ϱ�
vector<vector<pair<int, int>>> rotations;

//2���� �迭 arr�� �ð�������� 90�� ���� ����� ��ȯ�Ѵ�.
vector<string> rotate(const vector<string>& arr) {
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[0].size(); j++)
			ret[j][arr.size() - i - 1] = arr[i][j];
	return ret;
}
//block�� �� ���� ȸ�� ���¸� ����� �̵��� ��� ��ǥ�� ������� ��ȯ�Ѵ�.
void generateRotations(vector<string> block) {
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		int originY = -1, originX = -1;
		for(int i=0; i<block.size(); i++)
			for(int j=0; j<block[i].size(); j++)
				if (block[i][j] == '#') {
					if (originY == -1) {
						//���� ���� �� ���ʿ� �ִ� ĭ�� ������ �ȴ�.
						originY = i;
						originX = j;
					}
					//�� ĭ�� ��ġ�� �������κ����� �����ǥ�� ǥ���Ѵ�.
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
		//����� �ð� �������� 90�� ȸ���Ѵ�.
		block = rotate(block);
	}
	//�� ���� ȭ�� ���� �� �ߺ��� ���� ��� �̸� �����Ѵ�.
	sort(rotations.begin(), rotations.end());
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	//����� �� ĭ ¥������ ������ �д�.
	blockSize = rotations[0].size();
}

//������ ���� 2 ������ �ذ��ϴ� ���� Ž�� �˰���
//�������� ����
int boardH, boardW;
vector<string> board;
//�������� �� ĭ�� ���������� ��Ÿ����. 1�̸� ���� ĭ�̰ų� �̹� ���� ĭ, 0�̸� �� ĭ
int covered[10][10];
//���ݱ��� ã�� ������
int best;
//(y, x)�� ���� ��ĭ���� �ؼ� �־��� ����� delta = 1�̸� ����, -1�̸� ���ش�.
//����� ���� �� �̹� ���� ����̳� ���� ĭ�� ��ġ�� ������, �ƴϸ� ���� ��ȯ�Ѵ�.
bool set(int y, int x, const vector<pair<int, int>>& block, int delta) {
	bool ok = true;
	int placex, placey;
	for (int i = 0; i < block.size(); i++) {
		placex = x + block[i].second, placey = y + block[i].first;
		if (placex < 0 || placex >= boardW || placey < 0 || placey >= boardH) ok = false;
		else {
			covered[placey][placex] += delta;
			if (covered[placey][placex] > 1) ok = false;
		}
	}
	return ok;
}
int simpleHeuristic(int whiteSpace) {
	return whiteSpace / blockSize;
}
//placed: ���ݱ��� ���� ����� ��
void search(int placed, int whiteSpace) {
	if (simpleHeuristic(whiteSpace) + placed <= best)
		return;
	//���� ä���� ���� �� ĭ �� ���� ���� ���ʿ� �ִ� ĭ�� ã�´�.
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
	//���� ���: �������� ��� ĭ�� ó���� ���
	if (y == -1) {
		best = max(best, placed);
		return;
	}
	//�� ĭ�� ���´�.
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1))
			search(placed + 1, whiteSpace - blockSize);
		set(y, x, rotations[i], -1);
	}
	//�� ĭ�� ���� �ʰ� '����'�д�.
	covered[y][x] = 1;
	search(placed, whiteSpace - 1);
	covered[y][x] = 0;
}
int solve() {
	int whiteSpace = 0;
	best = 0;
	//covered �迭�� �ʱ�ȭ�Ѵ�.
	for (int i = 0; i < boardH; i++)
		for (int j = 0; j < boardW; j++) {
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
			if (!covered[i][j]) whiteSpace++;
		}
	search(0, whiteSpace);
	return best;
}

int main(void) {
	cin >> T;
	for (int test = 0; test < T; test++) {
		memset(covered, 0, sizeof(covered));
		vector<string> block;
		string input;
		cin >> boardH >> boardW >> R >> C;
		for (int i = 0; i < boardH; i++) {
			cin >> input;
			board.push_back(input);
		}
		for (int i = 0; i < R; i++) {
			cin >> input;
			block.push_back(input);
		}
		generateRotations(block);
		cout << solve() << endl;
		rotations.clear();
		board.clear();
	}
}