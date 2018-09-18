#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1082 虽然是矩阵乘法的背景 但是是计算括号表达式顺序 用堆栈计算

*/



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <stack>

#define N 27

struct matrix {
	int left;
	int right;
} matrices[N];

bool flag;
int t;

void stackpush(std::stack<matrix> & cs, matrix & mt) {
	std::stack<matrix> temp;
	switch (mt.left)
	{
	case -1:
		cs.push(mt);
		break;
	case -2:
		while (!cs.empty() && cs.top().left > 0) {
			temp.push(cs.top());
			cs.pop();
		}
		if (!cs.empty() && cs.top().left == -1)
			cs.pop();
		while (!temp.empty()) {
			stackpush(cs,temp.top());
			temp.pop();
		}
		break;
	default:
		if (cs.empty() || (cs.top().left<0)) cs.push(mt);
		else {
			if (cs.top().right != mt.left)
				flag = false;
			else {
				t += cs.top().right*cs.top().left*mt.right;
				cs.top().right = mt.right;
			}
		}
		break;
	}
};

int main() {
	int n;
	char ch;
	freopen("data.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		getchar();
		scanf("%c", &ch);
		scanf("%d %d", &matrices[ch - 'A'].left, &matrices[ch - 'A'].right);
	}
	getchar();
	while (scanf("%c", &ch) != EOF) {
		t = 0;
		flag = true;
		std::stack<matrix> cs;
		while (ch != '\n'&&ch!=-1) {
			matrix mt;
			switch (ch)
			{
			case '(':
				mt.left = -1;
				break;
			case ')':
				mt.left = -2;
				break;
			default:
				mt = matrices[ch - 'A'];
				break;
			}
			stackpush(cs, mt);
			ch = getchar();
		}
		while (!cs.empty()) {
			if (cs.top().left < 0)flag = false;
			cs.pop();
		}
		if (flag)
			printf("%d\n", t);
		else
			printf("error\n");
	}
	return 0;
}