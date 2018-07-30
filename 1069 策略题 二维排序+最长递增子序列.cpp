#include "stdafx.h"

/*
1069 排序

猴子玩n积木 积木有 xi, yi, zi 表示长宽高（搭建的时候可以旋转使得任意两个值作为基部尺寸），用这些积木搭建一个塔，要求上一块积木的
基部尺寸完全小于下一块积木的，输出能搭建的最大高度




*/

#include <stdio.h>
#define MAX(a,b) (a>b?a:b)
#define N 95

int n;

int block[N][3];

int	dp[N] = { 0 };

void sort3(int &l, int &w, int &h) {
	if (l > w) {
		l = l + w;
		w = l - w;
		l = l - w;
	}
	if (w > h) {
		h = h + w;
		w = h - w;
		h = h - w;
		if (l > w) {
			l = l + w;
			w = l - w;
			l = l - w;
		}
	}
};

int main() {

	int max, h, w, l, t = 1;
	freopen("data.txt", "r", stdin);
	while (scanf("%d", &n) != EOF&&n) {
		max = 0;
		n *= 3;
		for (int i = 0; i < n; i+=3) {
			scanf("%d %d %d", &l, &w, &h);
			//三者排序
			sort3(l, w, h);
			//插入排序
			int j;
			for (j = i - 1; j >= 0&&block[j][0] > w; j--) {
				//腾出两个位置放置 l&w 和w&h组合
				block[j + 3][0] = block[j][0];
				block[j + 3][1] = block[j][1];
				block[j + 3][2] = block[j][2];
			}
			block[j + 3][0] = w;
			block[j + 3][1] = h;
			block[j + 3][2] = l;
			for (; j >= 0 && block[j][0] > l; j--) {
				block[j + 2][0] = block[j][0];
				block[j + 2][1] = block[j][1];
				block[j + 2][2] = block[j][2];
			}
			block[j + 2][0] = l;
			block[j + 2][1] = h;
			block[j + 2][2] = w;
			block[j + 1][0] = l;
			block[j + 1][1] = w;
			block[j + 1][2] = h;	
		}
		for (int i = 0; i < n; i++) {
			dp[i] = block[i][2];
			for (int j = 0; j < i; j++) {
				if (block[i][1] > block[j][1] && block[i][0] > block[j][0]) {
					dp[i] = MAX(dp[i], dp[j] + block[i][2]);
				}
			}
			if (dp[i] > max)max = dp[i];
		}
		printf("Case %d: maximum height = %d\n",t++, max);
	}
	return 0;
}