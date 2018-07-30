#include "stdafx.h"

/*

1083 n皇后问题的变形

看了一下评论，有高效的匈牙利算法
***********************************************************
我试试有没有更简单的方法

因为其实不需要求出具体的匹配方案，只需要验证能不能匹配

算了不写了，只写出大致思路
对关系矩阵map划横线和竖线，要求用最少的线，覆盖所有有关系的节点
如果线的数量==p，满足要求，否则不满足要求

原理：
首先有p<=n，因为如果较小的话，那么一定不行
现在要证明，p线条的覆盖是能匹配的充要条件
这是怎么得到的呢？？？不想了
*/

#include <stdio.h>
#include <string>
#define MAX(a,b) (a>b)?a:b

#define N 405
#define P 405

int n, p;

int map[P][N];

/******************************************匈牙利匹配算法**********************************************/
bool	state[N];		//在当前状态下，该节点是否被访问过
int		link[N];		//记录之前n与p的连接
bool find(int x) {
	for (int i = 1; i <= map[x][0]; i++) {
		if (!state[map[x][i]]) {
			state[map[x][i]] = 1;
			if (link[map[x][i]] == 0 || find(link[map[x][i]])) {
				link[map[x][i]] = x;
				return 1;
			}
		}
	}
	return 0;
};

bool match() {
	memset(link, 0, sizeof(link));
	for (int i = 1; i <= p; i++) {
		memset(state, 0, sizeof(state));
		if (!find(i))		//如果有一个点未找到匹配路径
			return false;
	}
	return true;
};

int main()
{
	int t;
	freopen("data.txt", "r", stdin);
	scanf("%d", &t);
	while (t--) {
		//读入数据
		scanf("%d%d", &p, &n);
		for (int i = 1; i <= p; i++) {
			scanf("%d", &map[i][0]);
			for (int j = 1; j <= map[i][0]; j++)
				scanf("%d", &map[i][j]);
		}

		//处理数据
		if (n>=p&&match())
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}


