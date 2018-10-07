#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1105 二维网格 解空间
2018、10、2 只有44个通过22个acmer

1、100个网格，放置1个羊三个狼 有 100*99*98*97/6 = 15684900 个解空间
进行位置编码

int sum = 0;
for (int i = 0; i <= 96; i++)
for (int j = 0; j <= i; j++)
for (int k = 0; k <= j; k++)sum++;
sum = 156849;

羊的位置 y [0,99]
倒数一只狼的位置（除了羊） x1[0,96] （应该从2-98，这里从0-96）
倒数二只狼距离第一狼的位置 x2[0，x1]
倒数三只狼距离第二狼的位置 x3[0，x2]
编码 y*156849 + s(s=0;for(int i=0;i<x1;i++)s+=(97-i)*(98-i)/2;) + z(z=0;for(int i=0;i<x2;i++)z+=(97-x1-i);)

*******************************************************************************************************************
使用递归+正向深度搜索 堆栈溢出
*******************************************************************************************************************
使用队列+反向递推

1、状态编码，需要对解空间状态进行保存-100个网格，放置1个羊三个狼 有 100*99*98*97/6 = 15684900 个解空间
进行位置编码：100可以重复，99*98*97/6可以想象是正方体截取一个三角体正好是1/6

hashtable[100]
for (int i = 0; i <= 96; i++){
	sum=0;
for (int j = 0; j <= i; j++)
for (int k = 0; k <= j; k++)sum++;
hashtable[i+1]=hashtable[i]+sum;
}
hashtable[97] 正好等于 156849

羊的位置 y [0,99]
倒数一只狼的位置（除了羊） x1[0,96] （应该从2-98，这里从0-96）
倒数二只狼的位置 x2[0，x1]
倒数三只狼的位置 x3[0，x2]
编码 y * hashtable[r*c - 3] + hashtable[x1] + ((x2 - 1)*x2) / 2 + x3;

2、状态设置 char hashmap[15684900]; 
一个byte：
0 0 0 0 0 0 0 0
|	表示是否是起始点
  |		表示是否是死点——这种情况下羊必死，当反向推导起始点也是死点时，羊必被抓
	| | | | 这四位表示羊可以移动的四个方向，如果可以移动的初始为1，当四个方向的结果都是0时，这个状态被更改为死点

3、反向搜索
先对起始情况下，把狼移动后的状态标志为起始点——状态为第一个bit设为1

然后统计当前矩阵中，所有直接可以计算的死点——即：某个位置为'.'且有相邻一面或几面是'X'，然后将剩余面补齐'W'，设置为死点加入队列

循环取出队列中的死点状态，尝试移动可以移动的W，在W移动的情况下将S移动，对移动后的状态的对应某个方向的bit设为0，当这个状态的状态码后四位（方向）全为0时，将这个状态加入死点队列

循环中遇到起始点为死点情况——输出能抓到
如果循环完队列还没有遇到起点——输出不可能抓到
*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define SUB(x,y) (x>y?(x-y):(y-x))
#define R  12
#define C  12
#define N  101
#define N_ 156849

int r, c;
int s[2], w[3][2]; //位置信息，动态调整
int startcode;


int hashtable[N] = {
	0,
	1,
	4,
	10,
	20,
	35,
	56,
	84,
	120,
	165,
	220,
	286,
	364,
	455,
	560,
	680,
	816,
	969,
	1140,
	1330,
	1540,
	1771,
	2024,
	2300,
	2600,
	2925,
	3276,
	3654,
	4060,
	4495,
	4960,
	5456,
	5984,
	6545,
	7140,
	7770,
	8436,
	9139,
	9880,
	10660,
	11480,
	12341,
	13244,
	14190,
	15180,
	16215,
	17296,
	18424,
	19600,
	20825,
	22100,
	23426,
	24804,
	26235,
	27720,
	29260,
	30856,
	32509,
	34220,
	35990,
	37820,
	39711,
	41664,
	43680,
	45760,
	47905,
	50116,
	52394,
	54740,
	57155,
	59640,
	62196,
	64824,
	67525,
	70300,
	73150,
	76076,
	79079,
	82160,
	85320,
	88560,
	91881,
	95284,
	98770,
	102340,
	105995,
	109736,
	113564,
	117480,
	121485,
	125580,
	129766,
	134044,
	138415,
	142880,
	147440,
	152096,
	156849
};
char map[R][C];
char hashmap[N*N_]; //状态表 0：未达； 后四位可达以后初始化为1，每一条路堵死为0，直到全为0，表示该状态是死状态
int direct[4][2] = { -1,0,1,0,0,-1,0,1 };
char bits[4] = { 1,2,4,8 };
char rbits[4] = { 2,1,8,4 };
struct pos {
	unsigned int sx : 4;
	unsigned int sy : 4;
	unsigned int w1x : 4;
	unsigned int w1y : 4;
	unsigned int w2x : 4;
	unsigned int w2y : 4;
	unsigned int w3x : 4;
	unsigned int w3y : 4;
};

queue<pos> list;
bool flag;

int map2code() {
	int y, x1, x2, x3, x11, x22, x33;
	y = s[0] * c + s[1];
	x1 = w[0][0] * c + w[0][1];
	x2 = w[1][0] * c + w[1][1];
	x3 = w[2][0] * c + w[2][1];
	x11 = MAX(x1, MAX(x2, x3));
	x33 = MIN(x1, MIN(x2, x3));
	x22 = x1 + x2 + x3 - x11 - x33;
	x1 = x11 - 2;
	x2 = x22 - 1;
	x3 = x33;
	if (x11 > y) {//y在x11之后
		x1--;
		if (x22 > y) {//y在x22之后
			x2--;
			if (x33 < y)//y在x33之后
				x3--;
		}
	}
	return y * hashtable[r*c - 3] + hashtable[x1] + ((x2 - 1)*x2) / 2 + x3;
};

void push_pos() {
	int temp = map2code();
	//if (temp == 264) {
	//	map2code();
	//}
	//if (hashmap[temp])return;
	pos p = { s[0],s[1],w[0][0],w[0][1],w[1][0],w[1][1] ,w[2][0],w[2][1] };
	//if (s[0] == ss[0] && s[1] == ss[1] && w[0][0] == sw[0][0] && w[0][1] == sw[0][1] && w[1][0] == sw[1][0] && w[1][1] == sw[1][1] && w[2][0] == sw[2][0] && w[2][1] == sw[2][2])
	if (hashmap[temp] & 0x40)return;//已经是死点——返回
	list.push(p);
	if (hashmap[temp]&0x80)//如果死点是起点——能被抓
		flag = true;
	hashmap[temp] |= 0x40;
};

void search_deal_pos(int nums) {
	if (nums < 0) {
		push_pos(); return;
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i][j] == '.') {
				map[i][j] = 'W';
				w[nums][0] = i;
				w[nums][1] = j;
				search_deal_pos(nums - 1);
				map[i][j] = '.';
			}
		}
	}
};

inline void map1pos() {
	map[s[0]][s[1]] = '.';
	map[w[0][0]][w[0][1]] = '.';
	map[w[1][0]][w[1][1]] = '.';
	map[w[2][0]][w[2][1]] = '.';
};

inline void pos2map(pos p) {
	s[0] = p.sx;
	s[1] = p.sy;
	w[0][0] = p.w1x;
	w[0][1] = p.w1y;
	w[1][0] = p.w2x;
	w[1][1] = p.w2y;
	w[2][0] = p.w3x;
	w[2][1] = p.w3y;
	map[p.sx][p.sy] = 'S';
	map[p.w1x][p.w1y] = 'W';
	map[p.w2x][p.w2y] = 'W';
	map[p.w3x][p.w3y] = 'W';
};

int main() {
	int x, y, sx, sy;
	int counts = 0;
	freopen("data.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	while (scanf("%d %d\n", &r, &c) != EOF) {
		w[0][0] = w[1][0] = w[2][0] = -1;
		counts = 0;
		flag = 0;
		while (!list.empty())list.pop();
		memset(hashmap, 0, sizeof(hashmap));
		for (int i = 0; i < r; i++) {
			scanf("%s", map + i);
			for (int j = 0; j < c; j++) {
				if (map[i][j] == 'S') {
					s[0] = i;
					s[1] = j;
				}
				else if (map[i][j] == 'W') {
					w[counts][0] = i;
					w[counts][1] = j;
					++counts;
				}
			}
		}
		startcode = map2code();
		counts = 0;
		for (int i = 0; i < 3; i++) {
			x = w[i][0];
			y = w[i][1];
			for (int j = 0; j < 4; j++) {
				w[i][0] = x + direct[j][0];
				w[i][1] = y + direct[j][1];
				if (w[i][0] >= 0 && w[i][0] < r&&w[i][1] >= 0 && w[i][1] < c&&map[w[i][0]][w[i][1]] == '.') {
					counts++;
					int temp = map2code();
					hashmap[temp] = 0x80;
				}
			}
			w[i][0] = x;
			w[i][1] = y;
		}
		if (!counts)
			hashmap[startcode] = 0x80;
		map1pos();
		//将所有的死点标记出来
		for (int i = 1; i < r-1; i++) {
			for (int j = 1; j < c - 1; j++) {
				if (map[i][j] == '.' && (map[i - 1][j] == 'X' || map[i + 1][j] == 'X' || map[i][j - 1] == 'X' || map[i][j + 1] == 'X')) {
					int temp = 2;
					map[i][j] = 'S';
					s[0] = i;
					s[1] = j;
					for (int k = 0; k < 4; k++) {
						if (map[i + direct[k][0]][j + direct[k][1]] == '.') {
							map[i + direct[k][0]][j + direct[k][1]] = 'W';
							w[temp][0] = i + direct[k][0];
							w[temp][1] = j + direct[k][1];
							--temp;
						}
					}
					search_deal_pos(temp);
					map1pos();
				}
			}
		}

		while (!flag && !list.empty()) {
			pos p = list.front();
			list.pop();
			counts = 1;
			pos2map(p);
			sx = s[0];
			sy = s[1];
			for (int i = 0; i < 3; i++) {
				x = w[i][0];
				y = w[i][1];
				map[x][y] = '.';
				for (int j = 0; j < 4; j++) {
					w[i][0] = x + direct[j][0];
					w[i][1] = y + direct[j][1];
					if (w[i][0] >= 0 && w[i][0] < r&&w[i][1] >= 0 && w[i][1] < c&&map[w[i][0]][w[i][1]] == '.') {
						map[sx][sy] = '.';
						map[w[i][0]][w[i][1]] = 'W';
						counts = 0;
						for (int k = 0; k < 4; k++) {
							s[0] = sx + direct[k][0];
							s[1] = sy + direct[k][1];

							if (s[0] > 0 && s[0] < r-1&&s[1] > 0 && s[1] < c-1&&map[s[0]][s[1]] == '.') {////注意这里是1 - r-1
								//map[s[0]][s[1]] = 'S';
								int temp = map2code();
								if (!(hashmap[temp] & 0x40)) {//不是死点
									if ((hashmap[temp] & 0x0F) == 0) {
										for (int p = 0; p < 4; p++)
											if (map[s[0] + direct[p][0]][s[1] + direct[p][1]] == '.')
												hashmap[temp] |= bits[p];		
									}
									if (hashmap[temp] & 0x0F) {
										hashmap[temp] &= (~rbits[k]);
										if ((hashmap[temp] & 0x0F) == 0) {
											push_pos();
										}
									}
								}
								//map[s[0]][s[1]] = '.';
							}
						}
						map[sx][sy] = 'S';
						map[w[i][0]][w[i][1]] = '.';
					}
				}
				w[i][0] = x;
				w[i][1] = y;
				map[x][y] = 'W';
			}
			s[0] = sx;
			s[1] = sy;
			map1pos();
		}

		if (flag)
			printf("Poor Mmxl is in danger:(\n");
		else
			printf("Lucky Mmxl is safe:)\n");
	}
	return 0;
}