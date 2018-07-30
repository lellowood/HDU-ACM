#include "stdafx.h"

/*
1033 模拟过程
题目看起来很复杂，到现在我也没弄懂什么意思
看了一些翻译，大致知道要用单线程模拟直线移动过程就行
*/

#include "stdio.h"
#include "string.h"
#define _Inf -0x7fffffff
#define MAX(a,b) a>b?a:b


#define N 125
#define X 300
#define Y 420

int x, y;

char dir[N];
int oir[4][2] = { 10, 0, 0, -10, -10, 0, 0, 10 };

int main() {
	int temp = 0;
	freopen("data.txt", "r", stdin);// 
	while (scanf("%s", dir) != EOF) {
		x = X, y = Y;
		printf("300 420 moveto\n");
		temp = 0;
		for (int i = 0; i < strlen(dir)+1; i++) {
			x += oir[temp][0];
			y += oir[temp][1];
			printf("%d %d lineto\n", x, y); 
			if (dir[i] == 'A')
				temp++;
			else temp--;
			temp += 4;
			temp %= 4;
		}
		printf("stroke\nshowpage\n");
	}
	return 0;
}