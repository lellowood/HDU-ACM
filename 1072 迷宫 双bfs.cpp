#include "stdafx.h"

/*
1072 迷宫路径搜索 输出规定时间内能走出的最短时间

图中有
0：墙，不准走
1：路
2：起点
3：终点
4：时间重置

思路：类似这样一个场景：从一个路灯下出发，或者在这个路灯能照到的范围内走出去，或者走到下一个路灯处打开开关
起始点就是第一个路灯，路灯的半径类似曼哈顿圆⚪

算法：对每一个路灯计算其与其他路灯的距离，方式是bfs（不能直接使用曼哈顿圆，因为会有遮挡）
然后沿着路灯间的距离寻找到终点的距离，方式还是bfs

wrong 不知道是我的思路不对还是编程出现错误

******************************************************************************************************************
为了验证，我换一种暴力解法

暴力解法没问题
******************************************************************************************************************

原先解法问题的关键在后一个bfs没有列举出所有情况
******************************************************************************************************************
*/


//////路灯思路
#include <stdio.h>  
#include <queue>

#define L 8
#define LL 65
#define T 6

int map[L][L];//地图  

int lights[LL][2];//路灯位置  2为起始路灯 3为终点 3以后为中间路灯

int dist[LL][LL];

int n, m, ll;

int direct[4][2] = { 1,0,0,1,-1,0,0,-1 };
inline int check(int nx, int ny) {	//检查x,y处是什么元素
	if (nx >= n || ny >= m || nx < 0 || ny< 0 || map[nx][ny] == 0)return -1;//不可达
	return map[nx][ny];
};
void bfs_dist(int snode) {
	std::queue<int> list;
	list.push((lights[snode][0] << 3) + lights[snode][1]);//哈希一下 x*64+y
	int smap[L][L] = { 0 };
	smap[lights[snode][0]][lights[snode][1]] = T;
	dist[snode][snode] = 0;
	while (!list.empty()) {
		int node = list.front();
		list.pop();
		int x = node >> 3;
		int y = node & 7;
		for (int i = 0; i < 4; ++i) {
			int nx = x + direct[i][0];
			int ny = y + direct[i][1];
			node = check(nx, ny);
			if (node > 0&&smap[nx][ny] == 0) {//如果node>0
				smap[nx][ny] = smap[x][y] - 1;
				if(node > 1)
					dist[snode][node] = T - smap[nx][ny];
				if(smap[nx][ny]>1)
					list.push((nx << 3) + ny);
			}
		}
	}
};

int bfs_path() {
	std::queue<int> list;
	list.push(2);// 2为起始节点
	int smap[LL] = { 0 };
	smap[2] = 1;
	while (!list.empty()) {
		int node = list.front();
		list.pop();
		for (int i = 3; i < ll; ++i) {
			if (dist[node][i]&&(smap[i]==0||smap[i]>smap[node] + dist[node][i])) {//两者间存在路径 并且距离未更新或者新更新的距离小于原先的距离
				smap[i] = smap[node] + dist[node][i];
				list.push(i);
			}
		}
	}
	return smap[3]-1;
};

int main()
{
	int t;
	freopen("data.txt", "r", stdin);// 
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		ll = 4;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 4)map[i][j] = ll++;
				lights[map[i][j]][0] = i;
				lights[map[i][j]][1] = j;
			}
		}
		memset(dist, 0, sizeof(dist));//距离矩阵初始0——
		for (int i = 2; i < ll; ++i) {
			bfs_dist(i);
		}
		printf("%d\n", bfs_path());
	}
	return 0;
}

//////////////暴力解法

//#include <stdio.h>  
//#include <queue>
//
//#define L 8
//#define LL 65
//#define T 6
//
//int map[L][L];
//int tmap[L][L];
//int smap[L][L];
//
//int direct[4][2] = { 1,0,0,1,-1,0,0,-1 };
//
//int n, m;
//int x, y;
//
//inline int check(int nx, int ny) {	//检查x,y处是什么元素
//	if (nx >= n || ny >= m || nx < 0 || ny< 0 || map[nx][ny] == 0)return -1;//不可达
//	return map[nx][ny];
//};
//
//int bfs_path() {
//	std::queue<int> list;
//	list.push((x << 3) + y);// 2为起始节点
//	tmap[x][y] = 6;
//	smap[x][y] = 0;
//	while (!list.empty()) {
//		int node = list.front();
//		int mx = node >> 3;
//		int my = node & 7;
//		list.pop();
//		for (int i = 0; i < 4; ++i) {
//			int nx = mx + direct[i][0];
//			int ny = my + direct[i][1];
//			node = check(nx, ny);
//			if (node > 0) {
//				if (node == 4) {
//					if (tmap[nx][ny] < T) {
//						tmap[nx][ny] = T;
//						smap[nx][ny] = smap[mx][my] + 1;
//						list.push((nx << 3) + ny);
//					}
//				}
//				else if (node > 0 && tmap[nx][ny] < tmap[mx][my] - 1) {
//					tmap[nx][ny] = tmap[mx][my] - 1;
//					smap[nx][ny] = smap[mx][my] + 1;
//					if (tmap[nx][ny]>1)
//						list.push((nx << 3) + ny);
//				}
//			}
//			if (node == 3) return smap[nx][ny];
//		}
//	}
//	return -1;
//};
//
//int main()
//{
//	int t;
//	freopen("data.txt", "r", stdin);// 
//	scanf("%d", &t);
//	while (t--) {
//		scanf("%d %d", &n, &m);
//		for (int i = 0; i < n; ++i) {
//			for (int j = 0; j < m; ++j) {
//				scanf("%d", &map[i][j]);
//				if (map[i][j] == 2) { x = i; y = j; }
//			}
//		}
//		memset(tmap, 0, sizeof(tmap));//距离矩阵初始0——
//
//		printf("%d\n", bfs_path());
//	}
//	return 0;
//}