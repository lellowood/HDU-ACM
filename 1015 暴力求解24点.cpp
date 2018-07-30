//#include "stdafx.h"
//
//#include "stdio.h"
//#include "string.h"
//
//int M, N;
////地图
//int map[101][101] = { 0 };
////节点
//int node[101][2] = { 0 };
////递推矩阵
//int dp[101][101] = { 0 };
//
//void directgraph(int cnode) {
//	int link[101] = { 0 };
//	int temp[101] = { 0 };//临时数组保存每一个节点更新后的变量
//	for (int i = 1; i <= N; i++) {
//		if (map[cnode][i]) {
//			map[i][cnode] = 0;//所有连向上一节点的路径消除：因为所有节点都可达且只有一条路径可达;消除死循环
//			directgraph(i);
//			link[0]++;
//			link[link[0]] = i;
//		}
//	}
//	int begin = (node[cnode][0] + 19) / 20;
//	//for (int j = begin>0?begin:1; j <= M; j++) {
//	//	dp[cnode][j] = node[cnode][1];
//	//}
//	for (int j = begin; j <= M; j++) {
//		dp[cnode][j] = node[cnode][1];
//	}
//	for (int p = 1; p <= link[0]; p++) {
//		for (int j = begin + 1; j <= M; j++) {
//			for (int k = 1; k <= j - begin; k++) {
//				if (dp[cnode][j - k] + dp[link[p]][k] > dp[cnode][j])
//					temp[j] = dp[cnode][j - k] + dp[link[p]][k];
//			}
//		}
//		for (int j = begin + 1; j <= M; j++) {
//			dp[cnode][j] = temp[j];
//		}
//	}
//};
//
//int main() {
//	int x, y;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d%d", &N, &M)!=EOF&&M!=-1&&N!=-1) {
//		memset(map, 0, sizeof(int) * 101 * 101);
//		memset(dp, 0, sizeof(int) * 101 * 101);
//		for (int i = 1; i <= N; i++) {
//			scanf("%d%d", node[i], node[i] + 1);
//		}
//		for (int i = 0; i < N-1; i++) {
//			scanf("%d%d", &x, &y);
//			map[x][y] = map[y][x] = 1;//先记录为无向图
//		}
//		directgraph(1);//重置有向图
//		if (M == 0)
//			printf("0\n");
//		else
//			printf("%d\n", dp[1][M]);
//	}
//}

#include "stdafx.h"

#include "stdio.h"
#include "string.h"
#include <algorithm>
/*
1012 变形24点
v - w^2 + x^3 - y^4 + z^5 = target
暴力解有 A(5,N)个
解空间不是很大
但同样可以剪枝
1：当前计算的值加上后半部分最小值也会超过目标值的剪掉
2：当前计算的值加上后半部分最大值也会小于目标值的剪掉
但是我好像还是。。。没有做剪枝
*/

int M, N;
//字母表
char dict[30];
//26缓存次方表
int temp[30][6] = {
	{ 0, 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 4, 8, 16, 32 },
	{ 1, 3, 9, 27, 81, 243 },
	{ 1, 4, 16, 64, 256, 1024 },
	{ 1, 5, 25, 125, 625, 3125 },
	{ 1, 6, 36, 216, 1296, 7776 },
	{ 1, 7, 49, 343, 2401, 16807 },
	{ 1, 8, 64, 512, 4096, 32768 },
	{ 1, 9, 81, 729, 6561, 59049 },
	{ 1, 10, 100, 1000, 10000, 100000 },
	{ 1, 11, 121, 1331, 14641, 161051 },
	{ 1, 12, 144, 1728, 20736, 248832 },
	{ 1, 13, 169, 2197, 28561, 371293 },
	{ 1, 14, 196, 2744, 38416, 537824 },
	{ 1, 15, 225, 3375, 50625, 759375 },
	{ 1, 16, 256, 4096, 65536, 1048576 },
	{ 1, 17, 289, 4913, 83521, 1419857 },
	{ 1, 18, 324, 5832, 104976, 1889568 },
	{ 1, 19, 361, 6859, 130321, 2476099 },
	{ 1, 20, 400, 8000, 160000, 3200000 },
	{ 1, 21, 441, 9261, 194481, 4084101 },
	{ 1, 22, 484, 10648, 234256, 5153632 },
	{ 1, 23, 529, 12167, 279841, 6436343 },
	{ 1, 24, 576, 13824, 331776, 7962624 },
	{ 1, 25, 625, 15625, 390625, 9765625 },
	{ 1, 26, 676, 17576, 456976, 11881376 }
};
bool flag[30];
char path[6];

bool dsf(int pos, int sco) {
	if (sco == M&&pos == 5)
		return true;
	if (pos > 4)
		return false;
	for (int i = N - 1; i >= 0; i--) {
		if (flag[i]) {//没被用过
			flag[i] = false;
			path[pos] = dict[i];
			if (dsf(pos + 1,sco + (1 - (pos & 1) - (pos & 1))*temp[dict[i] - 64][pos + 1]))return true;//如果pos偶数，位置符号是+
			flag[i] = true;
		}
	}
	return false;
};

int main() {
	int x, y;
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d%s",&M, dict) != EOF&&M != 0 && strcmp(dict, "END")) {
		N = strlen(dict);
		memset(flag, 1, sizeof(bool)*N);
		std::sort(dict, dict + N);//由小到大
		if(dsf(0,0))
			for(int i=0;i<5;i++)
				printf("%c", path[i]);
		else
			printf("no solution");
		printf("\n");
	}
}