#include "stdafx.h"

/*
1043 迷宫移动寻找匹配值的方法
因为有9个数，将x换为9，哈希映射维987654321个
在解空间之内只能用广度优先遍历寻找，因为深度空间是一直寻找
********************************************************************
提交一次，超出内存限制

需要压缩一下hash表
有一个方法和1027是类似的，那个是求第m个数字，这里是求数字是排第几
后来看了一下博客才知道这种方法竟然很有名：康拓展开
********************************************************************
超时了！！！！！！！
看了一下评论，主要是因为unsolve的情况
我想采用对目标12345678x进行展开对所有能达到的情况进行记录
********************************************************************
看了一下讨论，发现了一种方式：
1 2 3
4 5 6
7 8 x
每次只考虑一行和最后一行的关系，先把1 2 3排序好，再处理6 7 8的情况
用时是质的飞跃
********************************************************************
*/

#include "stdio.h"
#include "string.h"
#include <queue>	//第一次用queue模板

#define N 362890 //362880 = 1*2*3*4*5*6*7*8*9
//哈希表
unsigned table[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880 };	//来源于 1027——有一个专业名词 康拓展开
unsigned exps[] = { 100000000, 10000000, 1000000, 100000, 10000, 1000, 100, 10, 1 };

int hash(int value) {
	if (value < 123456789 || value>987654321)return -1;
	int pos = 0, th, temp;
	bool flag[10] = { 0 };
	int bit[10];
	for (int i = 8; i >= 0 && value; i--, value /= 10) {
		bit[i] = value % 10;
	}
	for (int i = 0; i < 9; i++) {
		th = 0;
		flag[bit[i]] = 1;
		for (int j = 1; j < bit[i]; j++) {
			if (!flag[j])
				th++;
		}
		pos += th*table[8 - i];
	}
	return pos;
};

bool solve[N] = { 0 };
//到达j位置的来源：d、u、l、r四个值
char ori[N] = { 0 };
//路径
char path[1000];

//0 1 2
//3 4 5
//6 7 8
void neighbor(int value, int & d, int & u, int & l, int & r) {//数字转换为矩阵——并完成移动
	if (value < 123456789 || value>987654321)return;
	int matrix[9];
	int pos;
	int temp = value;
	for (int i = 8; i >= 0; i--){
			matrix[i] = temp % 10;
			temp /= 10;
			if (matrix[i] == 9) { pos = i; }
	}
	d = u = l = r = -1;
	if (pos < 6) 
		d = value - (9 - matrix[pos + 3]) * 999 * exps[pos + 3];
	if (pos > 2) 
		u = value + (9 - matrix[pos - 3]) * 999 * exps[pos];
	if (pos != 2 && pos != 5 && pos != 8) 
		r = value - (9 - matrix[pos + 1]) * 9 * exps[pos + 1];
	if (pos != 0 && pos != 3 && pos != 6) 
		l = value + (9 - matrix[pos - 1]) * 9 * exps[pos];
};

//void dfs(int value) {
//	int  d, u, r, l;
//	neighbor(value, d, u, l, r);
//	int hd = hash(d), hu = hash(u), hr = hash(r), hl = hash(l);
//	solve[hd] = solve[hu] = solve[hl] = solve[hr] = 1;//这四者可达
//	ori[hash(value)] = 1;
//	if (hd != -1 && !ori[hd])dfs(d);
//	if (hu != -1 && !ori[hu])dfs(u);
//	if (hl != -1 && !ori[hl])dfs(l);
//	if (hr != -1 && !ori[hr])dfs(r);
//};

int bfs_solve(int value) {
	int  d, u, r, l;
	std::queue<int> list;
	list.push(value);
	int step = 0;
	solve[0] = 1;
	while (!list.empty()) {
		value = list.front();
		list.pop();
		neighbor(value, d, u, l, r);
		int hd = hash(d), hu = hash(u), hr = hash(r), hl = hash(l);	
		//if (hd != -1 && !solve[hd]){list.push(d); solve[hd] = 1;  }
		//if (hu != -1 && !solve[hu]){list.push(u); solve[hu] = 1;  }
		//if (hl != -1 && !solve[hl]){list.push(l); solve[hl] = 1;  }
		//if (hr != -1 && !solve[hr]){list.push(r); solve[hr] = 1;  }
		if (hu != -1 && !ori[hu]) { list.push(u); ori[hu] = 'u'; }
		if (hl != -1 && !ori[hl]) { list.push(l); ori[hl] = 'l'; }
		if (hd != -1 && !ori[hd]) { list.push(d); ori[hd] = 'd'; }
		if (hr != -1 && !ori[hr]) { list.push(r); ori[hr] = 'r'; }
		//printf("%d %d\n", step++,value);
	}
	return 0;
};


//int bfs(int value) {
//	if (value == 123456789)//最开始就是正确的
//		return 1;
//	int  d, u, r, l;
//	std::queue<int> list;
//	list.push(value);
//	while (!list.empty()) {
//		value = list.front();
//		list.pop();
//		neighbor(value, d, u, l, r);
//		if (d == 123456789 || u == 123456789 || l == 123456789 || r == 123456789)
//			return 1;
//		if (!ori[hash(d)])list.push(d);
//		if (!ori[hash(u)])list.push(u);
//		if (!ori[hash(l)])list.push(l);
//		if (!ori[hash(r)])list.push(r);
//	}
//	return 0;
//};
//
//int backtracing(int value) {
//	int cur = 123456789;
//	int steps = 0;
//	char matrix[3][3];
//	int x, y;
//	while (cur != value) {
//		path[steps] = ori[hash(cur)];
//		for (int i = 2; i >= 0; i--)
//			for (int j = 2; j >= 0; j--) {
//				matrix[i][j] = cur % 10;
//				cur /= 10;
//				if (matrix[i][j] == 9) { x = i; y = j; }
//			}
//		if (path[steps] == 'd') {
//			matrix[x][y] = matrix[x - 1][y];
//			matrix[x - 1][y] = 9;
//		}
//		else if (path[steps] == 'u') {
//			matrix[x][y] = matrix[x + 1][y];
//			matrix[x + 1][y] = 9;
//		}
//		else if (path[steps] == 'r') {
//			matrix[x][y] = matrix[x][y - 1];
//			matrix[x][y - 1] = 9;
//		}
//		else {
//			matrix[x][y] = matrix[x][y + 1];
//			matrix[x][y + 1] = 9;
//		}
//		cur = 0;
//		for (int i = 0; i < 3; i++)
//			for (int j = 0; j < 3; j++)
//				cur = cur * 10 + matrix[i][j];
//		steps++;
//	}
//	return steps;
//};

int backtracing(int value) {
	int steps = 0;
	int  d, u, r, l;
	while (value != 123456789) {
		path[steps] = ori[hash(value)];
		neighbor(value, d, u, l, r);
		if (path[steps] == 'd') {value = u; path[steps] = 'u';	}
		else if (path[steps] == 'u') {value = d; path[steps] = 'd';	}
		else if (path[steps] == 'r') {value = l; path[steps] = 'l';	}
		else {value = r; path[steps] = 'r';	}
		steps++;
	}
	return steps;
};


int main() {
	int value;
	char ch;
	memset(solve, 0, sizeof(solve));//赋初值
	bfs_solve(123456789);
	freopen("data.txt", "r", stdin);// 
	while (scanf("%c ", &ch) != EOF) {
		value = 0;
		//memset(ori, 0, sizeof(ori));//赋初值
		if (ch != 'x')
			value = value * 10 + ch - '0';
		else
			value = value * 10 + 9;
		for (int i = 1; i < 9; i++) {
			scanf(" %c ", &ch);
			if (ch != 'x')
				value = value * 10 + ch - '0';
			else
				value = value * 10 + 9;
		}
		//ori[hash(value)] = 1;
		//if (solve[hash(value)]&&bfs(value)) {
		if (ori[hash(value)]) {
			value = backtracing(value);
			for (int i = 0; i < value; i++)
				printf("%c", path[i]);
		}
		else printf("unsolvable");
		printf("\n");
	}
	return 0;
}