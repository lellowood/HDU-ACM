#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1081 最大子矩阵 类似最大子序列

同样的思想，先对二维矩阵求一维压缩，再对一维数组求最大子序列
问题的关键在于求一维压缩，有C（2，n）种选择 复杂度是 O(n^2)
再加上一维子序列复杂度是O(n^3)

才用预处理的方式求矩阵在前i维之和，即sum[i][j] = map[i][1]+...map[i][j];
map:
a11 a12 a13 ... a1n
a21 ............a2n
...
ai1 ai2.........ain
-------------------
sum[i][j] 为横向压缩第i行从第一列到第j列之和

则任意两列p、q之间的矩阵值是sum[i][q] - sum[i][p]

这样处理复杂度为O(n^3)

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