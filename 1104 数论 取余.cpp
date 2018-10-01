#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1104 最开始错误
1、输入没有看直接写！nmk顺序错误
2、取余操作%和题目要求的不一样——一个是数论取余，一个是数值取余
3、值域！这是解题的关键
4、"%"用printf输出需要转义

解题思路：解题的关键是弄清广搜的区间，是[0,k-1]， 因为最后都是对k的取余进行比较，除了%外其他的操作结果是xn+ym，对%k操作结果是一样的
这里需要对%进行额外的讨论：
假设最佳答案p1 p2 .... pn
%首次出现在 pi处，那么1 - i-1操作得到的结果可以表示为 (m^x)*n + y*m
若x>0 取余操作后为0
若x=0 取余操作后为n%m
即，出现%操作后当前值只可能是0或者n%m 所以%最多出现1次，且只出现在最开始或者*%

起点有3个： n、n%m、0
n是起始输入
n%m是第一个用%操作，因为+ -操作之后，对m取余是一个固定值，所以如果最佳答案是从n%m开始的 那么最开始起点就是 n%m
0是使用*之后使用%操作，且两个连操固定结果为0，所以如果最佳答案从0开始，起点就是0 操作时*%

*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
#define MIN(x,y) (x<y?x:y)
#define MAX(x,y) (x>y?x:y)
#define SUB(x,y) (x>y?(x-y):(y-x))
#define N  1000


int sign[N];

queue<int> list;

void output(int pos, int num) {
	if (sign[pos] == 0x3FFFFF) {
		printf("%d\n", num);
		return;
	}
	output(sign[pos] & 0x0FFFFF, num + 1);
	int sn = sign[pos] & 0xF00000;
	switch (sn)
	{
	case 0x100000:
		printf("+");
		break;
	case 0x200000:
		printf("-");
		break;
	case 0x300000:
		printf("*");
		break;
	case 0x400000:
		printf("%%");
		break;
	default:
		//printf("错误");
		break;
	}
	return;
};

int main() {
	int r;
	int pos, temp;
	int count;
	bool flag;
	int n, m, k;
	freopen("data.txt", "r", stdin);
	while (scanf("%d %d %d\n", &n, &k, &m) != EOF && (n || m || k)) {
		if (!(n & 1) && !(m & 1) && !(k & 1))printf("%d\n", 0);
		else {
			memset(sign, 0, sizeof(sign));
			temp = ((n) % k + k) % k;
			r = (temp + 1 + k) % k;
			while (!list.empty())list.pop();
			list.push(temp);
			sign[temp] = 0x3FFFFF;
			count = 0;
			flag = true;
			while (flag && !list.empty()) {
				pos = list.front();
				list.pop();
				if (pos == r) flag = false;
				else {
					temp = (pos + m) % k;
					if (!sign[temp]) {
						sign[temp] = 0x100000 | pos;
						list.push(temp);
					}
					temp = ((pos - m) % k + k) % k;
					if (!sign[temp]) {
						sign[temp] = 0x200000 | pos;
						list.push(temp);
					}
					temp = (pos*m) % k;
					if (!sign[temp]) {
						sign[temp] = 0x300000 | pos;
						list.push(temp);
					}
					if (count < 2 && (sign[pos] & 0xF00000) == 0x300000) {
						if (count == 0) {	//n%m入口
							temp = (n % m + m) % m;
							temp %= k;
							if (!sign[temp]) {
								sign[temp] = 0x400000 | pos;
								list.push(temp);
							}
						}
						else {			//0入口
							temp = 0;
							if (!sign[temp]) {
								sign[temp] = 0x400000 | pos;
								list.push(temp);
							}
						}
						count++;
					}
				}
			}
			if (flag)printf("%d", 0);
			else output(pos, 0);
			printf("\n");
		}
	}
	return 0;
}