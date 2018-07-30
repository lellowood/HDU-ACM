#include "stdafx.h"

/*

1067 挑战一下非常难得一道题
目标格式
11 12 13 14 15 16 17
21 22 23 24 25 26 27
31 32 33 34 35 36 37
41 42 43 44 45 46 47

计算初始格式到目标格式的最短步骤
步骤的定义是：只能比空格左边的值大1的才能填充到空格

在解空间中搜索最佳解
有一个需要注意的是，这个搜索过程是不可逆的，因为假设在某一步发生了移动，使得两个节点相连，无论如何操作，
都无法再让这两个节点分开（？？其实是可以分开的，如果前一个节点先发生移动，但如果前一节点发生移动，那么前一节点也应该和一个节点相连）
所以我们认为这种变化是不可逆的。

用一个char[20] = 160 bit 保存一个状态
具体而言
4*8矩阵
8列分为4份 4*2矩阵
每一个元素（11 - 47 + 【 】）用5 bit 表示，前2bit表示1-4 后3bit表示1-7 空格【】 约定为全0
如此每5个bit对应一个矩阵

堆栈溢出了
*******************************************************************************************************
每个代码能处的位置是有限的
12能在原地或者11后面呆着		2
13能在原地或者12后面呆着		3
.
.
.
22								2
...

总共有
2^24种情况

设置2^24长度的hash数组
0：原地
1：前者后面

0 0 0 0 0 0 —— 47-42
0 0 0 0 0 0 —— 37-32
0 0 0 0 0 0 —— 27-22
0 0 0 0 0 0 —— 17-12
*********************************************************************************************************
*/

//int mat[4][8];
//int smat[4][8];	//原始矩阵
//int hash[48][2];
//
//bool table[280];
//
//void mat2hash() {
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 8; j++) {
//			hash[mat[i][j]][0] = i;
//			hash[mat[i][j]][1] = j;
//		}
//	}
//};
//
//int tab() {
//	int flag = 0;
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 8; j++) {
//			flag += fabs(mat[i][j]-smat[i][j]);
//		}
//	}
//	return flag;
//};
//
//int goal[4][8] = {11,12,13,14,15,16,17,00,
//				  21,22,23,24,25,26,27,00,
//				  31,32,33,34,35,36,37,00,
//				  41,42,43,44,45,46,47,00};
//
//bool isok() {
//	for (int i = 0; i < 4; i++) 
//		for (int j = 0; j < 7; j++) 
//			if (mat[i][j] != goal[i][j])return false;
//	return true;
//};
//
//struct gap {
//	char state[21];
//	int steps;
//	gap(int s, const int mat[][8]) {
//		steps = s;
//		mat2code(mat);
//		state[20] = '\0';
//	};
//	void mat2code(const int mat[][8]) {
//		for (int i = 0; i < 4; i++) {
//			for (int s = 0; s < 3; s++) {
//				int temp = 0;
//				for (int j = 0; j < 8; j++) {
//					temp = (temp << 1) + ((mat[i][j]%10) >> s & 1);
//				}
//				state[i * 5 + s] = temp;
//			}
//			for (int s = 3; s < 5; s++) {
//				int temp = 0;
//				for (int j = 0; j < 8; j++) {
//					temp = (temp << 1) + ((mat[i][j]/10-1) >> (s-3) & 1);
//				}
//				state[i * 5 + s] = temp;
//			}
//		}
//
//		//for (int i = 0; i < 4; i++) {
//		//	for (int s = 0; s < 5; s++) {
//		//		int temp = 0;
//		//		for (int j = 0; j < 2; j++) {
//		//			for (int k = 0; k < 4; k++) {
//		//				//mat[k][i << 1 + j] >> 5
//		//				temp = (temp << 1) + ((mat[k][(i << 1) + j] >> s) & 1);
//		//				/*int temp = mat[k][i << 1 + j];
//		//				for (int s = 0; s < 5; s++) {
//		//					state[i * 5 + s] = state[i * 5 + s] | (((temp >> (4-s)) & 1) << (2 * j + k));
//		//				}*/
//		//			}
//		//		}
//		//		state[i * 5 + s] = temp;
//		//	}
//		//}
//	};
//	void code2mat(int (& mat)[4][8]) {
//		//for (int i = 0; i < 4; i++) {
//		//	for (int j = 0; j < 2; j++) {
//		//		for (int k = 0; k < 4; k++) {
//		//			mat[k][i << 1 + j] = ((state[i * 5] >> (2 * j + k)) & 1) * 16 + ((state[i * 5 + 1] >> (2 * j + k)) & 1) * 8 + ((state[i * 5 + 2] >> (2 * j + k)) & 1) * 4 + ((state[i * 5 + 3] >> (2 * j + k)) & 1) * 2 + ((state[i * 5 + 4] >> (2 * j + k)) & 1);
//		//		}
//		//	}
//		//}
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 8; j++) {
//				mat[i][7-j] = (((state[i * 5 + 4] >> j) & 1) * 2 + ((state[i * 5 + 3] >> j) & 1) * 1 + 1) * 10 + ((state[i * 5 + 2] >> j) & 1) * 4 + ((state[i * 5 + 1] >> j) & 1) * 2 + ((state[i * 5] >> j) & 1);
//			}
//		}	
//	};
//};
//
//std::queue<gap *> list;
//
//int main()
//{
//	int t;
//	int flag;
//	freopen("data.txt", "r", stdin);
//	scanf("%d", &t);
//	while (t--) {
//
//		//读入数据
//		flag = 1;
//		for (int i = 0; i < 4; i++) {
//			for (int j = 1; j < 8; j++) {
//				scanf("%d", &smat[i][j]);
//				if (smat[i][j] % 10 == 1) {
//					smat[smat[i][j] / 10 - 1][0] = smat[i][j];
//					smat[i][j] =10*(flag++);	//记录第几个空格
//				}
//			}
//		}
//
//		//初始化
//		gap *g = new gap(0,smat);
//		flag = -1;
//		memset(table, 0, sizeof(table));
//		while (!list.empty())list.pop();
//		list.push(g);
//		while (!list.empty()&&flag==-1) {
//			g = list.front();
//			list.pop();
//
//			g->code2mat(mat);
//			mat2hash();
//
//			//达到目标位置
//			if (isok())
//				flag = g->steps;
//
//			for (int i = 10; i < 50; i+=10) {//四个空格位置
//				if (mat[hash[i][0]][hash[i][1]]%10 == 0 && mat[hash[i][0]][hash[i][1]-1]%10 && (mat[hash[i][0]][hash[i][1]-1] % 10) != 7 && mat[hash[mat[hash[i][0]][hash[i][1] - 1] + 1][0]][hash[mat[hash[i][0]][hash[i][1] - 1] + 1][1]] != goal[hash[mat[hash[i][0]][hash[i][1] - 1] + 1][0]][hash[mat[hash[i][0]][hash[i][1] - 1] + 1][1]]) {
//					int kx = hash[i][0];
//					int ky = hash[i][1];
//					int cx = hash[mat[hash[i][0]][hash[i][1] - 1] + 1][0];
//					int cy = hash[mat[hash[i][0]][hash[i][1] - 1] + 1][1];
//					int temp = mat[kx][ky];
//					mat[kx][ky] = mat[cx][cy];
//					mat[cx][cy] = temp;
//					int temp1 = tab();
//					if (!table[temp1]) {
//						gap * newg = new gap(g->steps + 1, mat);
//						list.push(newg);
//						table[temp1] = 1;
//					}
//
//					//还原
//					mat[cx][cy] = mat[kx][ky];
//					mat[kx][ky] = temp;
//				}
//			}
//			delete g;
//		}
//		while (!list.empty()) {
//			g = list.front();
//			list.pop();
//			delete g;
//		}
//		//处理数据
//		printf("%d\n",flag);
//	}
//	return 0;
//}


//bool tab[48];
//int num[4];
//
//void mat2pos() {
//	int flag = 10;
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 8; j++) {
//			position[mat[i][j]][0] = i;
//			position[mat[i][j]][1] = j;
//			if (mat[i][j] == 0) {
//				position[flag][0] = i;
//				position[flag][1] = j;
//				flag += 10;
//			}
//		}
//	}
//};
//
//int find(int target, int steps) {
//	if (target % 10 == 0) { return steps; num[target / 10 - 1]++; }
//	if (position[target - 1][1] > 6 && tab[mat[position[target - 1][0]][position[target - 1][1] + 1]])return -1;
//	tab[mat[position[target - 1][0]][position[target - 1][1] + 1]] = 1;
//	return find(mat[position[target - 1][0]][position[target - 1][1] + 1], steps + 1);
//};
//
//int main()
//{
//	int t, steps;
//	int flag;
//	freopen("data.txt", "r", stdin);
//	scanf("%d", &t);
//	while (t--) {
//
//		//读入数据
//		flag = 10;
//		for (int i = 0; i < 4; i++) {
//			for (int j = 1; j < 8; j++) {
//				scanf("%d", &mat[i][j]);
//				if (mat[i][j] % 10 == 1) {
//					mat[mat[i][j] / 10 - 1][0] = mat[i][j];
//					mat[i][j] =flag;	//记录第几个空格
//					flag += 10;
//				}
//			}
//		}
//
//		//初始化
//		flag = -1;
//		steps = -1;
//
//		while (flag==-1) {
//			mat2pos();
//
//			int min = 12341234123;
//			int target;
//			memset(num, 0, sizeof(num));
//			for (int i = 0; i < 4; i++) {
//				for (int j = 0; j < 6; j++) {
//					if (mat[i][j] == goal[i][j] && mat[i][j + 1] != goal[i][j + 1]) {
//						memset(tab, 0, sizeof(tab));
//						int step = find(mat[i][j] + 1, 0);
//						//if (step < min) { min = step; target = mat[i][j]; }
//					}
//				}
//			}
//			int max = 0;
//			int pos = -1;
//			for (int i = 0; i < 4; i++) {
//				if (num[i] > max) {
//					max = num[i];
//					pos = (i + 1) * 10;
//				}
//			}
//			for (int i = 10; i < 50; i+=10) {//四个空格位置
//				if (mat[position[i][0]][position[i][1]]%10 == 0 && mat[position[i][0]][position[i][1]-1]%10 && (mat[position[i][0]][position[i][1]-1] % 10) != 7) {
//					int kx = position[i][0];
//					int ky = position[i][1];
//					int cx = position[mat[position[i][0]][position[i][1] - 1] + 1][0];
//					int cy = position[mat[position[i][0]][position[i][1] - 1] + 1][1];
//					mat[kx][ky] = mat[cx][cy];
//					mat[cx][cy] = i;
//					position[i][0] = cx;
//					position[i][1] = cy;
//					position[mat[kx][ky - 1] + 1][0] = kx;
//					position[mat[kx][ky - 1] + 1][1] = ky;
//					int temp = mat2hash();
//					if (!table[temp]) {
//						gap * newg = new gap(g->steps + 1, temp);
//						list.push(newg);
//						table[temp] = 1;
//						if (temp == 0)
//							flag = g->steps + 1;
//					}
//					//还原
//					mat[cx][cy] = mat[kx][ky];
//					mat[kx][ky] = i;
//					position[i][0] = kx;
//					position[i][1] = ky;
//					position[mat[kx][ky - 1] + 1][0] = cx;
//					position[mat[kx][ky - 1] + 1][1] = cy;
//				}
//			}
//			delete g;
//		}
//		while (!list.empty()) {
//			g = list.front();
//			list.pop();
//			delete g;
//		}
//		//处理数据
//		printf("%d\n",flag);
//	}
//	return 0;
//}


/*********************************
最后解决还是参考的别人的代码，在我的设想中，是想
将所有的情况用一种编码代替的，这次终于见识到碰撞哈希的应用，而且花了四五天时间，非常有感触！最后能通过我也感谢天感谢地！

字符串hash的博客
https://blog.csdn.net/g1036583997/article/details/51910598
**********************************/
#include <stdio.h>
#include <string>
#include <queue>
#define MAX(a,b) (a>b)?a:b

#define MAXN	1324124

#define MOD		245665


char goal[20] = { -86, 102, 30, 0, 0, - 86, 102, 30, - 1, 0, - 86, 102, 30, 0, - 1, - 86, 102, 30, - 1, - 1 };

int mat[4][8];

int position[48][2];

int head, tail;

int hashid;


void mat2pos() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			position[mat[i][j]][0] = i;
			position[mat[i][j]][1] = j;
		}
	}
};

int DJBHash(const char *state)
{
	register size_t hash = 5381;
	for (int i = 0; i < 20; i++)
	{
		int ch = (int)*state++;
		hash += (hash << 5) + ch;
	}
	return hash;
};

size_t BKDRHash(const char *state)
{
	register size_t hash = 0;
	for (int i = 0; i < 20; i++)
	{
		int ch = (int)*state++;
		hash = hash * 131 + ch;
	}
	return hash;
};


//一个状态节点
struct gap {
	char state[20];
	int steps;
	size_t hash;
	void init(int s) {
		steps = s;
		mat2code();
		//hash = DJBHash(state);
		hash = BKDRHash(state);
	};
	void mat2code() {
		for (int i = 0; i < 4; i++) {
			for (int s = 0; s < 3; s++) {
				int temp = 0;
				for (int j = 0; j < 8; j++) {
					temp = (temp << 1) + ((mat[i][j]%10) >> s & 1);
				}
				state[i * 5 + s] = temp;
			}
			for (int s = 3; s < 5; s++) {
				int temp = 0;
				for (int j = 0; j < 8; j++) {
					temp = (temp << 1) + ((mat[i][j]/10-1) >> (s-3) & 1);
				}
				state[i * 5 + s] = temp;
			}
		}
	};
	void code2mat() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				mat[i][7-j] = (((state[i * 5 + 4] >> j) & 1) * 2 + ((state[i * 5 + 3] >> j) & 1) * 1 + 1) * 10 + ((state[i * 5 + 2] >> j) & 1) * 4 + ((state[i * 5 + 1] >> j) & 1) * 2 + ((state[i * 5] >> j) & 1);
			}
		}
	};
	bool operator == (const gap &g) {
		for (int i = 0; i < 20; i++) {
			if (state[i] != g.state[i])return false;
		}
		return true;
	};
	bool isok() {
		for (int i = 0; i < 20; i++)
			if ((state[i]>>1) != (goal[i]>>1))return false;
		return true;
	};
} node[MAXN];

struct hashnode {
	int gapid, next;
} list[MAXN];


int findhash() {
	int temp = node[tail].hash % MOD;
	while (list[temp].next != 0) {
		if (node[tail].hash == node[list[temp].gapid].hash&&node[tail] == node[list[temp].gapid])
			return -1;
		temp = list[temp].next;
	}
	return temp;
};


int main(){
	int t;
	int flag;
	freopen("data.txt", "r", stdin);
	scanf("%d", &t);
	while (t--) {

		//读入数据
		flag = 10;
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j < 8; j++) {
				scanf("%d", &mat[i][j]);
				if (mat[i][j] % 10 == 1) {
					mat[mat[i][j] / 10 - 1][0] = mat[i][j];
					mat[i][j] =flag;	//记录第几个空格
					flag += 10;
				}
			}
		}

		//初始化
		//gap g = gap(0, mat2hash());
		flag = -1;
		hashid = MOD;
		head = 0;
		tail = 0;
		memset(list, 0, sizeof(list));

		node[tail].init(0);
		int temp = findhash();
		list[temp].gapid = tail++;
		list[temp].next = hashid++;

		while (head < tail && flag==-1) {

			node[head].code2mat();
			mat2pos();

			//达到目标位置
			if (node[head].isok())
				flag = node[head].steps;

			for (int i = 10; i < 50; i+=10) {//四个空格位置
				if (mat[position[i][0]][position[i][1]]%10 == 0 && mat[position[i][0]][position[i][1]-1]%10 && (mat[position[i][0]][position[i][1]-1] % 10) != 7) {
					int kx = position[i][0];
					int ky = position[i][1];
					int cx = position[mat[position[i][0]][position[i][1] - 1] + 1][0];
					int cy = position[mat[position[i][0]][position[i][1] - 1] + 1][1];
					mat[kx][ky] = mat[cx][cy];
					mat[cx][cy] = i;
					position[i][0] = cx;
					position[i][1] = cy;
					position[mat[kx][ky - 1] + 1][0] = kx;
					position[mat[kx][ky - 1] + 1][1] = ky;
					node[tail].init(node[head].steps + 1);
					
					int temp = findhash();

					if (temp != -1) {
						if (node[tail].isok())
							flag = node[tail].steps;
						list[temp].gapid = tail++;
						list[temp].next = hashid++;
					}
					
					//还原
					mat[cx][cy] = mat[kx][ky];
					mat[kx][ky] = i;
					position[i][0] = kx;
					position[i][1] = ky;
					position[mat[kx][ky - 1] + 1][0] = cx;
					position[mat[kx][ky - 1] + 1][1] = cy;
				}
			}
			head++;
		}
		//处理数据
		printf("%d\n",flag);
	}
	return 0;
}

