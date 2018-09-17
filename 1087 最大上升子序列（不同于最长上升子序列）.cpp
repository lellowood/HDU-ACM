#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1081 最长递增子序列 的变形
由于求得是最大值而不是最大长度 传统O(n)算法并不适用

可以用贪心算法O(n^2) 并不是超时 

但其实是有更好的，在前项比较的时候我们只比较比现有值小的最大值，再找这个值的时候才用二分查找，

*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>

#define N 1005

int dp [N];
int num[N];

int main() {
	int n, t;
	freopen("data.txt", "r", stdin);
	while (scanf("%d", &n) != EOF && n) {
		t = -32143124;
		for (int i = 0; i < n; i++) {
			scanf("%d", &num[i]);
			dp[i] = num[i];
			for (int j = 0; j < i; j++)
				if (num[j]<num[i] && dp[j] + num[i] > dp[i])dp[i] = dp[j] + num[i];
			if (dp[i] > t)t = dp[i];
		}
		printf("%d\n",t);
	}
	return 0;
}