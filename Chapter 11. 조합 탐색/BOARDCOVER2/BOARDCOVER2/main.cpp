#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int boardH, boardW; // ������ ����
int covered[10][10]; // �������� ����
vector<string> board;
int blockSize;
int best; //���ݱ��� ã�� ������

//����� �� ȸ���� ���¸� ��� ��ǥ�� ������� ������ �д�.
vector<vector<pair<int, int>>> rotations;

//2���� �迭 arr�� �ð�������� 90�� ���� ����� ��ȯ�Ѵ�.
vector<string> rotate(const vector<string>& arr) {
	//arr.size() = ���� ����, arr[0].size = ���� ����
	vector<string> ret(arr[0].size(), string(arr.size(), ' '));
	for (int i = 0; i < arr.size(); i++)
		for (int j = 0; j < arr[0].size(); j++)
			ret[j][arr.size() - i - 1] = arr[i][j];
	return ret;
}

//block�� 4���� ȸ�� ���¸� ����� �̵��� ��� ��ǥ�� ������� ��ȯ�Ѵ�.
void generateRotations(vector<string> block) {
	rotations.clear();
	rotations.resize(4);
	for (int rot = 0; rot < 4; rot++) {
		int originY = -1, originX = -1;
		for (int i = 0; i < block.size(); i++) // block.size() = ����� ����
			for (int j = 0; j < block[i].size(); j++) //block[i].size() = ����� ����
				if (block[i][j] == '#') {
					if (originY == -1) {
						originY = i;
						originX = j;
					}
					rotations[rot].push_back(make_pair(i - originY, j - originX));
				}
		// ����� �ð� �������� 90�� ȸ���Ѵ�
		block = rotate(block);
	}
	// 4���� ȸ�� ���� �� �ߺ��� ���� ��� �̸� �����Ѵ�.
	sort(rotations.begin(), rotations.end());
	// ���ĵǾ��ִ� ������ ���۰� �� iterator �� ���ڷ� �ָ� ��� ������ 
	// �ѹ����� �Ἥ ������ sequence �� �Ǿտ� ������ ������ ���ġ �ϰ� 
	// �� �� iterator �� ��ȯ�Ѵ�.
	rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
	blockSize = rotations[0].size();
}

//(y,x)�� ���� ��ĭ���� �ؼ� �־��� ����� delta=1�̸� ����, -1�̸� ���ش�.
//����� ���� �� �̹� ���� ����� ���� ĭ�� ��ġ�� ������, �ƴϸ� ���� ��ȯ�Ѵ�.
bool set(int y, int x, const vector<pair<int, int>>& block, int delta) {
	bool ok = true;
	for (int i = 0; i < block.size(); i++) {
		int cy = y + block[i].first, cx = x + block[i].second;
		if (cy < 0 || cx < 0 || cy >= boardH || cx >= boardW)
			ok = false;
		else {
			covered[cy][cx] += delta; //(y,x)�� ���� �ʱ�� ������ ��쿡�� ���� �д�.
			if (covered[cy][cx] > 1) ok = false;
		}
	}
	return ok;
}

//placed: ���ݱ��� ���� ����� ��
void search(int placed, int blanks) {
	//���� ä���� ���� �� ĭ �� ���� ���� ���ʿ� �ִ� ĭ�� ã�´�.
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
	//���� ���: �������� ��� ĭ�� ó���� ���
	if (y == -1) {
		best = max(best, placed);
		return;
	}

	int upperBound = blanks / blockSize + placed;
	if (upperBound <= best) return;

	//�� ĭ�� ���´�.
	for (int i = 0; i < rotations.size(); i++) {
		if (set(y, x, rotations[i], 1))
			search(placed + 1, blanks - blockSize);
		set(y, x, rotations[i], -1);
	}
	//�� ĭ�� ���� �ʰ� '����'�д�.
	covered[y][x] = 1;
	search(placed, blanks-1);
	covered[y][x] = 0;
}

int solve() {
	best = 0;
	//covered �迭�� �ʱ�ȭ�Ѵ�.
	for (int i = 0; i < boardH; i++) {
		for (int j = 0; j < boardW; j++)
			covered[i][j] = (board[i][j] == '#' ? 1 : 0);
	}
	search(0, boardH*boardW);
	return best;
}