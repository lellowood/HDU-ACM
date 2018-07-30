#include "stdafx.h"

#include "stdio.h"
#include "string.h"
/*
推箱子
一个路径搜索问题，但比一般的路径问题多了一个方向限制：箱子移动到另一个格子的要求是搬运工能走到箱子的反面
考虑的情况：
1、箱子到达目的地的移动路径
2、在箱子每次移动一步搬运工的移动路径

所以定义一个地图格子：（flag,id）flag表示箱子能否到达这个格子（可达的步数，不可达-1），id表示搬运工所处位置的编号（上下左右：01编码，最大1111表示四者可达，最小0000表示都不可达）
一个格子不被重复定义的条件是：如果新的定义的编码和以往的有相同的，比较两者步数，较小者保留。因为编码数量有限，所以算法一定会终结

一个问题：我们是准备采用暴力吗？将地图上所有格子都点亮？所以这里有一个搜索遍历顺序选择，我们选择尽量靠近目标点的方向
*/

int T, M, N,ex,ey;
//地图
int map[8][8] = { 0 };
//地图备份
int smap[8][8] = { 0 };
//地图格子
int step[8][8][16];

void copymap(int x = -1,int y = -1) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			smap[i][j] = map[i][j];
			if (smap[i][j] == 2)
				smap[i][j] = 0;
		}
	}
	if (x != -1 && y != -1)smap[x][y] = 2;
};
//深度遍历，避开1和2
int pathfind(int s_x, int s_y, int e_x, int e_y,int steps) {
	if (e_x < 0 || e_x >= M || e_y < 0 || e_y >= N || smap[e_x][e_y] == 1 || smap[e_x][e_y] == 2)//排除不符合要求的情况
		return -1;
	if (s_x == e_x&&s_y == e_y)
		return steps;
	int direction[4][2];
	if (s_x>e_x && s_y>e_y) {
		direction[0][0] = -1; direction[0][1] = 0;
		direction[1][0] = 0; direction[1][1] = -1;
		direction[2][0] = 0; direction[2][1] = 1;
		direction[3][0] = 1; direction[3][1] = 0;
	}
	else if (s_x>e_x && s_y<=e_y) {
		direction[0][0] = -1; direction[0][1] = 0;
		direction[2][0] = 0; direction[2][1] = -1;
		direction[1][0] = 0; direction[1][1] = 1;
		direction[3][0] = 1; direction[3][1] = 0;
	}
	else if (s_x<=e_x && s_y>e_y) {
		direction[3][0] = -1; direction[3][1] = 0;
		direction[0][0] = 0; direction[0][1] = -1;
		direction[2][0] = 0; direction[2][1] = 1;
		direction[1][0] = 1; direction[1][1] = 0;
	}
	else  {
		direction[2][0] = -1; direction[0][1] = 0;
		direction[3][0] = 0; direction[1][1] = -1;
		direction[0][0] = 0; direction[2][1] = 1;
		direction[1][0] = 1; direction[3][1] = 0;
	}
	smap[s_x][s_y] = 1;//去过的地方不再去了
	for (int i = 0; i < 4; i++){
		int x = s_x + direction[i][0], y = s_y + direction[i][1];
		int cs = -1;
		if (x >= 0 && x < M&&y >= 0 && y < N&&smap[x][y] != 1 && smap[x][y] != 2) {
			cs = pathfind(x, y, e_x, e_y, steps + 1);
		}
		if (cs != -1)
			return cs;
	}
	smap[s_x][s_y] = 0;//这个方向走不通还原
};

//深度遍历，标记可达区域
void areafind(int s_x, int s_y) {
	if (s_x < 0 || s_x >= M || s_y < 0 || s_y >= N || smap[s_x][s_y] == 1 || smap[s_x][s_y] == 2 || smap[s_x][s_y] == 5)//排除不符合要求的情况
		return;
	int direction[4][2];
	direction[0][0] = -1; direction[0][1] = 0;
	direction[1][0] = 0; direction[1][1] = -1;
	direction[2][0] = 0; direction[2][1] = 1;
	direction[3][0] = 1; direction[3][1] = 0;
	smap[s_x][s_y] = 5;//去过的地方标记可达且不再去
	for (int i = 0; i < 4; i++) {
		int x = s_x + direction[i][0], y = s_y + direction[i][1];
		if (x >= 0 && x < M&&y >= 0 && y < N&&smap[x][y] != 1 && smap[x][y] != 2 && smap[x][y] != 5) {
			areafind(x, y);
		}
	}
};

//工人坐标（w_x,w_y）
//箱子坐标(b_x,b_y)
//返回箱子在坐标处，搬运工编号
//
int worker(int w_x, int w_y, int b_x, int b_y) {
	int id = 0;
	copymap(b_x, b_y);
	areafind(w_x, w_y);
	//上下左右--下上右左
	if (b_x - 1 >= 0 && smap[b_x - 1][b_y] == 5)//上可达
		id += 8;
	if (b_x + 1 < M && smap[b_x + 1][b_y] == 5)//下可达
		id += 4;
	if (b_y - 1 >= 0 && smap[b_x][b_y - 1] == 5)//左可达
		id += 2;
	if (b_y + 1 < N && smap[b_x][b_y + 1] == 5)//右可达
		id += 1;
	return id;
};
void recursive(int b_x,int b_y, int w_x, int w_y,int steps) {
	//这里使用的是深度遍历，所以得到的结果并不一定是最近解
	//if (b_x == ex&&b_y == ey)
	//	return steps;
	int id = worker(w_x, w_y, b_x, b_y);
	if (id < 1)
		return;
	if (step[b_x][b_y][id] == -1 || (step[b_x][b_y][id] != -1 && steps < step[b_x][b_y][id])) {
		step[b_x][b_y][id] = steps;
		int direction[4][2];
		direction[0][0] = 1; direction[0][1] = 0;//上-下
		direction[1][0] = -1; direction[1][1] = 0; //下-上
		direction[2][0] = 0; direction[2][1] = 1;//左-右
		direction[3][0] = 0; direction[3][1] = -1; //右-左
		for (int i = 0, dir = 8; i < 4; i++, dir /= 2) {
			int x = b_x + direction[i][0], y = b_y + direction[i][1];
			if (x >= 0 && x < M&&y >= 0 && y < N&&map[x][y] != 1 && (dir&id)) {
				recursive(x, y, b_x, b_y, steps + 1);
			}
		}
	}
};

int main() {
	freopen("data.txt", "r", stdin);// 
	scanf("%d", &T);
	while (T--) {
		int bx = -1, by = -1, wx = -1, wy = -1;
		ex = -1, ey = -1;
		scanf("%d%d", &M, &N);
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 2)bx = i, by = j;
				if (map[i][j] == 3)ex = i, ey = j;
				if (map[i][j] == 4)wx = i, wy = j;
			}
		}
		memset(step, -1, sizeof(int) * 8 * 8 * 16);
		if (bx==-1||by==-1||wx==-1||wy==-1||ex==-1||ey==-1) {
			printf("-1\n");
		}
		else {
			recursive(bx, by, wx, wy, 0);
			int steps = 132414;
			int id = -1;
			for (int i = 0; i < 16; i++) {
				if (step[ex][ey][i] != -1 && step[ex][ey][i] < steps) {
					steps = step[ex][ey][i];
					id = i;
				}
			}
			if(id!=-1) printf("%d\n", steps);
			else printf("-1\n");
		}
	}
}