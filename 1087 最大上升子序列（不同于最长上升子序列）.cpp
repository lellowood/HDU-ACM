#include "stdafx.h"

// ConsoleApplication1.cpp: �������̨Ӧ�ó������ڵ㡣
//

/*
1081 ����������� �ı���
������������ֵ��������󳤶� ��ͳO(n)�㷨��������

������̰���㷨O(n^2) �����ǳ�ʱ 

����ʵ���и��õģ���ǰ��Ƚϵ�ʱ������ֻ�Ƚϱ�����ֵС�����ֵ���������ֵ��ʱ����ö��ֲ��ң�

*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>

#define N 1005

int dp [N];
int num[N];

int main() {
	int n, t;
	freopen("data.txt", "r", stdin);
	while (scanf("%d", &n) != EOF && n) {
		t = -32143124;
		for (int i = 0; i < n; i++) {
			scanf("%d", &num[i]);
			dp[i] = num[i];
			for (int j = 0; j < i; j++)
				if (num[j]<num[i] && dp[j] + num[i] > dp[i])dp[i] = dp[j] + num[i];
			if (dp[i] > t)t = dp[i];
		}
		printf("%d\n",t);
	}
	return 0;
}