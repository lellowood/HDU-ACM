#include "stdafx.h"

/*

1068 部分元素之间存在联系，找到一个元素的最大集合，要求集合中任意元素没有联系————————
请注意上面的描述——————上面的描述是图论中一个著名问题——最大独立集问题————是NP难问题——在多项式复杂度内是不可解的

补充一点知识：
图的最大独立集 = 补图的最大团 （一般图）

在二分图中：
|最小路径覆盖| = |G| - |最大匹配数| 

|最小点覆盖| = |最大匹配数|		：选出最少的点，使得能覆盖图中所有的边
证明： 每一个匹配中，都选出一个节点（匹配的两端不可能同时有为匹配的点）放入覆盖集中，则前者大于等于后者
		先将最大匹配中，每一个匹配中一个有位匹配节点的节点放入最小点覆盖中，如果最小覆盖点中有某一个点不是这种方式得到的，那么它一定有一条边没有统计在最大匹配中，这与最大匹配矛盾，所以前者一定小于等于后者
		总之，两者相等
		
|最大独立集| = |G| - |最大匹配数|


|最小支配集|
*/

#include <stdio.h>

#define N 500

int n;

int map[N][N];

bool	state[N];		//在当前状态下，该节点是否被访问过
int		link[N];		//记录之前n与p的连接


bool find(int x) {
	for (int i = 1; i <= map[x][0]; i++) {
		if (!state[map[x][i]]) {
			state[map[x][i]] = 1;
			if (!link[map[x][i]] || find(link[map[x][i]])) {
				link[map[x][i]] = x;
				return 1;
			}
		}
	}
	return 0;
};

int match() {
	int mat = 0;
	for (int i = 1; i <= n; i++) {
		memset(state, 0, sizeof(state));
		if (find(i))mat++;
	}
	return mat;
};

int main() {

	int x, y;
	freopen("data.txt", "r", stdin);
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++) {
			scanf("%d: (%d)", &x, &y);
			x++;
			map[x][0] = y;
			for (int j = 1; j <= y; j++) {
				scanf("%d", map[x] + j);
				map[x][j]++;
			}
		}
		memset(link, 0, sizeof(link));
		printf("%d\n", n - match()/2);
	}
	return 0;
}