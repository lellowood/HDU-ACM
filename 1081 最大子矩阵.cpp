#include "stdafx.h"

// ConsoleApplication1.cpp: �������̨Ӧ�ó������ڵ㡣
//

/*
1081 ����Ӿ��� �������������

ͬ����˼�룬�ȶԶ�ά������һάѹ�����ٶ�һά���������������
����Ĺؼ�������һάѹ������C��2��n����ѡ�� ���Ӷ��� O(n^2)
�ټ���һά�����и��Ӷ���O(n^3)

����Ԥ����ķ�ʽ�������ǰiά֮�ͣ���sum[i][j] = map[i][1]+...map[i][j];
map:
a11 a12 a13 ... a1n
a21 ............a2n
...
ai1 ai2.........ain
-------------------
sum[i][j] Ϊ����ѹ����i�дӵ�һ�е���j��֮��

����������p��q֮��ľ���ֵ��sum[i][q] - sum[i][p]

���������Ӷ�ΪO(n^3)

*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>

#define N 1005

int map[N][N];

int sum[N][N] = { 0 };


int main() {
	int n, t;
	freopen("data.txt", "r", stdin);
	while (scanf("%d", &n) != EOF) {
		t = -32452345;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &map[i][j]);
				sum[i + 1][j] = sum[i][j] + map[i][j];
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j <= n; j++) {
				int temp = sum[j][0] - sum[i][0];
				if (temp > t)t = temp;
				for (int k = 1; k < n; k++) {
					if (temp > 0)temp += sum[j][k] - sum[i][k];
					else if (temp < sum[j][k] - sum[i][k]) temp = sum[j][k] - sum[i][k];
					if (temp > t)t = temp;
				}
			}
		}
		printf("%d\n", t);
	}
	return 0;
}