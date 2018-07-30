#include "stdafx.h"

/*
1044 迷宫路径搜索 规定步数内最大化收益

图在确定起点和终点后，在规定的步数内得到尽量多的收益
好像一点思路也没有

定义
dp[node1][G][node2]:表示以node1为起点，node2为终点，G为结点集合，所得到的最少步数
公式
dp[node1][G][node2] = min{ dp[node1][G-nodek][nodek]+dis(nodek,node2) }
****************************************************************************************************
定义
dp[node][C],G:表示以node为尾节点的路径在花费步数c后所得到的最大价值,G记录了这条路径上的节点集合
公式
dp[node][C] = max{dp[nodek][C-dis(nodek,node)]+if(node在这条路径上出现过)0 else +node的价值}
但是在实现的时候，C的取值范围过大（L），我们使用保存键对的方式

在实现的时候，采用深度优先遍历

程序分为两个部分：
1、计算各个节点之间的相互最短距离——bfs
2、更新dp数组
****************************************************************************************************
超时！！！！！！！！！！！！！！！！

超时的原因再后来对照别人的代码中发现，是由于没有使用sum控制广搜的过程，在得到最大的结果后马上放弃

*/

#include <stdio.h>  
#include <queue>

#define W 55	//宽
#define H 55	//高
#define L 1000005	//时间
#define M 15	//财宝

char map[H][W];//地图  
int dist[H][W];//起点，珠宝，出口之间的距离  
int smap[H][W];//  

bool flag[M];//DFS标记  
int jewels[M][3];//珠宝价值  
int w, h, l, m;
int  sum,value;////注意这里的sum是关键，没有它就会超时！！！！！！！！！！！！！
int direct[4][2] = { 1,0,0,1,-1,0,0,-1 };
inline int check(int nx, int ny) {	//检查x,y处是什么元素
	if (nx >= h || ny >= w || nx < 0 || ny< 0 || map[nx][ny] == '*' || smap[nx][ny])return -1;//不可达
	if (map[nx][ny] == '@') return m;//起点
	if (map[nx][ny] == '<') return m + 1;//终点
	if (map[nx][ny] == '.') return 20;	//普通点
	return map[nx][ny] - 'A';
};
void bfs_dist(int snode) {
	int x, y, nx, ny, node;
	int step = 0;
	std::queue<int> list;
	list.push((jewels[snode][1]<<6) + jewels[snode][2]);//哈希一下 x*64+y
	memset(smap, 0, sizeof(smap));
	smap[jewels[snode][1]][jewels[snode][2]] = 1;
	dist[snode][snode] = 0;
	while (!list.empty()&&step<m+1) {
		node = list.front();
		x = node >> 6;
		y = node & 63;
		list.pop();
		for (int i = 0; i < 4; i++) {
			nx = x + direct[i][0], ny = y + direct[i][1];
			node = check(nx, ny);
			if (node == 20) {
				smap[nx][ny] = smap[x][y] + 1;
				list.push((nx << 6) + ny);
			}
			else if (node >= 0) {
				dist[snode][node] = smap[x][y];
				list.push((nx << 6) + ny);
				smap[nx][ny] = smap[x][y] + 1;
				step++;
			}
		}
	}
};
//当前珠宝，当前珠宝价值，消耗时间  
void dfs_update(int node, int j, int time)
{
	//注意下面三条语句的顺序  
	if (value == sum)
		return;
	if (node == m+1){
		if (j>value)
			value = j;
		return;
	}
	for (int i = 0; i <= m + 1; i++)
	{
		//if (flag[i] || dist[node][i] == 0)
		//	continue;
		//if (!flag[i] && dist[node][i]) {	////////这里是问题的关键！！！！如果我用 node!=i 作为判定条件就会出错
		if (!flag[i] && node!=i && (time - dist[node][i] >= dist[i][m + 1])) {	//之前这里的原因是dist初始化为0，如果直接i！=node就会误判很多根本不可达的节点距离
			flag[i] = true;
			dfs_update(i, j + jewels[i][0], time - dist[node][i]);
			flag[i] = false;
		}
	}
}

int main()
{
	int T, kase = 1;
	freopen("data.txt", "r", stdin);// 
	scanf("%d", &T);
	while (T--){
		scanf("%d %d %d %d", &w, &h, &l, &m);
		sum = 0;
		for (int i = 0; i < m; i++){
			scanf("%d", jewels + i);
			sum += jewels[i][0];
		}
		jewels[m][0] = jewels[m + 1][0] = 0;
		for (int i = 0; i<h; i++)
			scanf("%s", map[i]);
		memset(dist, 0x3f, sizeof(dist));
		for (int i = 0; i<h; i++){
			for (int j = 0; j<w; j++){
				if (map[i][j] == '@') { jewels[m][1] = i; jewels[m][2] = j; }//起点
				else if (map[i][j] == '<') { jewels[m + 1][1] = i; jewels[m + 1][2] = j; }//终点
				else if (map[i][j] >= 'A'&&map[i][j] <= 'J') { jewels[map[i][j] - 'A'][1] = i; jewels[map[i][j] - 'A'][2] = j;}
			}
		}
		for (int i = 0; i < m + 2; i++) {
			bfs_dist(i);
		}
		memset(flag, false, sizeof(flag));
		flag[m] = true;
		value = -1;
		dfs_update(m, 0, l);
		printf("Case %d:\n", kase++);
		if(value == -1)
			printf("Impossible\n");
		else
			printf("The best score is %d.\n", value);
		if(T)
			printf("\n");
	}
	return 0;
}