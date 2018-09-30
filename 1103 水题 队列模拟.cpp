#include "stdafx.h"

// ConsoleApplication1.cpp: �������̨Ӧ�ó������ڵ㡣
//

/*
1103 ��ˮ��ˮ���� �����һ��ǻ���һ��Сʱ��������̫����
�ܾ�û��� ˼ά��ʶ�Ѿ����ˣ������쳣��飬�ֻ���������
*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define SUB(x,y) (x>y?(x-y):(y-x))
#define N 30
#define Pi2 6.28318530717958647692
#define Pi 3.14159265358979323846

int num[3];
queue<int> list[3];

int main() {
	char ch = 0;
	int hh, mm, ss, nn, n;
	int count;
	freopen("data.txt", "r",stdin);
	//�ʼ����������д�� &num,&num+1,&num+2, ����ڴ��������list��������ʹ��
	while (scanf("%d %d %d\n", num, num+1, num+2)!=EOF&&(num[0]||num[1]||num[2])) {
		while (!list[0].empty())list[0].pop();
		while (!list[1].empty())list[1].pop();
		while (!list[2].empty())list[2].pop();
		ch = 0;
		count = 0;
		ch = getchar();
		while (ch != '#') {
			hh = 0;
			while (ch != ':') {
				hh = hh * 10 + ch - '0';
				ch = getchar();
			}
			scanf("%d %d\n", &mm, &n);
			ss = hh * 60 + mm;
			nn = (n - 1) / 2;
			if (list[nn].size() < num[nn]) {
				list[nn].push(ss);
				count += n;
			}
			else if (list[nn].size() > 0 && list[nn].front() <= ss) {
				list[nn].push(MAX(ss, N + list[nn].front()));
				list[nn].pop();
				count += n;
			}
			ch = getchar();
		}
		printf("%d\n", count);
	}
	return 0;
}