#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1101
题意：二维空间中输入一个大矩形，一个小矩形，一个点。小矩形和点都在大矩形范围内，点可以沿着任意直线移动，在第一次碰到大矩形边缘时会反弹。
输出 点随机移动，碰到小矩形的概率是多少

********************************************************************************
题意理解错误，我以为每次区域内只有一个矩形，实际上是有很多（n个）矩形
********************************************************************************
是逻辑错误了
最开始我设想对每条边分别计算四个点儿对应的点，然后计算点之间的线段集合 利用atan函数得到角度
不过这种方式的错误在于总共四个点对于一个中心只有四个映射点，在四条边界上是不行的
********************************************************************************

再次错误！错误的原因在于当点位于大矩形的边界上时，折射角度计算不了！
********************************************************************************
最后只能采用别人对称的思路，将goal区域和四边映射四个对称区域，然后计算。。。妥协了
其中还有一些点需要注意，比如在0/pi2分界线的判断
*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <stack>
#include <vector>

#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define SUB(x,y) (x>y?(x-y):(y-x))
#define N 1005
#define Pi2 6.28318530717958647692
#define Pi 3.14159265358979323846
int line[2][2];

int rect[2][2];

int point[2];

double angle;


struct stack_node {
	unsigned int symbol;
	double pos;
	stack_node * next;
	stack_node * prev;
	friend bool operator < (const stack_node a, const stack_node b) { return a.pos < b.pos; };
	stack_node(unsigned int s, double p) :symbol(s), pos(p), next(NULL), prev(NULL) {};
};

struct stack_list {
	unsigned int node_num;
	stack_node * head;
	stack_node * tail;
	void push_node(double pos_l, double pos_r) {
		node_num += 2;
		if (node_num == 2 && head == NULL && tail == NULL) {
			head = new stack_node(0, pos_l);
			tail = new stack_node(1, pos_r);
			head->next = tail;
			tail->prev = head;
			return;
		}
		stack_node * cur = tail;
		stack_node * node_l = new stack_node(0, pos_l);
		stack_node * node_r = new stack_node(1, pos_r);
		while (cur != NULL && (pos_l < (*cur).pos)) cur = cur->prev;//寻找插入位置
		if (cur == NULL) {    //cur是队列的最头上
			node_l->next = head;
			if (head != NULL) head->prev = node_l;
			head = node_l;
		}
		else {
			node_l->prev = cur;
			node_l->next = cur->next;
			if (cur->next != NULL)
				cur->next->prev = node_l;
			else //cur是tail
				tail = node_l;
			cur->next = node_l;
		}
		cur = tail;
		while (cur != NULL && (pos_r < (*cur).pos)) cur = cur->prev;//寻找插入位置
		if (cur == NULL) {    //cur是队列的最头上
			node_r->next = head;
			if (head != NULL) head->prev = node_r;
			head = node_r;
		}
		else {
			node_r->prev = cur;
			node_r->next = cur->next;
			if (cur->next != NULL)
				cur->next->prev = node_r;
			else //cur是tail
				tail = node_r;
			cur->next = node_r;
		}
		if (node_l->next != NULL && node_l->next->symbol == 0)node_l = node_l->next;
		while (node_l != NULL && node_l->symbol == 0 && node_l->prev != NULL && node_l->prev->symbol == 0 && node_l->next != NULL && node_l->next->symbol == 1) {
			cur = node_l->prev;
			node_l->prev->next = node_l->next->next;
			if (node_l->next->next != NULL)
				node_l->next->next->prev = node_l->prev;
			node_num -= 2;
			delete node_l->next;
			delete node_l;
			node_l = cur->next;
		}
	};
	void calangle() {
		stack_node * cur = head;
		stack_node * temp;
		while (cur != NULL && cur->next != NULL) {
			temp = cur;
			if (cur->symbol == 0 && cur->next->symbol == 1) {
				angle += cur->next->pos - cur->pos;
				//printf("%lf %lf\n", cur->pos, cur->next->pos);
				if (angle > Pi2)angle = Pi2;
				cur = cur->next->next;
				delete temp->next;
				delete temp;
			}
			else {
				//出错了
				cur = cur->next;
				delete temp;
			}
		}
		while (cur != NULL) {
			temp = cur;
			cur = cur->next;
			delete temp;
		}
		head = tail = NULL;
		node_num = 0;
	};
} list;


void calrange() {
	double x_[] = { rect[0][0], rect[1][0], rect[0][0], rect[1][0] };
	double y_[] = { rect[0][1], rect[1][1], rect[1][1], rect[0][1] };
	double a = point[0];
	double b = point[1];
	double zmax = -N, zzmax = -N;
	double zmin = N, zzmin = N;
	//判断点a，b是否在矩形内
	if (((x_[0] - a)*(a - x_[1]) >= 0) && ((y_[0] - b)*(b - y_[1]) >= 0)) {
		list.push_node(0, Pi2);
		return;
	}
	for (int k = 0; k < 2; k++) {
		double y = line[k][1] * 2;
		double fmax = -N;
		double fmin = N;
		for (int i = 0; i < 4; i++) {
			double ang = atan2(y - y_[i], x_[i]);
			if (ang < 0)ang += Pi2;
			if (ang > fmax)fmax = ang;
			if (ang < fmin)fmin = ang;
		}
		list.push_node(fmin, fmax);
	}

	for (int k = 0; k < 2; k++) {
		double x = line[k][0] * 2;
		double fmax = -N, ffmax = -N;
		double fmin = N, ffmin = N;
		for (int i = 0; i < 4; i++) {
			double ang = atan2(y_[i], x - x_[i]);
			if (ang < 0)ang += Pi2;
			if (ang > fmax) {
				ffmax = fmax; fmax = ang;
			}
			else if (ang > ffmax) ffmax = ang;
			if (ang < fmin) {
				ffmin = fmin;	fmin = ang;
			}
			else if (ang < ffmin)ffmin = ang;
		}
		if (fmax - fmin > Pi) {
			list.push_node(0, ffmin);
			list.push_node(ffmax, Pi2);
		}
		else
			list.push_node(fmin, fmax);
	}
	for (int i = 0; i < 4; i++) {
		double ang = atan2(y_[i], x_[i]);
		if (ang < 0)ang += Pi2;
		if (ang > zmax) {
			zzmax = zmax; zmax = ang;
		}
		else if (ang > zzmax)zzmax = ang;
		if (ang < zmin) {
			zzmin = zmin; zmin = ang;
		}
		else if (ang < zzmin)zzmin = ang;
	}
	if (zmax - zmin > Pi) {
		list.push_node(0, zzmin);
		list.push_node(zzmax, Pi2);
	}
	else list.push_node(zmin, zmax);
};


int main() {
	int t, n;
	freopen("data.txt", "r", stdin);
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d", line, (*line) + 1, line + 1, (*(line + 1)) + 1);
		if (line[0][0] > line[1][0]) {
			int temp = line[1][0];
			line[1][0] = line[0][0];
			line[0][0] = temp;
		}
		if (line[0][1] > line[1][1]) {
			int temp = line[1][1];
			line[1][1] = line[0][1];
			line[0][1] = temp;
		}
		scanf("%d %d", point, point + 1);
		line[0][0] -= point[0];
		line[0][1] -= point[1];
		line[1][0] -= point[0];
		line[1][1] -= point[1];
		scanf("%d", &n);
		angle = 0;
		while (n--) {
			scanf("%d %d %d %d", rect, (*rect) + 1, rect + 1, (*(rect + 1)) + 1);
			rect[0][0] -= point[0];
			rect[0][1] -= point[1];
			rect[1][0] -= point[0];
			rect[1][1] -= point[1];
			calrange();
		}
		list.calangle();
		printf("%.2lf%%\n", (100 * angle) / Pi2);
	}
	return 0;
}