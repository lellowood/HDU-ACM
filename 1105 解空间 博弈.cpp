#include "stdafx.h"

// ConsoleApplication1.cpp: �������̨Ӧ�ó������ڵ㡣
//

/*
1105 ��ά���� ��ռ�
2018��10��2 ֻ��44��ͨ��22��acmer

1��100�����񣬷���1���������� �� 100*99*98*97/6 = 15684900 ����ռ�
����λ�ñ���

int sum = 0;
for (int i = 0; i <= 96; i++)
for (int j = 0; j <= i; j++)
for (int k = 0; k <= j; k++)sum++;
sum = 156849;

���λ�� y [0,99]
����һֻ�ǵ�λ�ã������� x1[0,96] ��Ӧ�ô�2-98�������0-96��
������ֻ�Ǿ����һ�ǵ�λ�� x2[0��x1]
������ֻ�Ǿ���ڶ��ǵ�λ�� x3[0��x2]
���� y*156849 + s(s=0;for(int i=0;i<x1;i++)s+=(97-i)*(98-i)/2;) + z(z=0;for(int i=0;i<x2;i++)z+=(97-x1-i);)

*******************************************************************************************************************
ʹ�õݹ�+����������� ��ջ���
*******************************************************************************************************************
ʹ�ö���+�������

1��״̬���룬��Ҫ�Խ�ռ�״̬���б���-100�����񣬷���1���������� �� 100*99*98*97/6 = 15684900 ����ռ�
����λ�ñ��룺100�����ظ���99*98*97/6�����������������ȡһ��������������1/6

hashtable[100]
for (int i = 0; i <= 96; i++){
	sum=0;
for (int j = 0; j <= i; j++)
for (int k = 0; k <= j; k++)sum++;
hashtable[i+1]=hashtable[i]+sum;
}
hashtable[97] ���õ��� 156849

���λ�� y [0,99]
����һֻ�ǵ�λ�ã������� x1[0,96] ��Ӧ�ô�2-98�������0-96��
������ֻ�ǵ�λ�� x2[0��x1]
������ֻ�ǵ�λ�� x3[0��x2]
���� y * hashtable[r*c - 3] + hashtable[x1] + ((x2 - 1)*x2) / 2 + x3;

2��״̬���� char hashmap[15684900]; 
һ��byte��
0 0 0 0 0 0 0 0
|	��ʾ�Ƿ�����ʼ��
  |		��ʾ�Ƿ������㡪�������������������������Ƶ���ʼ��Ҳ������ʱ����ر�ץ
	| | | | ����λ��ʾ������ƶ����ĸ�������������ƶ��ĳ�ʼΪ1�����ĸ�����Ľ������0ʱ�����״̬������Ϊ����

3����������
�ȶ���ʼ����£������ƶ����״̬��־Ϊ��ʼ�㡪��״̬Ϊ��һ��bit��Ϊ1

Ȼ��ͳ�Ƶ�ǰ�����У�����ֱ�ӿ��Լ�������㡪������ĳ��λ��Ϊ'.'��������һ�������'X'��Ȼ��ʣ���油��'W'������Ϊ����������

ѭ��ȡ�������е�����״̬�������ƶ������ƶ���W����W�ƶ�������½�S�ƶ������ƶ����״̬�Ķ�Ӧĳ�������bit��Ϊ0�������״̬��״̬�����λ������ȫΪ0ʱ�������״̬�����������

ѭ����������ʼ��Ϊ����������������ץ��
���ѭ������л�û��������㡪�����������ץ��
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
int s[2], w[3][2]; //λ����Ϣ����̬����
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
char hashmap[N*N_]; //״̬�� 0��δ� ����λ�ɴ��Ժ��ʼ��Ϊ1��ÿһ��·����Ϊ0��ֱ��ȫΪ0����ʾ��״̬����״̬
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
	if (x11 > y) {//y��x11֮��
		x1--;
		if (x22 > y) {//y��x22֮��
			x2--;
			if (x33 < y)//y��x33֮��
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
	if (hashmap[temp] & 0x40)return;//�Ѿ������㡪������
	list.push(p);
	if (hashmap[temp]&0x80)//�����������㡪���ܱ�ץ
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
		//�����е������ǳ���
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

							if (s[0] > 0 && s[0] < r-1&&s[1] > 0 && s[1] < c-1&&map[s[0]][s[1]] == '.') {////ע��������1 - r-1
								//map[s[0]][s[1]] = 'S';
								int temp = map2code();
								if (!(hashmap[temp] & 0x40)) {//��������
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