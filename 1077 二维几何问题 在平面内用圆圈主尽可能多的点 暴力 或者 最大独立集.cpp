#include "stdafx.h"

/*
1077 抓鱼 要求用一个半径1的圆圈套住尽可能多的点，分布范围【0，10】，点数<=300

一开始我的思路是求概率密度函数，将有最大概率密度的点作为圆圈中心
具体是以每个点为圆心，1为半径画圆，圆圈内的区域标记+1，最后有最大标记的的区域内的标记值就是能得到的最大结果
但是有一个问题，如何对区域进行标记，一个方式是进行网格划分，如果网格的规格足够小就能保证正确性
但是，这和遍历所有圆心没有什么差别

另一个思路是：假设我们能抓住这样一群点，这群点在一个圆内，那么这些点满足的条件是这群点两两之间距离小于2（直径）
所以我们需要找的就是这样一个点集合，集合中任意两个点距离小于2，这也是这道题讨论中说的最大独立集
这也是比较合理的方式，因为点数数量有限，而遍历可行解是太大
设定：两点之间有关系，如果两点之间距离大于2，问题变成找到对于这个关系的最大独立集
方法：
暴力搜索：二叉树，对当前节点进不进入集合进行判定

超时了！！！！！！！！！！！！！
*************************************************************************************************
遍历的时候加入剪枝

依然超时！！！！！！！！！！！！

这种暴力方式的复杂度是2^n，即使剪枝复杂度还是很高

另一种枚举中心点的方式复杂度控制在多项式复杂度内
主要思想是设定极限情况：某两个点在目标圆的边缘上，这样找到的圆就是极限情况，其他的不在边缘的情况都可以用这个圆去包括
按照这种设定有思路
1、对两两点求所在圆的圆心（并不是两点中点），对剩下的点求到圆心的距离判断是否在这个圆内，复杂度 n^3
2、对两两点求所在圆，对剩下的点求以其为圆心的圆在圆上的两个交点，两点之间是相交弧，如果两段相交弧有公共区域，那么这两段弧对应的点就可以被一个圆包围

采用第一种方式，一顿百度抄袭终于过了

哇，又看到一种方式：模拟退火
******************************************************************************************************************
*/


//#include <stdio.h> 
//
//#define N 305
//#define L 10.0
//#define EXP 0.0001
//
//int map[N][N];		//关系映射矩阵
//int sorts[N];		//节点关系多少的排序，和link联合应用
//int link[N][N];		//邻接表
//float points[N][2];	//节点位置
//
//int nowpoints[N];
//int nownum;
//int n;
//
//int max;
//
//void sortpoints(int left = 1, int right = n) {
//	if (left >= right)return;
//	int temp = sorts[left];//关系映射的多少
//	int i = left, j = right;
//	while (i < j) {
//		while (i < j&&map[sorts[j]][0] <= map[temp][0])--j;
//		if (j > i)sorts[i] = sorts[j];
//		while (i < j&&map[sorts[i]][0] >= map[temp][0])++i;
//		if (i < j)sorts[j] = sorts[i];
//	}
//	sorts[i] = temp;
//	sortpoints(left, i - 1);
//	sortpoints(i + 1, right);
//};
//
//void dfs(int node) {
//	if (nownum > max)max = nownum;
//	int flag = 1;
//	for (int i = 0; i < nownum && flag; ++i) {
//		if (map[nowpoints[i]][sorts[node]] != 1)
//			flag = 0;
//	}
//	if (flag) {
//		nowpoints[nownum++] = sorts[node];
//		dfs(node + 1);
//		nownum--;
//	}
//	if (node < n && max - nownum <= map[sorts[node] + 1][0])
//		dfs(node + 1);
//};
//
//int main()
//{
//	int t;
//	freopen("data.txt", "r", stdin);// 
//	scanf("%d", &t);
//	while (t--) {
//		scanf("%d", &n);
//		for (int i = 1; i <= n; ++i) {
//			scanf("%f %f", points[i], points[i]+1);
//			map[i][0] = 0;
//			sorts[i] = i;
//			for (int j = 1; j < i; j++) {
//				map[i][j] = map[j][i] = 0;
//				if ((points[i][0] - points[j][0])*(points[i][0] - points[j][0]) + (points[i][1] - points[j][1])*(points[i][1] - points[j][1]) - 4 < EXP) {
//					map[i][0]++;
//					map[j][0]++;
//					map[i][j] = map[j][i] = 1;
//				}
//			}
//		}
//		sortpoints();
//		max = 1;
//		nownum = 0;
//		dfs(1);
//		printf("%d\n", max);
//	}
//	return 0;
//}


//#include <stdio.h> 
//
//#define N 305
//#define L 10.0
//#define EXP1 10000
//#define EXP2 20000
//#define EXP3 400000000
//#define SUB(x,y) x>y?x-y:y-x
//
//int map[N][N];		//关系映射矩阵
//int sorts[N];		//节点关系多少的排序，和link联合应用
//int link[N][N];		//邻接表
//int points[N][2];	//节点位置
//
//
//int nownum;
//int n;
//
//int max;
//
//void sortpoints(int left = 1, int right = n) {
//	if (left >= right)return;
//	int temp = sorts[left];//关系映射的多少
//	int i = left, j = right;
//	while (i < j) {
//		while (i < j&&map[sorts[j]][0] <= map[temp][0])--j;
//		if (j > i)sorts[i] = sorts[j];
//		while (i < j&&map[sorts[i]][0] >= map[temp][0])++i;
//		if (i < j)sorts[j] = sorts[i];
//	}
//	sorts[i] = temp;
//	sortpoints(left, i - 1);
//	sortpoints(i + 1, right);
//};
//
//void dfs(int pointsnode[]) {
//	if (max - nownum >= pointsnode[0] || pointsnode[0]<2)return;///如果连接的数量少于需要的数量返回
//
//	int node = pointsnode[1];
//	nownum++;
//	if (nownum > max)max = nownum;
//	int newpointsnode[N];
//	int k = 1;
//	for (int i = 1, j = 1; i < link[node][0] && j < pointsnode[0];) {
//		if (link[node][i] > pointsnode[j])++j;
//		else if (link[node][i] < pointsnode[j]) ++i;
//		else {
//			newpointsnode[k++] = pointsnode[j++];
//			i++;
//		}
//	}
//	newpointsnode[0] = k;
//	dfs(newpointsnode);
//	nownum--;
//	for (int j = 1; j < pointsnode[0] - 1; ++j)newpointsnode[j] = pointsnode[j + 1];
//	newpointsnode[0] = pointsnode[0] - 1;
//	dfs(newpointsnode);
//};
//
//int main()
//{
//	int t;
//	float x, y;
//	freopen("data.txt", "r", stdin);// 
//	scanf("%d", &t);
//	while (t--) {
//		scanf("%d", &n);
//		for (int i = 1; i <= n; ++i) {
//
//			scanf("%f %f", &x, &y);
//			points[i][0] = x * EXP1;
//			points[i][1] = y * EXP1;
//			map[i][0] = 0;
//			sorts[i] = i;
//			for (int j = 1; j < i; j++) {
//				map[i][j] = map[j][i] = 0;
//				unsigned int temp = SUB(points[i][0], points[j][0]);
//				unsigned int temp1 = SUB(points[i][1], points[j][1]);
//				if (temp1 < EXP2&&temp < EXP2&&temp1*temp1 + temp*temp < EXP3) {
//					map[i][0]++;
//					map[j][0]++;
//					map[i][j] = map[j][i] = 1;
//				}
//			}
//		}
//		sortpoints();
//
//		for (int i = 1; i <= n; ++i) {
//			int num = 1;
//			for (int j = i + 1; j <= n; ++j) {
//				if (map[sorts[i]][sorts[j]])
//					link[i][num++] = j;
//			}
//			link[i][0] = num;
//			sorts[i] = i;
//		}
//		sorts[0] = n + 1;
//
//		max = 1;
//		nownum = 0;
//		dfs(sorts);
//		printf("%d\n", max);
//	}
//	return 0;
//}
//#include <stdio.h> 
//
//#define N 305
//#define L 10.0
//#define EXP1 10000
//#define EXP2 20000
//#define EXP3 400000000
//#define SUB(x,y) x>y?x-y:y-x
//
//int map[N][N];		//关系映射矩阵
//int sorts[N];		//节点关系多少的排序，和link联合应用
//int link[N][N];		//邻接表
//int points[N][2];	//节点位置
//
//
//int nownum;
//int n;
//
//int max;
//
//void sortpoints(int left = 1, int right = n) {
//	if (left >= right)return;
//	int temp = sorts[left];//关系映射的多少
//	int i = left, j = right;
//	while (i < j) {
//		while (i < j&&map[sorts[j]][0] <= map[temp][0])--j;
//		if (j > i)sorts[i] = sorts[j];
//		while (i < j&&map[sorts[i]][0] >= map[temp][0])++i;
//		if (i < j)sorts[j] = sorts[i];
//	}
//	sorts[i] = temp;
//	sortpoints(left, i - 1);
//	sortpoints(i + 1, right);
//};
//
//void dfs(int pointsnode[]) {
//	if (max - nownum >= pointsnode[0] || pointsnode[0]<2)return;///如果连接的数量少于需要的数量返回
//
//	int node = pointsnode[1];
//	nownum++;
//	if (nownum > max)max = nownum;
//	int newpointsnode[N];
//	int k = 1;
//	for (int i = 1, j = 1; i < link[node][0] && j < pointsnode[0];) {
//		if (link[node][i] > pointsnode[j])++j;
//		else if (link[node][i] < pointsnode[j]) ++i;
//		else {
//			newpointsnode[k++] = pointsnode[j++];
//			i++;
//		}
//	}
//	newpointsnode[0] = k;
//	dfs(newpointsnode);
//	nownum--;
//	for (int j = 1; j < pointsnode[0] - 1; ++j)newpointsnode[j] = pointsnode[j + 1];
//	newpointsnode[0] = pointsnode[0] - 1;
//	dfs(newpointsnode);
//};
//
//int main()
//{
//	int t;
//	float x, y;
//	freopen("data.txt", "r", stdin);// 
//	scanf("%d", &t);
//	while (t--) {
//		scanf("%d", &n);
//		for (int i = 1; i <= n; ++i) {
//
//			scanf("%f %f", &x, &y);
//			points[i][0] = x * EXP1;
//			points[i][1] = y * EXP1;
//			map[i][0] = 0;
//			sorts[i] = i;
//			for (int j = 1; j < i; j++) {
//				map[i][j] = map[j][i] = 0;
//				unsigned int temp = SUB(points[i][0], points[j][0]);
//				unsigned int temp1 = SUB(points[i][1], points[j][1]);
//				if (temp1 < EXP2&&temp < EXP2&&temp1*temp1 + temp*temp < EXP3) {
//					map[i][0]++;
//					map[j][0]++;
//					map[i][j] = map[j][i] = 1;
//				}
//			}
//		}
//		sortpoints();
//
//		for (int i = 1; i <= n; ++i) {
//			int num = 1;
//			for (int j = i + 1; j <= n; ++j) {
//				if (map[sorts[i]][sorts[j]])
//					link[i][num++] = j;
//			}
//			link[i][0] = num;
//			sorts[i] = i;
//		}
//		sorts[0] = n + 1;
//
//		max = 1;
//		nownum = 0;
//		dfs(sorts);
//		printf("%d\n", max);
//	}
//	return 0;
//}

#include <stdio.h> 
#include <math.h>
#define N 305
#define L 10.0
#define EXP1 1
#define EXP2 2
#define EXP3 4
#define EXP32 1
#define SUB(x,y) x>y?x-y:y-x

struct location {
	float x;
	float y;
}points[N];

bool isCircle(const location& l1, const location & l2) {
	float temp = SUB(l1.x, l2.x);
	float temp1 = SUB(l1.y, l2.y);
	if (temp1 > EXP2 || temp > EXP2 || temp1*temp1 + temp*temp > EXP3 + 0.0001) return false;
	return true;
};

bool isCenter(const location& l1, const location & l2) {
	float temp = SUB(l1.x, l2.x);
	float temp1 = SUB(l1.y, l2.y);
	if (temp1 > EXP1 || temp > EXP1 || temp1*temp1 + temp*temp > EXP32 + 0.0001) return false;
	return true;
};
location center(int p1, int p2) {
	float x, y;
	double dis = SUB(points[p2].x, points[p1].x);
	if (dis < 0.0001) {
		y = (points[p2].y + points[p1].y) / 2;
		x = points[p2].x + sqrt(EXP32 - ((SUB(points[p1].y, y))*(SUB(points[p1].y, y))));
	}
	else {
		double c1 = (points[p2].x*points[p2].x - points[p1].x*points[p1].x + points[p2].y*points[p2].y - points[p1].y*points[p1].y) / (2 * (points[p2].x - points[p1].x));
		double c2 = (points[p2].y - points[p1].y) / (points[p2].x - points[p1].x);
		double A = (c2*c2 + 1);
		double B = (2 * points[p1].x*c2 - 2 * c1*c2 - 2 * points[p1].y);
		double C = points[p1].x*points[p1].x - 2 * points[p1].x*c1 + c1*c1 + points[p1].y*points[p1].y - EXP32;
		y = (-B + sqrt(B*B - 4 * A*C)) / (2 * A);
		x = c1 - c2 * y;
	}
	location cen = { x, y };
	return cen;
};

int main()
{
	int t, n;
	int max, sum;
	float x, y;
	freopen("data.txt", "r", stdin);// 
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%f %f", &x, &y);
			points[i] = { x,y };
		}
		max = 1;
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				sum = 0;
				if (isCircle(points[i], points[j])) {
					location cen = center(i, j);
					for (int k = 0; k < n; ++k) {
						if (isCenter(cen, points[k]))sum++;
					}
				}
				if (sum > max)
					max = sum;
			}
		}
		printf("%d\n", max);
	}
	return 0;
}