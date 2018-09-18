#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1099 题目简单 题意复杂 解题简单
题意：有1-n张彩票，问需要买多少张才能得到一套1-n的彩票。求期望值
公式
E = n(1/1+1/2+1/3+...1/n)

*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <stack>

#define MIN(x,y) (x<y?x:y)
#define N 23

unsigned long long caltable[N] = { 0,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,121645100408832000,2432902008176640000 };
int main() {
	int n;
	int left, up, down;
	unsigned long long sum;
	unsigned long long cal;
	freopen("data.txt", "r",stdin);
	while (scanf("%d",&n)!=EOF) {
		cal = caltable[MIN(n, 19)];
		sum = 0;
		for (int i = 1; i <= n; i++)
			sum += cal / i;
		sum *= n;
		for (int i = 2; i <= n; i++) {
			if (cal%i == 0 && sum%i == 0) {
				cal /= i;
				sum /= i;
				i--;
			}
		}
		left = sum / cal;
		up = sum % cal;
		down = cal;
		if (up == 0)
			printf("%d\n", left);
		else {
			int temp = left;
			while (temp) { 
				temp /= 10;
				printf(" ");
			}
			printf(" %d\n", up);
			printf("%d ", left);
			temp = cal;
			while (temp) {
				temp /= 10;
				printf("-");
			}
			printf("\n");
			temp = left;
			while (temp) {
				temp /= 10;
				printf(" ");
			}
			printf(" %d\n", down);
		}
		n++;
	}
	return 0;
}