#include "stdafx.h"

#include "stdio.h"
#include "string.h"
#include <algorithm>
/*
1025 最大公共子序列的变换
定义
dp[i][j]: 上面i到下面j能得到的最多的路径
公式
dp[i][j] = dp[i-1][j-1]+1 if(i和j能是对应的)
		 = max(dp[i-1][j], dp[i][j-1]);

结果超时了！！！
这么做的时间复杂度是n^2
**********************************************************
定义
dp[i][j]:以i和j结尾的路径最多的数量
公式
dp[i][j] = max(dp[p][r])+1 if(i和j能对应) p<i r<j
		 = 0
这样定义的方式是只需要考虑已经出现的连接
最坏的时间复杂度是n^2/2 最好的时间复杂度是 n
在编程的时候，遍历已有的连接就行
**********************************************************
在后续编程发现改进的问题，对这个题目重新定义
重新定义
dp[i]: 以i对应的路径为最后路径的组合
dp[i] = 
*/
#define _Inf -0x7fffffff
#define MAX(a,b) a>b?a:b

#define N 500005
int n;
//序列表
int str [2][N];
int  dp	[N] = { 0 };

//int main() {
//	int r, p, left, temp;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d", &n) != EOF&&n > 0) {
//		for (int i = 0; i < n; i++) {
//			scanf("%d %d", &p,&r);
//			str[0][p]= str[1][r] = i;
//			dp[i + 1] = 0;
//		}
//		for (int i = 1; i <= n; i++) {
//			left = 0;
//			for (int j = 1; j <= n; j++) {
//				//if (str[0][i] == str[1][j])
//				//	dp[i][j] = dp[i - 1][j - 1] + 1;
//				//else
//				//	dp[i][j] = MAX(dp[i - 1][j], dp[i][j - 1]);
//				if (str[0][i] == str[1][j])
//					temp =left + 1;
//				else
//					temp = MAX(dp[j], dp[j - 1]);
//				left = dp[j];
//				dp[j] = temp;
//			}
//		}
//		printf("%d\n", dp[n]);
//	}
//	return 0;
//}

//空间复杂度 3n
//时间复杂度 n^2/2
//************************************************************
//结果超时！！！！！
//int main() {
//	int max, temp, time = 1;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d", &n) != EOF&&n > 0) {
//		for (int i = 1; i <= n; i++) {
//			scanf("%d %d", str[0] + i, str[1] + i);
//		}
//		max = 0;
//		for (int i = 1; i <= n; i++) {
//			temp = 0;
//			int j;
//			//这么编程会有bug的！！
//			// for (j = i - 1; j > 0 && ((str[0][i] - str[0][j])*(str[1][i] - str[1][j])) < 0; j--); 
//			for (j = i - 1; j > 0; j--) {
//				//if (((str[0][i] - str[0][j])*(str[1][i] - str[1][j])) > 0 && dp[j] > temp)temp = dp[j];这是有bug的
//			}
//			dp[i] = temp + 1;
//			if (dp[i] > max)
//				max = dp[i];
//		}
//		if(max>1)
//			printf("Case %d:\nMy king, at most %d roads can be built.\n\n", time++, max);
//		else
//			printf("Case %d:\nMy king, at most %d road can be built.\n\n", time++, max);
//	}
//	return 0;
//}

//比上一个节约空间和时间
//利用一个数组保存上一个的记录位置避免重复比较
//空间复杂度 3n
//时间复杂度 最坏 n^2/2 最好 n
//************************************************************
//错误！我有点找不到哪儿错了
//
//好吧这种方式确实有逻辑上的错误！！
//************************************************************
//
//int main() {
//	int p, r, max, temp, time = 1;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d", &n) != EOF&&n > 0) {
//		for (int i = 1; i <= n; i++) {
//			scanf("%d %d", &p, &r);
//			str[0][p] = r;
//		}
//		max = 0;
//		for (int i = 1; i <= n; i++) {
//			p = r = temp = 0;
//			for (int j = i - 1; j > r; j--) {
//				if (str[0][i] > str[0][j] && dp[j] > temp) {
//					temp = dp[j];
//					r = str[1][j];
//					p = j;
//				}
//			}
//			dp[i] = temp + 1;
//			str[1][i] = p;
//			if (dp[i] > max)
//				max = dp[i];
//		}
//		if (max>1)
//			printf("Case %d:\nMy king, at most %d roads can be built.\n\n", time++, max);
//		else
//			printf("Case %d:\nMy king, at most %d road can be built.\n\n", time++, max);
//	}
//	return 0;
//}

//在上一个方法上改进的逻辑错误
//空间复杂度 3n
//时间复杂度 最坏 n^2/2 最好 n
//结果还是超时！！
////看来必须是nlogn的复杂度才能通过
//int main() {
//	int p, r, max, temp, time = 1;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d", &n) != EOF&&n > 0) {
//		for (int i = 1; i <= n; i++) {
//			scanf("%d %d", &p, &r);
//			str[0][p] = r;
//		}
//		max = 0;
//		for (int i = 1; i <= n; i++) {
//			p = i;
//			temp = 0;
//			for (int j = i - 1; j > 0; j--) {
//				if (str[0][i] > str[0][j] && dp[j] > temp) {
//					temp = dp[j];
//					j = str[1][j];
//					p = j;
//				}
//			}
//			dp[i] = temp + 1;
//			str[1][i] = p;
//			if (dp[i] > max)
//				max = dp[i];
//		}
//		if (max>1)
//			printf("Case %d:\nMy king, at most %d roads can be built.\n\n", time++, max);
//		else
//			printf("Case %d:\nMy king, at most %d road can be built.\n\n", time++, max);
//	}
//	return 0;
//}

//还是同样的思路
//遍历一遍1-n，找到以<n路径结尾的最大的路径数量+1
//在找以n路径结尾的最大路径的时候，用一个数组a[i]记录以i为最大路径数量的最小的对应的富城市编号值
//如果要使用二分查找，一个重要的保证是证明a[i]是递增的数组
//证明：假设a数组中存在i<j使得a[i]>a[j]
//因为在计算数组a的时候是从逐渐递增的，a[i]记录的是以i为最大路径数量的最小城市编号
//假设a[i]城市先出现，那么a[j]出现的时候一定是排在i前面（因为如果a[j]<a[i]那么会排在i后面）i>j所以矛盾
//假设a[j]城市先出现,那么a[i]出现的时候因为比a[j]大，所以起码排的位置在j后面，所以i>j矛盾
//这样在每次寻找以<n路径结尾的最大路径的时候，只需要
//去二分查找这个数组a，找到存储比n小的某个位置存储上就行

//还是超时！！！！！！——原来是有一个死循环，在197行有标注
//还是错误！！！！！！——原来是边界错误！！！！

void binary_search(int value, int start, int end) {
	while (start < end) {
		int half = (start + end) / 2;
		//if (dp[half] == value)return half;
		if (dp[half] > value) end = half;
		//else start = half;		///这样写会陷入死循环，比如dp[half]<value start = half;
		else start = half + 1;
	}
	dp[end] = value;
	//return start;
};

int main() {
	int p, r, max, time = 1;
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d", &n) != EOF&&n > 0) {
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &p, &r);
			str[0][p] = r;
		}
		max = 0;
		for (int i = 1; i <= n; i++) {
			if (str[0][i] > dp[max])//如果新来的比之前记录的最大值的值还大，那么记录新的值
				dp[++max] = str[0][i];	//其实这只是二分查找的一种特例，最后面的一个
			else {
				binary_search(str[0][i], 1, max);
				//dp[binary_search(str[0][i], 1, max)] = str[0][i];	//更新
			}
		}
		if (max>1)
			printf("Case %d:\nMy king, at most %d roads can be built.\n\n", time++, max);
		else
			printf("Case %d:\nMy king, at most %d road can be built.\n\n", time++, max);
	}
	return 0;
}

//void binary_search(int value, int end) {
//	int start = 0;
//	while (start < end) {
//		int half = (start + end) / 2;
//		//if (dp[half] == value)return half;
//		if (dp[half] > value) end = half - 1;
//		else start = half;
//	}
//	dp[start] = value;
//	//return start;
//};
//
//int main() {
//	int p, r, max, time = 1;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d", &n) != EOF&&n > 0) {
//		for (int i = 1; i <= n; i++) {
//			scanf("%d %d", &p, &r);
//			str[0][p] = r;
//		}
//		max = 0;
//		for (int i = 1; i <= n; i++) {
//			if (str[0][i] > dp[max])//如果新来的比之前记录的最大值的值还大，那么记录新的值
//				dp[++max] = str[0][i];	//其实这只是二分查找的一种特例，最后面的一个
//			else {
//				binary_search(str[0][i], 1, max);
//				//dp[binary_search(str[0][i], 1, max)] = str[0][i];	//更新
//			}
//		}
//		if (max>1)
//			printf("Case %d:\nMy king, at most %d roads can be built.\n\n", time++, max);
//		else
//			printf("Case %d:\nMy king, at most %d road can be built.\n\n", time++, max);
//	}
//	return 0;
//}
//
////别人的代码为了调试用的
//void fun(int n, int num)
//{
//	int i = 0, j = n - 1;
//	int mid, find = 0;
//	while (i <= j)
//	{
//		mid = (i + j) / 2;
//		if (dp[mid] == num) { find = 1; break; }
//		else if (dp[mid]>num)  j = mid - 1;
//		else i = mid + 1;
//	}
//	if (!find)  dp[i] = num;
//}
//int main() {
//	int p, r, max, temp, time = 1;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d", &n) != EOF&&n > 0) {
//		for (int i = 1; i <= n; i++) {
//			scanf("%d %d", &p, &r);
//			str[0][p-1] = r;
//		}
//		dp[0] = str[0][0];
//		temp = 1;
//		for (int i = 1; i<n; i++)
//		{
//			if (str[0][i]>dp[temp - 1])  dp[temp++] = str[0][i];
//			else if (str[0][i]<dp[temp - 1])  fun(temp, str[0][i]);
//		}
//		//printf("Case %d:\n", ++t);
//		//if (len == 1) printf("My king, at most %d road can be built.\n\n", len);
//		//else  printf("My king, at most %d roads can be built.\n\n", len);
//
//		if (temp>1)
//			printf("Case %d:\nMy king, at most %d roads can be built.\n\n", time++, temp);
//		else
//			printf("Case %d:\nMy king, at most %d road can be built.\n\n", time++, temp);
//	}
//	return 0;
//}