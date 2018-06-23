#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_FENCE = 20000;
int C, N;
//int maxArea;
vector<int> fences;

/*
//���� § �˰���. �־��� ���� ��Ÿ���� ���̰� ���� ��Ÿ�� ����
//������������ ���ĵǾ� ��ġ���ִ� ����, ��� ��Ÿ������ fences�ȿ�
//����Ǳ� ������ O(n^2)�� �ð����⵵�� ������. ���� �� �ð� �ȿ��� ���ư���.

//numOfFences[i] = ������ �������� ���� i������ ���� ����
int numOfFences[MAX_FENCE];


void maxSquare() {
	//������� ������ �������� ���� ��Ÿ�� ���
	vector<int> curFences;
	int fenceSize = fences.size();

	for (int i = 0; i < fenceSize; i++) {
		int curfence = fences[i];

		//���� ���� Ȯ���ϴ� ��Ÿ���� curFences�� ���� ū ��Ÿ������ �۴ٸ�
		//������ �������� ��Ÿ���� ������ ���̴�. 
		//���� Ȯ���ϴ� ��Ÿ���� curFences�� ���� ū ��Ÿ���� ���̰� ���� ��쵵
		//����ó�� ���ش�.
		while (!curFences.empty() && curFences.back() >= curfence) {
			numOfFences[curfence] = max(numOfFences[curfence], numOfFences[curFences.back()]);
				
			if (curFences.back() > curfence)
				numOfFences[curFences.back()] = 0;

			curFences.pop_back();	
		}

		curFences.push_back(curfence);
		sort(curFences.begin(), curFences.end());

		for (int j = 0; j < curFences.size(); j++) {
			numOfFences[curFences[j]]++;
			maxArea = max(maxArea, numOfFences[curFences[j]] * curFences[j]);
		}
	}
}
*/

//å�� ���� ������ �� �˰���. å�� �����ϰ� n���� ���ڸ� �������� ���� �� ����
//�κ� ������ �����, �κ� ���� ��迡 �ִ� �� ���� ��� �� �κ� ������ ���ԵǴ�
//�ϳ��� ���ڸ� �߽����� ���� ������ �Ͽ���. ���� ���, 7���� ���ڰ� �־����ٸ�
//3�� ���ڸ� �߽����� 0~3, 3~6�� �� �κй����� ���� ���ȣ���ϰ�, 3�� ���ڷκ���
//�����ϴ� ���簢�� �� ���� ū ���簢���� ã�� �� �κй����� ���Ѵ�.
//�� ����� �������� n���� ���ڸ� �� ���� �κй����� ���� �� �ߺ��Ǵ� ��� ���ڷ� ����
//���ȣ���� �ʺ� �о����ٴ� �Ͱ�, �� ���� ���ڰ� ������ �� �̸� �������� ������ ����
//����ó���� ���־�� �ϱ� ������ �ڵ尡 ������ٴ� ������ �ִ�. 

int mySolve(int left, int right) {
	int mid = (left + right) / 2;
	if (left == right)
		return fences[left];
	else if (right - left == 1)
		return max(max(fences[left], fences[right]), min(fences[left], fences[right]) * 2);

	int ret = max(mySolve(left, mid), mySolve(mid, right));
	int lo = mid, hi = mid;
	int length = 1, height = fences[mid];
	ret = max(ret, fences[mid]);

	while (left < lo || right > hi) {
		if (hi < right && (lo == left || fences[lo - 1] < fences[hi + 1])) {
			height = min(height, fences[++hi]);
			ret = max(ret, height * ++length);
		}
		else {
			height = min(height, fences[--lo]);
			ret = max(ret, height * ++length);
		}
	}
	return ret;
}

//å�� �˰���. n���� ���ڸ� �������� ���� �� ���� �κ� ������ �����. �� ��,
//1. ���� ū ���簢���� ���� �κ� ���������� �߶� �� �ִ� ���
//2. ���� ū ���簢���� ������ �κ� ���������� �߶� �� �ִ� ���
//3. ���� ū ���簢���� ���� �κ� ������ ������ �κ� ������ �����ִ� ���
//�߿� �츮�� ã������ �ִ� ���簢���� �����Ѵ�.
//���� ���� �������� ������ �ذ��غ��� ���� �� ����� ����������, �߰��� �����ϴ�
//���� �ϳ��� �������� ���ʰ� �������� ������ �� �߰��� �����ϴ� ���ڸ� ���� �κй�������
//���ܽ�Ű�� ���ȣ�� �� ��ġ�� �κ��� �����ϰ�, ���� �κй����� ��� ���Խ�Ű�� ���ȣ����
//�ʺ� �о����ٴ� ������ ����� �����߾���. (�߰� ���ڸ� ���� �κй������� ���Խ�Ű��
//���� �κ� ������ �����ִ� ���簢���� ��� ã�� �� ����)
//��, �κ� ���� ��迡 �ִ� �� ���ڸ� �߽����� ���� ������ �ϸ� �ȴٴ� ���̵� �����س��� ���ߴ�.

int solve(int left, int right) {
	//���� ���: ���ڰ� �ϳ��ۿ� ���� ���
	if (left == right)	return fences[left];
	//[left, mid], [mid+1, right]�� �� �������� ������ �����Ѵ�.
	int mid = (left + right) / 2;
	//������ ������ ��������
	int ret = max(solve(left, mid), solve(mid + 1, right));
	//�κ� ���� 3: �� �κп� ��� ��ġ�� �簢�� �� ���� ū ���� ã�´�.
	int lo = mid, hi = mid + 1;
	int height = min(fences[lo], fences[hi]);
	//[mid, mid+1]�� �����ϴ� �ʺ� 2�� �簢���� ����Ѵ�.
	ret = max(ret, height * 2);

	//�簢���� �Է� ��ü�� ���� ������ Ȯ���� ������.
	while (left < lo || hi < right) {
		//�׻� ���̰� �� ���� ������ Ȯ���Ѵ�.
		if (hi < right && (lo == left || fences[hi + 1] > fences[lo - 1]))
			height = min(height, fences[++hi]);
		else
			height = min(height, fences[--lo]);
		//Ȯ���� �� �簢���� ����
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}


int main(void) {
	cin >> C;
	for (int test = 0; test < C; test++) {
		int input;
		cin >> N;
		//memset(numOfFences, 0, sizeof(numOfFences));
		//maxArea = 0;
		for (int i = 0; i < N; i++) {
			cin >> input;
			fences.push_back(input);
		}
		//cout << mySolve(0, fences.size()-1) << endl;
		//maxSquare();
		//cout << maxArea <<  endl;
		fences.clear();
	}
}