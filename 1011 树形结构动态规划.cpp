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
/*
1011找bug
树形结构，每一个节点有两个值：第一个是从上节点到达该节点的花费，第二个是得到的价值
深度遍历，找到在一定成本下能得到的最大价值

结构体的关键是记录有向图的边

ok，题意理解错了
这题是树的动态规划

设置二维数组dp[i][j]表示当i节点分配j个成本所能得到的最大价值
dp[i][j] = node[i][1]+max(j-(node[i]+19/20)分配给连接i的下一层节点)

上面的思路出现了问题，再提交后是超时

新的想法是：
每一个节点都有一个分段函数
对于一个节点 s 的所有子节点
for subnode p
for k=1; k<=j-自己消耗的成本; k++
dp[s][j] = max(dp[s][j-k]+dp[p][k],dp[s][j])

尝试了好几次终于成功，有这样几个注意：
1）更新顺序对结果的影响：由于对数据不停的更新，导致前面更新的影响叠加到后面；
2）在发现这个问题之后，尝试用temp存储更新的结果，但是会导致更新的结果没有及时传递到计算中，忽略了新的结果
3）最后将计算顺序倒装

题意的理解：
1）每一个节点只有去过士兵才能获取里面的价值，没有士兵去，即使里面不需要士兵打架，也得不到里面的东西——可以不停留
2）子结点的顺序是动态规划的关键
*/



int M, N;
//地图
int map[101][101] = { 0 };
//节点
int node[101][2] = { 0 };
//递推矩阵
int dp[101][101] = { 0 };

////
//int dpo(int cnode, int captial, int nnode) {
//	if(])
//	int tnode;
//	for (tnode = nnode + 1; tnode <= N && !map[cnode][tnode]; tnode++);//查找比nnode大的且与cnode相连的节点
//	int max = 0;
//	for (int i = 0; i <= captial; i++) {
//		int value = dpgraph(tnode, i);//给tnode节点i个成本能得到的最大的效益
//		value += dpo(cnode, captial - 1, tnode);//
//		if (value > max)
//			max = value;
//	}
//	return max;
//};
//
////当前节点，本钱，以获取价值
//int dpgraph(int cnode, int capital) {
//	if (capital*20 >= node[cnode][0]) {
//		capital -= (node[cnode][0]+19)/20;
//	}
//	else
//		return 0;
//	return node[cnode][1]+dpo(cnode, capital, 0);
//};
//
//int recursive(int link[], int cnode, int capital) {
//	if (cnode + 1 > link[0])
//		return dp[link[cnode]][capital];
//	int max = 0;
//	for (int i = 0; i <= capital; i++) {
//		int value = recursive(link, cnode + 1, i);
//		if (value + dp[link[cnode]][capital - i] > max)
//			max = value + dp[link[cnode]][capital - i];
//	}
//	return max;
//};
//
//void dpgraph(int cnode) {
//	//bool flag = true;
//	int link[101] = { 0 };
//	for (int i = 1; i <= N; i++)//遍历所有连接cnode的节点是否已经path置为-1
//		if (map[cnode][i]) {
//			if (path[i] != -1)dpgraph(i);//没有置为1，递归调用dpgraph
//			link[0]++;
//			link[link[0]] = i;
//		}
//	int value = (node[cnode][0] + 19) / 20;
//	for (int i = 0; i < value; i++)
//		dp[cnode][i] = 0;
//	for (int i = value+1; i <= M; i++) {
//		dp[cnode][i] = recursive(link, 1, i-value) + node[cnode][1];
//	}
//	path[cnode] = -1;
//};
//void directgraph(int cnode) {
//	for (int i = 1; i <= N; i++) {
//		if (map[cnode][i]) {
//			map[i][cnode] = 0;//所有连向上一节点的路径消除：因为所有节点都可达且只有一条路径可达
//			directgraph(i);
//			path[cnode]++;
//		}
//	}
//};

void directgraph(int cnode) {
	int link[101] = { 0 };
	//int temp[101] = { 0 };//临时数组保存每一个节点更新后的变量
	for (int i = 1; i <= N; i++) {
		if (map[cnode][i]) {
			map[i][cnode] = 0;//所有连向上一节点的路径消除：因为所有节点都可达且只有一条路径可达;消除死循环
			directgraph(i);
			link[0]++;
			link[link[0]] = i;
		}
	}
	int begin = (node[cnode][0] + 19) / 20;
	for (int j = begin>0 ? begin : 1; j <= M; j++) {
		dp[cnode][j] = node[cnode][1];
	}
	for (int p = 1; p <= link[0]; p++) {
		for (int j = M; j > begin; j--) {
			if (begin == 0 && node[cnode][1] + dp[link[p]][j]> dp[cnode][j])	//特判 该节点无需代价的情况
				dp[cnode][j] = dp[link[p]][j] + node[cnode][1];
			else if (dp[cnode][begin] + dp[link[p]][j - begin] > dp[cnode][j])
				dp[cnode][j] = dp[cnode][begin] + dp[link[p]][j - begin];
			for (int k = 1; k < j - begin; k++) {
				if (dp[cnode][j - k] + dp[link[p]][k] > dp[cnode][j])
					dp[cnode][j] = dp[cnode][j - k] + dp[link[p]][k];
			}
		}
	}
};

int main() {
	int x, y;
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d%d", &N, &M) != EOF&&M != -1 && N != -1) {
		memset(map, 0, sizeof(int) * 101 * 101);
		memset(dp, 0, sizeof(int) * 101 * 101);
		//memset(node, 0, sizeof(int) * 101);
		for (int i = 1; i <= N; i++) {
			scanf("%d%d", node[i], node[i] + 1);
			//if (node[i][0] == 0)node[i][0]++;
		}
		for (int i = 0; i < N - 1; i++) {
			//scanf("%d%d", path[i], path[i] + 1);
			scanf("%d%d", &x, &y);
			map[x][y] = map[y][x] = 1;//先记录为无向图
		}
		directgraph(1);//重置有向图
					   //for (int i = 1; i <= N; i++) {
					   //	if (path[i] == 0) {
					   //		dp[i][0] = 0;
					   //		for (int j = 1; j <= M; j++) {
					   //			if (j * 20 >= (node[i][0]))
					   //				dp[i][j] = node[i][1];
					   //			else
					   //				dp[i][j] = 0;
					   //		}
					   //		path[i] = -1;
					   //	}
					   //}
					   //dpgraph(1);
		printf("%d\n", dp[1][M]);
	}
}