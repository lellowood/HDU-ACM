#include "stdafx.h"

/*
1035 二维矩阵路径模拟
*/

#include "stdio.h"
#include "string.h"


#define N 12
#define M 12

int n, m, s;

//地图
char map[M][N] = { 0 };
//时间 到达[i][j]位置的最少时间
unsigned tmap[M][N] = { 0 };


int main() {
	int steps, x, y;
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d%d%d", &m, &n, &s) != EOF&&(m||n||s)) {
		for (int i = 0; i < m; i++) scanf("%s", map[i]);
		memset(tmap, 0, sizeof(tmap));
		steps = 1;	//从1开始，实际应该从0开始，待会儿减掉
		x = 0, y = s - 1;
		while (x >= 0 && y >= 0 && x < m && y < n && tmap[x][y] == 0) {
			tmap[x][y] = steps++;
			switch (map[x][y])
			{
			case 'E'://	东
				y++;
				break;
			case 'W':// 西
				y--;
				break;
			case 'N':// 北
				x--;
				break;
			case 'S':// 南
				x++;
				break;	
			default:
				printf("输入错误\n");
				break;
			}
		}
		if (x >= 0 && y >= 0 && x < m && y < n)
			printf("%d step(s) before a loop of %d step(s)\n", tmap[x][y]-1, steps- tmap[x][y]);
		else
			printf("%d step(s) to exit\n", steps - 1);
	}
	return 0;
}