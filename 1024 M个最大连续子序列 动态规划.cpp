#include "stdafx.h"

#include "stdio.h"
#include "string.h"
#include <algorithm>
/*
1024 M段最大连续子序列之和
看到这里还是去查了一下最大连续子序列的知识，我以前关于动态规划的知识让我过拟合了，原来还可以这样动态规划
动态规划最重要的是状态转移公式，是状态的定义

定义
dp[i][j]: 序列前i个单元分为j段子序列的最大值
公式
dp[i][j] = max( dp[i-k][j-1] + 最大连续子序列(i-k+1, i))  0 < k <= i-j+1

对于矩阵dp，每一列j只和之前j-1列有关，所以可以进行压缩
***********************************************************************************************************

好吧！！！！！！！超时——其实我在编程时候就有预感，因为很多操作是重复的
只有看了别人的解答才知道，打死我也想不出来，其实下午我还看了最大连续子序列，还是不能联系

定义
dp[i][j]: 序列前i个单元分为j段子序列，且最后一段以str[i]结尾（定义和最大连续子序列很相似）
公式
dp[i][j] = max (dp[i-1][j]+str[i], max(dp[i-k][j-1])+str[i]) 0 < k <= i-j+1
前一项表示str[i]加到以str[i-1]结尾的第j段
后一项表示以str[i]作为第j段的开头
***********************************************************************************************************
但是我们的好像还是可以改进
公式
dp[i][j] = max( dp[i-1][j-1] + str[i], dp[i][j-1]))  0 < k <= i-j+1

好吧我放弃了
***********************************************************************************************************
提交一次错误！
因为没有注意到边界情况
***********************************************************************************************************
在一次错误！
好几次对比更改才发现问题：
1）char保存的数据通不过，最少是short
2）边界错误，最开始设置的是 i<=N-M+j 后来发现 i<=N-M+j+1 才行 原因吗我也不知道
*/
#define _Inf -0x7fffffff
#define MAX(a,b) a>b?a:b
int M, N;
//序列表
short str [1000005];
int  dp	 [1000005] = { _Inf };
int	 temp[1000005] = { _Inf };

//int main() {
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d%d", &M, &N) != EOF&&N > 0) {
//		for (int i = 0; i < N; i++) {
//			scanf("%d", str + i);
//			dp[i + 1] = str[i];
//			temp[i + 1] = MAX(temp[i], dp[i]);
//		}
//		temp[N+1] = MAX(temp[N], dp[N]);
//		if (M != 0 && M <= N) {
//			for (int j = 2; j <= M; j++) {
//				for (int i = j; i <= N - M + j; i++) {
//					dp[i] = (MAX(dp[i - 1], temp[i])) + str[i - 1];
//					temp[i] = MAX(temp[i - 1], dp[i - 1]);
//				}
//				temp[N - M + j + 1] = MAX(temp[N - M + j], dp[N - M + j]);			
//			}
//			printf("%d\n", temp[N+1]);
//		}
//		else
//			printf("0\n");
//	}
//	return 0;
//}

int main() {
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d%d", &M, &N) != EOF&&N > 0) {
		for (int i = 0; i < N; i++)
			scanf("%d", str + i);
		if (M != 0 && M <= N) {
			memset(temp, 0, sizeof(temp));
			for (int j = 1; j <= M; j++) {
				temp[j - 1] = dp[j-1] = _Inf;
				for (int i = j;i<=N-M+j+1 &&i <= N; i++) {
					dp[i] = (MAX(dp[i - 1], temp[i])) + str[i - 1];
					temp[i] = MAX(temp[i - 1], dp[i - 1]);
				}
				temp[N + 1] = MAX(temp[N ], dp[N]);
			}
			printf("%d\n", temp[N + 1]);
		}
		else
			printf("0\n");
	}
	return 0;
}

//int main() {
//	int mmax;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d%d", &M, &N) != EOF&&N > 0) {
//		for (int i = 0; i < N; i++) {
//			scanf("%d", str + i);
//		}
//		if (M != 0 && M <= N) {
//			temp[N + 1] = MAX(temp[N], dp[N]);		
//			memset(dp, 0, sizeof(dp));
//			memset(temp, 0, sizeof(temp));
//			for (int i = 1; i <= M; i++)//分成几组  
//			{
//				mmax = _Inf;
//				for (int j = i; j <= N; j++)//j个数分成i组，至少要有i个数  
//				{
//					dp[j] = MAX(dp[j - 1] + str[j-1], temp[j - 1] + str[j-1]);
//					temp[j - 1] = mmax;
//					mmax = MAX(mmax, dp[j]);
//				}
//			}
//			printf("%d\n", mmax);
//		}
//		else
//			printf("0\n");
//	}
//	return 0;
//}