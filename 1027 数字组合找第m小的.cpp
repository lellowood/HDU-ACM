#include "stdafx.h"

/*
1027 1-n个数字组合第m小的数
最小数是：1 2 3...n
要求输出小的数，从后往前考虑
后p个数能组合的数是p*(p-1)*(p-2)*...*2*1
所以建立一个缓存表存储组合数
*/

#include "stdio.h"
#include "string.h"
#define _Inf -0x7fffffff
#define MAX(a,b) a>b?a:b

#define N 1005
#define M 10005

unsigned table[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800 };
bool	 flag [N];
//unsigned num  [N];
int n, m;


int main() {
	int pos,i,j;
	freopen("data.txt", "r", stdin);// 
	while (scanf("%d%d", &n, &m) != EOF) {	
		memset(flag, 1, sizeof(flag));
		for (int pos = n; pos > 1; pos--) {
			if (pos > 10) {
				i = 0;
			}
			else {
				i = (m - 1) / table[pos - 1];//
				m = (m - 1) % table[pos - 1] + 1;
			}
			for (j = 1; j <= n&&i >= 0; j++)if (flag[j])  i--;
			flag[--j] = 0;
			printf("%d ", j);
		}
		for (i = 0,j = 1; j <= n&&i >= 0; j++)if (flag[j])  i--;
		printf("%d", --j);
		printf("\n");
	}
	return 0;
}