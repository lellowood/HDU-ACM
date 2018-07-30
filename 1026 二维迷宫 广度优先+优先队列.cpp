#include "stdafx.h"

#include "stdio.h"
#include "string.h"
/*
1026 迷宫最短路径搜索
有一个陷阱：最开始的位置没有消耗，但最后的位置是不一定的
*/
#define _Inf -0x7fffffff
#define MAX(a,b) a>b?a:b

#define N 106
#define M 105

int n, m;

//地图
char map[M][N] = { 0 };
//地图备份
bool bmap[M][N] = { 0 };
//时间 到达[i][j]位置的最少时间
unsigned tmap[M][N] = { 0 };
//上一节点 到达[i][j]位置的用时最少的上一节点 1 上 2 下 3 左 4 右 5 自己冒出来的
char smap[M][N] = { 0 };
//回溯路径
char path[M*N][2];


struct queue_node {
	unsigned pos_x, pos_y;
	unsigned times;
	queue_node * next;
	queue_node * prev;
	friend bool operator< (const queue_node a, const queue_node b) { //重载<操作
		return (a.times < b.times);
	};
	queue_node(unsigned x, unsigned y, unsigned t) :pos_x(x), pos_y(y), times(t) { next = NULL; prev = NULL; }
};


//优先队列
struct queue_list {
	unsigned node_num;
	queue_node * head;	//队列头
	queue_node * tail;	//队列尾
	void push_node(queue_node * newnode) {
		node_num++;
		if (node_num == 1&&head == NULL&&tail == NULL) {
			head = tail = newnode;
			return;
		}
		queue_node * cur = tail;
		while (cur != NULL&&(*newnode < *cur))cur = cur->prev;//寻找插入位置
		if (cur == NULL) {	//cur是队列的最头上
			newnode->next = head;
			head->prev = newnode;
			head = newnode;
		}
		else {
			newnode->prev = cur;
			newnode->next = cur->next;
			if (cur->next != NULL)
				cur->next->prev = newnode;
			else //cur是tail
				tail = newnode;
			cur->next = newnode;
		}
	};
	queue_node * pop_node() {
		if (node_num < 1)return NULL;
		node_num--;
		queue_node * cur = head;
		head = head->next;
		if (head != NULL)head->prev = NULL;
		if (node_num == 0)head = tail = NULL;
		return cur;
	};
	unsigned getnum() { return node_num; };
};


bool bfs() {
	//这里使用的广度优先
	queue_list list = { 0,NULL,NULL };
	queue_node * node;
	node = new queue_node(0, 0, 0);
	list.push_node(node);
	while (list.getnum() > 0) {
		node = list.pop_node();
		//能这么做的原因是起点和终点一定不在一个点
		if (node->pos_x == m - 1 && node->pos_y == n - 1)//到达目的地
			return true;
		bmap[node->pos_x][node->pos_y] = 0;//封存这个位置
		//上下左右
		if (node->pos_x > 0 && map[node->pos_x - 1][node->pos_y] != 'X'&& bmap[node->pos_x - 1][node->pos_y]) {///////////////////上
			queue_node * cnode = NULL;
			unsigned time = 1 + node->times;
			if (map[node->pos_x - 1][node->pos_y] != '.')//有怪兽
				time += map[node->pos_x - 1][node->pos_y] - '0';
			if (tmap[node->pos_x - 1][node->pos_y] > time) {//如果比以往的值大
				tmap[node->pos_x - 1][node->pos_y] = time;
				smap[node->pos_x - 1][node->pos_y] = 1;
				cnode = new queue_node(node->pos_x - 1, node->pos_y, time);
				list.push_node(cnode);
			}
		}
		if (node->pos_x < m-1 && map[node->pos_x + 1][node->pos_y] != 'X'&& bmap[node->pos_x + 1][node->pos_y]) {///////////////////下
			queue_node * cnode = NULL;
			unsigned time = 1 + node->times;
			if (map[node->pos_x + 1][node->pos_y] != '.')//有怪兽
				time += map[node->pos_x + 1][node->pos_y] - '0';
			if (tmap[node->pos_x + 1][node->pos_y] > time) {//如果比以往的值大
				tmap[node->pos_x + 1][node->pos_y] = time;
				smap[node->pos_x + 1][node->pos_y] = 2;
				cnode = new queue_node(node->pos_x + 1, node->pos_y, time);
				list.push_node(cnode);
			}
		}
		if (node->pos_y > 0 && map[node->pos_x][node->pos_y - 1] != 'X'&& bmap[node->pos_x][node->pos_y - 1]) {///////////////////左
			queue_node * cnode = NULL;
			unsigned time = 1 + node->times;
			if (map[node->pos_x][node->pos_y - 1] != '.')//有怪兽
				time += map[node->pos_x][node->pos_y - 1] - '0';
			if (tmap[node->pos_x][node->pos_y - 1] > time) {//如果比以往的值大
				tmap[node->pos_x][node->pos_y - 1] = time;
				smap[node->pos_x][node->pos_y - 1] = 3;
				cnode = new queue_node(node->pos_x, node->pos_y - 1, time);
				list.push_node(cnode);
			}
		}
		if (node->pos_y < n-1 && map[node->pos_x][node->pos_y + 1] != 'X'&& bmap[node->pos_x][node->pos_y + 1]) {///////////////////右
			queue_node * cnode = NULL;
			unsigned time = 1 + node->times;
			if (map[node->pos_x][node->pos_y + 1] != '.')//有怪兽
				time += map[node->pos_x][node->pos_y + 1] - '0';
			if (tmap[node->pos_x][node->pos_y + 1] > time) {//如果比以往的值大
				tmap[node->pos_x][node->pos_y + 1] = time;
				smap[node->pos_x][node->pos_y + 1] = 4;
				cnode = new queue_node(node->pos_x, node->pos_y + 1, time);
				list.push_node(cnode);
			}
		}
		delete node;
	}
	return false;
};

//void bfs() {
//	//这里使用的广度优先
//	queue_list list = { 0,NULL,NULL };
//	queue_node * node = new queue_node(0, 0, 0);
//	list.push_node(node);
//	while (list.getnum() > 0) {
//		node = list.pop_node();
//		//在这里判定没有在下面判定时间快，因为下面一旦达到就结束，这里达到了还需要执行前面的
//		//if (node->pos_x == m - 1 && node->pos_y == n - 1)//到达目的地
//		//	return;
//		map[node->pos_x][node->pos_y] = 'X';//封存这个位置
//											//上下左右
//		if (node->pos_x > 0 && map[node->pos_x - 1][node->pos_y] != 'X') {///////////////////上
//			queue_node * cnode = NULL;
//			unsigned time = 1 + node->times;
//			if (map[node->pos_x - 1][node->pos_y] != '.')//有怪兽
//				time += map[node->pos_x - 1][node->pos_y] - '0';
//			if (tmap[node->pos_x - 1][node->pos_y] != 0 && tmap[node->pos_x - 1][node->pos_y] > time) {//如果比以往的值大
//				tmap[node->pos_x - 1][node->pos_y] = time;
//				smap[node->pos_x - 1][node->pos_y] = 1;
//				cnode = new queue_node(node->pos_x - 1, node->pos_y, time);
//				list.push_node(cnode);
//			}
//		}
//		if (node->pos_x < m - 1 && map[node->pos_x + 1][node->pos_y] != 'X') {///////////////////下
//			queue_node * cnode = NULL;
//			unsigned time = 1 + node->times;
//			if (map[node->pos_x + 1][node->pos_y] != '.')//有怪兽
//				time += map[node->pos_x + 1][node->pos_y] - '0';
//			if (tmap[node->pos_x + 1][node->pos_y] != 0 && tmap[node->pos_x + 1][node->pos_y] > time) {//如果比以往的值大
//				tmap[node->pos_x + 1][node->pos_y] = time;
//				smap[node->pos_x + 1][node->pos_y] = 1;
//				cnode = new queue_node(node->pos_x + 1, node->pos_y, time);
//				list.push_node(cnode);
//			}
//		}
//		if (node->pos_y > 0 && map[node->pos_x][node->pos_y - 1] != 'X') {///////////////////左
//			queue_node * cnode = NULL;
//			unsigned time = 1 + node->times;
//			if (map[node->pos_x][node->pos_y - 1] != '.')//有怪兽
//				time += map[node->pos_x][node->pos_y - 1] - '0';
//			if (tmap[node->pos_x][node->pos_y - 1] != 0 && tmap[node->pos_x][node->pos_y - 1] > time) {//如果比以往的值大
//				tmap[node->pos_x][node->pos_y - 1] = time;
//				smap[node->pos_x][node->pos_y - 1] = 1;
//				cnode = new queue_node(node->pos_x, node->pos_y - 1, time);
//				list.push_node(cnode);
//			}
//		}
//		if (node->pos_x < n - 1 && map[node->pos_x][node->pos_y + 1] != 'X') {///////////////////右
//			queue_node * cnode = NULL;
//			unsigned time = 1 + node->times;
//			if (map[node->pos_x][node->pos_y + 1] != '.')//有怪兽
//				time += map[node->pos_x][node->pos_y + 1] - '0';
//			if (tmap[node->pos_x][node->pos_y + 1] != 0 && tmap[node->pos_x][node->pos_y + 1] > time) {//如果比以往的值大
//				tmap[node->pos_x][node->pos_y + 1] = time;
//				smap[node->pos_x][node->pos_y + 1] = 1;
//				cnode = new queue_node(node->pos_x, node->pos_y + 1, time);
//				list.push_node(cnode);
//			}
//		}
//		delete node;
//	}
//};

int backtracing() {
	if (tmap[m - 1][n - 1] == 0)//目标点不能达到
		return false;
	int x = m - 1, y = n - 1;
	int steps = 1;
	path[0][0] = x;
	path[0][1] = y;
	while (x != 0 || y != 0) {
		switch (smap[x][y])
		{
		case 1:
			x = x + 1;
			break;
		case 2:
			x = x - 1;
			break;
		case 3:
			y = y + 1;
			break;
		case 4:
			y = y - 1;
			break;
		default:
			return 0;//出现错误！！
			break;
		}
		path[steps][0] = x;
		path[steps++][1] = y;
	}
	return steps;
};

int main() {
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d%d", &m, &n) != EOF) {	
		for (int i = 0; i < m; i++) {
			scanf("%s", map[i]);
		}
		memset(tmap, -1, sizeof(tmap));//赋极大值
		memset(bmap, 1, sizeof(bmap));//赋极大值
		if(!bfs())//不可达
			printf("God please help our poor hero.\n");
		else {
			int steps = backtracing();
			if (steps > 1) {//起码要2步
				int times = 1;
				printf("It takes %d seconds to reach the target position, let me show you the way.\n",tmap[m-1][n-1]);
				for (int i = steps - 1; i > 0; i--) {
					printf("%ds:(%d,%d)->(%d,%d)\n", times++,path[i][0],path[i][1], path[i-1][0], path[i-1][1]);
					if (map[path[i - 1][0]][path[i - 1][1]] != 'X'&&map[path[i - 1][0]][path[i - 1][1]] != '.') {
						while (map[path[i - 1][0]][path[i - 1][1]] > '0') {
							printf("%ds:FIGHT AT (%d,%d)\n", times++, path[i - 1][0], path[i - 1][1]);
							map[path[i - 1][0]][path[i - 1][1]]--;
						}
					}
				}
			}
			else {//
				printf("出现了未知的错误！\n");
			}
		}
		printf("FINISH\n");
	}
}