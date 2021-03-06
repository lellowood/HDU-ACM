﻿#include "stdafx.h"

/*
1066 求 N! 的最后一位非零位
在N比较大的时候，N!会非常大


f(n) = n! = 1*2*3...*n
	 = (1*3*7*9*11...) * (2*4*6*8*12...) * (5*10*15*20...)						//将5和5的倍数提出来，并分离奇数和偶数
	 = 1*3*7*9*11...*(1*2*3*4*6)*2^(2n/5) * (1*2*3*4...) * 5^(n/5)				//将偶数的2提出来，将5从5的倍数中提出来
	 = 1*1*3*2*3*7*4*9*1*6*3*7*8*7*9*9... * (1*2*3*4...) * 2^(2n/5) * 5^(n/5)	//将提出2的偶数部分和奇数部分合并
	 = 1*1*3*2*3*7*4*9*1*6*3*7*8*7*9*9... * f(n/5) * 2^(n/5) * 10^(n/5)			//将一半的2和全部的5合并

	 将		1 2 3 4	  6 7 8 9   11 12 13 14   16 17 18 19  21 22 23 24  26累×的结果找规律
	乘数	1 1 3 2   3 7 4 9   1  6  3  7    8  7  9  9   1  1  3	2	3
	乘积    1 1 3 6	  8 6 4 6	6  6  8  6    8  6  4  6   6  6  8	6	8
				  |													|	这两个位置出现循环
				  ---------------------------------------------------					
	设循环数组 int t[] = { 6,6,6,8,6,8,6,4,6,6,6,8,6,8,6,4 }; 用以计算第一项的最后一位
	这里有一个问题，n从4开始循环，所以n<4的值需要手动添加
			

	 乘数	2 2 2 2		2  2  2  2 
	 乘积	2 4 8 6		2
			|			|	这两个位置出现循环
			-------------
	设循环数组 int s[] = { 6,2,4,8 }; 用以计算第三项的最后一位

求取最后非零位
而第一项(1*1*3*2*3*7*4*9*1*6*3*7*8*7*9*9...)和第三项(2^(n/5))并不会产生0位
设
	f[n]为n的阶乘的最后一位非0位
	t[t1]为上式第一项之积的最后一位（第一项最后一位一定不为0），t1为第一项乘数个数
	s[s1]为上式第三项2^(n/5)的最后一位，s1为乘数个数
则
f[n] = (t[t1] * s[s1] * f[n/5])%10

关键问题是t1和s1的计算，有一个映射关系
t1				s1
1——1			1——0
2——2			2——1
3——3			3——1
4——4			4——2
5——4			5——1	//这里需要消耗一个2
6——5			6——2
7——6			7——2
8——7			8——3
9——8			9——3
10——8			10——2	//这里需要消耗一个2
//n为int型
t1 = (4 * n + 4) / 5 
s1 = (n / 5 + q[n%10])
其中
int q[] = { 0,0,1,1,2,0,1,1,2,2 };
为什么q和上面最后一列不一样，因为有一个1已经在n/5中了

如果n是有限范围的，那么通过递推公式就能得到所有的答案
但如果n是通过字符数组输入的，那么我们就要每次递归计算f[n/5]
为了计算方便f[n/5]变为f[2n/10]，这样就从最后一位开始每次计算完丢掉一位

*/

#include <stdio.h>  
#include <string>
#define MAX(a,b) (a>b)?a:b
#define N 1000
#define NN N+5
#define NNN 10000

int t[] = { 6,6,6,8,6,8,6,4,6,6,6,8,6,8,6,4 };
int q[] = { 0,0,1,1,2,0,1,1,2,2 };

int f[NN] = { 1,1,2,6,4,2,7};
int s[] = { 6,2,4,8 };
int num[NNN];


//计算1000以内的值
void table() {
	for (int n = 6; n < N; n++) {
		int snf = f[(int)(n / 5)];
		int sns = s[((int)(n / 5 + q[n % 10])) % 4];
		int snt = t[((4 * n + 4) / 5) % 16];
		f[n] = (snt*snf*sns) % 10;
	}
};

int table(char* nums) {
	int len = strlen(nums)-1;
	for (int i = len; i >= 0; i--) {
		num[len - i] = (nums[i] - '0');
	}
	int value = 1;
	for (int i = 0; i <= len - 3; i++) {
		int bit = 0;
		for (int j = i; j <= len; j++) {
			num[j] = num[j] * 2 + bit;
			bit = num[j] / 10;
			num[j] %= 10;
		}
		if (bit)
			num[++len] = bit;
		int n2 = ((num[i + 3] * 10 + num[i + 2]) * 10 + num[i + 1]) * 10 + num[i];//因为里面有一个除以10操作所以加一位///三位数，因为1000能被8和4整除
		int snt = t[((int)((2 * n2 + 4) / 5)) % 16];
		int sns = s[((int)(n2 / 10 + q[(n2 % 20) / 2])) % 4];
		value *= snt*sns;
		value %= 10;
	}
	int n = num[len];
	int up = MAX(0, len - 2);
	for (int i = len - 1; i >= up; i--) {
		n *= 10;
		n += num[i];
	}
	value *= f[n];
	return value%10;
};



int main()
{
	int n;
	char nums[NNN];
	table();
	freopen("data.txt", "r", stdin);
	while (scanf("%s", nums)!=EOF && N){
		printf("%d\n", table(nums));
	}
	return 0;
}