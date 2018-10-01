#include "stdafx.h"

// ConsoleApplication1.cpp: �������̨Ӧ�ó������ڵ㡣
//

/*
1104 �ʼ����
1������û�п�ֱ��д��nmk˳�����
2��ȡ�����%����ĿҪ��Ĳ�һ������һ��������ȡ�࣬һ������ֵȡ��
3��ֵ�����ǽ���Ĺؼ�
4��"%"��printf�����Ҫת��

����˼·������Ĺؼ���Ū����ѵ����䣬��[0,k-1]�� ��Ϊ����Ƕ�k��ȡ����бȽϣ�����%�������Ĳ��������xn+ym����%k���������һ����
������Ҫ��%���ж�������ۣ�
������Ѵ�p1 p2 .... pn
%�״γ����� pi������ô1 - i-1�����õ��Ľ�����Ա�ʾΪ (m^x)*n + y*m
��x>0 ȡ�������Ϊ0
��x=0 ȡ�������Ϊn%m
��������%������ǰֵֻ������0����n%m ����%������1�Σ���ֻ�������ʼ����*%

�����3���� n��n%m��0
n����ʼ����
n%m�ǵ�һ����%��������Ϊ+ -����֮�󣬶�mȡ����һ���̶�ֵ�����������Ѵ��Ǵ�n%m��ʼ�� ��ô�ʼ������ n%m
0��ʹ��*֮��ʹ��%���������������ٹ̶����Ϊ0�����������Ѵ𰸴�0��ʼ��������0 ����ʱ*%

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
		//printf("����");
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
						if (count == 0) {	//n%m���
							temp = (n % m + m) % m;
							temp %= k;
							if (!sign[temp]) {
								sign[temp] = 0x400000 | pos;
								list.push(temp);
							}
						}
						else {			//0���
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