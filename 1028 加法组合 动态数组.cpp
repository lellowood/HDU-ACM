#include "stdafx.h"

/*
1028 数n的加法组合方式

最开始拿到题时我是毫无办法的！瞟了一眼是背包问题
定义：
dp[i][j]:数i分解为以j为最大成员的组合方式的数量 i>=j
公式
dp[i][j] = ∑dp[i-j][k] k <= min(j, i-j)
一个dp矩阵如下
1 1 1 1 1
  1 1 2 2
    1 1 2
	  1 1
	    1
我们要求的结果就等于一列的累加和

观察公式可以发现有很多累加操作是重复的，因此定义一个新的矩阵
定义
dps[i][j]:dp矩阵第i列到第j个元素的累加值 即 dps[i][j] = ∑dp[i][k] 0<k<=j
公式
dps[i][j] = dps[i][j-1] + dps[i-j][j]

对于n，它的输出就是dps[n][n]
*/

#include "stdio.h"
#include "string.h"
#define _Inf -0x7fffffff
#define MAX(a,b) a>b?a:b

#define N 121

int dps[N][N] = { 0 };

int n, m;

int main() {
	//memset(dps, 1, sizeof(dps));
	//for (int i = 1; i < N; i++)
	//	dps[1][i] = dps[i][1] = 1;
	for (int i = 0; i < N; i++)
		dps[0][i] = 1;
	for (int i = 1; i < N; i++) {
		for (int j = 1; j <= i; j++)
			dps[i][j] = dps[i][j - 1] + dps[i - j][j>i-j?i-j:j];
		//for (int j = i+1; j < N; j++)
		//	dps[i][j] = dps[i][j - 1];
	}
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d", &n) != EOF) {
		printf("%d\n", dps[n][n]);
	}
	return 0;
}