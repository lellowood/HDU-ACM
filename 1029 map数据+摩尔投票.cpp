#include "stdafx.h"

/*
1029 本来应该是用map
后来看到一种有意思的方法：摩尔投票
如果出现的数字超过了总数的一半，那么这个数字就有实力干翻剩下所有的数字
*/

#include "stdio.h"
#include "string.h"
#define _Inf -0x7fffffff
#define MAX(a,b) a>b?a:b

#define N 1000100

int n;


////一般的方法
//int map[N] = { 0 };
//
//int main() {
//	int max, pos, temp;
//	freopen("data.txt", "r", stdin);// 
//	while (scanf("%d", &n) != EOF) {
//		max = 0;
//		memset(map, 0, sizeof(map));
//		for (int i = 0; i < n; i++) {
//			scanf("%d", &temp);
//			map[temp]++;
//			if (map[temp] > max) { max = map[temp]; pos = temp; }
//		}
//		printf("%d\n", pos);
//	}
//	return 0;
//}


//摩尔投票
int main() {
	int max, pos, temp;
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d", &n) != EOF) {
		max = 0;
		pos = -1;
		for (int i = 0; i < n; i++) {
			scanf("%d", &temp);
			if (max == 0) { max = 1; pos = temp; }
			else if (temp == pos)max++;
			else max--;//只有有数量超过一半的数字才能最后留下来
		}
		printf("%d\n", pos);
	}
	return 0;
}