#include "stdafx.h"

// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

/*
1075 字符串映射转换

建立字典树

*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define N 100000

char start[N];
char end[N];
char str1[N];
char str2[N];

#define uint unsigned int
#define SIZE 26	//字典字母数量
uint char2uint(char ch) {
	if (ch >= 'a'&&ch <= 'z')return ch - 'a';
	return SIZE;
};
struct trienode {
	uint num;	//经过该节点的单词数量
	bool isleaf;
	char  ch;
	char * transtr;
	trienode * sons[SIZE];
};

trienode * trieroot;

void insert(const char * str, const char * transtr) {
	if (str == NULL)return;
	trienode *node = trieroot;
	int len = strlen(str);
	for (int i = 0; i < len; ++i) {
		int pos = char2uint(str[i]);
		if (pos < SIZE){
			(*node).isleaf = 0;
			if ((*node).sons[pos] == NULL) {
				(*node).sons[pos] = (trienode *)malloc(sizeof(trienode));
				memset((*node).sons[pos], 0, sizeof(trienode));
				(*(*node).sons[pos]).ch = str[i];
				(*(*node).sons[pos]).isleaf = 1;
			}
			(*(*node).sons[pos]).num++;
			node = (*node).sons[pos];
		}
	}
	(*node).transtr = (char *)malloc(sizeof(char)*strlen(transtr));
	strcpy((*node).transtr, transtr);
};

const trienode * search(const char * str) {
	if (str == NULL)return NULL;
	trienode *node = trieroot;
	int len = strlen(str);
	for (int i = 0; i < len&&node != NULL; ++i) {
		int pos = char2uint(str[i]);
		if (pos < SIZE) {
			node = (*node).sons[pos];
		}
	}
	return node;
};

int main()
{
	int t, code;
	int i, j;
	int len;
	char ch;
	trieroot = (trienode *)malloc(sizeof(trienode));
	memset(trieroot, 0, sizeof(trienode));
	freopen("data.txt", "r", stdin);
	scanf("%s", start);
	scanf("%s", str1);
	while (strcmp("END", str1)) {
		scanf("%s", str2);
		insert(str2, str1);
		scanf("%s", str1);
	}
	scanf("%s", start);
	getchar();
	fgets(str1, N, stdin);
	while (strcmp("END", str1)&& strcmp("END\n", str1)) {
		len = strlen(str1);
		int cur = 0;
		while (cur < len) {
			//while (cur < len && (str1[cur] == ' ' || str1[cur] == '\t' || str1[cur] == '\n'))printf("%c", str1[cur++]);
			while (cur < len && (str1[cur] < 'a' || str1[cur] > 'z'))printf("%c", str1[cur++]);
			int sur = cur;
			//while (cur < len && str1[sur] != ' ' && str1[sur] != '\t' && str1[sur] != '\n')str2[sur - cur] = str1[sur++];
			while (cur < len && str1[sur] >= 'a' && str1[sur] <= 'z')str2[sur - cur] = str1[sur++];
			str2[sur - cur] = '\0';
			const trienode * node = search(str2);
			if (node != NULL && (*node).transtr != NULL)
				printf("%s", (*node).transtr);
			else
				printf("%s", str2);
			cur = sur;
		}
		fgets(str1, N, stdin);
	}
	return 0;
}